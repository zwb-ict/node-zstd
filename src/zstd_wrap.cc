#include "zstd_wrap.h"
#include <zstd.h>
#include <cstdlib>

namespace {

  using Nan::NewBuffer;
  using Nan::NanThrow;

  using node::Buffer::HasInstance;
  using node::Buffer::Length;
  using node::Buffer::Data;

  using v8::Object;
  using v8::Local;

  NAN_METHOD(Compress) {

    ZSTDWrap *obj = ObjectWrap::Unwrap<ZSTDWrap>(info.Holder());

    if (info.Length() < 1 || !HasInstance(info[0])) {
      return NanThrow("First argument should be a buffer");
    }

    Local<Ojbect> buf = info[0]->ToObject();
    char *src = Data(buf);
    sizt_t srcSize = Length(buf);

    size_t dstCapacity = ZSTD_compressBound(srcSize);
    char *dst = malloc(dstCapacity);
    if (NULL == dst) {
      return NanThrow("Too large, Out of memory!");
    }

    int compressionLevel = 1;
    if (info.Length() == 2) {
      compressionLevel = info[1]->IsUndefined() ? 0 : info[1]->NumberValue();
    }

    size_t cSize = ZSTD_compress(dst, dstCapacity, src, srcSize, compressionLevel);
    Local<Object> dstBuf = NewBuffer(dst, cSize);
    free(dst);

    return info.GetReturnValue().Set(dstBuf);
  }

}
