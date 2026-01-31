//
// Created by Brayhan De Aza on 1/30/26.
//

#include "emitter/emitter.h"
#include <iostream>

Emitter::Emitter(ProgramNode ast): ir(""), ast(std::move(ast)) {
    visitModules();
    visitMain();
}

void Emitter::visitMain() {
    // for(auto node : ast.main) {

    // }
    std::cout << "Main: " << std::endl;
}

void Emitter::visitModules() {
    // for(auto node : ast.modules) {

    // }
    std::cout << "Modules: " << std::endl;
}

