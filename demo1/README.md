# demo1 — C++ Hello World

A minimal project to learn C++17, Git, GitHub and CMake.

## Prerequisites

- A C++ compiler (GCC, Clang or MSVC)
- CMake 3.16+

## Build and run

```sh
cmake -S . -B build
cmake --build build
```

Run on Linux/macOS:

```sh
./build/demo1
```

Run on Windows with Visual Studio's default multi-config generator:

```powershell
.\build\Debug\demo1.exe
```

Expected output:

```text
Hello, World!
```

## Next exercises

1. Change the greeting and rebuild.
2. Ask the user for their name with `std::cin`.
3. Add a function that prints a custom greeting.
4. Commit and push each exercise to GitHub.
