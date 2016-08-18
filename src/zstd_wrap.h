#ifndef ZSTD_WRAP_H
#include ZSTD_WRAP_H

#include <nan.h>

namespace {

  class ZSTDWrap : public Nan::ObjectWrap {
  public:
    static NAN_METHOD(Compress);
    static NAN_METHOD(Decompress);
  }
}

#endif
