{
  "targets": [
    {
      "target_name": "compressor",
      "type": "static_library",
      "standlone_static_library": 1,
      "defines": [
      ],

      "include_dirs": [
        "zstd/lib",
        "zstd/lib/common",
        "zstd/lib/compress"
      ],

      "sources" : [
        '<!@(ls -1 zstd/lib/common/*.c)',
        '<!@(ls -1 zstd/lib/compress/*.c)'
      ],

      "conditions": [
        [
          "OS == 'mac'", {
            "xcode_settings": {
              "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
              "MACOSX_DEPLOYMENT_TARGET": "10.11"
            }
          }
        ],
        [
          'OS=="win"', {
            "sources=" : [
              '<!@(FOR %i IN (zstd/lib/common/*.c)      DO @echo zstd/lib/common/%i)',
              '<!@(FOR %i IN (zstd/lib/compress/*.c)    DO @echo zstd/lib/compress/%i)'
            ]
          }
        ]
      ]
    },
    {
      "target_name": "decompressor",
      "type": "static_library",
      "standlone_static_library": 1,
      "defines": [
      ],

      "include_dirs": [
        "zstd/lib",
        "zstd/lib/common",
        "zstd/lib/decompress"
      ],

      "sources" : [
        '<!@(ls -1 zstd/lib/common/*.c)',
        '<!@(ls -1 zstd/lib/decompress/*.c)'
      ],

      "conditions": [
        [
          "OS == 'mac'", {
            "xcode_settings": {
              "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
              "MACOSX_DEPLOYMENT_TARGET": "10.11"
            }
          }
        ],
        [
          'OS=="win"', {
            "sources=" : [
              '<!@(FOR %i IN (zstd/lib/common/*.c)      DO @echo zstd/lib/common/%i)',
              '<!@(FOR %i IN (zstd/lib/decompress/*.c)  DO @echo zstd/lib/decompress/%i)'
            ]
          }
        ]
      ]
    }
  ]
}
