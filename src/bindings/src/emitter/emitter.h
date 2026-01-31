//
// Created by Brayhan De Aza on 1/30/26.
//

#pragma once

#include <utility>
#include "nodes/programs.h"

class Emitter {
  public:
    std::string ir;
    explicit Emitter(ProgramNode ast);

  private:
    ProgramNode ast;
    void visitMain();
    void visitModules();
};