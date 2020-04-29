# Task 01

## Problem Statement

Write a Linux kernel module, and stand-alone Makefile, that when loaded
prints to the kernel debug log level, "Hello World!"  Be sure to make
the module be able to be unloaded as well.

The Makefile should build the kernel module against the source for the
currently running kernel, or, use an environment variable to specify
what kernel tree to build it against.

## Theory

### Linux Kernel Module

First of all, operating system kernel commonly categorized into either
monolithic or microkernel. Monolithic kernel have all its core services
to live in a same address space (i.e. one process), while microkernel
approach isolate different services into different address spaces (i.e. many processes).
There are advantages and disadvantages to the different approaches. As an example,
in microkernel, if a single service crash, it could theoritically be restarted without having
to crash the entire kernel. As a drawback, however, there's a performance overhead in microkernel
approach because inter-services communications would require some sort of IPC. And also, microkernel
is more complex to implement.

Linux kernel is a modular monolithic kernel. Don't confuse modular with microkernel.
Modular simply means that the different functionalities in Linux kernel can be implemented
as a separate module. In a C programming world, think of it as including an external module
to a program. The included module is still running in the same process space as the program itself.
One of the motivations behind making Linux kernel modular is that there are millions of hardware
supported by the kernel, but at runtime, only a small number of hardware attached to the computer
need to be supported. It doesn't make sense to load all the drivers of unused hardware, because it would take up RAM unnecessarily. The other motivation behind modularization is to support different
functionalities for different use cases. As an example, there are tons of different filesystem
implementations that many of regular users wouldn't ever need to use.

## Further Readings

- [Chapter 2 of Linux Device Drivers, Third edition (LDD3)](https://lwn.net/Kernel/LDD3/)
- [Arch Wiki: Compiling Kernel Module](https://wiki.archlinux.org/index.php/Compile_kernel_module)

## Implementation Details

Linux kernel module is a .ko file that can be loaded by kernel at runtime
and be removed when it's no longer needed. The module is coded in C and compiled
using gcc, just like a typical C program. The difference is that it needs to be compiled using the dependencies compatible with the running kernel. After the C code is compiled it produces .ko file, which
when loaded by the kernel, its init function will be called. And when it's removed, its exit function will be called. The purpose of the two functions are to do initialization and cleanup appropriately
(i.e. to avoid memory leak)

### helloworld.c

- module_init() and module_exit() are the functions to register the module's callback.
- printk() is kernel equivalance of printf(). But since kernel module is running on a kernel space,
  printk() doesn't print to terminal like printf() does. Instead, it prints to global kernel
  log buffer that's accessible through ```dmesg``` command.

### Makefile

- The make program needs to be invoked at a special directory where relevant kernel's dependencies
  are located at, such as header files, and hence the -C flag. The directory specified defines
  linux kernel build system that module compilation relies on, such as obj-m variable or 'modules'
  keyword at the end.
- ```uname -r``` gives out the version of currently running Linux kernel. It's uncommon for a Linux
  distribution to have several Linux kernels installed. One typical use case is for a fallback
  when there's a bug on a newly installed one.

## Testing

- Compile the module, by invoking ```make```
- Upon successful compilation, helloworld.ko would be generated.
- Load the module into currently running kernel: ```sudo insmod helloworld.ko```
  root privilege is needed because kernel module runs in kernel space and so could do dangerous stuffs
- Run ```dmesg``` and checks that 'Hello world!' is printed
- Unload the module by running: ```sudo rmmod helloworld```, 'See you later!' message should be printed

### Additional Tips

- After module is loaded into kernel, you can check that it's loaded by running ```lsmod```
