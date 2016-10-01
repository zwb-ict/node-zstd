#ifndef STREAM_DECOMPRESSOR_H
#define STREAM_DECOMPRESSOR_H

#include <nan.h>

#define ZSTD_STATIC_LINKING_ONLY
#include "zstd.h"
#include "stream_coder.h"

namespace ZSTD_NODE {

  using Nan::Persistent;

  using v8::Function;
  using v8::Object;
  using v8::Local;

  class StreamDecompressor : public StreamCoder {
  public:
    friend class StreamDecompressWorker;
    static NAN_MODULE_INIT(Init);

  private:
    explicit StreamDecompressor(Local<Object> userParams);
    ~StreamDecompressor();

    static NAN_METHOD(New);
    static NAN_METHOD(GetBlockSize);
    static NAN_METHOD(Copy);
    static NAN_METHOD(Decompress);

    static inline Persistent<Function>& constructor();

    ZSTD_DStream *zds;
    size_t inputSize;
    size_t pos;
    void *input;
    void *dict;
  };

}

#endif
