---
title: "x86-64 Assembly on Linux"
layout: post
author: Brandon Nguyen
date: 2020-04-25 01:36:00
categories: []
tags: [linux, assembly, x86-64]
excerpt_separator: <!--more-->
---

# Introduction
So it's been a busy (and rough) semester effectively rebuilding and teaching
[EECS 201](https://www.eecs.umich.edu/courses/eecs201) at the University of Michigan.
Grades have finally been posted, so I decided to treat myself to some good ol' systems programming
before getting back into the research grind.
What better way to unwind than hardcore assembly programming?
<!--more-->

I'm going to admit that I'm no expert at x86-64 programming, having only dabbled a bit in x86
when I was "auditing" good ol' Gheith's computer architecture and operating systems courses at UT.
In addition my classes back then that did deal in some sort of assembly already had a toolchain
and build system provided, so I never really got a hands-on feel for such low level building
(I do have a more conceptual, academic understanding though).

I figured that I would kill two birds with one stone (no birds harmed) by writing a "Hello, world"
program from scratch with no outside instruction besides the official documentation for the
GNU utilities and Linux itself. A lot of times information gets elided for sake of time
or brevity with details lost when being informed by others: I've learned a lot teaching EECS 201
just by referring to primary sources for all of the tools that I introduced to students.

# What I knew
Being the architecture-systems software weirdo I am, I already had a fairly decent understanding
of what would be involved: an assembly program assembled into an ELF object, which then
has to be linked into an actual executable with a `_start` symbol as a default
(but configurable) entry point.

For the program itself, just getting it to print "Hello, world!" simply involves:
* Having a (constant) string in memory
* Make a `write` syscall to `stdout`
* Make an  `exit` syscall to cleanly end the process, lest it wander into the unmapped void

This code would be in the `.text` section of a program, being constants and code.
But, I wasn't 100% sure on the details, so I decided to find what info I could in the documentation.

# Documentation hunt
After a bit of stumbling around, I noticed in the manpage for `as` (the GNU Assembler) a reference
to "Info" documents. Naturally, I ran `$ man info` which let me know of the existence of Info documents
which let me look at the Texinfo-produced manuals for various utilities.

This was a huge step, so I immediately took to looking at that Info pages for `as` and `ld` (the GNU Linker).
There I confirmed what program sections `as` supported out of the box with its directives along with the
context of the sections: I would place my string constant in the `.text`. The part on sections
also handily brought my attention to the `.ascii` directive for a (non-null terminated) string constant.
In addition I learned a bit more on declaring symbols: a symbol starting with `.L` would indicate
that a symbol is local on ELF systems.

I'm going to admit that not everything can be found through Linux documentation:
I had to look up what sort of x86-64 calling convention is done on Linux systems,
learning that it was the [System V ABI](https://github.com/hjl-tools/x86-psABI/wiki/x86-64-psABI-1.0.pdf),
and found the [x86-64 ISA documentation](https://developer.amd.com/resources/developer-guides-manuals/) to keep on hand
(AMD actually designed the 64-bit x86 ISA, hence you see references to AMD64. I found Intel's manual on its "Intel 64",
but I prefer AMD's since, besides AMD being the original designer, Intel's manual also bundles in "IA-32" or the 32-bit x86).

That looks like it would be enough to get me started!

# Hello, world!
`hello.s`
```asm
.text
.Lstring: .ascii "Hello, world!\n"

_start:
```

Well that's a `_start`!

From here, I needed to figure out how to make a syscall.
`$ man 2 syscall` would elucidate me here (as well as really point out to me how C-oriented the documentation
is: it's highly encouraged to go through the C wrappers for everything!): the manpage provided the info
on x86-64 systems on how to make the syscall: pass the syscall number through `rax` and then the arguments
through `rdi`, `rsi`, `rdx`, `r10`, `r8`, and `r9` (which is similar to the System V ABI function call),
then execute the `syscall` instruction.

Cool, time to go look at the `write` system call! In our handy dandy manpage (`$ man 2 write`),
we get all the arguments needed. But note what's missing: the actual syscall number (and thus
the above-assembly oriented nature of the documentation strikes again).
If you look at the `syscalls` manpage, the Notes section mentions how you can find them in
the `/usr/include/asm/unistd.h` under the `__NR_xxx` defines. After going through
the goose chase of other header includes (this becomes a recurring theme),
mine were finally found in `/usr/include/asm/unistd_64.h`, and `write` is syscall #1.

`hello.s`
```asm
.text
.Lstring: .ascii "Hello, world!\n"

_start:
    # write(STDOUT_FILENO, .Lstring, 14)
    mov $1, %rax        # write is sycall 1
    mov $1, %rdi        # stdout is fd 1
    mov $.Lstring, %rsi # the string's buffer
    mov $14, %rdx       # how long the string is
    syscall
```
(At this point I got excited and forgot to do `exit`).

I'm using AT&T syntax simply because this is a \*nix system and the default for `as`.
Being more familiar with ARM's and other assembly languages, with the right-to-left flow feeling more natural for me (it resemblng assignments), and being annoyed at having to delimit every register with a `%`, I actually strongly prefer Intel syntax.


Time to assemble it! An `as -o hello.o hello.s` and an `ld -o hello hello.o` later and...
```
$ as -o hello.o hello.s
$ ld -o hello hello.o
ld: warning: cannot find entry symbol _start; defaulting to 000000000040100
```

Huh, it can't find `_start` to set as the entry point?
After perusing the `as` Info pages some more, I found out about the `.global` directive
that makes symbols visible to the linker.

Now:

`hello.s`
```asm
.text
.Lstring: .ascii "Hello, world!\n"

.global _start
_start:
    # write(STDOUT_FILENO, .Lstring, 14)
    mov $1, %rax        # write is sycall 1
    mov $1, %rdi        # stdout is fd 1
    mov $.Lstring, %rsi # the string's buffer
    mov $14, %rdx       # how long the string is
    syscall
```

After assembling and running it, I get the "Hello, world!", but get a segfault.
That's when I realized that I forgot to `exit`:

`hello.s`
```asm
.text
.Lstring: .ascii "Hello, world!\n"

.global _start
_start:
    # write(STDOUT_FILENO, .Lstring, 14)
    mov $1, %rax        # write is sycall 1
    mov $1, %rdi        # stdout is fd 1
    mov $.Lstring, %rsi # the string's buffer
    mov $14, %rdx       # how long the string is
    syscall

    # exit(0)
    mov $60, %rax       # exit is syscall 60
    mov $0, %rdi        # exit with a 0: success!
    syscall
```

And now we have a clean, beautiful "Hello, world!" :)
```
$ ./hello
Hello, world!
$ echo $?
0
```

# Conclusion
This was a really fun exercise: maybe I'm weird enjoying looking at manuals
and other documentation and programming assembly.
There's a lot of little gotchas that get in the way,
but they only let you learn more!

# Extra

## Entry point
I decided to also play around with `ld` in changing up what the entry point
of the program was using the `--entry` option. Now I can enter at `main` instead of `_start`
to prevent any C-induced confusion :)

## `.rodata`
`objdump -d` picks up on everything in the `.text` section as code: not surprising
as, going by the ELF Info pages (`$ info elf`) the `.text` section is for read-only code.
Looking through the Info pages some more, I saw the `.rodata` section that's meant for read-only data.

Using the power of the `.section` directive:

`hello.s`
```asm
.section .rodata
.Lstring: .ascii "Hello, world!\n"

.text
.global _start
_start:
    # write(STDOUT_FILENO, .Lstring, 14)
    mov $1, %rax        # write is sycall 1
    mov $1, %rdi        # stdout is fd 1
    mov $.Lstring, %rsi # the string's buffer
    mov $14, %rdx       # how long the string is
    syscall

    # exit(0)
    mov $60, %rax       # exit is syscall 60
    mov $0, %rdi        # exit with a 0: success!
    syscall
```

Now `objdump -d` doesn't print out the string :)
