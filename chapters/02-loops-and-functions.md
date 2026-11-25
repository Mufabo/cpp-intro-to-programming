# Chapter 2: Loops and Functions

This chapter introduces the two tools that let programs grow beyond a handful of lines. **Loops** repeat code, and **functions** give a name to a piece of code so that it can be reused. Before them, we look at a few patterns that keep showing up in programs.

## 2.1 Recurring problems and patterns to solve them

Programming problems are rarely brand new. The same small sub-problems — read a number, compute something, choose between options, repeat until done — appear over and over. Experienced programmers recognise these sub-problems and reach for a familiar pattern. This section collects the patterns from Chapter 1.

### Reading user input

```cpp
#include <iostream>
#include <print>
#include <string>

int main() {
    std::string line;

    std::println("Write text:");
    std::getline(std::cin, line);              // a string

    std::println("Write an integer:");
    std::getline(std::cin, line);
    int number = std::stoi(line);              // an int

    std::println("Write a decimal number:");
    std::getline(std::cin, line);
    double decimal = std::stod(line);          // a double
}
```

### Calculating

Calculations follow the same shape: read the inputs, compute, print.

```cpp
std::string line;
std::getline(std::cin, line);
int first = std::stoi(line);
std::getline(std::cin, line);
int second = std::stoi(line);

int sum = first + second;
std::println("The sum is {}", sum);
```

The standard library contains many mathematical functions in the header `<cmath>`. For example `std::sqrt(x)` computes the square root, `std::pow(x, y)` raises `x` to the power `y`, and `std::abs(x)` gives the absolute value.

### Exercise 2.1: Squared

*Template: `exercises/part02/02_01_Squared`*

Read an integer and print its square (the number multiplied by itself).

```
> 4
16
```

```
> -3
9
```

### Exercise 2.2: Square Root of Sum

*Template: `exercises/part02/02_02_SquareRootOfSum`*

Read two integers and print the square root of their sum. You do not have to handle negative sums. Use `std::sqrt` from `<cmath>`:

```cpp
#include <cmath>
// ...
int number = 42;
double squareRoot = std::sqrt(number);
std::println("{}", squareRoot);
```

```
> 5
> 4
3
```

```
> 1
> 35
6
```

### Conditional logic

When a program must behave differently in different situations, the pattern is a chain of `if` / `else if` / `else`.

### Exercise 2.3: Absolute Value

*Template: `exercises/part02/02_03_AbsoluteValue`*

Read an integer. If it is negative, print it multiplied by `-1`; otherwise print it as it is. (Solve this with an `if` — do not use `std::abs`.)

```
> -3
3
```

### Exercise 2.4: Comparing Numbers

*Template: `exercises/part02/02_04_ComparingNumbers`*

Read two integers and print one of the following, with the actual numbers filled in.

```
> 8
> 4
8 is greater than 4.
```

```
> -3
> 5
-3 is smaller than 5.
```

```
> 1
> 1
1 is equal to 1.
```

## 2.2 Repeating functionality

A **loop** repeats a block of code. The simplest loop in C++ is `while (true)`, which repeats forever:

```cpp
while (true) {
    std::println("I can program!");
}
```

This program never stops on its own (press `Ctrl+C` in the terminal to end it). An endless loop is rarely what we want — but combined with a way to *leave* the loop, it becomes very useful.

### Ending a loop

The `break` statement jumps out of the loop immediately, and execution continues after the loop's closing brace:

```cpp
std::string line;
while (true) {
    std::println("Exit? (y exits)");
    std::getline(std::cin, line);
    if (line == "y") {
        break;
    }
    std::println("Ok! Let's carry on!");
}
std::println("Ready!");
```

```
Exit? (y exits)
> no
Ok! Let's carry on!
Exit? (y exits)
> y
Ready!
```

### Exercise 2.5: Carry On?

*Template: `exercises/part02/02_05_CarryOn`*

Ask `Shall we carry on?` again and again until the user writes `no`.

```
Shall we carry on?
> yes
Shall we carry on?
> ye
Shall we carry on?
> no
```

### Exercise 2.6: Are We There Yet?

*Template: `exercises/part02/02_06_AreWeThereYet`*

Ask the user for numbers until they enter `4`.

```
Give a number:
> 5
Give a number:
> 744
Give a number:
> 4
```

### Returning to the start of the loop

The `continue` statement skips the rest of the current round and jumps back to the start of the loop. It is handy for rejecting bad input:

```cpp
std::string line;
while (true) {
    std::println("Insert positive integers");
    std::getline(std::cin, line);
    int number = std::stoi(line);

    if (number <= 0) {
        std::println("Unfit number! Try again.");
        continue;
    }

    std::println("Your input was {}", number);
}
```

A loop body often has this shape: read input, `break` if it is the end signal, `continue` if it is invalid, and otherwise process it.

### Exercise 2.7: Only Positives

*Template: `exercises/part02/02_07_OnlyPositives`*

Ask the user for numbers. For a negative number print `Unsuitable number`; for zero, end the loop; for a positive number print its square.

```
Give a number:
> 5
25
Give a number:
> -3
Unsuitable number
Give a number:
> 0
```

### Calculation with loops

Loops often *accumulate* information: counting things, summing things. The pattern is to create a helper variable **before** the loop, update it **inside** the loop, and use it **after** the loop.

```cpp
std::string line;
int count = 0;     // created before the loop

while (true) {
    std::println("Give a number (0 ends):");
    std::getline(std::cin, line);
    int number = std::stoi(line);
    if (number == 0) {
        break;
    }
    count = count + 1;    // updated inside the loop
}

std::println("You gave {} numbers", count);   // used after the loop
```

Adding one to a variable is so common that C++ has shorthands: `count += 1;` and `count++;` both mean `count = count + 1;`. Likewise there are `-=`, `*=`, `/=` and `--`. (The language name *C++* is a programmer joke: "one more than C".)

### Exercise 2.8: Number of Numbers

*Template: `exercises/part02/02_08_NumberOfNumbers`*

Read numbers until the user enters `0`, then print how many numbers were entered (not counting the zero).

```
Give a number:
> 5
Give a number:
> 22
Give a number:
> 9
Give a number:
> -2
Give a number:
> 0
Number of numbers: 4
```

### Exercise 2.9: Number of Negative Numbers

*Template: `exercises/part02/02_09_NumberOfNegativeNumbers`*

As before, but count only the negative numbers. For the input above the output is `Number of negative numbers: 1`.

### Exercise 2.10: Sum of Numbers

*Template: `exercises/part02/02_10_SumOfNumbers`*

Read numbers until `0` and print their sum. For the input above: `Sum of the numbers: 34`.

### Exercise 2.11: Number and Sum of Numbers

*Template: `exercises/part02/02_11_NumberAndSumOfNumbers`*

Print both the count and the sum. You need two helper variables.

```
Number of numbers: 4
Sum of the numbers: 34
```

### Exercise 2.12: Average of Numbers

*Template: `exercises/part02/02_12_AverageOfNumbers`*

Print the average of the numbers. You may assume that at least one number is entered. For the input above: `Average of the numbers: 8.5`.

### Exercise 2.13: Average of Positive Numbers

*Template: `exercises/part02/02_13_AverageOfPositiveNumbers`*

Read numbers until `0` and print the average of the **positive** numbers only. If there are none, print `Cannot calculate the average`.

```
> 3
> 5
> 1
> -3
> 0
3
```

```
> -3
> 0
Cannot calculate the average
```

## 2.3 More loops

### `while` loop with a condition

Instead of `true`, a `while` loop can have any condition. The condition is checked before each round, and the loop ends when it becomes false:

```cpp
int number = 1;
while (number < 6) {
    std::println("{}", number);
    number++;
}
```

```
1
2
3
4
5
```

### `for` loop

The loop above has three parts that always come together: initialise a counter, check a condition, update the counter. The **`for` loop** puts all three on one line:

```cpp
for (int i = 0; i < 5; i++) {
    std::println("{}", i);
}
```

```
0
1
2
3
4
```

Read it as: "start with `i = 0`; while `i < 5`, run the block and then do `i++`". The variable `i` exists only inside the loop. Counting from zero and using `<` is the conventional style in C++, and you will see why in the next chapter.

A `for` loop can count in any direction and with any step:

```cpp
for (int i = 10; i > 0; i -= 2) {
    std::print("{} ", i);
}
std::println("");
```

```
10 8 6 4 2
```

### Exercise 2.14: Counting

*Template: `exercises/part02/02_14_Counting`*

Read an integer and print the numbers from 0 up to and including it.

```
> 4
0
1
2
3
4
```

### Exercise 2.15: Counting to Hundred

*Template: `exercises/part02/02_15_CountingToHundred`*

Read an integer (smaller than 100) and print the numbers from it up to 100.

```
> 98
98
99
100
```

### Exercise 2.16: From Where to Where? (2 parts)

*Template: `exercises/part02/02_16_FromWhereToWhere`*

**Part 1.** Print the integers from 1 up to a number given by the user.

```
Where to?
> 3
1
2
3
```

**Part 2.** Ask also for a starting point. If the end is smaller than the start, nothing is printed. Remember that both numbers may be negative.

```
Where to?
> 8
Where from?
> 5
5
6
7
8
```

### On stopping a loop

A loop condition is checked only at the start of each round, not continuously. If the condition becomes false halfway through the block, the rest of the block still runs:

```cpp
int number = 1;
while (number != 2) {
    std::println("{}", number);
    number = 2;
    std::println("{}", number);   // still printed
    number = 1;
}
```

This loop never ends: whenever the condition is checked, `number` is 1 again. When a loop does not end as you expect, trace by hand what the variables contain at the moment the condition is checked.

### Repeating functionality

Loops are perfect for sums and products over a range of numbers:

```cpp
int sum = 0;
for (int i = 1; i <= 10; i++) {
    sum += i;
}
std::println("{}", sum);   // 55
```

### Exercise 2.17: Sum of a Sequence

*Template: `exercises/part02/02_17_SumOfASequence`*

Compute `1 + 2 + 3 + … + n`, where `n` comes from the user.

```
Last number?
> 7
The sum is 28
```

### Exercise 2.18: Sum of a Sequence — the Sequel

*Template: `exercises/part02/02_18_SumOfASequenceTheSequel`*

Compute the sum of all integers between two numbers (inclusive). The user gives the smaller number first.

```
First number?
> 3
Last number?
> 5
The sum is 12
```

### Exercise 2.19: Factorial

*Template: `exercises/part02/02_19_Factorial`*

The factorial `n!` is `1 * 2 * 3 * … * n`, and by definition `0! = 1`. Compute the factorial of a number given by the user.

```
Give a number:
> 10
Factorial: 3628800
```

An `int` can hold values only up to about two billion, and `13!` already exceeds that. For bigger results, use the type `long long`, which holds numbers up to about 9.2 × 10¹⁸ (enough for `20!`).

### On the structure of programs that use loops

Most loop programs share a structure:

```cpp
// 1. helper variables for the whole loop
// 2. the loop
while (true) {
    // 2a. read input
    // 2b. exit condition -> break
    // 2c. invalid input -> continue
    // 2d. process the input, update helper variables
}
// 3. use the helper variables to print results
```

Build such programs **one piece at a time**: first make the loop read numbers and stop correctly; then add the sum; then the count; and so on. Run the program after every small step. Small steps make mistakes easy to find.

### Exercise 2.20: Repeating, Breaking and Remembering (5 parts)

*Template: `exercises/part02/02_20_RepeatingBreakingAndRemembering`*

Build the following program in five steps.

**Part 1: Reading numbers.** Print `Give numbers:` and read numbers until the user enters `-1`. Then print `Thx! Bye!`.

**Part 2: Sum.** Also print the sum of the numbers (not including the `-1`).

**Part 3: Count.** Also print how many numbers were entered.

**Part 4: Average.** Also print their average.

**Part 5: Even and odd.** Also print how many of the numbers were even and how many odd.

The final program works like this:

```
Give numbers:
> 5
> 2
> 4
> -1
Thx! Bye!
Sum: 11
Numbers: 3
Average: 3.6666666666666665
Even: 2
Odd: 1
```

## 2.4 Functions: dividing the program into smaller parts

So far all our code has been in `main`. As programs grow, that becomes unmanageable. A **function** is a named block of code that can be *called* from elsewhere in the program. You have already called functions written by others: `std::println`, `std::getline`, `std::stoi`, `std::sqrt`. Now you will write your own.

> **Terminology.** The Java course calls these *methods*. In C++, a free-standing piece of named code is a *function*; the word *method* (officially *member function*) is reserved for functions that belong to a class, which arrive in Chapter 4.

### Custom functions

```cpp
#include <print>

void greet() {
    std::println("Greetings from the function world!");
}

int main() {
    std::println("Let's try if we can travel to the function world:");
    greet();

    std::println("Looks like we can, let's try again:");
    greet();
    greet();
}
```

```
Let's try if we can travel to the function world:
Greetings from the function world!
Looks like we can, let's try again:
Greetings from the function world!
Greetings from the function world!
```

The definition `void greet() { ... }` has four parts:

- `void` — the **return type**. `void` means the function gives nothing back.
- `greet` — the **name**, used to call it. Function names are written in camelCase and are usually verbs.
- `()` — the **parameter list**, here empty.
- `{ ... }` — the **body**: the statements that run when the function is called.

A call `greet();` jumps to the function, runs its body, and then continues after the call.

> **Define before use.** The C++ compiler reads a file from top to bottom, and a function must be known before it is called. That is why `greet` is written *above* `main`. If you prefer `main` at the top, you can put a **declaration** (just the first line, ending in a semicolon) above it: `void greet();` — and define the function later in the file.

### Exercise 2.21: In a Hole in the Ground

*Template: `exercises/part02/02_21_InAHoleInTheGround`*

Implement the function `printText` in the template so that it prints `In a hole in the ground there lived a method` followed by a line break. (The sentence is an old joke from the Java course; we keep it.)

### Exercise 2.22: Reprint

*Template: `exercises/part02/02_22_Reprint`*

Extend the previous program: `main` asks how many times the text should be printed and calls `printText` that many times.

```
How many times?
> 3
In a hole in the ground there lived a method
In a hole in the ground there lived a method
In a hole in the ground there lived a method
```

### Function parameters

**Parameters** are variables that receive values when the function is called:

```cpp
void hello(std::string name) {
    std::println("Hi {}, greetings from the function world!", name);
}

int main() {
    hello("Ada");
    hello("Grace");
}
```

```
Hi Ada, greetings from the function world!
Hi Grace, greetings from the function world!
```

The value written in the call (`"Ada"`) is the **argument**. When the function starts, the parameter `name` is created and initialised with the argument.

### Exercise 2.23: From One to Parameter

*Template: `exercises/part02/02_23_FromOneToParameter`*

Write the function `void printUntilNumber(int number)` that prints the numbers from 1 to `number`, each on its own line. `printUntilNumber(3)` prints `1`, `2` and `3`.

### Exercise 2.24: From Parameter to One

*Template: `exercises/part02/02_24_FromParameterToOne`*

Write `void printFromNumberToOne(int number)`, which counts down from `number` to 1.

### Multiple parameters

A function may have several parameters, separated by commas:

```cpp
void sum(int first, int second) {
    std::println("The sum of numbers {} and {} is {}", first, second, first + second);
}

int main() {
    sum(3, 5);
}
```

### Exercise 2.25: Division

*Template: `exercises/part02/02_25_Division`*

Write `void division(int numerator, int denominator)` that prints the result of the division as a floating-point number. `division(3, 5)` prints `0.6`.

### Exercise 2.26: Divisible by Three

*Template: `exercises/part02/02_26_DivisibleByThree`*

Write `void divisibleByThreeInRange(int beginning, int end)` that prints, in increasing order, every number in the range (inclusive) that is divisible by three. `divisibleByThreeInRange(2, 10)` prints `3`, `6` and `9`.

### Parameter values are copied

When a function is called, the argument's value is **copied** into the parameter. Changing the parameter inside the function does not affect the caller's variable:

```cpp
void addOne(int number) {
    number = number + 1;
    std::println("Inside the function: {}", number);
}

int main() {
    int number = 5;
    addOne(number);
    std::println("In main: {}", number);
}
```

```
Inside the function: 6
In main: 5
```

The two variables called `number` are completely separate; they just happen to share a name. (C++ *can* let a function change the caller's variable, using a *reference parameter*. That comes in Chapter 5.)

### Functions can return values

A function can compute a value and give it back to its caller with `return`. The type of the value is written in front of the function name instead of `void`:

```cpp
int alwaysReturnsTen() {
    return 10;
}

int main() {
    int number = alwaysReturnsTen();
    std::println("The function returned {}", number);
    std::println("Twice that is {}", alwaysReturnsTen() * 2);
}
```

`return` ends the function immediately. A function whose return type is not `void` must return a value on every path through it — the compiler warns if you forget.

### Exercise 2.27: Number Uno

*Template: `exercises/part02/02_27_NumberUno`*

Write a function `int numberUno()` that returns the value 1.

### Exercise 2.28: Word

*Template: `exercises/part02/02_28_Word`*

Write a function `std::string word()` that returns a word of your choice.

### Variables inside functions

Variables declared inside a function are **local**: they exist only while the function runs, and only that function can see them. `main` cannot see the variables of another function, and vice versa. This is a feature — it means you can understand each function on its own.

### Calculating the return value inside a function

```cpp
int sum(int first, int second) {
    int result = first + second;
    return result;
}

int main() {
    std::println("{}", sum(2, 7));
}
```

A function that returns a value should normally **not** print anything. Printing is the caller's business; the function's job is to compute. This makes the function reusable: the caller may want to print the result, but it may also want to use it in a further calculation.

### Exercise 2.29: Summation

*Template: `exercises/part02/02_29_Summation`*

Complete `int sum(int number1, int number2, int number3, int number4)` so that it returns the sum of its parameters. The `main` in the template prints `Sum: 14`.

### Exercise 2.30: Smallest

*Template: `exercises/part02/02_30_Smallest`*

Complete `int smallest(int number1, int number2)` so that it returns the smaller parameter. Do not print anything in the function.

### Exercise 2.31: Greatest

*Template: `exercises/part02/02_31_Greatest`*

Complete `int greatest(int number1, int number2, int number3)`, which returns the greatest of its three parameters.

### Exercise 2.32: Averaging

*Template: `exercises/part02/02_32_Averaging`*

Complete `double average(int number1, int number2, int number3, int number4)`. It **must** use your `sum` function to compute the sum. `average(4, 3, 6, 1)` returns `3.5`.

### Execution of function calls and the call stack

How does the computer remember where to continue after a function returns? It keeps a **call stack**. Every function call pushes a new *frame* onto the stack; the frame holds the function's parameters and local variables and the place to return to. When the function returns, its frame is removed and execution continues where the caller left off.

```cpp
void printNumbers(int count) {
    for (int i = 1; i <= count; i++) {
        std::println("{}", i);
    }
}

int main() {
    std::println("Start");
    printNumbers(2);
    std::println("End");
}
```

While `printNumbers` runs, the stack contains two frames: `main` (at the bottom, paused at the call) and `printNumbers` (on top, with `count` and `i`). When `printNumbers` returns, its frame disappears, and `main` resumes and prints `End`. A debugger shows you this stack: it is one of the most useful views when hunting bugs.

### Call stack and returning a value

When a function returns a value, the value is handed to the caller's frame just before the callee's frame is removed. The expression containing the call is then evaluated using that value.

### A function calling another function

Functions can call other functions, which can call others, and so on. Each call adds a frame; each return removes one. Breaking a problem into small functions that call each other is the core skill of structured programming.

### Exercise 2.33: Star Sign (4 parts)

*Template: `exercises/part02/02_33_StarSign`*

**Part 1: Printing stars.** Write `void printStars(int number)`, which prints `number` stars followed by a line break. Print a single star with `std::print("*")`, and end the line with `std::println("")`.

```cpp
printStars(5);
printStars(3);
```

```
*****
***
```

**Part 2: Printing a square.** Write `void printSquare(int size)`, which prints a `size × size` square of stars. It must call `printStars` for each row.

**Part 3: Printing a rectangle.** Write `void printRectangle(int width, int height)` using `printStars`.

**Part 4: Printing a triangle.** Write `void printTriangle(int size)` using `printStars`. `printTriangle(4)` prints:

```
*
**
***
****
```

### Exercise 2.34: Advanced Astrology (3 parts)

*Template: `exercises/part02/02_34_AdvancedAstrology`*

**Part 1: Stars and spaces.** Write `void printSpaces(int number)`, which prints `number` spaces without a line break. Copy `printStars` from the previous exercise too.

**Part 2: A right-leaning triangle.** Write `void printTriangle(int size)` using `printSpaces` and `printStars`. `printTriangle(4)` prints:

```
   *
  **
 ***
****
```

**Part 3: A Christmas tree.** Write `void christmasTree(int height)`. The tree is a triangle of the given height, plus a base that is two rows high and three stars wide, centred under the triangle. Heights below 3 do not have to work. `christmasTree(4)` prints:

```
   *
  ***
 *****
*******
  ***
  ***
```

## 2.5 Summary

In this chapter you learned:

- to recognise recurring patterns: reading input, calculating, choosing,
- `while (true)` loops with `break` and `continue`,
- loops with conditions, and the `for` loop,
- to accumulate results in helper variables declared before a loop,
- to write functions with parameters and return values,
- that arguments are copied into parameters, and how the call stack works.

Take a moment to look back. You can now write programs that read any amount of input and are built from small, named pieces. That is already enough to solve a remarkable range of problems.
