cd C:\Users\me\Desktop\CPP\cpp_demo1\demo1

# Configure (only needed initially or when configuration changes)
cmake -S . -B build

# Compile
cmake --build build --config Debug

# Run
.\build\Debug\demo1.exe