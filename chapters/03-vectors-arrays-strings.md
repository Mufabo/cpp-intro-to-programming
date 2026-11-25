# Chapter 3: Vectors, Arrays and Strings

Until now each value in a program has lived in its own variable. That works for two or three values, but not for a hundred, and not when we do not know in advance how many values the user will give. This chapter introduces containers that hold many values: the **vector** and the **array**. We also look more closely at strings. First, though, a few words about errors.

## 3.1 Discovering errors

Every programmer writes bugs. What separates experienced programmers from beginners is not that their code is free of errors, but that they find and fix errors systematically.

### A programmer blind to their own code

When you read your own code, you see what you *meant* to write, not what you actually wrote. A missing `=` in `<=`, a loop that starts at 1 instead of 0, a variable that is updated in the wrong place — these are easy to overlook precisely because you know what the code is supposed to do.

The remedy is to stop trusting your reading and start **observing**: run the program with different inputs, look at what it actually does, and compare that with what it should do. Students who succeed with programming tend to work in small steps, run the code very often, and investigate every surprise immediately rather than piling more code on top of it.

### Commenting the source code

Comments help readers — including you, a week later — understand *why* the code does what it does. Good comments explain intent and non-obvious decisions. Bad comments repeat the code:

```cpp
// Bad: says what the code already says
count++;   // increase count by one

// Good: says why
// The terminating zero is not part of the data, so it is not counted.
if (number == 0) {
    break;
}
```

Even better than a comment is code that explains itself: well-chosen variable names, and small functions with descriptive names. `printTriangle(5)` needs no comment.

### Searching for errors with print debugging

The simplest debugging technique is to add temporary print statements that show what the program is doing:

```cpp
int sum = 0;
for (int i = 1; i < 5; i++) {
    std::println("DEBUG: i = {}, sum before = {}", i, sum);
    sum += i;
}
```

Running this immediately reveals that `i` never reaches 5. Once the bug is fixed, remove the debug prints.

A **debugger** is the professional version of this technique. It lets you pause a program at any line (a *breakpoint*), step through it one statement at a time and inspect the value of every variable and the call stack. Every C++ IDE has one; in VS Code, click to the left of a line number to set a breakpoint and press `F5`. Learning to use the debugger early pays off enormously.

## 3.2 Vectors

A **vector** is a list of values that can grow and shrink while the program runs. It lives in the standard library header `<vector>`:

```cpp
#include <print>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> names;      // an empty list of strings
    names.push_back("First");
    names.push_back("Second");
    names.push_back("Third");

    std::println("{}", names[0]);
    std::println("{}", names[1]);
    std::println("{}", names[2]);
}
```

```
First
Second
Third
```

### Defining the type of the values a vector contains

The type in angle brackets — `std::vector<std::string>`, `std::vector<int>`, `std::vector<double>` — says what the vector holds. Every element of a vector has the same type.

A vector can be created with initial values:

```cpp
std::vector<int> numbers = {3, 2, 6, -1, 5, 1};
```

### Adding to a vector and retrieving a value from a specific place

- `push_back(value)` adds a value to the end.
- `vec[i]` retrieves the value at **index** `i`.

Indices start from **zero**. The first element is at index 0, the second at index 1, and the last at index `size() - 1`.

```cpp
std::vector<std::string> wordList;
wordList.push_back("First");
wordList.push_back("Second");
std::println("{}", wordList[1]);   // Second
```

A common pattern reads values into a vector until the user signals the end:

```cpp
std::vector<std::string> list;
std::string line;
while (true) {
    std::getline(std::cin, line);
    if (line.empty()) {
        break;
    }
    list.push_back(line);
}
```

`line.empty()` is `true` when the string has no characters — that is, the user just pressed Enter.

### Exercise 3.1: Third Element

*Template: `exercises/part03/03_01_ThirdElement`*

The template reads strings into a vector until the user enters an empty line, and then prints the first element. Change it to print the **third** element. You do not have to handle vectors with fewer than three elements.

```
> Tom
> Emma
> Alex
> Mary
>
Alex
```

### Exercise 3.2: Second Plus Third

*Template: `exercises/part03/03_02_SecondPlusThird`*

The template reads integers into a vector until the user enters 0, and then prints the first number. Change it to print the sum of the second and the third numbers.

```
> 1
> 3
> 5
> 7
> 0
8
```

### Retrieving a value from a "non-existent" place

What happens if we ask for an index that does not exist?

```cpp
std::vector<std::string> list = {"Hello", "World"};
std::println("{}", list[2]);   // there is no index 2!
```

This is one of the most important differences between C++ and safer languages. Using `[]` with an invalid index is **undefined behaviour**: the C++ standard places no requirements at all on what happens. The program may crash, print garbage, or appear to work — until one day it doesn't. Bugs like this are a major source of security vulnerabilities in real software.

There are two good defences:

1. The member function `at(i)` checks the index. With an invalid index it throws an `std::out_of_range` exception, which stops the program with an error message:

   ```cpp
   std::println("{}", list.at(2));
   ```

   ```
   terminate called after throwing an instance of 'std::out_of_range'
     what():  vector::_M_range_check: __n (which is 2) >= this->size() (which is 2)
   ```

2. While developing, turn on your standard library's *hardened* or *debug* mode, which makes even `[]` check its index. With GCC, add `-D_GLIBCXX_ASSERTIONS` to the compiler options; with Clang/libc++ use `-D_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_FAST`; Visual Studio checks indices in Debug builds automatically.

Throughout this book, use `[]` when you are certain the index is valid (for example inside a loop over the vector's indices) and `at()` when you are not.

### Exercise 3.3: Out of Range

*Template: `exercises/part03/03_03_OutOfRange`*

The template contains a program that uses a vector. Modify it so that running it always ends in an `std::out_of_range` error. The user should not have to type anything.

### Iterating over a vector

`size()` tells how many elements a vector holds. Combined with a `for` loop, it lets us go through every element:

```cpp
std::vector<std::string> teachers = {"Simon", "Samuel", "Ann", "Anna"};

for (std::size_t i = 0; i < teachers.size(); i++) {
    std::println("{}", teachers[i]);
}
```

Now you can see why loops in C++ conventionally start from 0 and use `<`: the valid indices of a vector of size `n` are exactly 0, 1, …, `n − 1`.

> **Why `std::size_t`?** `size()` returns an unsigned integer type called `std::size_t`, which cannot be negative. Comparing it with a signed `int` triggers a compiler warning. Using `std::size_t` for the loop counter keeps the compiler happy. (C++20 also offers `std::ssize(vec)`, which returns a signed size.)

### Exercise 3.4: List Size

*Template: `exercises/part03/03_04_ListSize`*

The template reads strings until an empty line. Make it print how many values were read. Use `size()`.

```
> Tom
> Emma
> Alex
> Mary
>
In total: 4
```

### Iterating over a vector, continued

### Exercise 3.5: Last in List

*Template: `exercises/part03/03_05_LastInList`*

After reading stops, print the last value in the vector. Use `size()` to find its index. (Vectors also have a member function `back()`, but use the index this time.)

### Exercise 3.6: First and Last

*Template: `exercises/part03/03_06_FirstAndLast`*

Print both the first and the last values. You may assume at least two values are read.

```
> Tom
> Emma
> Alex
> Mary
>
Tom
Mary
```

### Exercise 3.7: Remember These Numbers

*Template: `exercises/part03/03_07_RememberTheseNumbers`*

The template reads numbers until the user enters `-1`. Extend it to print all the numbers (not the `-1`), each on its own line.

### Exercise 3.8: Only These Numbers

*Template: `exercises/part03/03_08_OnlyTheseNumbers`*

After reading the numbers, ask for a start index and an end index, and print the numbers whose indices are in that range (inclusive). You may assume the indices are valid.

```
> 3
> 1
> 4
> 1
> 5
> -1
From where?
> 1
To where?
> 3
1
4
1
```

### Exercise 3.9: Greatest in List

*Template: `exercises/part03/03_09_GreatestInList`*

Find and print the greatest number in the vector. Here is how to find the *smallest*:

```cpp
int smallest = list[0];
for (std::size_t i = 0; i < list.size(); i++) {
    if (list[i] < smallest) {
        smallest = list[i];
    }
}
std::println("The smallest number: {}", smallest);
```

```
> 2
> 5
> 93
> 6
> -1
The greatest number: 93
```

### Exercise 3.10: Index Of

*Template: `exercises/part03/03_10_IndexOf`*

After reading the numbers, ask for a number and print every index where it appears. Print nothing if it is not in the vector.

```
> 72
> 2
> 8
> 8
> 11
> -1
Search for?
> 8
8 is at index 2
8 is at index 3
```

### Exercise 3.11: Index of Smallest

*Template: `exercises/part03/03_11_IndexOfSmallest`*

Read numbers until `9999`. Then print the smallest number and every index where it appears.

```
> 72
> 2
> 8
> 2
> 11
> 9999
Smallest number: 2
Found at index: 1
Found at index: 3
```

*Hint:* first find the smallest number; then go through the vector again and print the indices where it occurs.

### Iterating over a vector with a range-based `for` loop

When you need the values but not the indices, the **range-based `for` loop** is shorter and cannot go out of bounds:

```cpp
std::vector<std::string> teachers = {"Simon", "Samuel", "Ann", "Anna"};

for (const std::string& teacher : teachers) {
    std::println("{}", teacher);
}
```

Read it as "for each `teacher` in `teachers`". The `const std::string&` means that `teacher` *refers* to each element in turn (instead of copying it) and promises not to change it. For small types like `int` a plain copy is just as good: `for (int number : numbers)`. If you don't want to spell out the type, `for (const auto& teacher : teachers)` lets the compiler work it out.

### Exercise 3.12: Sum of a List

*Template: `exercises/part03/03_12_SumOfAList`*

After reading the numbers (until `-1`), print their sum. Use a range-based `for` loop.

```
> 72
> 2
> 8
> 11
> -1
Sum: 93
```

### Exercise 3.13: Average of a List

*Template: `exercises/part03/03_13_AverageOfAList`*

Print the average of the numbers. For the input above: `Average: 23.25`.

### Removing from a vector and checking whether a value exists

Vectors do not have a "remove this value" or "contains" member function, but the standard library has algorithms that do the job:

```cpp
#include <algorithm>
// ...
std::vector<std::string> list = {"First", "Second", "Third"};

// Does the vector contain "Second"?
if (std::ranges::contains(list, "Second")) {
    std::println("Second is on the list");
}

// Remove all elements equal to "First"
std::erase(list, "First");

// Remove the element at index 0
list.erase(list.begin());

// Remove the last element
list.pop_back();
```

`list.begin()` is an *iterator*: a position in the vector. `list.begin() + 2` is the position of index 2. We will meet iterators again later; for now, `list.erase(list.begin() + i)` removes the element at index `i`.

`std::ranges::contains` is a C++23 algorithm. If your compiler does not have it yet, write `std::ranges::find(list, value) != list.end()` instead.

### Exercise 3.14: On the List?

*Template: `exercises/part03/03_14_OnTheList`*

After reading names until an empty line, ask for one more name and tell whether it is in the vector.

```
> Tom
> Emma
> Alex
> Mary
>
Search for?
> Mary
Mary was found!
```

```
Search for?
> Logan
Logan was not found!
```

### A vector as a function parameter

Vectors can be passed to functions like any other value. There is one decision to make: **how** to pass it.

```cpp
void print(const std::vector<std::string>& list) {
    for (const auto& value : list) {
        std::println("{}", value);
    }
}
```

The `&` makes the parameter a **reference**: the function works on the caller's vector directly, instead of a copy. `const` promises that the function will not modify it. Passing a large container by `const&` is the normal way in C++: it is fast (no copying) and safe (no accidental changes).

### Exercise 3.15: Print in Range

*Template: `exercises/part03/03_15_PrintInRange`*

Write `void printNumbersInRange(const std::vector<int>& numbers, int lowerLimit, int upperLimit)`, which prints the numbers in the vector whose values are between the limits (inclusive).

```cpp
std::vector<int> numbers = {3, 2, 6, -1, 5, 1};
std::println("The numbers in the range [0, 5]");
printNumbersInRange(numbers, 0, 5);
std::println("The numbers in the range [3, 10]");
printNumbersInRange(numbers, 3, 10);
```

```
The numbers in the range [0, 5]
3
2
5
1
The numbers in the range [3, 10]
3
6
5
```

### Exercise 3.16: Sum

*Template: `exercises/part03/03_16_Sum`*

Write `int sum(const std::vector<int>& numbers)`, which returns the sum of the numbers. For `{3, 2, 6, -1}` it returns 10; after adding 5 and 1, it returns 16.

### Copying a vector into a function parameter

Here C++ differs sharply from Java and Python. In C++ a vector parameter **without** `&` receives a full **copy** of the caller's vector. Changes made to the copy are invisible to the caller:

```cpp
void addElement(std::vector<int> numbers) {   // a copy!
    numbers.push_back(99);
}

void reallyAddElement(std::vector<int>& numbers) {   // a reference
    numbers.push_back(99);
}

int main() {
    std::vector<int> list = {1, 2, 3};
    addElement(list);
    std::println("{}", list);         // [1, 2, 3]
    reallyAddElement(list);
    std::println("{}", list);         // [1, 2, 3, 99]
}
```

So the rule is:

| Parameter | Meaning | Use when |
|---|---|---|
| `std::vector<int> v` | the function gets its own copy | it needs a private copy to modify |
| `const std::vector<int>& v` | read-only access to the caller's vector | it only reads (the usual case) |
| `std::vector<int>& v` | read-write access to the caller's vector | it must change the caller's vector |

Notice also that in C++23 `std::println("{}", list)` prints a whole vector: `[1, 2, 3]`. Vectors of strings print with quotes: `["First", "Second"]`.

### Exercise 3.17: Remove Last

*Template: `exercises/part03/03_17_RemoveLast`*

Write `void removeLast(std::vector<std::string>& strings)`, which removes the last value of the vector. If the vector is empty, it does nothing.

```cpp
std::vector<std::string> strings = {"First", "Second", "Third"};
std::println("{}", strings);
removeLast(strings);
removeLast(strings);
std::println("{}", strings);
```

```
["First", "Second", "Third"]
["First"]
```

### A summary of vector operations

| Operation | Meaning |
|---|---|
| `std::vector<T> v;` | create an empty vector of `T`s |
| `std::vector<T> v = {a, b, c};` | create a vector with values |
| `v.push_back(x)` | add `x` to the end |
| `v[i]`, `v.at(i)` | element at index `i` (unchecked / checked) |
| `v.front()`, `v.back()` | first and last element |
| `v.size()`, `v.empty()` | number of elements; is it empty? |
| `v.pop_back()` | remove the last element |
| `v.erase(v.begin() + i)` | remove the element at index `i` |
| `std::erase(v, x)` | remove all elements equal to `x` |
| `std::ranges::contains(v, x)` | is `x` in `v`? |
| `v.clear()` | remove everything |

## 3.3 Arrays

A vector can change its size. Sometimes we know the number of elements exactly and it never changes — the days of the week, the squares of a chessboard, the RGB components of a colour. For these, C++ offers the fixed-size **array**, `std::array`, in the header `<array>`.

### Creating an array

```cpp
#include <array>
// ...
std::array<int, 3> numbers{};   // three ints, all zero
```

The type `std::array<int, 3>` reads "an array of three `int`s". The size is part of the type and must be known when the program is compiled. The empty braces `{}` set every element to zero.

An array can also be created with its values:

```cpp
std::array<int, 5> numbers = {100, 1, 42, 23, 1};
std::array<std::string, 3> words = {"Hello", "World", "!"};
```

### Assigning and accessing elements

Elements are accessed with `[]` and `at()`, exactly as with vectors:

```cpp
std::array<int, 3> numbers{};
numbers[0] = 2;
numbers[1] = 3;
numbers[2] = 5;
std::println("{}", numbers[1]);   // 3
```

To swap the values of two elements you need a temporary helper variable:

```cpp
int helper = numbers[0];
numbers[0] = numbers[1];
numbers[1] = helper;
```

(The standard library has a function for this as well: `std::swap(numbers[0], numbers[1]);`.)

### Exercise 3.18: Swap

*Template: `exercises/part03/03_18_Swap`*

The template creates an array and prints it. After the first printout, ask the user for two indices, swap the values at those indices, and print the array again. You may assume the indices are valid.

```
1
3
5
7
9

Give two indices to swap:
> 0
> 3
7
3
5
1
9
```

### Size of an array and iterating

An array knows its size, and the range-based `for` loop works with arrays too:

```cpp
std::array<int, 4> numbers = {1, 8, 10, 3};

for (std::size_t i = 0; i < numbers.size(); i++) {
    std::println("{}", numbers[i]);
}

for (int number : numbers) {
    std::println("{}", number);
}
```

### Exercise 3.19: Index Was Not Found

*Template: `exercises/part03/03_19_IndexWasNotFound`*

The template contains an array of numbers. Ask the user for a number; if it is in the array, print its index; otherwise say that it was not found.

```
Search for?
> 3
3 is at index 4.
```

```
Search for?
> 22
22 was not found.
```

### The type of the elements

The element type of an array can be anything: `std::array<double, 10>`, `std::array<std::string, 7>`, `std::array<bool, 64>`.

> **C-style arrays.** You will see older code that writes arrays as `int numbers[5] = {...};`. These *C-style arrays* come from the C language. They do not know their own size and turn into pointers when passed to functions, which is the source of many bugs. Prefer `std::array` (fixed size) and `std::vector` (variable size).

### An array as a function parameter

The size is part of an array's type, so a function taking `std::array<int, 5>` accepts only arrays of exactly five `int`s. Functions that should work on *any* sequence of `int`s can take a **span**, `std::span<const int>` from the header `<span>`. A span is a lightweight view that refers to the elements of an array or a vector:

```cpp
#include <span>

int sumOfNumbersInArray(std::span<const int> numbers) {
    int sum = 0;
    for (int number : numbers) {
        sum += number;
    }
    return sum;
}

int main() {
    std::array<int, 5> numbers = {5, 1, 3, 4, 2};
    std::vector<int> more = {1, 2, 3};
    std::println("{}", sumOfNumbersInArray(numbers));   // 15
    std::println("{}", sumOfNumbersInArray(more));      // 6
}
```

### Exercise 3.20: Sum of Array

*Template: `exercises/part03/03_20_SumOfArray`*

Complete `int sumOfNumbersInArray(std::span<const int> numbers)`, which returns the sum of the numbers.

### Exercise 3.21: Print Neatly

*Template: `exercises/part03/03_21_PrintNeatly`*

Complete `void printNeatly(std::span<const int> numbers)` so that it prints the numbers on one line, separated by a comma and a space, with no comma after the last number. Print with `std::print`, and end with a line break.

```
5, 1, 3, 4, 2
```

(Yes, `std::println("{}", numbers)` would almost do this — but here you practise doing it yourself.)

### Exercise 3.22: Print in Stars

*Template: `exercises/part03/03_22_PrintInStars`*

Complete `void printArrayInStars(std::span<const int> numbers)`, which prints, for each number, a row with that many stars. For `{5, 1, 3, 4, 2}`:

```
*****
*
***
****
**
```

### Arrays and vectors: when to use which

Use `std::vector` by default. It is the most used container in C++ and is extremely efficient. Use `std::array` when the number of elements is a fixed fact of the problem.

## 3.4 Using strings

### Reading and printing strings

You already know how to read a line into a `std::string` and print it. Strings also support `+` for joining, and `+=` for appending:

```cpp
std::string word = "cake";
std::string result = word + word;   // "cakecake"
result += "!";                      // "cakecake!"
```

### Exercise 3.23: Print Thrice

*Template: `exercises/part03/03_23_PrintThrice`*

Read a string and print it three times on one line. Do not use a loop.

```
Give a word:
> cake
cakecakecake
```

### String comparisons

As you saw in Chapter 1, `std::string` values are compared with `==` and `!=`. The operators `<`, `>`, `<=` and `>=` compare strings alphabetically (more precisely, character by character by their numeric codes, so all upper-case letters come before lower-case letters).

### Exercise 3.24: Is It True?

*Template: `exercises/part03/03_24_IsItTrue`*

Ask for a string. If it is `true`, print `You got it right!`; otherwise print `Try again!`.

```
Give a string:
> trueish
Try again!
```

### Exercise 3.25: Login

*Template: `exercises/part03/03_25_Login`*

Write a program that recognises these users:

| username | password |
|---|---|
| alex | sunshine |
| emma | haskell |

```
Enter username:
> alex
Enter password:
> sunshine
You have successfully logged in!
```

```
Enter username:
> alex
Enter password:
> thunderstorm
Incorrect username or password!
```

> **Warning.** Real systems never store passwords in program code or in plain text. They store a *salted hash* computed by a dedicated algorithm such as Argon2 or bcrypt.

### Useful string operations

| Operation | Meaning | Example (`s = "volcanologist"`) |
|---|---|---|
| `s.size()` / `s.length()` | number of characters | `13` |
| `s[i]` | the character at index `i` | `s[0]` is `'v'` |
| `s.substr(pos, n)` | `n` characters from `pos` | `s.substr(3, 3)` is `"can"` |
| `s.substr(pos)` | from `pos` to the end | `s.substr(7)` is `"logist"` |
| `s.find(t)` | index of the first `t`, or `std::string::npos` | `s.find("log")` is `7` |
| `s.contains(t)` | does `s` contain `t`? (C++23) | `s.contains("can")` is `true` |
| `s.starts_with(t)`, `s.ends_with(t)` | prefix and suffix tests | `s.ends_with("ist")` is `true` |
| `s.empty()` | is it empty? | `false` |

A single character has type `char` and is written in single quotes: `'a'`. Note the difference between `'a'` (a character) and `"a"` (a string of length one).

### Splitting a string

A very common task is to split a line into parts, such as words separated by spaces or fields separated by commas. The standard library does not have a ready-made `split` that returns a vector of strings, so we write one. It is a nice example of the string operations above:

```cpp
std::vector<std::string> split(const std::string& text, char delimiter) {
    std::vector<std::string> parts;
    std::size_t start = 0;
    while (true) {
        std::size_t end = text.find(delimiter, start);
        if (end == std::string::npos) {           // no more delimiters
            parts.push_back(text.substr(start));
            break;
        }
        parts.push_back(text.substr(start, end - start));
        start = end + 1;
    }
    return parts;
}
```

`text.find(delimiter, start)` searches for the delimiter starting at index `start`. When there are no more delimiters, the rest of the string is the last part.

```cpp
std::vector<std::string> pieces = split("first second third", ' ');
std::println("{}", pieces[0]);     // first
std::println("{}", pieces.size()); // 3
```

The templates of the exercises below already contain this `split` function.

### Exercise 3.26: Line by Line

*Template: `exercises/part03/03_26_LineByLine`*

Read lines until an empty line. Split each line at spaces and print each part on its own line.

```
> once upon a time
once
upon
a
time
> a little program
a
little
program
>
```

### Exercise 3.27: AV Club

*Template: `exercises/part03/03_27_AVClub`*

Read lines until an empty line. Split each at spaces and print the parts that contain `av`.

```
> java is a programming language
java
> navy blue shirt
navy
> Do you have a favorite flavor
have
favorite
flavor
>
```

### Data of fixed format

Splitting is especially useful for data in a fixed format, such as `name,age`:

```cpp
std::vector<std::string> parts = split("sebastian,2", ',');
std::string name = parts[0];
int age = std::stoi(parts[1]);
```

### Exercise 3.28: First Words

*Template: `exercises/part03/03_28_FirstWords`*

Read lines until an empty line. For each line, print its first word.

```
> one two three four
one
> this is a very important message
this
>
```

### Exercise 3.29: Last Words

*Template: `exercises/part03/03_29_LastWords`*

As above, but print the last word of each line.

```
> one two three four
four
```

### Using diverse text

### Exercise 3.30: Age of the Oldest

*Template: `exercises/part03/03_30_AgeOfTheOldest`*

Read `name,age` lines until an empty line. Then print the age of the oldest person. You may assume there is exactly one oldest person.

```
> sebastian,2
> lucas,2
> lily,1
> hanna,5
> gabriel,10
>
Age of the oldest: 10
```

### Exercise 3.31: Name of the Oldest

*Template: `exercises/part03/03_31_NameOfTheOldest`*

As above, but print the *name* of the oldest person: `Name of the oldest: gabriel`.

### Exercise 3.32: Personal Details

*Template: `exercises/part03/03_32_PersonalDetails`*

Read `name,birth year` lines until an empty line. Print the longest name and the average of the birth years. If several names are equally long, print any of them.

```
> sebastian,2017
> lucas,2017
> lily,2017
> hanna,2014
> gabriel,2009
>
Longest name: sebastian
Average of the birth years: 2014.8
```

## 3.5 Summary

The amount of data a program handles can now grow without limit: a vector holds as many values as needed, and loops process them all. In this chapter you learned:

- how to look for errors by observing the program, with print statements and a debugger,
- to store values in `std::vector`, access them by index, and iterate over them,
- that out-of-range indexing with `[]` is undefined behaviour, and how `at()` protects you,
- to pass containers to functions by `const&` (read), `&` (modify) or by value (copy),
- to use fixed-size `std::array` and the `std::span` view,
- many string operations, and how to split text into parts.
