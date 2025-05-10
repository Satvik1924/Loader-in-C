# ELF Loader

This project is a custom ELF (Executable and Linkable Format) loader written in C. It demonstrates how an ELF binary can be manually loaded, parsed, and executed from user space using system calls like `mmap`, `read`, and `open`. This can serve as an educational tool for understanding how low-level binary execution and process loading works on Linux.

## 📁 Project Structure

- `loader.c`: Core logic for reading, parsing, and executing ELF binaries.
- `launch.c`: Driver program that validates an ELF file and invokes the loader.
- `loader.h`: Header file containing necessary declarations.
  
## 🛠️ Features

- Manually reads and verifies ELF magic headers.
- Parses ELF headers and program headers.
- Identifies PT_LOAD segments and memory maps them.
- Calculates the entry point and transfers control to it.
- Safely cleans up allocated memory and file descriptors after execution.

## 🚀 How to Use

### 🔧 Prerequisites
- A Linux-based system.
- GCC compiler.

### 🧪 Build Instructions

```bash
gcc -o elf_loader loader.c launch.c
````

### 🏃 Run

```bash
./elf_loader <path_to_ELF_executable>
```

> ⚠️ Only 32-bit ELF binaries are supported (`Elf32_Ehdr`). Make sure to compile your test executable accordingly using:
>
> ```bash
> gcc -m32 -o hello hello.c
> ```

## 📌 Example

```bash
./elf_loader ./hello
```

## 🧼 Cleanup

The loader ensures that all allocated memory and file descriptors are properly freed or closed after execution to prevent leaks.

## 🧠 Educational Value

This project helps you understand:

* ELF file format internals.
* Manual process loading.
* Use of `mmap`, `lseek`, and `read` system calls.
* Low-level memory management and function pointer invocation in C.

## 📚 References

* [ELF Format on Wikipedia](https://en.wikipedia.org/wiki/Executable_and_Linkable_Format)
* [Linux man pages](https://man7.org/linux/man-pages/)

## 📄 License

This project is for educational use only. You may modify and use it freely for academic purposes.


Made with ❤️ by Satvik – IIITD

