#include <nan.h>
#include "stream_decompressor.h"

namespace ZSTD_NODE {

  NAN_MODULE_INIT(Init) {
    StreamDecompressor::Init(target);
  }

  NODE_MODULE(decompressor, Init)

}
