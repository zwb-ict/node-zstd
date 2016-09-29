#include "stream_compress.h"
#include "stream_compress_worker.h"

namespace ZSTD_NODE {

  using Nan::SetPrototypeMethod;
  using Nan::GetCurrentContext;
  using Nan::AsyncQueueWorker;
  using Nan::GetFunction;
  using Nan::HandleScope;
  using Nan::ObjectWrap;
  using Nan::NewBuffer;
  using Nan::Callback;
  using Nan::Has;
  using Nan::Get;
  using Nan::Set;

  using node::Buffer::Length;
  using node::Buffer::Data;

  using v8::FunctionTemplate;
  using v8::Number;
  using v8::String;
  using v8::Local;
  using v8::Value;

  NAN_MODULE_INIT(StreamCompress::Init) {
    Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("StreamCompress").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    SetPrototypeMethod(tpl, "getBlockSize", GetBlockSize);
    SetPrototypeMethod(tpl, "copy", Copy);
    SetPrototypeMethod(tpl, "compress", Compress);

    constructor().Reset(GetFunction(tpl).ToLocalChecked());
    Set(target, Nan::New("StreamCompress").ToLocalChecked(),
        GetFunction(tpl).ToLocalChecked());
  }

  StreamCompress::StreamCompress(Local<Object> userParams) : dict(NULL), zcs(NULL) {
    HandleScope scope;

    int level = 1;
    size_t dictSize = 0;

    Local<String> key;
    key = Nan::New<String>("level").ToLocalChecked();
    if (Has(userParams, key).FromJust()) {
      level = Get(userParams, key).ToLocalChecked()->Int32Value();
    }
    key = Nan::New<String>("dict").ToLocalChecked();
    if (Has(userParams, key).FromJust()) {
      Local<Object> dictBuf = Get(userParams, key).ToLocalChecked()->ToObject();
      dictSize = Length(dictBuf);
      dict = alloc.Alloc(dictSize);
      memcpy(dict, Data(dictBuf), dictSize);
    }

    ZSTD_customMem zcm = {Allocator::Alloc, Allocator::Free, &alloc};
    zcs = ZSTD_createCStream_advanced(zcm);

    if (dict != NULL && dictSize > 0) {
      ZSTD_initCStream_usingDict(zcs, dict, dictSize, level);
    } else {
      ZSTD_initCStream(zcs, level);
    }
  }

  StreamCompress::~StreamCompress() {
    if (dict != NULL) {
      alloc.Free(dict);
    }
    if (input != NULL) {
      alloc.Free(input);
    }
    ZSTD_freeCStream(zcs);
  }

  NAN_METHOD(StreamCompress::New) {
    if (info.IsConstructCall()) {
      StreamCompress *sc = new StreamCompress(info[0]->ToObject());
      sc->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
    } else {
      const int argc = 1;
      Local<Value> argv[argc] = {info[0]};
      Local<Function> cons = Nan::New(constructor());
      //      info.GetReturnValue().Set(cons->NewInstance(GetCurrentContext(),
      //argc, argv).ToLocalChecked());
      info.GetReturnValue().Set(cons->NewInstance(argc, argv));
    }
  }

  NAN_METHOD(StreamCompress::GetBlockSize) {
    info.GetReturnValue().Set(Nan::New<Number>(ZSTD_CStreamInSize()));
  }

  NAN_METHOD(StreamCompress::Copy) {
    StreamCompress* sc = ObjectWrap::Unwrap<StreamCompress>(info.Holder());
    Local<Object> chunk = info[0]->ToObject();
    int chunkSize = Length(chunk);
    input = alloc.Alloc(chunkSize);
    memcpy(input, Data(chunk), chunkSize);
  }

  NAN_METHOD(StreamCompress::Compress) {
    StreamCompress* sc = ObjectWrap::Unwrap<StreamCompress>(info.Holder());
    bool isLast = info[0]->BooleanValue();
    Callback *callback = new Nan::Callback(info[1].As<Function>());
    StreamCompressWorker *worker = new StreamCompressWorker(callback, sc, isLast);
    if (info[2]->BooleanValue()) {
      AsyncQueueWorker(worker);
    } else {
      worker->Execute();
      worker->WorkComplete();
      worker->Destroy();
    }
  }

  inline Persistent<Function>& StreamCompress::constructor() {
    static Persistent<Function> ctor;
    return ctor;
  }

}
