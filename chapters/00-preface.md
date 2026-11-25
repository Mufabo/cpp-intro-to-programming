# Preface

This book teaches programming from scratch. It assumes no earlier experience: if you can use a computer and are willing to type, run, break and fix a lot of small programs, you have everything you need.

The language of the book is **modern C++** — specifically C++23. C++ has a reputation for being difficult, and older textbooks earned it that reputation: they started with pointers, manual memory management and arcane input/output. We take the opposite route. From the first chapter we use the parts of the language that make everyday programming pleasant — `std::println` for output, `std::string` for text, `std::vector` for lists, classes with automatic cleanup, ranges and lambdas — and we postpone the sharp tools until you have a reason to want them.

## Where this book comes from

The structure, the order of topics and most of the exercise ideas follow the University of Helsinki's *Java Programming* MOOC (MOOC.fi), one of the most successful introductory programming courses in the world. Its material is published under the Creative Commons BY-NC-SA 4.0 license, and this book is an adaptation released under the same license.

"Translating" a course from Java to C++ is not a word-for-word job. Some ideas map directly (a `while` loop is a `while` loop), some need a different explanation (C++ objects are *values*, not references), and some need a different tool entirely (the Java course builds graphical programs with JavaFX; we use the raylib library). Where the languages differ, the book says so and explains the C++ way of thinking.

## How the book is organised

There are fourteen chapters. Each corresponds to one week-sized *part* of the original course.

| Chapter | Topics |
|---|---|
| 1 | Printing, reading input, variables, arithmetic, conditionals |
| 2 | Problem-solving patterns, loops, functions |
| 3 | Finding errors, `std::vector`, arrays, strings |
| 4 | Classes and objects, objects in a list, reading files |
| 5 | More object-oriented programming, overloading, values vs. references |
| 6 | Objects inside objects, separating UI from logic, unit testing |
| 7 | Programming paradigms, searching and sorting, larger programs |
| 8 | Hash maps, object equality, grouping data |
| 9 | Inheritance, abstract classes, polymorphism |
| 10 | Ranges and lambdas, ordering objects, handy techniques |
| 11 | Class diagrams, namespaces and headers, exceptions, files |
| 12 | Templates, building your own containers, randomness, 2-D data |
| 13 | Graphical user interfaces with raylib |
| 14 | Visualisation, sound and images, a larger game, CMake and libraries |

Every chapter is full of **exercises**. They are the heart of the book; reading about programming does not teach programming any more than reading about swimming teaches swimming. Each exercise names a folder in the `exercises/` directory of the book's repository, for example `exercises/part01/01_02_AdaLovelace`, which contains a starting `main.cpp` (and sometimes other files).

## Setting up your tools

You need three things:

1. **A C++23 compiler** with a recent standard library. Any of these work:
   - GCC 15 or newer (Linux: from your distribution or a toolchain PPA; Windows: the MSYS2 UCRT64 toolchain),
   - Clang 19 or newer with its libc++ standard library (macOS: `brew install llvm`),
   - Microsoft Visual Studio 2022, version 17.10 or newer (Windows).

   The book uses `std::println` and prints whole containers with it (`std::println("{}", numbers)`); older compilers lack one or both.
2. **CMake 3.25 or newer**, which turns a short project description into build files for your compiler.
3. **An editor.** Visual Studio Code with the *C/C++* and *CMake Tools* extensions is a good free choice; CLion and Visual Studio are excellent too.

To check your setup, clone the repository and build all exercise templates:

```
git clone https://github.com/Mufabo/cpp-intro-to-programming.git cpp-intro
cd cpp-intro
cmake -S exercises -B build
cmake --build build
```

Every exercise becomes a program named after its folder, in a folder of its own. On Linux and macOS you run the first exercise with `./build/part01/01_01_Sandbox/01_01_Sandbox` (on Windows the file ends in `.exe`). Exercises that read data files from Chapter 4 onwards find their files in that same folder, so run those programs from inside it. Editors with CMake support let you pick an exercise from a list and run it with a single click — this is the most comfortable way to work.

If you would rather not use CMake for the small exercises of the first chapters, you can compile a single file directly:

```
g++ -std=c++23 -Wall -Wextra main.cpp -o main
./main
```

The `-Wall -Wextra` flags ask the compiler to warn about suspicious code. Leave them on: warnings are free advice.

## Conventions

Program code looks like this:

```cpp
std::println("Hello world!");
```

Example runs of a program look like this. A line starting with `> ` is something the *user* typed (the `> ` itself is not part of the input):

```
What's your name?
> Ada
Hi Ada
```

Boxes like the one below hold tips, warnings, and notes about how C++ differs from other languages you may meet later.

> **Note.** You do not need to understand every word of a program the first time you see it. The book returns to every topic several times.

Let's begin.
