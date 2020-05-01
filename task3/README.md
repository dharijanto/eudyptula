# Task 03

## Problem Statement

This is Task 03 of the Eudyptula Challenge

Now that you have your custom kernel up and running, it's time to modify
it!

The tasks for this round is:

- take the kernel git tree from Task 02 and modify the Makefile to
and modify the EXTRAVERSION field.  Do this in a way that the
running kernel (after :modifying the Makefile, rebuilding, and
rebooting) has the characters "-eudyptula" in the version string.
- show proof of booting this kernel.  Extra cookies for you by
providing creative examples, especially if done in intrepretive
dance at your local pub.
- Send a patch that shows the Makefile modified.  Do this in a manner
that would be acceptable for merging in the kernel source tree.
(Hint, read the file Documentation/SubmittingPatches and follow the
steps there.)

## Theory

All the technical knowledge required to solve this challenge is
already covered in task 2. What remains is understanding Linux
kernel path submission process. The nitty-gritty details about
submitting a kernel patch can be found on the aforementioned
documentation file, which can also be found in HTML format.

The documentation covers up so many cases. But don't be discouraged
but the sheer amount of information that's there. In order create
a patch for this task, we don't need to understand everything.
And as always, practice is the best way to learn.

### Recommended Readings

- [Linux Kernel: Submitting Patches](https://www.kernel.org/doc/html/latest/process/submitting-patches.html)

### Modiying EXTRAVERSION

This is done by opening Makefile and append "-eudyptula" onto
EXTRAVERSION variable. After that, simply re-compile the kernel
and install the kernel as described on Task 2.

After the kernel is installed, reboot and run ```uname -a```
and see make sure that the suffix we added into the kernel config
appears.

### Creating Patch

First off, make the change to the Makefile. Afterwards, stage
the change and commit using ```git commit -s``` where -s would
auto-generate "Signed-off-by" at the end of the file. Make sure
to follow the guideline for writing out commit header and body.

After commited, generate a patch file using ```git format-patch origin/master --stdout``` where origin/master is the reference point to compare our current tree into. After that, a patch would
be generated.

Neatly, a lot of the instructions specified on the documentation
are automatically handled by Git. And the reason is because Git
was originally invented by Linus Torvalds, the founder of Linux,
in order to help with Linux kernel collaboration.

Having seen how Git makes it easy to create patch for this
particular task, be sure to read through the submission guideline before making contribution. I've heard stories about people having
spent a lot of their time working on patches, ended up being disappointed because the maintainers wouldn't take the patches as
they're not following the guildeline.