//
// Created by Brayhan De Aza on 1/30/26.
//

#include "binder/binder.h"

Binder::Binder(const Napi::CallbackInfo& info): ObjectWrap(info),
    ast(
        info[0].As<Napi::Object>()
        .Get("ast").As<Napi::Object>()
        .Get("name").As<Napi::String>(),

        info[0].As<Napi::Object>()
        .Get("ast").As<Napi::Object>()
        .Get("main").As<Napi::Array>(),

        info[0].As<Napi::Object>()
        .Get("ast").As<Napi::Object>()
        .Get("modules").As<Napi::Array>()
    ) {

    const auto root = info[0].As<Napi::Object>();
    const auto config = root.Get("config").As<Napi::Object>();

    output   = config.Get("output").As<Napi::String>().Utf8Value();
    target   = config.Get("target").As<Napi::String>().Utf8Value();
    optimize = config.Get("optimize").As<Napi::String>().Utf8Value();

    Emitter emitter(ast);

    std::cout << "AST name: " << ast.name << std::endl;
    std::cout << "Target: " << target << std::endl;
    std::cout << "IR: " << emitter.ir << std::endl;
}

Napi::Function Binder::Init(Napi::Env env) {
    return DefineClass(env, "Binder", {
        InstanceMethod("print", &Binder::Print),
        // add more methods here later
    });
}

Napi::Value Binder::Print(const Napi::CallbackInfo& info) {
    return Napi::String::New(info.Env(), ast.name);
}