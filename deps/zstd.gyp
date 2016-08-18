{
  "targets": [
    {
      "target_name": "zstd",
      "type": "static_library",
      "standlone_static_library": 1,
      "defines": [
      ],

      "include_dirs": [
        "zstd/lib",
        "zstd/lib/common",
        "zstd/lib/compress",
        "zstd/lib/decompress",
        "zstd/lib/dictBuilder"
      ],

      "sources" : [
        '<!@(ls -1 zstd/lib/common/*.c)',
        '<!@(ls -1 zstd/lib/compress/*.c)',
        '<!@(ls -1 zstd/lib/decompress/*.c)',
        '<!@(ls -1 zstd/lib/dictBuilder/*.c)'
      ],

      "conditions": [
        [
          "OS == 'mac'", {
            "xcode_settings": {
              "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
              'MACOSX_DEPLOYMENT_TARGET': '10.11'
            }
          }
        ]
      ]
    }
  ]
}
