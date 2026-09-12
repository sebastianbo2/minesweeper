help too many segfaults when playing (80% chance u wont get to finish ur game)

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
