//
// Created by Brayhan De Aza on 11/24/25.
//

#pragma once

#include <any>
#include <memory>
#include <string>
#include <unordered_map>
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include  <json.hpp>

namespace past::core::ir {
    class IR {
       public:
        explicit IR(const std::string& moduleName);

        // Generate module from AST
        llvm::Module* generate(const nlohmann::ordered_json& node);

       private:
        // Core LLVM pieces
        std::unique_ptr<llvm::LLVMContext> context;
        std::unique_ptr<llvm::Module> module;
        std::unique_ptr<llvm::IRBuilder<>> builder;

        // Symbol table: variable name -> alloca
        std::unordered_map<std::string, llvm::Value*> symbols;

        // Helpers
        [[nodiscard]] llvm::Type* mapDataType(const std::string& typeName) const;
        llvm::Value* promoteToDouble(llvm::Value* value) const;
        // llvm::Type* inferType(const std::any& node) const;
        // llvm::Value* convertType(llvm::Value* val, llvm::Type* targetType, const std::string& name, const std::string& phase) const;
        //
        // // Codegen utilities
        // static llvm::AllocaInst* createEntryBlockAlloca(llvm::Function* function, llvm::Type* type, const std::string& name);
        // static std::unique_ptr<llvm::Module> loadBitcode(const std::string& path, llvm::LLVMContext& context);

        // Codegen for different node types
        llvm::Value* program(const nlohmann::ordered_json& node);
        llvm::Value* statements(const nlohmann::ordered_json& node);
        llvm::Value* literal(const nlohmann::ordered_json& node);
        llvm::Value* variableDeclaration(const nlohmann::ordered_json& node);
        llvm::Value* expressions(const nlohmann::ordered_json& node);

        // llvm::Value* variableAssignment(const visitor::nodes::VariableDeclarationNode& node);
        // llvm::Value* arrayDeclaration(const visitor::nodes::ArrayDeclarationNode& node);


        // void loadAndLinkModulesFromFolder() const;
        // bool linkModule(std::unique_ptr<llvm::Module> other) const;
    };
} // namespace yogi::core::ir
