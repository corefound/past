#pragma once
#include <string>
#include <utility>
#include <llvm/IR/Module.h>

class Compiler : public Emitter {
  public:
    explicit Compiler(ProgramNode ast);
    ~Compiler() = default;
};
