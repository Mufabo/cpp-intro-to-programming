# Chapter 7: Paradigms and Algorithms

This chapter steps back to look at *styles* of programming, then dives into two classic families of algorithms: sorting and searching. It ends with larger exercises that combine everything from the first half of the book.

## 7.1 Programming paradigms

A **programming paradigm** is a way of thinking about and structuring programs. C++ is a *multi-paradigm* language: it supports several styles, and good C++ programs mix them freely.

### Object-oriented programming

In object-oriented programming, a program is built from objects that combine data and behaviour. Each object is responsible for its own state, and objects cooperate by calling each other's member functions. You have been doing this since Chapter 4.

The strengths of the object-oriented style are **encapsulation** (an object protects its own consistency) and **abstraction** (users of a class need to know *what* it does, not *how*).

### Procedural programming

In procedural programming, a program is a sequence of steps, organised into functions that operate on data passed to them. Chapters 1–3 were procedural: data in variables and vectors, processed by functions.

Procedural code is often the simplest solution for small, linear tasks. Consider a program that controls two liquid containers. Written procedurally, the state is two integer variables and all logic lives in `main`. Written in an object-oriented way, a `Container` class owns its amount and enforces its own limits, and `main` only interprets commands. The procedural version is shorter at first; the object-oriented version is easier to extend (what if we need ten containers?) and to test.

### Other paradigms

C++ supports more paradigms that you will meet later in the book:

- **Generic programming** writes code that works for many types: `std::vector<T>` works for any element type `T`. Chapter 12 shows how to write such code yourself with *templates*.
- **Functional programming** builds programs from functions without side effects, and passes functions around as values. Chapter 10 introduces *lambdas* and *ranges*, which bring this style to C++.

### Exercise 7.1: Liquid Containers (3 parts)

*Template: `exercises/part07/07_01_LiquidContainers`*

Write an interactive program that controls two liquid containers, *first* and *second*, each holding at most 100 litres. Write everything in `main` — a procedural solution, no classes.

The commands are:

- `add amount` — adds the amount to the first container. Anything beyond 100 is lost.
- `move amount` — moves the amount from the first container to the second. If the first holds less, move all of it. The second container cannot exceed 100 either.
- `remove amount` — removes the amount from the second container, or all of it if it holds less.
- `quit` — ends the program.

Negative amounts are ignored. After every command, print the contents of both containers. The template already contains the loop and the `quit` command, and splits each line into a command and an amount.

**Part 1: Adding.**

```
First: 0/100
Second: 0/100
> add 5
First: 5/100
Second: 0/100
> add 1000
First: 100/100
Second: 0/100
> add -5
First: 100/100
Second: 0/100
> quit
```

**Part 2: Moving.**

```
First: 0/100
Second: 0/100
> add 10
First: 10/100
Second: 0/100
> move 20
First: 0/100
Second: 10/100
> quit
```

**Part 3: Removing.**

```
First: 0/100
Second: 0/100
> add 20
First: 20/100
Second: 0/100
> move 15
First: 5/100
Second: 15/100
> remove 5
First: 5/100
Second: 10/100
> remove 20
First: 5/100
Second: 0/100
> quit
```

### Exercise 7.2: Liquid Containers 2.0 (2 parts)

*Template: `exercises/part07/07_02_LiquidContainers2`*

Now the object-oriented version.

**Part 1: Container.** Create a class `Container` with:

- `int contains() const` — the amount of liquid,
- `void add(int amount)` — adds liquid (negative amounts are ignored, maximum 100),
- `void remove(int amount)` — removes liquid (negative amounts are ignored, minimum 0),
- `std::string toString() const` — for example `"32/100"`.

```cpp
Container container;
std::println("{}", container.toString());
container.add(50);
std::println("{}", container.toString());
std::println("{}", container.contains());
container.remove(60);
std::println("{}", container.toString());
container.add(200);
std::println("{}", container.toString());
```

```
0/100
50/100
50
0/100
100/100
```

**Part 2: Functionality.** Rewrite the user interface of the previous exercise using two `Container` objects. It should behave exactly as before. Compare the two solutions: which one is easier to read?

## 7.2 Algorithms

An **algorithm** is a precise, step-by-step procedure for solving a problem. Recipes are algorithms; so are the instructions for assembling furniture. In programming, the study of algorithms is about finding procedures that are *correct* and *efficient*.

Two of the most fundamental problems are **sorting** (putting data in order) and **searching** (finding data). They are worth studying both for their own sake and because they teach how to reason about efficiency.

### Sorting information

Suppose we have a vector of numbers and want it in increasing order. How would you do it by hand with a row of playing cards? A natural approach: find the smallest card and put it first; then find the smallest of the rest and put it second; and so on.

### Selection sort

That approach is called **selection sort**:

1. Find the smallest value in the whole sequence and swap it with the value at index 0.
2. Find the smallest value from index 1 onwards and swap it with the value at index 1.
3. Continue the same way until the end.

```
[8, 3, 7, 9, 1, 2, 4]    smallest from index 0 is 1 (index 4) → swap
[1, 3, 7, 9, 8, 2, 4]    smallest from index 1 is 2 (index 5) → swap
[1, 2, 7, 9, 8, 3, 4]    smallest from index 2 is 3 (index 5) → swap
[1, 2, 3, 9, 8, 7, 4]    smallest from index 3 is 4 (index 6) → swap
[1, 2, 3, 4, 8, 7, 9]    smallest from index 4 is 7 (index 5) → swap
[1, 2, 3, 4, 7, 8, 9]    smallest from index 5 is 8 (index 5) → nothing to do
[1, 2, 3, 4, 7, 8, 9]    sorted
```

You will implement it in the next exercise, building it from smaller functions.

### Exercise 7.3: Sorting (5 parts)

*Template: `exercises/part07/07_03_Sorting`*

All functions take their numbers as a `std::span<int>` (or `std::span<const int>` when they only read), so they work with both arrays and vectors.

**Part 1: The smallest value.** Implement `int smallest(std::span<const int> numbers)`.

```cpp
std::vector<int> numbers = {6, 5, 8, 7, 11};
std::println("Smallest: {}", smallest(numbers));   // Smallest: 5
```

**Part 2: Index of the smallest value.** Implement `std::size_t indexOfSmallest(std::span<const int> numbers)`. For the numbers above it returns 1.

**Part 3: Index of the smallest value from a given index.** Implement `std::size_t indexOfSmallestFrom(std::span<const int> numbers, std::size_t startIndex)`, which only considers indices from `startIndex` onwards.

```cpp
// indices:              0  1  2  3   4
std::vector<int> numbers = {-1, 6, 9, 8, 12};
std::println("{}", indexOfSmallestFrom(numbers, 0));   // 0
std::println("{}", indexOfSmallestFrom(numbers, 1));   // 1
std::println("{}", indexOfSmallestFrom(numbers, 2));   // 3
```

**Part 4: Swapping.** Implement `void swap(std::span<int> numbers, std::size_t index1, std::size_t index2)`. (A `std::span<int>` refers to the caller's elements, so changes through it are visible to the caller.)

```cpp
std::vector<int> numbers = {3, 2, 5, 4, 8};
std::println("{}", numbers);
swap(numbers, 1, 0);
std::println("{}", numbers);
swap(numbers, 0, 3);
std::println("{}", numbers);
```

```
[3, 2, 5, 4, 8]
[2, 3, 5, 4, 8]
[4, 3, 5, 2, 8]
```

**Part 5: Sorting.** Implement `void sort(std::span<int> numbers)` as a selection sort using the functions above. Print the numbers once before sorting and then after each step to watch the algorithm work:

```
[8, 3, 7, 9, 1, 2, 4]
[1, 3, 7, 9, 8, 2, 4]
[1, 2, 7, 9, 8, 3, 4]
[1, 2, 3, 9, 8, 7, 4]
[1, 2, 3, 4, 8, 7, 9]
[1, 2, 3, 4, 7, 8, 9]
[1, 2, 3, 4, 7, 8, 9]
```

### How fast is selection sort?

To sort `n` values, selection sort scans `n` values to find the first minimum, `n − 1` for the second, and so on: about `n²/2` comparisons in total. Doubling the input makes the work four times bigger. We say its **time complexity** is *O(n²)* ("order n squared"). For a thousand values that is half a million comparisons — fine. For a million values it is half a trillion — far too slow.

Better algorithms, such as *merge sort* and *quicksort*, sort in *O(n log n)* time: for a million values about twenty million steps.

### Built-in sorting in C++

You will rarely write a sorting algorithm yourself. The standard library's `std::ranges::sort` (header `<algorithm>`) sorts any vector, array or other random-access sequence in *O(n log n)* time:

```cpp
#include <algorithm>

std::vector<int> numbers = {8, 3, 7, 9, 1, 2, 4};
std::ranges::sort(numbers);
std::println("{}", numbers);   // [1, 2, 3, 4, 7, 8, 9]

std::vector<std::string> words = {"pear", "apple", "fig"};
std::ranges::sort(words);
std::println("{}", words);     // ["apple", "fig", "pear"]
```

It works for any element type that can be compared with `<`. Chapter 10 shows how to sort objects of your own classes, and how to sort in other orders.

### Exercise 7.4: Ready-made Sorting Algorithms

*Template: `exercises/part07/07_04_ReadymadeSortingAlgorithms`*

Implement these functions using `std::ranges::sort`:

- `void sort(std::array<int, 5>& numbers)`,
- `void sort(std::array<std::string, 3>& words)`,
- `void sortIntegers(std::vector<int>& integers)`,
- `void sortStrings(std::vector<std::string>& strings)`.

### Information retrieval

The other classic problem is **searching**: is a value in a collection, and where?

### Linear search

The obvious method checks every element in turn:

```cpp
int linearSearch(const std::vector<int>& numbers, int searched) {
    for (std::size_t i = 0; i < numbers.size(); i++) {
        if (numbers[i] == searched) {
            return static_cast<int>(i);
        }
    }
    return -1;   // not found
}
```

In the worst case — the value is last, or not there at all — linear search looks at all `n` elements: *O(n)*.

### Binary search

If the data is **sorted**, we can do much better. Think of looking up a word in a paper dictionary: you open it in the middle, see whether your word comes before or after, and discard half of the book. Then repeat with the remaining half.

**Binary search** does exactly this:

```
begin = 0
end = size − 1
repeat while begin <= end:
    middle = (begin + end) / 2
    if the value at middle is the searched value: return middle
    if the value at middle is smaller than searched: begin = middle + 1
    otherwise: end = middle − 1
return −1
```

Each step halves the remaining range. A sorted vector of a million values needs at most about 20 steps; a billion values, about 30. Binary search runs in *O(log n)* time.

The standard library provides binary search too: `std::ranges::binary_search(numbers, value)` tells whether the value exists, and `std::ranges::lower_bound` finds where it is (or would be).

### Exercise 7.5: Searching (2 parts)

*Template: `exercises/part07/07_05_Searching`*

The template contains a class `Book` with an `id` and a `name`, and a `main` that creates many books and measures how long the searches take.

**Part 1: Linear search.** Implement `int linearSearch(const std::vector<Book>& books, int searchedId)`, which returns the index of the book with the given id, or `-1`.

**Part 2: Binary search.** Implement `int binarySearch(const std::vector<Book>& books, int searchedId)` using binary search. You may assume the books are sorted by id in increasing order.

Run the program with a large number of books and compare the timings. The difference is dramatic.

## 7.3 Larger programming exercises

The following exercises are larger than the earlier ones. They have no ready-made structure: you decide which classes and functions to create. Spend a moment planning before you start, and build the program step by step.

A suggested process:

1. Read the whole assignment and the examples.
2. Identify the *concepts*: they become classes. Identify the *operations*: they become member functions.
3. Write the user interface loop first, with commands that do nothing yet.
4. Implement one command at a time, running the program after each.

### Exercise 7.6: Grade Statistics (4 parts)

*Template: `exercises/part07/07_06_GradeStatistics`*

Write a program that reads course point totals (integers from 0 to 100) until the user enters `-1`. Other numbers are invalid and are ignored.

**Part 1: Point averages.** Print the average of all valid point totals.

```
Enter point totals, -1 stops:
> 102
> -4
> 33
> 77
> 99
> 1
> -1
Point average (all): 52.5
```

**Part 2: Average of passing points.** Points of 50 or more give a passing grade. Also print the average of the passing points, or `-` if there are none.

```
Point average (passing): 88
```

**Part 3: Pass percentage.** Also print the pass percentage: `100 * passing / participants`.

```
Pass percentage: 50
```

**Part 4: Grade distribution.** Also print the grade distribution, using this table:

| points | grade |
|---|---|
| < 50 | failed, 0 |
| < 60 | 1 |
| < 70 | 2 |
| < 80 | 3 |
| < 90 | 4 |
| ≥ 90 | 5 |

The whole output for the input above:

```
Point average (all): 52.5
Point average (passing): 88
Pass percentage: 50
Grade distribution:
5: *
4:
3: *
2:
1:
0: **
```

### Exercise 7.7: Recipe Search (4 parts)

*Template: `exercises/part07/07_07_RecipeSearch`*

Write a program that reads recipes from a file and lets the user search them by name, cooking time or ingredient. In the file, each recipe takes three or more lines: the name, the cooking time in minutes, and one ingredient per line. Recipes are separated by an empty line. The template folder contains `recipes.txt`:

```
Pancake dough
60
milk
egg
flour
salt
butter

Meatballs
20
ground meat
egg
breadcrumbs

Tofu rolls
30
tofu
rice
water
carrot
cucumber
avocado
wasabi
```

**Part 1: Reading and listing.**

```
File to read:
> recipes.txt

Commands:
list - lists the recipes
stop - stops the program

Enter command:
> list

Recipes:
Pancake dough, cooking time: 60
Meatballs, cooking time: 20
Tofu rolls, cooking time: 30

Enter command:
> stop
```

**Part 2: Finding by name.** The command `find name` asks for a word and lists the recipes whose name contains it.

```
Enter command:
> find name
Searched word:
> roll

Recipes:
Tofu rolls, cooking time: 30
```

**Part 3: Finding by cooking time.** The command `find cooking time` asks for a maximum and lists the recipes whose cooking time is at most that.

**Part 4: Finding by ingredient.** The command `find ingredient` asks for an ingredient and lists the recipes that contain exactly that ingredient (`egg` matches `egg`, but `eg` matches nothing).

```
Enter command:
> find ingredient
Ingredient:
> egg

Recipes:
Pancake dough, cooking time: 60
Meatballs, cooking time: 20
```

Remember to update the list of commands printed at the start as you add commands.

### Exercise 7.8: Big Year (3 parts)

*Template: `exercises/part07/07_08_BigYear`*

A "big year" is a birdwatcher's attempt to observe as many species as possible in one year. Write a database for birdwatchers. It contains birds, each with a name and a Latin name, and counts the observations of each bird.

The commands are:

- `Add` — adds a bird,
- `Observation` — adds an observation of a bird,
- `All` — prints all birds,
- `One` — prints one bird,
- `Quit` — ends the program.

Handle incorrect input gracefully.

```
? Add
Name: Crow
Name in Latin: Corvus Corvus
? Add
Name: Hawk
Name in Latin: Dorkus Dorkus
? Observation
Bird? Hawk
? Observation
Bird? Lion
Not a bird!
? Observation
Bird? Hawk
? All
Crow (Corvus Corvus): 0 observations
Hawk (Dorkus Dorkus): 2 observations
? One
Bird? Hawk
Hawk (Dorkus Dorkus): 2 observations
? Quit
```

(Here the prompt `? ` and the user's input are on the same line.) You are free to structure the program as you like. A class for birds, a class for the bird database, and a user interface class make a good start.

## 7.4 Halfway there

You have reached the halfway point of the book. Take a moment to appreciate how much you have learned. You can write programs that read input from the user and from files; store data in variables, vectors and objects; make decisions and repeat actions; break programs into functions and classes; test them automatically; and reason about how efficient they are.

The second half builds on this foundation. Chapter 8 introduces hash maps, one of the most useful data structures in all of programming. Chapters 9 and 10 explore inheritance, polymorphism, lambdas and ranges. Chapters 11 and 12 cover how real C++ projects are organised, error handling with exceptions, and writing generic code with templates. The final two chapters build graphical programs and games.

### Summary

- Programming paradigms are styles of structuring programs. C++ supports procedural, object-oriented, generic and functional styles.
- Selection sort repeatedly selects the smallest remaining value. It is simple but runs in *O(n²)* time.
- `std::ranges::sort` sorts in *O(n log n)* time.
- Linear search checks every element (*O(n)*); binary search on sorted data halves the search range at every step (*O(log n)*).
- Larger programs are planned by finding concepts (classes) and operations (member functions), then built step by step.
