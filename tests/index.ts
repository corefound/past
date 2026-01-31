import { Past } from "@/index"
import { binder } from '@/bindings';

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


const api = binder({
    config: {
        output: "./tests/output",
        target: "aot",
        optimize: "-O2"
    },
    ast: ast
})

api.print()
