#ifndef STREAM_ENCODE_H
#define STREAM_ENCODE_H

#include <nan.h>

#define ZSTD_STATIC_LINKING_ONLY
#include "zstd.h"
#include "stream_coder.h"

namespace ZSTD_NODE {

  using Nan::Persistent;

  using v8::Function;
  using v8::Object;
  using v8::Local;

  class StreamCompress : public StreamCoder {
  public:
    friend class StreamCompressWorker;
    static NAN_MODULE_INIT(Init);

  private:
    explicit StreamCompress(Local<Object> userParams);
    ~StreamCompress();

    static NAN_METHOD(New);
    static NAN_METHOD(GetBlockSize);
    static NAN_METHOD(Copy);
    static NAN_METHOD(Compress);

    static inline Persistent<Function>& constructor();

    void *dict;
    ZSTD_CStream *zcs;
    ZSTD_inBuffer input;
    ZSTD_outBuffer output;
  };

}

#endif
