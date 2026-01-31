//
// Created by Brayhan De Aza on 1/30/26.
//

#pragma once
#include <any>
#include "helpers/helpers.h"

struct ProgramNode {
    std::string name;
    std::vector<std::any> main;
    std::vector<std::any> modules;

    ProgramNode(const Napi::String& _name, const Napi::Array& _main, const Napi::Array& _modules) {
        name =  _name.Utf8Value();
        main = Helpers::NapiArrayToAnyVector(_main);
        modules = Helpers::NapiArrayToAnyVector(_modules);
    }
};