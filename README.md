# Intel-8080-emulator
Emulator + disassembler for the Intel 8080 ISA written in C++

# Compile

Build using CMake and `CMakeList.txt` to your desired target.

# Run

To run the emulator or disassembler pass the target binaries as program argument:

`./compiled-executable <binary_file_to_emulate/disassemble>`

The disassembler outputs its results to stdout. To save it as a text file redirect the output.

e.g. on linux `./disassembler >> assembly.txt `
