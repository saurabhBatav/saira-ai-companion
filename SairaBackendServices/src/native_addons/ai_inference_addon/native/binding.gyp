{
  "targets": [
    {
      "target_name": "ai_inference_addon",
      "sources": [
        "../src/ai_inference_addon.cpp"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      "libraries": [],
      "defines": [
        "NAPI_DISABLE_CPP_EXCEPTIONS"
      ]
    }
  ]
}