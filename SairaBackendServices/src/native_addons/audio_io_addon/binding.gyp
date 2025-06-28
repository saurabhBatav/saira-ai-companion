{
  "targets": [
    {
      "target_name": "audio_io_addon",
      "cflags": ["-std=c++17"],
      "cflags_cc": ["-std=c++17"],
      "sources": [
        "src/audio_io.cpp"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      "dependencies": [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ],
      "defines": [
        "NAPI_DISABLE_CPP_EXCEPTIONS"
      ]
    }
  ]
}