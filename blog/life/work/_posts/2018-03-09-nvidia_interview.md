---
title: "Technical interview with NVIDIA"
layout: post
author: Brandon Nguyen
categories: [life, work]
tags: [internship, job interview, nvidia]
excerpt_separator: <!--more-->
---

*This post is a copy from my old website and blog. I have kept its original post date.*

This happened about a month ago, two days after the Valentine's day post.
I didn’t really get a chance to make a post on reflect on it, but I’ve got some time now.

So a while back I made a [post](/blog/life/work/2018/02/03/another_nvidia_interview)
about how I had another interview with NVIDIA with the Director of Linux Software.
Turns out it was a behavioral interview with the director acting as the hiring manager.
He told me about the team and what products they were involved with (hint hint: it’s related to Linux).
Anyway, it was pretty uneventful, and I soon scheduled my 2nd interview.

<!--more-->

The 2nd interview was a technical one with one of the engineers.
The first question was about what the keyword “volatile” meant in C.
Easy enough: it marks a variable as one that can be modified independently of the thread of execution,
so it is to not be cached in a register and must be loaded from memory every time.

The next question was describe a deadlock and how to prevent one.
I had more of an issue with this: I never really did any concurrent work,
but I was able to describe a deadlock. Describing the prevention of a deadlock was harder:
I settled on making sure that the order of resource locking and unlocking happened in a consistent manner,
which was an answer the interviewer seemed content with.

My third and last question was a programming question: find a decimal palindrome passed in as a `uint32_t`.
I made a joke about the cop out solution being to use `sscanf()` to build a string version and do a
string palindrome check.
More seriously, I noted that it being a `uint32_t` I already knew the max number of digits possible
(10 for 4 billion-ish), so you could allocate a 10 byte buffer on the stack to hold digits,
use another variable to keep track of the number of digits, and perform a modulo-divide to extract each digit.
From that point on, with the knowledge of how many digits there were you could check for the palindrome using
index 0 and the number of digits – 1 and working inwards (ironically, pretty much the same way as doing
it as with a string).
The interviewer was satisfied with the solution, and then asked me what the time complexity is,
in terms of N being the number. I worked through it aloud: it requires 2 traversals of all the digits,
and the number of digits is log<sub>10</sub>(N), so the time complexity would be O(log<sub>10</sub>(N)).
They were happy with the answer.

After this, the interviewer asked me about the projects on my resume.
I told them about the “Power Glove” project my friend Ryan and I did in EE 445L last year,
and told them the journey of debugging the host side driver.
Next they asked me about the [LCCC (Little Computer Compiler Collection)](https://github.com/aeturnus/lccc)
project that I was working on.
I told them about the pitiful state of the tools for LC-3 and that I was currently working on designing
a binary format based on ELF to replace the primitive old one, and that I was currently digesting
the ELF specification to see what would be needed or not in the format
(such as PLTs). The interviewer was pretty helpful: they suggested a document
by Ulrich Drepper about dynamic shared objects.

After this, the interviewer asked if I had any questions for them.
I asked them about the structure of the Linux driver team, and how much theyinteracted with X11, OpenGL,
and Vulkan: they said that this team would focus more on the driver itself,
but the engineers did dabble in those above technologies.

This is a team that I actually am really interest in working with.
Currently (2018-03-09), I haven’t heard anything back from the recruiters.
This seems like a long time, but at least I haven’t gotten bad news!
