# Task 01

## Problem Statement

Now that you have written your first kernel module, it's time to take
off the training wheels and move on to building a custom kernel.  No
more distro kernels for you, for this task you must run your own kernel.
And use git!  Exciting isn't it!  No, oh, ok...

The tasks for this round is:

- download Linus's latest git tree from git.kernel.org (you have to
  figure out which one is his, it's not that hard, just remember what
  his last name is and you should be fine.)
- build it, install it, and boot it.  You can use whatever kernel
  configuration options you wish to use, but you must enable
  CONFIG_LOCALVERSION_AUTO=y.
- show proof of booting this kernel.  Bonus points for you if you do
  it on a "real" machine, and not a virtual machine (virtual machines
  are acceptable, but come on, real kernel developers don't mess
  around with virtual machines, they are too slow.  Oh yeah, we aren't
  real kernel developers just yet.  Well, I'm not anyway, I'm just a
  script...)  Again, proof of running this kernel is up to you, I'm
  sure you can do well.

Hint, you should look into the 'make localmodconfig' option, and base
your kernel configuration on a working distro kernel configuration.
Don't sit there and answer all 1625 different kernel configuration
options by hand, even I, a foolish script, know better than to do that!

After doing this, don't throw away that kernel and git tree and
configuration file.  You'll be using it for later tasks, a working
kernel configuration file is a precious thing, all kernel developers
have one they have grown and tended to over the years.  This is the
start of a long journey with yours, don't discard it like was a broken
umbrella, it deserves better than that.

## Theory

### Booting Process

Since the task requires us to install and run a Linux kernel, an
understanding about a kernel's role is required. Although Linux kernel
is an operating system, it's unlike Mac OS or Windows, where they're
bundled with GUI. Linux kernel on the other hand, only provides the
core functionality in order to make use of the connected hardware.

When computer first boots up, BIOS is started. BIOS is a software that's
typically flashed onto a computer's motherboard. It has some configurable
settings such as whether to enable/disable specific features on the hardware,
boot priority, password protection, etc. After initializing several low-level
stuffs that the hardware needed, it then hands over the software control into
bootloader.

Bootloader does further initialization, such as allowing user to choose between
different operating systems that are installed. In addition to that, it also
abstracts out nitty-gritty details so that operating system can easily takes over.
An example is on how it would load operating system software code into specific
initial address space. Bootloader then hands over the control over to operating system,
such as Linux kernel.

While Windows 10 and Mac OS X have GUI integrated with them, Linux kernel doesn't.
Linux kernel provides access for hardware access, such filesystem, keyboard and mouse
drivers, monitor, etc. The access, however, is provided in a very foundational level.
For a USB mouse, for example, it allows for applications to get raw value of mouse movements.
It doesn't provide a cursor that would move around when the mouse is moved. Instead, it provides
an abstraction that can be used by user to write a program to show a cursor that would move as
the mouse is moved. After it finishes initialization, Linux kernel invokes the first user
space program that is referred as "init process". At this point, the computer and hardware connected
onto it are ready to be used, but there's still no interface that user can use to interact easily.
The responsibility to provide a user-friendly interface is then handed over to Linux distribution/distro.

There are tons of different Linux distro out there, such as Ubuntu, ArchLinux, CentOS, etc. These distros
are what end users typically associate as Linux OS. Distro comes pre-configured and bundled with
the different tools that end-users can use to do something productive with their computers.
This includes desktop manager, network manager, audio manager, web browser, text editor, etc.

### Reading Resources

- [Arch Wiki: Kernel Compilation](https://wiki.archlinux.org/index.php/Kernel#Compilation)
- [Upgrade Kernel on ArchLinux](https://linuxhint.com/upgrade-kernel-on-arch-linux/)
- [What is initramfs?](https://www.kernel.org/doc/Documentation/filesystems/ramfs-rootfs-initramfs.txt)

## Explanation

### Installing Linux Kernel

So what the problem statement is really asking one to change the Linux kernel that their
Linux distro is currently using, into a new one. Specifically it asks us to get the
latest Linux kernel from Linus Torvald's tree, compile it, install it, and finally run it.
Since Linux kernel can support for billions of different devices out there, it has quite
a complex configuration. Even to understand each and every one of the configurations, it
is a daunting process. So the easiest way to get started is to use the configuration that
the currently running distro is using.

This task is highly distro-specific. So you might have search around for how to do
certain steps on your distro. The example below is for Arch Linux, which is the distro
I've been using very happily for a few years.

#### Getting Latest Linux Kernel Source Code

- First go to [Kernel.org git repositories](https://git.kernel.org) which hosts
  the different open source projects.
- Then search for Torvald, and find his linux repository. Which would be
  [this](https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git)
- I'd suggest doing a shallow clone:
    ```git clone https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git --depth 1```

#### Using Current Distro's Configuration

- Kernel config is stored in the file named .config on the root directory of kernel source
- Current kernel config can be found under /proc/config.gz
- So let's copy it over ```zcat /proc/config.gz > .config```

#### Enabling CONFIG_LOCALVERSION_AUTO

One might be tempted to just open .config file, search for CONFIG_LOCALVERSION_AUTO and change its value, 
but that's not a correct way to modify kernel config. The problem is because some kernel settings are
dependent on other settings. In order for it to be enabled/disabled, there could be some other deendencies
that need to also be enabled/disabled.

Because of that, a proper way of modifying kernel config is through the provided UI which would automatically
manages the dependencies. There are different ways of doing it, but one is through ```make menuconfig```.
When the UI is opened, press / key and type LOCALVERSION to search where to modify it.

#### Building Linux Kernel

Linux kernel build system uses make. If you're building on the target machine (i.e. the same architecture)
then simply run the following command. Optimize the number of the number jobs (-j) according to the
number of cores your processor have.

```bash
make -j4
```

#### Installing Kernel Modules

After the compilation is done, a kernel image would be generated (i.e. arch/x86_64/boot/bzImage).
The next step is to copy over the kernel modules that are compiled by the previous steps, into the
disk. Remember from Task 1 we learned that one of the motivations behind Linux kernel modularization
is to reduce memory usage. While kernel image is loaded on the memory throughout its runtime we don't
want unused modules to also be hogging up the memory, and that's why they're stored on the disk

```bash
sudo make modules_install
```

The command would copy over the compiled modules, typically into /lib/modules/[KERNEL VERSION] directory, which is the default place to store version-specific kernel modules. To see get [KERNEL VERSION] of the compiled kernel 'file' command can be used like the following:

```bash
file arch/x86_64/boot/bzImage
```

Which would print out information about the file, including KERNEL VERSION, such as:

```text
../../x86/boot/bzImage: Linux kernel x86 boot executable bzImage, version 5.7.0-rc2-gb2768df24 (aharijanto@aharijanto-S3) #1 SMP PREEMPT Sun Apr 26 23:21:40 +08 2020, RO-rootFS, swap_dev 0x6, Normal VGA
```

#### Generating initramfs for Kernel Booting

The next step is to generate initramfs image. It is a basic root filesystem image that
is used by the kernel to boot. In can be generated using 'mkinitcpio' command, which
takes the KERNEL VERSION as its input. It would look into /lib/modules/[KERNEL VERSION] in order to pick up the necessary files:

```bash
sudo mkinitcpio -k 5.7.0-rc2-gb2768df24 -g /boot/initramfs-5.7.0-rc2-gb2768df24.img
```

When run, the command above would generate initramfs-5.7.0-rc2-gb2768df24.img file
whose content would be mounted by the kernel as files.

#### Updating Bootloader

We've finally compiled and generated all the files that can be used by a computer
to boot. The next step is to update bootloader's configuration to use it.

There are different bootloaders out there, but this tutorial is specifically
for the bootloader I'm using, which is GRUB.

Before booting into Linux, GRUB has a UI that is shown where user can
choose which kernel to boot from. This UI uses the configuration under
/boot/grub/grub.cfg. One can modify by opening it and adding new 'menuentry'
with 'linux' and 'initrd' variables pointed to the specific kernel and
initramfs to be used.

An easier way of modifying GRUB config file is by having
'grub-mkconfig' to auto-generate it for us. In order to have it generate
one for our own build, we have to first copy the kernel and initramfs into
the /boot/ directory, suffixed by KERNEL VERSION.

``` bash
sudo cp [KERNEL DIR]/arch/x86_64/boot/bzImage /boot/vmlinuz-5.7.0-rc2-gb2768df24
sudo mkinitcpio -k 5.7.0-rc2-gb2768df24 -g initramfs-5.7.0-rc2-gb2768df24.img
```

Then try running grub-mkconfig command and see if it spits out a new menuentry
with our compiled kernel.

```bash
sudo grub-mkconfig | less
```

If everything is correct, it should create a new 'menuentry' with its 'linux'
and 'initrd' pointing to our kernel and initramfs files, such as:

```text
        menuentry 'Arch Linux, with Linux 5.7.0-rc2-gb2768df24' --class arch --class gnu-linux --class gnu --class os $menuentry_id_option 'gnulinux-5.7.0-rc2-gb2768df24-advanced-06dc5093-62a9-4af7-bfd7-a02fa5775a18' {
                load_video
                set gfxpayload=keep
                insmod gzio
                insmod part_msdos
                insmod ext2
                set root='hd0,msdos1'
                if [ x$feature_platform_search_hint = xy ]; then
                  search --no-floppy --fs-uuid --set=root --hint-ieee1275='ieee1275//disk@0,msdos1' --hint-bios=hd0,msdos1 --hint-efi=hd0,msdos1 --hint-baremetal=ahci0,msdos1  06dc5093-62a9-4af7-bfd7-a02fa5775a18
                else
                  search --no-floppy --fs-uuid --set=root 06dc5093-62a9-4af7-bfd7-a02fa5775a18
                fi
                echo    'Loading Linux 5.7.0-rc2-gb2768df24 ...'
                linux   /boot/vmlinuz-5.7.0-rc2-gb2768df24 root=UUID=06dc5093-62a9-4af7-bfd7-a02fa5775a18 rw  audit=0 loglevel=3 quiet
                echo    'Loading initial ramdisk ...'
                initrd  /boot/initramfs-5.7.0-rc2-gb2768df24.img
        }
```

If all is well, make a backup of current grub config file, so in case for some
reasons we can't boot, we can revert it back. After that, run grub-mkconfig again, but this time have it write to file.

```bash
sudo grub-mkconfig | sudo tee /boot/grub/grub.cfg
```

After that, try to reboot, and when GRUB UI prompts for kernel version
to choose, pick our compiled one.
