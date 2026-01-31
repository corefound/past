//
// Created by Brayhan De Aza on 1/30/26.
//

#pragma once
#include <napi.h>
#include "nodes/programs.h"

class Emitter : public Napi::ObjectWrap<Emitter> {
public:
  static Napi::Object Init(const Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "Emitter", {
       InstanceMethod("toExecutableFile",  &Emitter::ToExecutableFile),
       InstanceMethod("print",  &Emitter::Print)
    });

    exports.Set("Emitter", func);
    return exports;
  }

  explicit Emitter(const Napi::CallbackInfo& info);

private:
  ProgramNode ast;
  std::string ir;

  Napi::Value ToExecutableFile(const Napi::CallbackInfo& info);

  Napi::Value Print(const Napi::CallbackInfo& info) {
    return Napi::String::New(info.Env(), ast.name);
  };
};

