#ifndef STREAM_CODER_H
#define STREAM_CODER_H

#include <nan.h>
#include "allocator.h"

namespace ZSTD_NODE {

  using Nan::ObjectWrap;

  using std::vector;

  using v8::Array;
  using v8::Local;

  class StreamCoder : public ObjectWrap {
  public:
    Allocator alloc;

    vector<char*> pending_output;
    Local<Array> PendingChunksAsArray();

  protected:
    explicit StreamCoder();
    ~StreamCoder();
  };

}

#endif
