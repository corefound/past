#include <napi.h>
#include <memory>


Napi::String ToExecutableFile(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    return Napi::String::New(env, "Hello from C++ Addon - byteCodeToFile");
}

Napi::Object Init(const Napi::Env env, const Napi::Object exports) {
    exports.Set("toExecutableFile", Napi::Function::New(env, ToExecutableFile));
    return exports;
}

NODE_API_MODULE(pastaddon, Init);
