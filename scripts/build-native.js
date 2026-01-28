import { execSync } from 'child_process'
import os from 'os'
import path from 'path'
import fs from 'fs'

const root = process.cwd()
const bindingsDir = path.join(root, 'src', 'bindings')
const buildDir = path.join(bindingsDir, 'build')

console.log(
  `Building native addon for ${os.platform()} ${os.arch()}`
)

// 1️⃣ Clean build directory
if (fs.existsSync(buildDir)) {
  fs.rmSync(buildDir, { recursive: true, force: true })
}
fs.mkdirSync(buildDir, { recursive: true })

// 2️⃣ node-gyp configure
execSync('npx node-gyp configure', {
  cwd: bindingsDir,
  stdio: 'inherit',
})

// 3️⃣ node-gyp build
execSync('npx node-gyp build', {
  cwd: bindingsDir,
  stdio: 'inherit',
})

console.log('Native addon build complete')
