#ifndef STREAM_COMPRESSOR_H
#define STREAM_COMPRESSOR_H

#include <nan.h>

#define ZSTD_STATIC_LINKING_ONLY
#include "zstd.h"
#include "stream_coder.h"

namespace ZSTD_NODE {

  using Nan::Persistent;

  using v8::Function;
  using v8::Object;
  using v8::Local;

  class StreamCompressor : public StreamCoder {
  public:
    friend class StreamCompressWorker;
    static NAN_MODULE_INIT(Init);

  private:
    explicit StreamCompressor(Local<Object> userParams);
    ~StreamCompressor();

    static NAN_METHOD(New);
    static NAN_METHOD(GetBlockSize);
    static NAN_METHOD(Copy);
    static NAN_METHOD(Compress);

    static inline Persistent<Function>& constructor();

    ZSTD_CStream *zcs;
    size_t inputSize;
    size_t pos;
    void *input;
    void *dict;
  };

}

#endif
