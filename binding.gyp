{
  "targets": [
    {
      "target_name": "node_zstd",
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "deps/zstd/lib"
      ],
      "dependencies": [
        "<(module_root_dir)/deps/zstd.gyp:zstd"
      ],
      "sources": [

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
