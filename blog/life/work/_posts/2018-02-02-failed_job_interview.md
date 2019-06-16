---
title: "Reminiscing on a failed job interview"
layout: post
author: Brandon Nguyen
categories: [life, work]
tags: [internship, job interview, nvidia]
excerpt_separator: <!--more-->
---

*This post is a copy from my old website and blog. I have kept its original post date.*

So in the summers of 2016 and 2017 I interned for NVIDIA’s Tegra Software, Camera teams,
with the first stint in the Controls team and my second stint in the Performance team.
I didn’t go for my return offer to the same team, instead opting to interview for a different team.

<!--more-->

Around the November 2017 time-frame I had a technical phone interview with an engineer
for an internship on a prospective team that my recruiter cryptically said was under “GPU-SW”.
I did some LinkedIn snooping and found that my interviewer had a significant Bio/BME background,
getting one of his masters’ in CS. Something that I should have paid attention to were that his
skills were primarily in the web sphere, covering front and backend stuff.
If you didn’t know, I am more of an embedded/systems guy who loves to pore over datasheets
and man-pages and applies for positions that reflect this.

Nevertheless, seeing that I would be interviewing for some internship in “GPU-SW”,
I proceeded to refresh my memory and bring into my mental cache with computer architecture
and operating systems knowledge.
Not once did I look at any HackerRank, LeetCode, or CTCI-type algorithms problem.

When the interview came, I was informed that this position was for the Android Platform team
whose duties include building board support packages for the various Shield and Tegra products.

My first question was to write a C function that would remove all white-space from a C string,
resulting in a C string that had all words concatenated together as a result of the removed white-space.
I sorta flubbed up the beginning, but with a hint of using a read and write pointer for the string,
I proceeded to successfully solve the problem.

My next questions were about C and Java languages.
I was asked what `malloc()`, `realloc()`, `calloc()`, and `free()` do.
Having not used `calloc()` before, I told the interviewer that I didn’t know what it did.
The interviewer was more or less satisfied with my answer.
I kind of wish that the question was how to implement the functions :).
Next, I was asked about what each word in `public static void main(String[] args)` in Java meant.
I proceeded to tell him about how public methods are visible to all other classes,
how the static keyword indicated that this function does not utilize
(and thus doesn’t need to be called with) an instance of the class,
and that the main function indicates that this class can be run as the driver for a Java program.
The interviewer didn’t seem too happy or disappointed about the answer.

My final question was, in my opinion, a doozy.
I had to write a Java method that determined if a singly-linked list was a palindrome.
I spent a lot of time mulling around before a eureka moment about using a slow and fast node
reference where the fast reference advanced two nodes.
However, I was unable to figure out how exactly to utilize these to solve the problem.

In the end, I failed this interview and didn’t get the position.
However, I wasn’t too distraught: I was not that interested in the position
after I heard exactly what it was.
I was also able to take away that despite my own strong opinions about (and aversion to)
CTCI/common interview questions, I should still study/work at them as to remain competitive in interviews.
I do wish that I would get asked more systems programming questions, though :(.
