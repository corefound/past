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
    Binder(const Napi::CallbackInfo& info);
    static Napi::Function Init(Napi::Env env);

  private:
    ProgramNode ast;
    std::string output;
    std::string target;
    std::string optimize;

    Napi::Value Print(const Napi::CallbackInfo& info);
};