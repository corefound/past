//
// Created by Brayhan De Aza on 2/16/26.
//

#include "ir.h"

#include <llvm/Bitcode/BitcodeReader.h>
#include <llvm/Support/MemoryBuffer.h>
#include <stdexcept>
#include <string>
#include "llvm/IR/Verifier.h"


namespace past::core::ir {
    llvm::Value* IR::variableDeclaration(const nlohmann::ordered_json& node) {
        const auto type = std::any_cast<std::string>(node["type"]);
        const auto value = std::any_cast<nlohmann::ordered_json>(node["value"]);

        const llvm::Type* varType = mapDataType(type);

        if (const llvm::Function* currentFn = builder->GetInsertBlock()->getParent(); !currentFn)
            throw std::runtime_error("Must be inside a function to declare variable");

        // Evaluate initializer if present
        llvm::Value* initVal = nullptr;
        if (value.empty()) {
            initVal = expression(node.value);
            if (!initVal)
                throw std::runtime_error("Variable initializer produced null");

            // Type conversion if necessary
            if (initVal->getType() != varType) {
                if (initVal->getType()->isIntegerTy() && varType->isFloatingPointTy()) {
                    initVal = initVal->getType()->getIntegerBitWidth() == 1 ? builder->CreateUIToFP(initVal, varType, "init_bool_to_fp") : builder->CreateSIToFP(initVal, varType, "init_int_to_fp");
                } else if (initVal->getType()->isFloatingPointTy() && varType->isIntegerTy()) {
                    initVal = builder->CreateFPToSI(initVal, varType, "init_fp_to_int");
                } else if (initVal->getType()->isIntegerTy() && varType->isIntegerTy()) {
                    const auto* initType = llvm::cast<llvm::IntegerType>(initVal->getType());
                    const auto* targetType = llvm::cast<llvm::IntegerType>(varType);

                    if (initType->getBitWidth() < targetType->getBitWidth()) {
                        initVal = initType->getBitWidth() == 1 ? builder->CreateZExt(initVal, varType, "init_zext") : builder->CreateSExt(initVal, varType, "init_sext");
                    } else if (initType->getBitWidth() > targetType->getBitWidth()) {
                        initVal = builder->CreateTrunc(initVal, varType, "init_trunc");
                    }
                } else if (initVal->getType()->isPointerTy() && varType->isPointerTy()) {
                    initVal = builder->CreateBitCast(initVal, varType, "init_bitcast");
                } else {
                    throw std::runtime_error("Cannot convert initializer to variable type for: " + node.identifier);
                }
            }
        } else {
            // No initializer - create a default value (0 for numbers, nullptr for pointers)
            if (varType->isIntegerTy()) {
                initVal = llvm::ConstantInt::get(varType, 0);
            } else if (varType->isFloatingPointTy()) {
                initVal = llvm::ConstantFP::get(varType, 0.0);
            } else if (varType->isPointerTy()) {
                initVal = llvm::ConstantPointerNull::get(llvm::cast<llvm::PointerType>(varType));
            } else {
                throw std::runtime_error("Unsupported type for uninitialized variable: " + node.identifier);
            }
        }

        // Store the SSA value directly - no alloca needed
        symbols[node.identifier] = initVal;
        return initVal;
    }
}