import { Past } from "@/index"

const ast = {
    "name": "./tests/index.ts",
    "main": [
        {
            "kind": "VariableDeclaration",
            "flag": "const",
            "name": "n",
            "type": "i8",
            "storage": "stack",
            "value": {
                "kind": "NullLiteral",
                "value": "null"
            }
        },
        {
            "kind": "VariableDeclaration",
            "flag": "const",
            "name": "a",
            "type": "i64",
            "storage": "stack",
            "value": {
                "kind": "IntegerLiteral",
                "value": "100"
            }
        },
        {
            "kind": "VariableDeclaration",
            "flag": "const",
            "name": "c",
            "type": "i64",
            "storage": "stack",
            "value": {
                "kind": "IntegerLiteral",
                "value": "24"
            }
        }
    ],
    "modules": []
}

const past = new Past(ast)
past.print();
console.log(past.toExecutableFile());