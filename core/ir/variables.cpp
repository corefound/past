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
    llvm::Module* IR::generate(const nlohmann::ordered_json& node) {
        loadAndLinkModulesFromFolder();
        program(node);
        return module.get();
    }

    llvm::Value* IR::program(const nlohmann::ordered_json& node) {
        // Create main function
        llvm::Type* retType = builder->getInt32Ty();
        auto* mainFunctionType = llvm::FunctionType::get(retType, false);
        auto* mainFunction = llvm::Function::Create(mainFunctionType, llvm::Function::ExternalLinkage, "main", module.get());

        auto* entry = llvm::BasicBlock::Create(*context, "entry", mainFunction);
        builder->SetInsertPoint(entry);

        // Process all statements in the program
        for (const auto body = static_cast<nlohmann::ordered_json>(node["body"]); const auto& statement : body) {
            try {
                statements(statement);
            } catch (const std::exception& e) {
                throw std::runtime_error("Program generation failed: " + std::string(e.what()));
            }
        }

        // Return 0
        builder->CreateRet(llvm::ConstantInt::get(builder->getInt32Ty(), 0));

        if (llvm::verifyFunction(*mainFunction, &llvm::errs()))
            throw std::runtime_error("IR verification failed");

        return mainFunction;
    }

    llvm::Value* IR::literal(const nlohmann::ordered_json& node) {
        if (!node)
            throw std::runtime_error("Cannot generate code for empty literal");

        const std::string type = node["type"];
        if (type == "FloatLiteral") {
            const auto value = std::any_cast<std::string>(node["value"]);
            return llvm::ConstantFP::get(builder->getDoubleTy(), std::stod(value));
        }

        if (type == "IntegerLiteral") {
            const auto value = std::any_cast<std::string>(node["value"]);
            return llvm::ConstantFP::get(builder->getInt32Ty(), std::stod(value));
        }

        if (type == "BooleanLiteral") {
            const auto value = std::any_cast<std::string>(node["value"]);
            return llvm::ConstantFP::get(builder->getInt1Ty(), value == "true" ? 1 : 0);
        }

        if (type == "NullLiteral") {
            return llvm::ConstantInt::get(builder->getInt8Ty(), 0);
        }

        if (type == "StringLiteral") {
            const auto value = std::any_cast<std::string>(node["value"]);
            return builder->CreateGlobalString(value, "str");
        }

        if (type == "IdentifierLiteral") {
            const auto value = std::any_cast<std::string>(node["value"]);
            const auto it = symbols.find(value);

            if (it == symbols.end())
                throw std::runtime_error("Undefined identifier: " + value);

            llvm::Value* alloc = it->second;
            return builder->CreateLoad(alloc->getType(), alloc, value + ".load");
        }

        return nullptr;
    }
}