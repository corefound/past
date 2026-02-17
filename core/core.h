//
// Created by Brayhan De Aza on 11/27/25.
//

#pragma once

#include <emitter/emitter.h>

namespace core {
    inline void compile(const nlohmann::ordered_json ast) {
        past::core::emitter::Emitter emitter(ast);
    }
}