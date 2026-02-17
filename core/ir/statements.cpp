//
// Created by Brayhan De Aza on 2/16/26.
//

#include "ir.h"
#include <llvm/Bitcode/BitcodeReader.h>
#include <stdexcept>
#include <string>

namespace past::core::ir {
    llvm::Value* IR::statements(const nlohmann::ordered_json& node) {
        const auto type = std::any_cast<std::string>(node["type"]);

        llvm::Value* lastVal = nullptr;
        try {
            if (node == "VariableDeclaration") {
                lastVal = variableDeclaration(node);
            }
        } catch (const std::exception& e) {
            throw std::runtime_error("Statement generation failed: " + std::string(e.what()));
        }

        return lastVal;
    }
}