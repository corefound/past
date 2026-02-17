//
// Created by Brayhan De Aza on 2/16/26.
//

#include <core.h>

#include <iostream>

int main() {
    const nlohmann::ordered_json ast = {
        {"kind", "VariableDeclaration"},
        {"flag", "const"},
        {"name", "c"},
        {"type", "i64"},
        {"storage", "stack"},
        {"value", {
             {"kind", "IntegerLiteral"},
             {"value", "24"}
         }}
    };

    core::compile(ast);

    std::cout << "Hello from Past" << std::endl;

    return 0;
}