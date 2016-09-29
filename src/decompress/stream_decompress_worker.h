#ifndef STREAM_DECOMPRESSOR_WORKER_H
#define STREAM_DECOMPRESSOR_WORKER_H

#include <nan.h>
#include "stream_decompressor.h"

namespace ZSTD_NODE {

  using Nan::AsyncWorker;
  using Nan::Callback;

  class StreamDecompressWorker : public AsyncWorker {
  public:
    StreamDecompressWorker(Callback *callback, StreamDecompressor *sd);
    ~StreamDecompressWorker();

    void Execute();
    void HandleOKCallback();
    void HandleErrorCallback();

  private:
    void pushToPendingOutput();

    StreamDecompressor *sd;
    ZSTD_outBuffer zOutBuf;
    ZSTD_inBuffer zInBuf;
    size_t ret;
  };

}

#endif
