# Task 04

## Problem Statement

Wonderful job in making it this far, I hope you have been having fun.
Oh, you're getting bored, just booting and installing kernels?  Well,
time for some pedantic things to make you feel that those kernel builds
are actually fun!

Part of the job of being a kernel developer is recognizing the proper
Linux kernel coding style.  The full description of this coding style
can be found in the kernel itself, in the Documentation/CodingStyle
file.  I'd recommend going and reading that right now, it's pretty
simple stuff, and something that you are going to need to know and
understand.  There is also a tool in the kernel source tree in the
scripts/ directory called checkpatch.pl that can be used to test for
adhering to the coding style rules, as kernel programmers are lazy and
prefer to let scripts do their work for them...

And why a coding standard at all?  That's because of your brain (yes,
yours, not mine, remember, I'm just some dumb shell scripts).  Once your
brain learns the patterns, the information contained really starts to
sink in better.  So it's important that everyone follow the same
standard so that the patterns become consistent.  In other words, you
want to make it really easy for other people to find the bugs in your
code, and not be confused and distracted by the fact that you happen to
prefer 5 spaces instead of tabs for indentation.  Of course you would
never prefer such a thing, I'd never accuse you of that, it was just an
example, please forgive my impertinence!

Anyway, the tasks for this round all deal with the Linux kernel coding
style.  Attached to this message are two kernel modules that do not
follow the proper Linux kernel coding style rules.  Please fix both of
them up, and send it back to me in such a way that does follow the
rules.

What, you recognize one of these modules?  Imagine that, perhaps I was
right to accuse you of the using a "wrong" coding style :)

Yes, the logic in the second module is crazy, and probably wrong, but
don't focus on that, just look at the patterns here, and fix up the
coding style, do not remove lines of code.

```c
#coding_style.c

#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/delay.h>
#include <linux/slab.h>

int do_work( int * my_int, int retval ) {
int x;
int y=*my_int;
int z;

for(x=0;x< * my_int;++x) {
	udelay(10);
}

if (y < 10 )
	// That was a long sleep, tell userspace about it
	printk("We slept a long time!");

z = x * y;

return z;


}

int
my_init (void)
{
int x = 10;

x = do_work(&x, x);

return x;


}

void my_exit( void )
{
return;
}

module_init(my_init);
module_exit(my_exit);
```

## Theory

### Summary

First off, go read the documentation about coding-style :)
After that, practice the theory by updating the code. Finally
try to run format-checker script on the Linux source tree:

```bash
./scripts/checkpatch.pl -f /home/aharijanto/Programming/tutorial/eudyptula/task4/coding_style.c
```

The `-f` flag is required because otherwise the script expects
a diff file instead of source code by default. When runned,
the script spits out the warnings and errors on the source code.
It looks like this:

```text
ERROR: space prohibited before that close parenthesis ')
#16: FILE: /home/aharijanto/Programming/tutorial/eudyptula/task4/coding_style.c:16:
+       if (y < 10 ) {
```

After fixing all the formatting issue, make sure that the code
compiles. I've created a Makefile adapted from Task 1, to make
sure that the code compiles fine. Compile as usual using `make`
command.

In order to further familiar yourself with Linux kernel coding
style, I'd recommend reading on certain self-contained modules,
such as the list data-structure implementation located here:

```text
vim [LINUX TREE]/linux/include/linux/list.h
```

### Required Reading

- [Linux Kernel: Coding Style](https://www.kernel.org/doc/html/v4.10/process/coding-style.html)