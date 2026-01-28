import * as literals from './literals';

export namespace Types {
    export type BooleanLiteral = literals.BooleanLiteral;
    export type IntegerLiteral = literals.IntegerLiteral;
    export type FloatLiteral = literals.FloatLiteralType;
    export type StringLiteral = literals.StringLiteral;
    export type NullLiteral = literals.NullLiteral;
    export type UndefinedLiteral = literals.UndefinedLiteral;

    export type Node = Record<string, any> & {
        kind: string;
    };

    export type Program = {
        name: string
        main: Node[]
        modules: Program[]
    }
}
