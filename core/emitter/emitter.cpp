//
// Created by Brayhan De Aza on 2/16/26.
//

#include "emitter.h"
#include <iostream>

namespace past::core::emitter {

    void Emitter::print(const std::string& text) {
        std::cout << text << std::endl;
    }

    std::vector<uint8_t> Emitter::toMemory(const llvm::Module& module) {
        return std::vector<uint8_t>();
    }

    std::vector<uint8_t> Emitter::toObjectInMemory(llvm::Module* module) {
        return std::vector<uint8_t>();
    }

    void Emitter::toObjectFile(llvm::Module* module, const std::string& outputPath) {

    }

    void Emitter::toExecutable(llvm::Module* module, const std::string& outputPath) {

    }


}