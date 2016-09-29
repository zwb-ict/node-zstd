{
  "targets": [
    {
      "target_name": "compressor",
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "deps/zstd/lib",
        "src/common"
      ],
      "dependencies": [
        "<(module_root_dir)/deps/zstd.gyp:compressor"
      ],
      "sources": [
        "src/common/stream_coder.cc",
        "src/common/allocator.cc",
        "src/compress/compressor_index.cc",
        "src/compress/stream_compressor.cc",
        "src/compress/stream_compress_worker.cc"
      ],
      "conditions": [
        [
          "OS == 'mac'", {
            "xcode_settings": {
              "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
              "MACOSX_DEPLOYMENT_TARGET": "10.12"
            }
          }
        ],
        [
          "OS=='linux'", {
            "cflags_cc": [ "-std=c++11" ]
          }
        ]
      ]
    },
    {
      "target_name": "decompressor",
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "deps/zstd/lib",
        "src/common"
      ],
      "dependencies": [
        "<(module_root_dir)/deps/zstd.gyp:decompressor"
      ],
      "sources": [
        "src/common/stream_coder.cc",
        "src/common/allocator.cc",
        "src/decompress/decompressor_index.cc",
        "src/decompress/stream_decompressor.cc",
        "src/decompress/stream_decompress_worker.cc"
      ],
      "conditions": [
        [
          "OS == 'mac'", {
            "xcode_settings": {
              "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
              "MACOSX_DEPLOYMENT_TARGET": "10.12"
            }
          }
        ],
        [
          "OS=='linux'", {
            "cflags_cc": [ "-std=c++11" ]
          }
        ]
      ]
    }
  ]
}
