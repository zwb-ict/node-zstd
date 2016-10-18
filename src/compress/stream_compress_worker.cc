#include "stream_compress_worker.h"

namespace ZSTD_NODE {

  using Nan::HandleScope;
  using Nan::Callback;
  using Nan::Error;

  using v8::String;
  using v8::Local;
  using v8::Value;

  StreamCompressWorker::StreamCompressWorker(Callback *callback, StreamCompressor* sc, bool isLast)
    : AsyncWorker(callback), sc(sc), isLast(isLast) {
    zInBuf = {sc->input, sc->pos, 0};
    size_t dstSize = ZSTD_CStreamOutSize();
    void *dst = sc->alloc.Alloc(dstSize);
    zOutBuf = {dst, dstSize, 0};
  }

  StreamCompressWorker::~StreamCompressWorker() {
    sc->alloc.Free(zOutBuf.dst);
  }

  void StreamCompressWorker::Execute() {
    while (zInBuf.pos < zInBuf.size) {
      zOutBuf.pos = 0;
      ret = ZSTD_compressStream(sc->zcs, &zOutBuf, &zInBuf);
      if (ZSTD_isError(ret)) {
        SetErrorMessage(ZSTD_getErrorName(ret));
        return;
      }
      pushToPendingOutput();
    }

    if (isLast) {
      zOutBuf.pos = 0;
      ret = ZSTD_endStream(sc->zcs, &zOutBuf);
      if (ret != 0) {
        SetErrorMessage("ZSTD compress failed, not fully flushed");
        return;
      }
      pushToPendingOutput();
    }
  }

  void StreamCompressWorker::pushToPendingOutput() {
    char *output = static_cast<char*>(sc->alloc.Alloc(zOutBuf.pos));
    if (output == NULL) {
      SetErrorMessage("ZSTD compress failed, out of memory");
      return;
    }
    memcpy(output, zOutBuf.dst, zOutBuf.pos);
    Allocator::AllocatedBuffer* buf_info = Allocator::GetBufferInfo(output);
    buf_info->available = 0;
    sc->pending_output.push_back(output);
  }

  void StreamCompressWorker::HandleOKCallback() {
    HandleScope scope;

    const int argc = 2;
    Local<Value> argv[argc] = {
      Nan::Null(),
      sc->PendingChunksAsArray()
    };
    callback->Call(argc, argv);

    sc->alloc.ReportMemoryToV8();
  }

  void StreamCompressWorker::HandleErrorCallback() {
    HandleScope scope;

    const int argc = 1;
    Local<Value> argv[argc] = {
      Error(Nan::New<String>(ErrorMessage()).ToLocalChecked())
    };
    callback->Call(argc, argv);

    sc->alloc.ReportMemoryToV8();
  }

}
