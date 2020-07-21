# README

## Problem Statement

### This is Task 07 of the Eudyptula Challenge

Great work with that misc device driver.  Isn't that a nice and simple
way to write a character driver?

Just when you think this challenge is all about writing kernel code,
this task is a throwback to your second one.  Yes, that's right,
building kernels.  Turns out that's what most developers end up doing,
tons and tons of rebuilds, not writing new code.  Sad, but it is a good
skill to know.

The tasks this round are:

- Download the linux-next kernel for today.  Or tomorrow, just use
the latest one.  It changes every day so there is no specific one
you need to pick.  Build it.  Boot it.  Provide proof that you built
and booted it.

What is the linux-next kernel?  Ah, that's part of the challenge.

For a hint, you should read the excellent documentation about how the
Linux kernel is developed in Documentation/development-process/ in the
kernel source itself.  It's a great read, and should tell you all you
never wanted to know about what Linux kernel developers do and how they
do it.

As always, please respond to this challenge with your id.  I know you
know what it is.  I'll not even include it this time, I trust you.
Don't make me feel that is a mistake.

## Theory

### linux-next Tree

All the information required to build, compile, and run linux-next tree is already covered on
the very first few tasks. So technically speaking, there's nothing needs to be explained here.
Although this task might sound boring to some people, I highly encourage everyone to read through
the documentation mentioned on the task description.There's a lot of "gold of information" to
be learned by reading through Linux kernel development process. Afterall, Linux kernel is one of
the largest active open-source project in the world, both in terms of project's size and the number
of collaborators.

What I really like about Linux's process is its simplicity and "cleanliness". Coming from userspace world,
I've been seeing a lot of projects rely on a lot of overly complex and bloated tools. These days, it's not
unusual to see a simple frontend website project development requiring at leasy 16GB of RAM to run efficiently.
As computer hardware becomes a lot cheaper, more people seem to care less about building system that's resource
efficient and simple. On the other hand, many aspects of Linux kernel, including its development
process, is very simple and efficient. If I were to guess why, I think it's because a lot of Linux kernel
experts are very experienced engineer who used to work on a very resource-constrained environment back in the
80s and 90s. An interesting fact: GIT was originally authored by Linus Torvald -- the author of Linux -- as a way
to acommodate better collaboration between the large number of contributors. Regardless whether one has an
intention to eventually becoming a contributor to Linux kernel or just learning it as a hobby, learning it is
a valuable resource to make one a better software engineer.
