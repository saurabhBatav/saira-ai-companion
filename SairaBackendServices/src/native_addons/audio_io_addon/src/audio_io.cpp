#include <napi.h>

Napi::String Hello(const Napi::CallbackInfo& info) {
  return Napi::String::New(info.Env(), "Hello from audio_io_addon!");
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set("hello", Napi::Function::New(env, Hello));
  return exports;
}

NODE_API_MODULE(audio_io_addon, Init)