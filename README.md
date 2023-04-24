# Intel-8080-emulator
An emulator and disassembler for the Intel 8080 instruction set architecture (ISA), 
written in C++. It comes with a graphical user interface (GUI) that includes a memory and state editor.

![image](https://user-images.githubusercontent.com/43931540/234068697-4b0e3658-34a4-4a10-abd4-7219ad3e463b.png)

## Features

+ Easy to use GUI with memory and state editor

## Know shortcomings:

+ Support for interrupts
+ Windows support
+ Fixed window size, no scaling

## Roadmap
- [ ] Complete full ISA implementation with unit test coverage.
- [ ] Pass all common 8080 test suites, such as TST8080.COM, 8080PRE.COM, CPUTEST.COM, 8080EXM.COM (a modified version of 8080EXER.COM).
- [ ] Add configurability to support a wide variety of I/O devices.
- [ ] Integrate decompiler within the emulator with support of breakpoints and other advanced debugging features.

# Run

Compile the project using the steps below or download one of the precompiled releases (only linux). Windows
users can run the linux binaries through WSL as Windows is not supported (for now).


## Getting Started

These instructions will get you a copy of the emulator up and running on your local
machine for development and testing purposes.

### Prerequisites

This project is meant to only be compiled for Linux for now (cross-platform support might come in 
the future). If you wish to use the project *as-is*, meaning using the versions recommended here, 
then you will need:

* **CMake v3.20+** - found at [https://cmake.org/](https://cmake.org/)

* **C++ Compiler** - needs to support at least the **C++17** standard, i.e.
  *GCC*, *Clang*
* **SFML**
* **SFML-Imgui**
* **Imgui**
* **fmt**

Use your platform specific package manager such as `apt` or compile and install from the respective
project sources.

### Building the project

To build the project, all you need to do, ***after correctly
[installing the project dependencies](README.md#Prerequisites)***, is run the following **CMake** routine:

```bash
mkdir build/ && cd build/
cmake .. 
cmake --build . --target 8080sim
```
> ***Note:*** use `--target 8080sim-diss` instead if you want build the disassembler instead.

### Disassembler

The project comes paired with a standalone disassembler.
To run disassembler pass the target binaries as program argument:

`./<compiled_disassembler> <binary_file_to_disassemble>`

The disassembler outputs its results to stdout. To save it as a text file redirect the output.

e.g. on linux `./disassembler >> assembly.txt `


### Running the tests

This project uses [Google Test](https://github.com/google/googletest/)
for unit testing. To run the tests, simply build the test and run it. An example of this procedure is:

```bash
cd build          # if not in the build directory already
cmake --build . --target Google_Tests_run
```

> ***Note:*** Only the ISA implementation is unit tested.


## Contributing

Please read [CONTRIBUTING.md](CONTRIBUTING.md) for details on our how you can
become a contributor and the process for submitting pull requests to us.

## Versioning

This project makes use of [SemVer](http://semver.org/) for versioning. A list of
existing versions can be found in the
[project's releases](https://github.com/Abd0s/Intel-8080-emulator/releases).

## Authors

* **Abdulahad Kancan** - [@Abd0s](https://github.com/Abd0s)

## License

This project is licensed under the [MIT](https://opensource.org/license/mit/) - see the
[LICENSE](LICENSE) file for details


