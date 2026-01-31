//
// Created by Brayhan De Aza on 1/30/26.
//

#pragma once
#include <napi.h>
#include "nodes/programs.h"
#include <llvm/IRReader/IRReader.h>
#include "helpers/helpers.h"
#include "iostream"
#include "emitter/emitter.h"


class Binder : public Napi::ObjectWrap<Binder> {
  public:
    static Napi::Function Init(Napi::Env env) {
        return DefineClass(env, "Binder", {
            InstanceMethod("print", &Binder::Print),
            // add more methods here later
        });
    }

    Binder(const Napi::CallbackInfo& info): ObjectWrap(info),
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

  private:
    ProgramNode ast;
    std::string output;
    std::string target;
    std::string optimize;

    Napi::Value Print(const Napi::CallbackInfo& info) {
        return Napi::String::New(info.Env(), ast.name);
    }
};