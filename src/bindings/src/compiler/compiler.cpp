#include "compiler.h"
#include <string>
#include <iostream>
#include <napi.h>


Compiler::Compiler(ProgramNode ast) : Emitter(ast), ast(ast) {}

void Compiler::visitNodes() const {
  for(auto node : this->ast.main) {
    if (node.has_value()) {
      // std::cout << node.type().name() << std::endl;
    }
  }
}

void Compiler::toExecutableFile() {
  // TODO: implement
  std::cout << "toExecutableFile() not implemented" << std::endl;
}

void Compiler::toBytecodeFile() {
  // TODO: implement
  std::cout << "toBytecodeFile() not implemented" << std::endl;
}

void Compiler::toIRFile() {
  // TODO: implement
  std::cout << "toIRFile() not implemented" << std::endl;
}