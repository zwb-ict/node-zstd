#ifndef STREAM_COMPRESS_WORKER_H
#define STREAM_COMPRESS_WORKER_H

#include <nan.h>
#include "stream_compressor.h"

namespace ZSTD_NODE {

  using Nan::AsyncWorker;
  using Nan::Callback;

  class StreamCompressWorker : public AsyncWorker {
  public:
    StreamCompressWorker(Callback *callback, StreamCompressor *sc, bool isLast);
    ~StreamCompressWorker();

    void Execute();
    void HandleOKCallback();
    void HandleErrorCallback();

  private:
    void pushToPendingOutput();

    StreamCompressor *sc;
    ZSTD_outBuffer zOutBuf;
    ZSTD_inBuffer zInBuf;
    bool isLast;
    size_t ret;
  };

}

#endif
