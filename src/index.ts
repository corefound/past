import llvm from 'llvm-bindings';
import { Kinds } from './constants';
import { binder } from '@/bindings';
import { Types } from './types';

export class Past {
    constructor(program: Types.Program) {
        // this.visitNodes(program);
    }

    // private visitNodes(program: Types.Program) {
    //     program.main.forEach((node: Types.Node) => {
    //         switch (node.kind) {
    //             case Kinds.VariableDeclaration:
    //                 this.variableDeclaration(node);
    //                 break;

    //             default:
    //                 this.literals(node);
    //                 break;
    //         }
    //     })

    //     this.builder.CreateRet(
    //         this.builder.getInt32(0)
    //     );

    //     this.ir = this.module.print();
    // }

    // private variableDeclaration = (node: Types.Node) => {
    //     const name = node.name;

    //     // Determinar el tipo correcto basado en el valor
    //     let type: llvm.Type;
    //     if (node.value.kind === Kinds.NullLiteral) {
    //         type = llvm.Type.getInt8PtrTy(this.context);
    //     } else {
    //         type = this.getType(node.type);
    //     }

    //     if (this.isLiteral(node.value)) {
    //         const ptr = this.builder.CreateAlloca(type, null, name);
    //         const value = this.literals(node.value);
    //         this.builder.setAl.CreateStore(value, ptr).setOperands([8, prt]);
    //     }
    // }

    // private literals = (node: Types.Node, name?: string) => {
    //     switch (node.kind) {
    //         case Kinds.IntegerLiteral:
    //             return this.builder.getInt64(Number(node.value));

    //         case Kinds.FloatLiteral:
    //             return llvm.ConstantFP.get(this.builder.getDoubleTy(), Number(node.value));

    //         case Kinds.StringLiteral:
    //             return this.builder.CreateGlobalString(node.value);

    //         case Kinds.BooleanLiteral:
    //             return this.builder.getInt1(Number(node.value) === 1);

    //         case Kinds.NullLiteral:
    //             const voidPtr = llvm.Type.getInt8PtrTy(this.context);
    //             return llvm.ConstantPointerNull.get(voidPtr);

    //         default:
    //             break;
    //     }
    // }

    // private isLiteral = (node: Types.Node) => {
    //     switch (node.kind) {
    //         case Kinds.IntegerLiteral:
    //         case Kinds.FloatLiteral:
    //         case Kinds.StringLiteral:
    //         case Kinds.BooleanLiteral:
    //         case Kinds.NaNLiteral:
    //         case Kinds.NullLiteral:
    //         case Kinds.UndefinedLiteral:
    //         case Kinds.InfinityLiteral:
    //             return true;
    //         default:
    //             return false;
    //     }
    // }

}

export type {
    Types,
    Kinds
}