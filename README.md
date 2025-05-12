# Tina3D

This a mini game engine created from two repositories: "CG" and "Jogos" by JudsonSS.

## How to build

### Dependencies

To build this project, you need to have the following dependencies installed:

#### Windows

- [Windows SDK](https://learn.microsoft.com/en-us/windows/apps/windows-app-sdk/downloads)

### Configure

This project uses CMake to generate the build files. To configure the project, you can use
the following commands:

```bash
cmake -B build -S . [flag(s)]
```

During the configuration process, the examples will be compiled. If you don't want to compile them, you could pass the -DBUILD_EXAMPLES=OFF flag to the cmake command above.

If you want to use shared libraries instead of static libraries, you can pass the -DBUILD_SHARED_LIBRARY=ON flag to the 
command above.

### Build

After configuring the project, you can build it using the following command:

```bash
cmake --build build
```