# Chapter 1: Getting Started

In this chapter you write your first programs. You will learn to print text, read what the user types, store values in variables, calculate with numbers, and make the program choose between alternatives.

## 1.1 Getting started with programming

Programming means designing and building software. Someone needs a program to do something — keep track of a library's books, steer a robot vacuum, show a weather forecast — and a programmer turns that wish into precise instructions for a computer.

Computers do not understand wishes. They follow instructions exactly, one after another, and they never guess what you meant. Those instructions are written in a **programming language**: a notation that people can read and write, and that a tool can translate into something the machine executes.

### Programmers write source code

The text a programmer writes is called **source code**. A C++ source file is an ordinary text file whose name usually ends in `.cpp`. Before the program can run, a **compiler** translates the source code into machine code and stores the result in an executable file. In C++ this happens ahead of time: you compile once and then run the resulting program as often as you like.

The smallest complete C++ program looks like this:

```cpp
int main() {
}
```

Every C++ program has exactly one function called `main`. When the program starts, the computer runs the statements between `main`'s curly braces `{` and `}` from top to bottom. This program has no statements, so it does nothing — but it is a correct program, and it compiles and runs.

Here is a program that actually does something:

```cpp
#include <print>

int main() {
    // Write your program here
    std::println("Hello world!");
}
```

```
Hello world!
```

The line starting with `//` is a **comment**. The compiler ignores comments; they are notes for human readers.

### Exercise 1.1: Sandbox

*Template: `exercises/part01/01_01_Sandbox`*

The exercise template contains an empty program with the comment `// Write your program here`. First build and run it unchanged — nothing is printed, but you have practised the build-and-run cycle. Then add a line that prints some text (anything you like) and run the program again.

Use this sandbox throughout the book whenever you want to try something out quickly.

## 1.2 Printing

Printing text to the screen is the first thing almost every programmer learns. In C++23 we print with `std::println`:

```cpp
#include <print>

int main() {
    std::println("Hello world!");
}
```

The `#include <print>` line at the top tells the compiler that we want to use the printing tools of the C++ standard library. The `std::` prefix says that `println` belongs to the **standard library** (`std` is short for *standard*).

### Program boilerplate

Everything except the `std::println` line is **boilerplate**: code that has to be there for the program to work, but that we do not change. For now you can think of it as a frame:

```cpp
#include <print>

int main() {
    // your statements go here
}
```

You will learn what `#include`, `int` and the parentheses mean as the book proceeds.

### Exercise 1.2: Ada Lovelace

*Template: `exercises/part01/01_02_AdaLovelace`*

Below the comment `// Write your program here`, add a statement that prints the text `Ada Lovelace`. The output should be:

```
Ada Lovelace
```

Ada Lovelace (1815–1852) wrote what is considered the first published computer program, for Charles Babbage's never-built Analytical Engine.

### Printing multiple lines

A program may contain many statements. They run in order, from top to bottom:

```cpp
std::println("Hello world!");
std::println("... and the universe!");
std::println("... and the rest of the galaxy too!");
```

```
Hello world!
... and the universe!
... and the rest of the galaxy too!
```

`std::println` ends the output with a line break, so each call starts a new line. Its sibling `std::print` prints *without* a line break:

```cpp
std::print("Hello ");
std::print("world");
std::println("!");
```

```
Hello world!
```

### Exercise 1.3: Once Upon a Time

*Template: `exercises/part01/01_03_OnceUponATime`*

Modify the program so that it prints the following text. Use three `std::println` statements.

```
Once upon a time
there was
a program
```

### Exercise 1.4: Dinosaur

*Template: `exercises/part01/01_04_Dinosaur`*

Print the following. Most editors offer *snippets* or auto-completion — type `std::pri` and look at the suggestions. Learn to use them; they save a lot of typing.

```
Once upon a time
there was
a dinosaur
```

### Terminology and code comments

**Statements and parameters.** Each `std::println(...)` line is a *statement*: one instruction to the computer. The information inside the parentheses is the *argument* (or *parameter*) given to `println` — here, the text to print. Text written between double quotes, such as `"Hello world!"`, is a **string literal**.

**The semicolon ends a statement.** Every statement ends with `;`. The compiler does not care about line breaks, so this works too, though it is hard to read:

```cpp
std::println("Hello"); std::println("world");
```

Forgetting a semicolon is the most common beginner error. The compiler will complain, usually pointing at the line *after* the missing semicolon.

**Comments.** Comments explain code to people. There are two kinds:

```cpp
// A line comment lasts until the end of the line.

/* A block comment
   can span several lines. */
std::println("Printing"); // a comment can follow code
```

Comments are also handy for temporarily disabling a statement without deleting it.

> **Compiler messages.** When the compiler finds a mistake, it prints an error with a file name, line number and description. Read the *first* error first: later errors are often consequences of it. Do not be afraid of long error messages — they will become familiar.

## 1.3 Reading input

A program becomes interesting when it reacts to its user. **Input** is text the user types; the program reads it while it runs.

In C++ the keyboard is available through `std::cin` ("character input"). The simplest robust way to read is a whole line at a time with `std::getline`:

```cpp
#include <iostream>
#include <print>
#include <string>

int main() {
    std::println("Write a message:");
    std::string message;
    std::getline(std::cin, message);
    std::println("{}", message);
}
```

```
Write a message:
> Hello there
Hello there
```

Three new things appear here:

- `#include <iostream>` and `#include <string>` make `std::cin`, `std::getline` and `std::string` available.
- `std::string message;` creates a **variable** named `message` that can hold a string. Variables are covered properly in the next section.
- `std::getline(std::cin, message);` waits until the user types a line and presses Enter, then stores the line (without the Enter) in `message`.

The last line prints the value. The format string `"{}"` contains a **placeholder** `{}`, which `std::println` replaces with the next argument. Placeholders are how we mix fixed text with values:

```cpp
std::println("You wrote: {}", message);
```

```
You wrote: Hello there
```

### Exercise 1.5: Message

*Template: `exercises/part01/01_05_Message`*

Write a program that asks the user to write a message and then prints it. The template already prints the prompt.

```
Write a message:
> Bye
Bye
```

```
Write a message:
> Once upon a time...
Once upon a time...
```

### Fundamentals of strings

A string is a sequence of characters. String literals are written between double quotes. Strings can be stored in variables of type `std::string`:

```cpp
std::string text = "Contains text";
std::println("{}", text);
```

### Concatenation — joining strings together

Strings can be joined with the `+` operator. This is called **concatenation**:

```cpp
std::string greeting = "Hello";
std::string target = "world";
std::string whole = greeting + " " + target + "!";
std::println("{}", whole);
```

```
Hello world!
```

In C++ you will usually prefer placeholders for output, because they are shorter and work with all kinds of values: `std::println("{} {}!", greeting, target);` prints the same thing.

> **A C++ detail.** `"Hello" + " world"` — adding two *literals* directly — does not compile, because string literals are not `std::string` objects. As long as at least one side of each `+` is a `std::string`, concatenation works.

### Exercise 1.6: Hi Ada Lovelace!

*Template: `exercises/part01/01_06_HiAdaLovelace`*

The template contains the variable `std::string name = "Ada Lovelace";`. Make the program print

```
Hi Ada Lovelace!
```

Do not write `Ada Lovelace` inside the print statement; use the variable `name`.

### Reading strings

Once a line has been read into a variable, we can use the variable as often as we want.

### Exercise 1.7: Message Three Times

*Template: `exercises/part01/01_07_MessageThreeTimes`*

Ask the user for a message and print it three times, each on its own line.

```
Write a message:
> Hi
Hi
Hi
Hi
```

### Exercise 1.8: Greeting

*Template: `exercises/part01/01_08_Greeting`*

Ask for the user's name with the message `What's your name?`, then greet them.

```
What's your name?
> Ada
Hi Ada
```

### Program execution waits for input

When a program reaches `std::getline`, it stops and waits until the user has pressed Enter. A program can read input as many times as it needs to; each `getline` call waits for a new line.

```cpp
std::string first;
std::string second;
std::println("Write the first line:");
std::getline(std::cin, first);
std::println("Write the second line:");
std::getline(std::cin, second);
std::println("You wrote {} and {}", first, second);
```

### Exercise 1.9: Conversation

*Template: `exercises/part01/01_09_Conversation`*

Write a program that chats with the user like this:

```
Greetings! How are you doing?
> Good thank you!
Oh, how interesting. Tell me more!
> Well, there's really nothing to tell.
Thanks for sharing!
```

The program does not need to look at what the user writes, only wait for it.

### Exercise 1.10: Story

*Template: `exercises/part01/01_10_Story`*

Ask for a main character's name and job, then print a short story built from them.

```
I will tell you a story, but I need some information first.
What is the main character called?
> Bob
What is their job?
> a builder
Here is the story:
Once upon a time there was Bob, who was a builder.
On the way to work, Bob reflected on life.
Perhaps Bob will not be a builder forever.
```

## 1.4 Variables

A **variable** is a named place in memory that holds a value. Every variable in C++ has a **type**, which decides what kind of values it can hold. The most important types for now are:

| Type | Holds | Example |
|---|---|---|
| `int` | whole numbers | `int age = 32;` |
| `double` | floating-point (decimal) numbers | `double weight = 72.5;` |
| `bool` | truth values, `true` or `false` | `bool isAdult = true;` |
| `std::string` | text | `std::string name = "Ada";` |
| `char` | a single character | `char grade = 'A';` |

A variable is created (*declared*) by writing its type, its name, and usually an initial value:

```cpp
std::string text = "contains text";
int wholeNumber = 123;
double decimalNumber = 3.141592653;
bool isTrue = true;

std::println("The string variable's value is: {}", text);
std::println("The integer variable's value is: {}", wholeNumber);
std::println("The floating-point variable's value is: {}", decimalNumber);
std::println("The boolean variable's value is: {}", isTrue);
```

```
The string variable's value is: contains text
The integer variable's value is: 123
The floating-point variable's value is: 3.141592653
The boolean variable's value is: true
```

Placeholders work with every one of these types — that is one reason `std::println` is so convenient.

### Exercise 1.11: Various Variables

*Template: `exercises/part01/01_11_VariousVariables`*

The template declares three variables and prints them. Change only the values of the variables (marked `MODIFY THESE`) so that the program prints:

```
Chicken:
9000
Bacon (kg):
0.1
Tractor:
Zetor

And finally, a summary:
9000
0.1
Zetor
```

### Changing a value assigned to a variable

A variable exists from the line where it is declared until the end of the block (the `{ ... }`) that contains it. Its value can be changed with the **assignment** operator `=`:

```cpp
int number = 123;
std::println("The value of the variable is {}", number);

number = 42;
std::println("The value of the variable is {}", number);
```

```
The value of the variable is 123
The value of the variable is 42
```

Assignment does not mean "is equal to" as in mathematics. It means "evaluate the right side and store the result in the variable on the left". So `number = number + 1;` is perfectly sensible: it increases `number` by one.

### A variable's type persists

Once a variable has been declared with a type, the type never changes. An `int` variable cannot hold a string:

```cpp
int number = 10;
number = "ten";   // compile error!
```

The compiler refuses the program. This is a good thing: type errors are caught *before* the program ever runs.

C++ will, however, quietly convert between number types. Assigning a `double` to an `int` throws away the decimal part:

```cpp
int whole = 3.9;   // whole is 3, not 4!
```

Most compilers warn about this. It is better to write `int whole{3.9};` with curly braces, which turns the silent loss into a compile error. Assigning an `int` to a `double` is always safe.

> **Constants.** If a value should never change, mark it `const`: `const double pi = 3.14159;`. The compiler then stops you from accidentally assigning to it.

### Naming variables

A good name tells the reader what the value means. `secondsInDay` is better than `s` or `x2`. In this book we use **camelCase**: the first word in lower case, each following word starting with a capital letter.

**Permissible names** consist of letters, digits and underscores, and must not start with a digit: `count`, `maxSpeed`, `point2`, `last_name`.

**Impermissible names** include names that start with a digit (`7days`), contain spaces or other symbols (`max speed`, `price€`), or are reserved words of the language (`int`, `return`, `class`, `if`, …). Names are case-sensitive: `name` and `Name` are different variables.

### The type of the variable tells what values it may hold

Choose the type by the meaning of the value: a count of things is an `int`, a measurement such as kilograms is a `double`, a yes/no answer is a `bool`, text is a `std::string`.

### Reading different types of values

`std::getline` always gives us a string. To get a number out of the text we **convert** it:

| From text to | Use |
|---|---|
| `int` | `std::stoi(text)` |
| `double` | `std::stod(text)` |

### Reading integers

```cpp
std::println("Give a number:");
std::string line;
std::getline(std::cin, line);
int number = std::stoi(line);
std::println("You gave the number {}", number);
```

This "read a line, then convert" pattern will appear again and again. If the user types something that is not a number, `std::stoi` stops the program with an error. Chapter 11 shows how to handle such errors gracefully.

> **What about `std::cin >> number`?** You will see this in many C++ programs. It reads a number directly, but it leaves the rest of the line (including the Enter) waiting in the input, which causes confusing bugs when it is mixed with `getline`. Reading whole lines and converting them avoids the problem.

### Exercise 1.12: Integer Input

*Template: `exercises/part01/01_12_IntegerInput`*

```
Give a number:
> 42
You gave the number 42
```

### Exercise 1.13: Double Input

*Template: `exercises/part01/01_13_DoubleInput`*

Ask the user for a floating-point number (use `std::stod`) and print it.

```
Give a number:
> 3.14
You gave the number 3.14
```

### Reading booleans

There is no standard function that turns text into a `bool`, but a comparison does the job. The expression `text == "true"` is itself a `bool`: it is `true` when the text is exactly `true`, and `false` otherwise.

```cpp
bool value = (line == "true");
```

### Exercise 1.14: Boolean Input

*Template: `exercises/part01/01_14_BooleanInput`*

Ask the user to write something. Print `true` if they wrote exactly `true`, otherwise print `false`. (`std::println` prints a `bool` as the word `true` or `false`.)

```
Write something:
> santa does not exist
True or false? false
```

```
Write something:
> true
True or false? true
```

### Exercise 1.15: Different Types of Input

*Template: `exercises/part01/01_15_DifferentTypesOfInput`*

Ask the user for a string, an integer, a double and a boolean, then print them all.

```
Give a string:
> bye-bye
Give an integer:
> 11
Give a double:
> 4.2
Give a boolean:
> true
You gave the string bye-bye
You gave the integer 11
You gave the double 4.2
You gave the boolean true
```

## 1.5 Calculating with numbers

The basic arithmetic operators are `+`, `-`, `*` and `/`, plus `%` for the remainder of a division. They work as in mathematics:

```cpp
int first = 2;
int second = 4;
int sum = first + second;
std::println("{}", sum);   // prints 6
```

### Precedence and parentheses

Multiplication and division are calculated before addition and subtraction. Parentheses change the order:

```cpp
int calculationWithParentheses = (1 + 1) + 3 * (2 + 5);   // 23
int calculationWithoutParentheses = 1 + 1 + 3 * 2 + 5;    // 13
```

An **expression** is any combination of values, variables and operators that produces a value. The program evaluates an expression first, and then uses the result — for example, stores it in a variable or prints it.

### Exercise 1.16: Seconds in a Day

*Template: `exercises/part01/01_16_SecondsInADay`*

Ask the user for a number of days, then print how many seconds those days contain.

```
How many days would you like to convert to seconds?
> 3
259200
```

### Calculating and printing

Expressions can be used directly as placeholder arguments:

```cpp
int first = 2;
int second = 4;
std::println("{} + {} = {}", first, second, first + second);
```

```
2 + 4 = 6
```

When you need several numbers from the user, read each into its own variable:

```cpp
std::string line;
std::println("Give the first number:");
std::getline(std::cin, line);
int first = std::stoi(line);
std::println("Give the second number:");
std::getline(std::cin, line);
int second = std::stoi(line);
```

Notice that the same `line` variable is reused for both reads; after converting, we no longer need the text.

### Exercise 1.17: Sum of Two Numbers

*Template: `exercises/part01/01_17_SumOfTwoNumbers`*

```
Give the first number:
> 8
Give the second number:
> 3
The sum of the numbers is 11
```

### Exercise 1.18: Sum of Three Numbers

*Template: `exercises/part01/01_18_SumOfThreeNumbers`*

```
Give the first number:
> 3
Give the second number:
> -1
Give the third number:
> 2
The sum of the numbers is 4
```

### Exercise 1.19: Addition Formula

*Template: `exercises/part01/01_19_AdditionFormula`*

Read two integers and print the whole addition formula.

```
Give the first number:
> 73457
Give the second number:
> 12888
73457 + 12888 = 86345
```

### Exercise 1.20: Multiplication Formula

*Template: `exercises/part01/01_20_MultiplicationFormula`*

As before, but multiply.

```
Give the first number:
> 277
Give the second number:
> 111
277 * 111 = 30747
```

### Division

Division of two integers produces an integer: the decimal part is simply thrown away.

```cpp
int result = 3 / 2;
std::println("{}", result);   // prints 1
```

If at least one of the operands is a `double`, the result is a `double`:

```cpp
double a = 3.0 / 2;                    // 1.5
double b = 3 / 2.0;                    // 1.5
int first = 3;
int second = 2;
double c = static_cast<double>(first) / second;   // 1.5
double d = first / second;             // 1 — the integer division happens first!
```

`static_cast<double>(first)` converts the value of `first` to a `double` for this calculation. Note the last line: the division `first / second` is between two `int`s, so it produces `1`, which is only *then* converted to `1.0`.

> **How doubles print.** `std::println` prints a `double` in the shortest form that reads back as the same value, so `5.0` prints as `5` and `4.5` as `4.5`. (Most decimal fractions, such as `0.1`, cannot be stored exactly in a `double`; printing picks the shortest text that still identifies the stored value.) If you want a fixed number of decimals, use a format specification: `std::println("{:.2f}", 5.0)` prints `5.00`.

### Exercise 1.21: Average of Two Numbers

*Template: `exercises/part01/01_21_AverageOfTwoNumbers`*

Read two integers and print their average.

```
Give the first number:
> 8
Give the second number:
> 3
The average is 5.5
```

### Exercise 1.22: Average of Three Numbers

*Template: `exercises/part01/01_22_AverageOfThreeNumbers`*

```
Give the first number:
> 8
Give the second number:
> 2
Give the third number:
> 3
The average is 4.333333333333333
```

### Exercise 1.23: Simple Calculator

*Template: `exercises/part01/01_23_SimpleCalculator`*

Read two integers and print their sum, difference, product and quotient. The quotient is a floating-point number.

```
Give the first number:
> 9
Give the second number:
> 2
9 + 2 = 11
9 - 2 = 7
9 * 2 = 18
9 / 2 = 4.5
```

### Misunderstandings about the value of a variable

Beginners are often surprised by these facts:

1. **Assignment copies a value; it does not create a link.** After `int a = 5; int b = a; a = 10;` the variable `b` is still `5`.
2. **Statements run in order.** A calculation uses the values the variables have *at that moment*. Changing a variable later does not change results computed earlier.
3. **The right side is evaluated first.** In `x = x * 2;` the old value of `x` is doubled and the result is stored back in `x`.

```cpp
int length = 5;
int area = length * length;   // 25
length = 10;
std::println("{}", area);     // still 25!
```

## 1.6 Conditional statements

So far our programs have executed every statement, every time. A **conditional statement** lets the program choose. It starts with `if`, followed by a condition in parentheses and a block of code in curly braces. The block runs only if the condition is true.

```cpp
std::println("Hello, world!");
if (true) {
    std::println("This code is unavoidable!");
}
```

A condition is usually a comparison:

```cpp
int number = 11;
if (number > 10) {
    std::println("The number was greater than 10");
}
```

### Exercise 1.24: Speeding Ticket

*Template: `exercises/part01/01_24_SpeedingTicket`*

Read an integer and print `Speeding ticket!` if it is greater than 120.

```
Give speed:
> 15
```

```
Give speed:
> 135
Speeding ticket!
```

### Code indentation and block statements

A **block** is the code between `{` and `}`. The statements inside a block are indented one level (four spaces in this book) further than the line that opened the block. The compiler does not need the indentation — it only looks at the braces — but people do. Badly indented code hides its own structure.

```cpp
if (number > 10) {
    std::println("The number was greater than 10");
    if (number > 100) {
        std::println("... even greater than 100!");
    }
}
```

Your editor can indent code automatically. In VS Code the command is *Format Document* (`Shift+Alt+F` on Windows); the `clang-format` tool does the same from the command line.

### Exercise 1.25: Check Your Indentation

*Template: `exercises/part01/01_25_CheckYourIndentation`*

The template contains a working program that is badly indented. Fix the indentation — try your editor's automatic formatting — so that every block is indented consistently.

### Comparison operators

| Operator | Meaning |
|---|---|
| `>` | greater than |
| `>=` | greater than or equal to |
| `<` | less than |
| `<=` | less than or equal to |
| `==` | equal to |
| `!=` | not equal to |

Be careful with `==`: a single `=` is assignment, two are comparison. Writing `if (number = 5)` is a classic bug — it *assigns* 5 to `number`, and the condition is then always true. Compilers warn about it when warnings are enabled.

### Exercise 1.26: Orwell

*Template: `exercises/part01/01_26_Orwell`*

Read an integer and print `Orwell` if it is exactly 1984.

```
Give a number:
> 1984
Orwell
```

### Exercise 1.27: Ancient

*Template: `exercises/part01/01_27_Ancient`*

Read a year. If it is smaller than 2015, print `Ancient history!`.

```
Give a year:
> 2013
Ancient history!
```

### Else

An `if` can have an `else` branch, which runs when the condition is false:

```cpp
int number = 4;
if (number > 5) {
    std::println("Your number is greater than five!");
} else {
    std::println("Your number is five or less!");
}
```

Exactly one of the two blocks runs.

### Exercise 1.28: Positivity

*Template: `exercises/part01/01_28_Positivity`*

```
Give a number:
> 5
The number is positive.
```

```
Give a number:
> -2
The number is not positive.
```

### Exercise 1.29: Adulthood

*Template: `exercises/part01/01_29_Adulthood`*

Ask for the user's age and tell them whether they are an adult (18 or older).

```
How old are you?
> 12
You are not an adult
```

```
How old are you?
> 32
You are an adult
```

### More conditionals: `else if`

When there are more than two alternatives, use `else if`. The conditions are checked from top to bottom, and the first true one wins; at most one block runs.

```cpp
int number = 3;
if (number == 1) {
    std::println("The number is one");
} else if (number == 2) {
    std::println("The given number is two");
} else if (number == 3) {
    std::println("The number must be three!");
} else {
    std::println("Something else!");
}
```

### Exercise 1.30: Larger Than or Equal To

*Template: `exercises/part01/01_30_LargerThanOrEqualTo`*

Read two integers and print the greater one, or tell the user that they are equal.

```
Give the first number:
> 5
Give the second number:
> 8
Greater number is: 8
```

```
Give the first number:
> 5
Give the second number:
> 5
The numbers are equal!
```

### Order of execution for comparisons

Because the first true condition wins, the order of `else if` branches matters. Checking `points >= 50` before `points >= 90` would give every excellent student a 1. When checking ranges, go from one end to the other.

### Exercise 1.31: Grades and Points

*Template: `exercises/part01/01_31_GradesAndPoints`*

Print the grade according to this table:

| points | grade |
|---|---|
| < 0 | impossible! |
| 0–49 | failed |
| 50–59 | 1 |
| 60–69 | 2 |
| 70–79 | 3 |
| 80–89 | 4 |
| 90–100 | 5 |
| > 100 | incredible! |

```
Give points [0-100]:
> 76
Grade: 3
```

```
Give points [0-100]:
> -3
Grade: impossible!
```

### The conditional expression and the `bool` variable

The condition of an `if` is just an expression whose value is `true` or `false`. Such a value can be stored in a `bool` variable:

```cpp
int first = 1;
int second = 3;
bool isGreater = first > second;
if (isGreater) {
    std::println("1 is greater than 3!");
} else {
    std::println("1 is not greater than 3.");
}
```

The remainder operator `%` is frequently used in conditions. `number % 2` is `0` exactly when `number` is even.

### Exercise 1.32: Odd or Even

*Template: `exercises/part01/01_32_OddOrEven`*

```
Give a number:
> 2
Number 2 is even.
```

```
Give a number:
> 7
Number 7 is odd.
```

### Conditional statements and comparing strings

In C++, `std::string` values can be compared with `==` and `!=`, just like numbers. The comparison looks at the contents of the strings:

```cpp
std::string text = "course";
if (text == "marzipan") {
    std::println("The variable text contains the text marzipan.");
} else {
    std::println("The variable text does not contain the text marzipan.");
}
```

> **Coming from Java?** In Java, comparing strings with `==` is a famous bug, and you must use `equals`. In C++, `==` on `std::string` compares the text, which is what you want.

### Exercise 1.33: Password

*Template: `exercises/part01/01_33_Password`*

Ask for a password. If it is `Caput Draconis`, print `Welcome!`; otherwise print `Off with you!`.

```
Password?
> Wattlebird
Off with you!
```

### Exercise 1.34: Same

*Template: `exercises/part01/01_34_Same`*

Read two strings and print `Same` if they are identical, otherwise `Different`.

```
Enter the first string:
> hello
Enter the second string:
> world
Different
```

### Logical operators

Conditions can be combined with **logical operators**:

| Operator | Name | True when |
|---|---|---|
| `a && b` | and | both `a` and `b` are true |
| `a \|\| b` | or | at least one of `a`, `b` is true |
| `!a` | not | `a` is false |

```cpp
int number = 7;
if (number >= 5 && number <= 10) {
    std::println("The number is between 5 and 10");
}
if (number < 0 || number > 100) {
    std::println("The number is out of range");
}
if (!(number > 4)) {
    std::println("The number is not greater than 4");
}
```

C++ also allows the words `and`, `or` and `not` in place of `&&`, `||` and `!`, but the symbols are far more common in real code.

### Exercise 1.35: Checking the Age

*Template: `exercises/part01/01_35_CheckingTheAge`*

Read an age and print `OK` if it is possible (from 0 to 120 inclusive), otherwise `Impossible!`. Use only one `if` statement.

```
How old are you?
> 150
Impossible!
```

### Execution order of conditional statements

Complex conditions are easiest to get right by writing out the cases in order, from the most specific to the most general. Consider the classic *FizzBuzz* problem: print `FizzBuzz` for numbers divisible by both 3 and 5, `Fizz` for numbers divisible by 3, `Buzz` for numbers divisible by 5, and the number otherwise. The "both" case must come first — otherwise a number like 15 would be caught by the "divisible by 3" branch.

```cpp
if (number % 3 == 0 && number % 5 == 0) {
    std::println("FizzBuzz");
} else if (number % 3 == 0) {
    std::println("Fizz");
} else if (number % 5 == 0) {
    std::println("Buzz");
} else {
    std::println("{}", number);
}
```

### Exercise 1.36: Leap Year

*Template: `exercises/part01/01_36_LeapYear`*

A year is a leap year if it is divisible by 4. However, a year divisible by 100 is a leap year only if it is also divisible by 400. Read a year and tell whether it is a leap year.

```
Give a year:
> 1800
The year is not a leap year.
```

```
Give a year:
> 2000
The year is a leap year.
```

*Hint:* think of the problem as a chain of `if`, `else if`, `else if`, …, `else`, starting with the most specific case.

### Exercise 1.37: Gift Tax

*Template: `exercises/part01/01_37_GiftTax`*

In Finland, a gift from a close relative is taxed when its value is at least €5,000. The tax is calculated from this table:

| Value of gift (€) | Tax at the lower limit (€) | Tax rate for the exceeding part |
|---|---|---|
| 5 000 – 25 000 | 100 | 8 % |
| 25 000 – 55 000 | 1 700 | 10 % |
| 55 000 – 200 000 | 4 700 | 12 % |
| 200 000 – 1 000 000 | 22 100 | 15 % |
| 1 000 000 – | 142 100 | 17 % |

For example, a €6,000 gift is taxed `100 + (6000 − 5000) × 0.08 = 180` euros, and a €75,000 gift `4700 + (75000 − 55000) × 0.12 = 7100` euros.

```
Value of the gift?
> 3500
No tax!
```

```
Value of the gift?
> 27500
Tax: 1950
```

## 1.7 Programming in our society

Software is everywhere: in phones and cars, in payment systems, hospitals, elections and power grids. Very little of modern life happens without programs written by somebody. That makes programming a powerful skill — and one that carries responsibility.

Programs are written by people, and people make mistakes and carry assumptions. A program that decides who gets a loan, or which job applicant gets an interview, reflects the choices its authors made about which data to use and what counts as a good outcome. Errors in software have grounded aircraft, lost spacecraft, and leaked the private data of millions.

C++ in particular runs much of the world's critical infrastructure: operating systems, browsers, databases, game engines, trading systems, embedded controllers in cars and medical devices. It gives the programmer a great deal of control, and with it the ability to make costly mistakes. Modern C++ — the style taught in this book — exists largely to make the safe way the easy way.

As you learn, ask yourself not only "does my program work?" but also "who uses it, and what happens when it goes wrong?" Good programmers test their code, write it so that others can read it, and think about the people at the other end.

### Summary

In this chapter you learned to:

- write, compile and run a C++ program,
- print text with `std::println` and placeholders `{}`,
- read lines with `std::getline` and convert them with `std::stoi` and `std::stod`,
- declare variables of types `int`, `double`, `bool` and `std::string`,
- calculate with arithmetic operators, and avoid the integer-division trap,
- make decisions with `if`, `else if`, `else`, comparisons and logical operators.

In the next chapter, programs learn to repeat themselves.
