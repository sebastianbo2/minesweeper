windows :

```bash
    cmake -S . -B build
    cmake --build build --config Release
    build\Release\main.exe
```

macos/linux:

```bash
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build
    ./build/main
```