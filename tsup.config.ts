import { defineConfig } from 'tsup'

export default defineConfig({
  entryPoints: ['./src/index.ts'],
  format: ['esm', 'cjs'],
  dts: true,
  external: [
    "chalk",
    "llvm-bindings",
    "node-addon-api",
    "tsconfig-paths",
    "typescript",
    "@types/node",
    "eslint",
    "mocha",
    "node",
    "ts-node",
    "tsup",
    "zod"
  ]
})
