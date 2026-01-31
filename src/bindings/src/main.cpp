#include <napi.h>
#include "iostream"
#include "binder/binder.h"

Napi::Value Binder(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if(!info[0].IsObject()) {
        Napi::TypeError::New(env, "Expected AST object").ThrowAsJavaScriptException();
        return env.Null();
    }

    const Napi::Function constructor = Binder::Init(env);
    return constructor.New({ info[0] });
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("binder", Napi::Function::New(env, Binder));
    return exports;
}

NODE_API_MODULE(pastaddon, Init)
