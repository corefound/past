{
    "targets": [
        {
            "target_name": "pastaddon",
            "sources": [
                "src/main.cpp",
                "src/binder/binder.cpp",            
                "src/emitter/emitter.cpp",            
            ],
            "include_dirs": [
                "<!@(node -p \"require('node-addon-api').include\")",
                "<!@(llvm-config --includedir)",
                "src/",
            ],
            "dependencies": ["<!(node -p \"require('node-addon-api').gyp\")"],
            "defines": ["NAPI_VERSION=8"],
            "cflags_cc": ["-std=c++23", "-fexceptions"],
            "xcode_settings": {
                "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
                "CLANG_CXX_LIBRARY": "libc++",
                "MACOSX_DEPLOYMENT_TARGET": "13.0",
            },
            "libraries": ["<!@(llvm-config --libs core support irreader)"],
            "ldflags": ["<!@(llvm-config --ldflags)"],
        }
    ]
}
