# README

## Problem Statement

### This is Task 05 of the Eudyptula Challenge

Yeah, you survived the coding style mess!  Now, on to some "real"
things, as I know you are getting bored by these so far.

So, simple task this time around:

- take the kernel module you wrote for task 01, and modify it so that
when a USB keyboard is plugged in, the module will be automatically
loaded by the correct userspace hotplug tools (which are implemented
by depmod / kmod / udev / mdev / systemd, depending on what distro
you are using.)

Yes, so simple, and yet, it's a bit tricky.  As a hint, go read chapter
14 of the book, "Linux Device Drivers, 3rd edition."  Don't worry, it's
free, and online, no need to go buy anything.

### Recommended Reading

- [Chapter 14 of Linux Device Drivers, Third edition (LDD3)](https://lwn.net/Kernel/LDD3/)
- [ArchWiki - Udev](https://wiki.archlinux.org/index.php/Udev)
- Linux man page: udev: `man udev`
- [USB Programming Guide](http://lmu.web.psi.ch/docu/manuals/software_manuals/linux_sl/usb_linux_programming_guide.pdf)

## Theory

### Hardware Device Fundamental

Compared to previous tasks, this one is actually quite theory-heavy. It'll take some time to read through Chapter 14 and really absorb it.

#### Kobject and Kset

In order to understand how hardware devices are handled / represented by the Linux kernel, we'd start with understanding `kobject`, which is one of the most basic representations of all hardware devices. After that, there's `kset`, which is several a set data structure that groups several kobject(s) together for a specific reason. It's nice to see what the kobject and kset structures consist of, but by themselves, they're not too interesting because mostly embedded within a bigger data structure where the funcitionalities are defined at . If you're familiar with OOP, an imperfect analogy is that kobject is like a base abstract class which is extended by other class that defines more information and functionalities. While kobject is passed around different functions, they are typically used to get its parent container using `container_of` macro. Also, kobject can have a parent kobject, which in the hardware device realm, might represent the "parent" hardware it's attached into. As an example, a keyboard might have a USB hub as its parent, which in turn parented by a PCI controller. For ruther understanding, kobject and kset structures are defined under `include/linux/kobject.h`.

#### Sysfs

Another fundamental concept every Linux aspirants need to know is that almost everything in Linux is represented using files. This includes kernel internal and hardware devices. This is often refered to as `sysfs`. So when a USB keyboard is attached to the system, there will be a virtual file created to represent it. For many devices, user space can interact with them doing read / write operations against the sysfs files, as if they're regular files. As experiment is the best way to learn, let's play around with an input device. Let's try to attach a USB mouse / keyboard onto a system. Before attaching it, take a note of all the files under `cat /dev/input/` and then attached the device and again check the files. There should be a new `eventX` file created there. Now, do `cat /dev/input/eventX` and then try to generate events with the input device (i.e press some keys). You should see some values generated on the terminal. The values are most likely unreadable, because they're meant to be read using specific-means.

The next important abstraction to understand is subsystem. Each of the ksets belongs to a subsystem. An example is a block subsystem located under `/sys/block/`, which hosts all the block-storage based devices (i.e. hard-drive, SSD). Device drivers developers almost never need to create a new subsystem, but instead just work with an already existing one.

#### Interactions between kobject, kset and sysfs

The next crucial knowledge to know is that kobject directly correlates with entries in the sysfs. For example, parent-children relationships within kobjects represents sysfs directories and sub-directories hierarchy. A kobject has a `name` property, which represents the name of the sysfs directory that's created when the kobject is registered. It can also have `attributes` which would appear in sysfs as files. When a read or write is made against those sysfs files, the underlying functions defined within the kobject are called. A kobject that's grouped together in a kset can also share the same sysfs hierarchy.

#### Hotplug

Another fundamental concept to know is hotplug event. It's a mechanism used by kernel space to notify userspace of changes in the hardware configuration. For example when a new USB device is plugged into a system, a hotplug event will be propagated by the kernel up to the userspace land. Userspace application can then handle it. For example, when a USB thumbdrive is attached, some Linux distros would pop out a nautilus window pointing to it.

#### Bus

Furthermore, every single device is attached into a `bus`. PCI, USB, AGP, are some examples of buses. Computer hardware devices are typically designed to communicate with these mainstream buses. Kernel drivers developer would then work with the abstraction provided by the bus layer.

### What's Next? How to find more information about dealing with USB in Linux?

The fundamental thinking required to solve this task is that Linux kernel is really large such that each subsystem is typically isolated from each others, and that driver developers generally don't need to understand everything, but instead, only need to leverage on the higher-level abstractions that are already provided. USB specification page itself is really large. At one point I thought I had to read through it and understand everything before I could begin. But then I learned what's needed is just to understand enough of the high-level concept to get started with the abstraction provided.

So as this task involves a USB device, we want to search on the documentation about the abstraction Linux kernel provides to work with USB: `linux-src/Documentation/driver-api/usb`. As we had previously learned about `hotplug` being the mechanism used by Linux to notify that a new device is connected, the file `hotplug.rst` under the folder seems like a potential candidate to start our research with.

Reading through `hotplug.rst` gives us a good starting point. It gives us a snippet of code that would be called when any of the specified USB devices is detected. Digging through the different documentation files on the same directory, there's also a useful information under `usb.rst`. In particular, at the "USB Core APIs" section. Finally, a complete epiphany came through reading the file `writing_usb_driver.rst`. It even gives point to `linux-src/drivers/usb/usb-skeleton.c` which is a skeleton file created by the documentation author to help people writing their own USB drivers. There're also very insightful readings on the resources side, one of them being 'USB Programming Guide'

### Finally, implementing it

`usb-skeleton.c` contains most of information we need to detect a USB keyboard device. The only missing information is the specific `usb_device_id` to get our module triggered when a USB keyboard is detected, which turns out could be found under `include/uapi/linux/hid.h`. Read the implementation on `usb-keyboard-module.c` it's pretty self-explanatory :)
