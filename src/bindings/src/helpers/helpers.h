//
// Created by Brayhan De Aza on 1/30/26.
//

#pragma once

#include <napi.h>
#include <vector>
#include <any>
#include <variant>
#include "nodes/literals.h"

class Helpers {
  public:
    static std::vector<std::any> NapiArrayToAnyVector(const Napi::Array& array) {
        std::vector<std::any> result;
        const uint32_t length = array.Length();
        result.reserve(length);

        for(uint32_t i = 0; i < length; ++i) {
            // For now: keep raw JS objects
            if(Napi::Value value = array.Get(i); value.IsObject()) {
                result.emplace_back(Helpers::getNodeByKind(value.As<Napi::Object>()));
            } else {
                result.emplace_back(std::monostate{});
            }
        }

        return result;
    }

    static std::any getNodeByKind(const Napi::Object node) {
        std::string kind = node.Get("kind").As<Napi::String>().Utf8Value();
        if(kind == "IntegerLiteral" || kind == "FloatLiteral" || kind == "StringLiteral" || kind == "BooleanLiteral" || kind == "NullLiteral" || kind == "UndefinedLiteral" || kind == "BigIntLiteral") {
            return LiteralsNode {
                kind,
                node.Get("value").As<Napi::String>().Utf8Value(),
            };
        }

        return std::monostate{};
    }
};