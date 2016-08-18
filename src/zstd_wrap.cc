#include <nan.h>
#include <zstd.h>

static NAN_METHOD(Compress) {

  if (info.Length() < 1 || !node::Buffer::HasInstance(info[0])) {
    return Nan::ThrowError("First argument should be a buffer");
  }

  v8::Local<v8::Object> buf = info[0]->ToObject();
  char *src = node::Buffer::Data(buf);
  size_t srcSize = node::Buffer::Length(buf);

  size_t dstCapacity = ZSTD_compressBound(srcSize);
  char *dst = (char*)malloc(dstCapacity);
  if (NULL == dst) {
    return Nan::ThrowError("Too large, Out of memory!");
  }

  int compressionLevel = 1;
  if (info.Length() == 2) {
    compressionLevel = info[1]->IsUndefined() ? 0 : info[1]->NumberValue();
  }

  size_t cSize = ZSTD_compress(dst, dstCapacity, src, srcSize, compressionLevel);
  if (ZSTD_isError(cSize)) {
    return Nan::ThrowError("Compress failed!");
  }

  Nan::MaybeLocal<v8::Object> dstBuf = Nan::NewBuffer(dst, cSize);
  free(dst);

  return info.GetReturnValue().Set(dstBuf.ToLocalChecked());
}

static NAN_METHOD(Decompress) {

  if (info.Length() < 1 || !node::Buffer::HasInstance(info[0])) {
    return Nan::ThrowError("First argument should be a buffer");
  }

  v8::Local<v8::Object> buf = info[0]->ToObject();
  char *src = node::Buffer::Data(buf);
  size_t srcSize = node::Buffer::Length(buf);

  size_t dstCapacity = ZSTD_getDecompressedSize(src, srcSize);
  if (0 == dstCapacity) {
    return Nan::ThrowError("Compressed size unknown");
  }

  char *dst = (char*)malloc(dstCapacity);
  if (NULL == dst) {
    return Nan::ThrowError("Too large, Out of memory!");
  }

  size_t dSize = ZSTD_decompress(dst, dstCapacity, src, srcSize);
  if (ZSTD_isError(dSize))  {
    return Nan::ThrowError("Decompress failed!");
  }

  Nan::MaybeLocal<v8::Object> dstBuf = Nan::NewBuffer(dst, dSize);
  free(dst);

  return info.GetReturnValue().Set(dstBuf.ToLocalChecked());
}

NAN_MODULE_INIT(Init) {
  NAN_EXPORT(target, Compress);
  NAN_EXPORT(target, Decompress);
}

NODE_MODULE(node_zstd, Init)
