import llvm from 'llvm-bindings';
import * as fs from "fs";

export class Emitter {
    protected context: llvm.LLVMContext;
    protected module: llvm.Module;
    protected builder: llvm.IRBuilder;
    protected ir: string;

    constructor() {
        this.context = new llvm.LLVMContext();
        this.module = new llvm.Module('test', this.context);
        this.builder = new llvm.IRBuilder(this.context);

        this.ir = this.module.print();

        const main = this.createFunction('main', this.builder.getInt32Ty(), []);
        this.builder.SetInsertPoint(main.getEntryBlock());
    }

    protected createFunction(name: string, returnType: llvm.Type, params: llvm.Type[]): llvm.Function {
        const fnType = llvm.FunctionType.get(returnType, params, false);
        const fn = llvm.Function.Create(fnType, llvm.Function.LinkageTypes.ExternalLinkage, name, this.module);

        // 🔑 Create entry block *inside the function*
        const entry = llvm.BasicBlock.Create(this.context, 'entry', fn);
        this.builder.SetInsertPoint(entry);

        return fn;
    }

    protected allocate(name: string, type: llvm.Type, value?: llvm.Value) {
        const ptr = this.builder.CreateAlloca(type, null, name);

        if (value) {
            this.builder.CreateStore(value, ptr);
        }

        return ptr;
    }

    protected getType = (type: string) => {
        switch (type) {
            case "i1":
                return this.builder.getInt1Ty();
            case "i8":
                return this.builder.getInt8Ty();
            case "i16":
                return this.builder.getInt16Ty();
            case "i32":
                return this.builder.getInt32Ty();
            case "i64":
                return this.builder.getInt64Ty();
            case "f32":
                return this.builder.getFloatTy();
            case "f64":
                return this.builder.getDoubleTy();
            case "str":
                return this.builder.getInt8PtrTy();
            default:
                return this.builder.getInt8PtrTy();
        }
    };

    toBycodeFile = (path: string) => {
        llvm.WriteBitcodeToFile(this.module, path);
    }

    toIRFile = (path: string) => {
        const ir = this.module.print()
        fs.writeFileSync(path, ir);
    }

    print() {
        console.log(this.module.print());
    }
}
