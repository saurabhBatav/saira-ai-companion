{
  "targets": [
    {
      "target_name": "audio_io_addon",
      "cflags": ["-std=c++17", "-ObjC++"],
      "cflags_cc": ["-std=c++17", "-ObjC++"],
      "sources": [
        "src/audio_io.cpp"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
        "<!(node -p \"require('node-addon-api').include_abs\")"
      ],
      "dependencies": [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ],
      "cflags": [
        "-std=c++17",
        "-fexceptions"
      ],
      "cflags_cc": [
        "-std=c++17",
        "-fexceptions"
      ],
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "conditions": [
        ['OS=="mac"', {
          'defines': [
            'NAPI_DISABLE_CPP_EXCEPTIONS',
            'NAPI_CPP_EXCEPTIONS'
          ],
          'xcode_settings': {
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
            'CLANG_CXX_LIBRARY': 'libc++',
            'MACOSX_DEPLOYMENT_TARGET': '10.14',
            'OTHER_CFLAGS': [
              '-ObjC++'
            ]
          },
          'link_settings': {
            'libraries': [
              '-framework CoreAudio',
              '-framework AudioToolbox',
              '-framework CoreFoundation',
              '-framework Foundation',
              '-framework AVFoundation',
              '-framework CoreServices',
              '-framework CoreMedia',
              '-framework AudioUnit'
            ]
          }
        }]
      ]
    }
  ]
}