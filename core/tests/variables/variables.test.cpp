// //
// // Created by Brayhan De Aza on 12/12/25.
// //
//
// #include <bitset>
// #include <random>
// #include <sstream>
// #include <string>
// #include "libs/catch2/catch_amalgamated.hpp"
//
// namespace yogi::visitor::nodes {
//
//
//     TEST_CASE("variables evaluation", "[VARIABLE]", ) {
//         const auto cases = GENERATE(
//             std::make_tuple<std::string>("str a = f\"Hello, {\"world!!!\"}\"", "str", "a", "Hello, world!!!")
//
//             );
//
//         // auto [text, type, name, expectedValue] = cases;
//         // const auto ast = Yogi::testAST(text);
//         // const auto& node = std::any_cast<VariableDeclarationNode>(ast.body.at(0));
//         // const auto [resolvedType, resolvedValue, resolvedNode] = utils::Helpers::resolveItem(node.value);
//         //
//         // REQUIRE(node.kind == Kind::VARIABLE_DECLARATION);
//         // REQUIRE(resolvedValue == expectedValue);
//         // REQUIRE(resolvedType == type);
//         // REQUIRE(resolvedNode.type() == node.value.type());
//
//     } // namespace yogi::visitor::nodes
// } // namespace yogi::visitor::nodes