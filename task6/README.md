# README

## Problem Statement

### This is Task 06 of the Eudyptula Challenge

Nice job with the module loading macros, those are tricky, but a very
valuable skill to know about, especially when running across them in
real kernel code.

Speaking of real kernel code, let's write some!

The task this time is this:

- Take the kernel module you wrote for task 01, and modify it to be a
  misc char device driver.  The misc interface is a very simple way to
  be able to create a character device, without having to worry about
  all of the sysfs and character device registration mess.  And what a
  mess it is, so stick to the simple interfaces wherever possible.
- The misc device should be created with a dynamic minor number, no
  need running off and trying to reserve a real minor number for your
  test module, that would be crazy.
- The misc device should implement the read and write functions.
- The misc device node should show up in /dev/eudyptula.
- When the character device node is read from, your assigned id is
  returned to the caller.
- When the character device node is written to, the data sent to the
  kernel needs to be checked.  If it matches your assigned id, then
  return a correct write return value.  If the value does not match
  your assigned id, return the "invalid value" error value.
- The misc device should be registered when your module is loaded, and
  unregistered when it is unloaded.
- Provide some "proof" this all works properly.

### Recommended Reading

- [Linux Device Driver](https://lwn.net/images/pdf/LDD3/ch01.pdf)
- [Misc Device](https://www.kernel.org/doc/html/v4.14/driver-api/misc_devices.html)

## Theory

### Linux Device Drivers

In order to implement this, we need to understand the basic Linux device drivers.
There are a few fundamental device types: character, block, and network.
We're going to need to understand character device. At its essence, it's an interface
for userspace to interact with kernel space, in a form of regular Linux file.
A userspace application interacts with the kernel space by reading to/from it.
When a read/write happens, it would invoke the corresponding callback on the
implementing device driver code. Character device is typically organized by its
functionality, such as input device, storage device, etc. A "misc" device is simply used for "other" category, which is perfect for this task as it doesn't have any particular functionality.

Take a look at the provided solution `eudyptula.c` as it's pretty self-explanatory. Note that kernel and userspace can't directly access each
other's memory region. In order to write a data into userspace address, a kernel function `copy_to_user()` needs to be used, and `copy_from_user()` in order to read. For this task, to make life a little easier, we're going to use
helper functions to help writing/reading to userspace buffer: `simply_write_to_buffer()` and `simple_read_to_buffer()` which both are implemented under `fs/libfs.c`. Read them to get fundamental understanding on how to  read and write to userspace memory location from the kernel.

That's it! :) This assignment is pretty straightforward compared to the previous task.
