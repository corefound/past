//
// Created by Brayhan De Aza on 1/30/26.
//

#pragma once

#include <any>
#include <string>

struct VariableNode {
    std::string kind;
    std::string flag;
    std::string name;
    std::string type;
    std::string storage;
    std::any value;
};
