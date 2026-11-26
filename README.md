# Introduction to Programming with Modern C++

A beginner's programming textbook that teaches programming from scratch in **C++23**. It is an adaptation of the University of Helsinki's [Java Programming MOOC](https://java-programming.mooc.fi/): the same fourteen-part structure and the same kinds of exercises, rewritten for modern C++ — `std::println`, `std::string`, `std::vector`, value semantics, RAII, `std::unique_ptr`, ranges, lambdas, templates and concepts, with raylib for the graphical chapters.

## Contents

| Chapter | File | Topics |
|---|---|---|
| — | [Preface](chapters/00-preface.md) | How the book works, setting up a compiler and CMake |
| 1 | [Getting Started](chapters/01-getting-started.md) | Printing, input, variables, arithmetic, conditionals |
| 2 | [Loops and Functions](chapters/02-loops-and-functions.md) | Problem-solving patterns, loops, functions, the call stack |
| 3 | [Vectors, Arrays and Strings](chapters/03-vectors-arrays-strings.md) | Debugging, `std::vector`, `std::array`, `std::span`, strings |
| 4 | [Objects and Files](chapters/04-objects-and-files.md) | Classes, objects in vectors, reading files |
| 5 | [Classes in Depth](chapters/05-values-and-references.md) | Overloading, values, references, pointers, `std::optional`, `operator==` |
| 6 | [Larger Programs and Testing](chapters/06-larger-programs-and-testing.md) | Objects containing objects, UI vs. logic, Catch2, TDD |
| 7 | [Paradigms and Algorithms](chapters/07-paradigms-and-algorithms.md) | Paradigms, sorting, searching, larger exercises |
| 8 | [Hash Maps](chapters/08-hash-maps.md) | `std::unordered_map`, `std::map`, `std::hash`, grouping, sets |
| 9 | [Inheritance and Polymorphism](chapters/09-inheritance-and-polymorphism.md) | Inheritance, `virtual`, abstract classes, interfaces, `std::unique_ptr` |
| 10 | [Ranges, Lambdas and Ordering](chapters/10-ranges-and-ordering.md) | Lambdas, views, `<=>`, regex, `enum class`, iterators, formatters |
| 11 | [Structure, Exceptions and Files](chapters/11-structure-exceptions-files.md) | Class diagrams, headers/sources, namespaces, exceptions, writing files |
| 12 | [Templates and Containers](chapters/12-templates-and-containers.md) | Templates, concepts, building a vector and a hash map, `<random>`, grids |
| 13 | [Graphical User Interfaces](chapters/13-graphical-user-interfaces.md) | raylib + raygui, layout, events, multiple views |
| 14 | [Visualisation, Games and Libraries](chapters/14-visualisation-games-libraries.md) | Charts, drawing, images, sound, an Asteroids game, CMake, SQLite |

The book contains 262 exercises. Each exercise has a starter folder under [`exercises/`](exercises), named after the corresponding exercise of the original course (for example `exercises/part03/03_17_RemoveLast`).

## Building the exercises

You need a C++23 compiler with a recent standard library (GCC 15+, Clang 19+ with libc++, or Visual Studio 2022 17.10+) and CMake 3.25+.

```
cmake -S exercises -B build -DBUILD_TESTED_EXERCISES=OFF
cmake --build build
./build/part01/01_01_Sandbox/01_01_Sandbox
```

`-DBUILD_TESTED_EXERCISES=OFF` skips the exercises with unit tests, so the first build needs no network access. When you reach the testing part of chapter 6, turn them back on. CMake then downloads Catch2 from GitHub:

```
cmake -S exercises -B build -DBUILD_TESTED_EXERCISES=ON
cmake --build build
ctest --test-dir build
```

Every exercise becomes its own program in `build/partNN/<exercise>/`. Data files are copied into that folder too. Programs open them relative to the folder you start them from, so run exercises that read files from their own folder:

```
cd build/part14/14_07_Collage
./14_07_Collage
```

The graphical exercises of chapters 13–14 (raylib, raygui, SQLite — downloaded automatically) are built only on request:

```
cmake -S exercises -B build -DBUILD_GRAPHICAL_EXERCISES=ON
```

On Linux this needs the X11/OpenGL development packages (`libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl1-mesa-dev` on Ubuntu). Exercises with unit tests use Catch2 (see above); run them with `ctest --test-dir build`.

`scripts/check-exercises.sh` and `scripts/check-graphical.sh` compile the templates quickly without CMake.

## Dev container

[`.devcontainer/`](.devcontainer) contains a development container with everything preinstalled: GCC 15, CMake, Ninja, GDB, clang-format, raylib's build dependencies and pandoc 3. In VS Code, install the *Dev Containers* extension and choose **Reopen in Container**; CMake Tools is preconfigured for the `exercises/` folder with the graphical exercises enabled. GitHub Codespaces uses the same configuration.

Without VS Code:

```
docker build -t cpp-intro-dev .devcontainer
docker run --rm -it -v "$PWD":/workspace cpp-intro-dev
```

The graphical exercises compile in the container, but showing their windows needs a display: on Linux, pass your X server in (`-e DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix`). Otherwise run the graphical programs on the host.

## Building the book

The book is plain Markdown. To build the EPUB locally, install [pandoc](https://pandoc.org/) and run:

```
bash scripts/build-epub.sh
```

The result is `dist/cpp-intro-to-programming.epub`.

## Releases

The GitHub Actions workflow [`.github/workflows/epub-release.yml`](.github/workflows/epub-release.yml) builds every exercise (in a GCC 15 container, graphical exercises included), runs the unit tests and builds the EPUB on every push and pull request. The EPUB is attached to each run as an artifact.

To publish a release with the EPUB attached, push a version tag:

```
git tag v1.0.0
git push origin v1.0.0
```

or run the workflow manually from the *Actions* tab and enter a version.

## License and attribution

This work is an adaptation of [*Java Programming*](https://java-programming.mooc.fi/) by the Agile Education Research Group of the University of Helsinki (MOOC.fi), used under the [Creative Commons Attribution-NonCommercial-ShareAlike 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/) license. The text has been rewritten for C++ and the exercises have been adapted; the adaptation is distributed under the same license. See [LICENSE](LICENSE).

Third-party data and media in the exercise folders are credited in the `SOURCE.md` file next to them.
