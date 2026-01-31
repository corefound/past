#pragma once
#include <utility>

#include "nodes/programs.h"

class Emitter {
  public:

    explicit Emitter(ProgramNode ast): ir("ir"), ast(std::move(ast)) {} // Declaration (definition in emitter.cpp)

  protected:
    std::string ir;
    ProgramNode ast;
};