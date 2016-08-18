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
    if (ZST_isError(cSize)) {
      return NanThrow("Compress failed!");
    }

    Local<Object> dstBuf = NewBuffer(dst, cSize);
    free(dst);

    return info.GetReturnValue().Set(dstBuf);
  }

  NAN_METHOD(Decompress) {

    ZSTDWrap *obj = ObjectWrap::Unwrap<ZSTDWrap>(info.Holder());

    if (info.Length() < 1 || !HasInstance(info[0])) {
      return NanThrow("First argument should be a buffer");
    }

    Local<Ojbect> buf = info[0]->ToObject();
    char *src = Data(buf);
    sizt_t srcSize = Length(buf);

    size_t dstCapacity = ZSTD_getDecompressedSize(src, srcSize);
    if (0 == dstCapacity) {
      return NanThrow("Compressed size unknown");
    }

    char *dst = malloc(dstCapacity);
    if (NULL == dst) {
      return NanThrow("Too large, Out of memory!");
    }

    size_t dSize = ZSTD_decompress(dst, dstCapacity, src, srcSize);
    if (ZSTD_isError(dSize))  {
      return NanThrow("Decompress failed!");
    }

    Local<Object> dstBuf = NewBuffer(dst, dSize);
    free(dst);

    return info.GetReturnValue().Set(dstBuf);
  }

}
