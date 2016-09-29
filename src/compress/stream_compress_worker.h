#ifndef STREAM_COMPRESS_WORKER_H
#define STREAM_COMPRESS_WORKER_H

#include <nan.h>
#include "stream_compress.h"

namespace ZSTD_NODE {

  using Nan::AsyncWorker;
  using Nan::Callback;

  class StreamCompressWorker : public AsyncWorker {
  public:
    StreamCompressWorker(Callback *callback, StreamCompress *sc, bool isLast);
    ~StreamCompressWorker();

    void Execute();
    void HandleOKCallback();
    void HandleErrorCallback();

  private:
    void pushToPendingOutput();

    ZSTD_outBuffer zOutBuf;
    ZSTD_inBuffer zInBuf;
    StreamCompress *sc;
    bool isLast;
    size_t ret;
  };

}

#endif
