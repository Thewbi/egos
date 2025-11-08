# Building

Add your toolchain (the bin folder) to the PATH variable

```
PATH=/c/Users/lapto/Downloads/xpack-riscv-none-elf-gcc-14.2.0-3-win32-x64/xpack-riscv-none-elf-gcc-14.2.0-3/bin:$PATH
```

Inside the Makefile, adjust the prefix so that when the tools are prefixed with the prefix, a valid binary from the bin
folder of the toolchain that has been added to the PATH variable in the previous step, creates a valid binary file.

```
prefix 		= riscv64-unknown-elf
```

Type make to execute the Makefile and build the binary.

```
make
```