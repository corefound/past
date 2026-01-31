// index.d.ts

type BinderType = {
    print: () => void
}

export function binder(p: any): BinderType;


