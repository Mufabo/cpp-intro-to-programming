# Chapter 4: Objects and Files

This chapter introduces **object-oriented programming**: building programs out of objects that combine data with the operations on that data. You will write your own classes, store objects in vectors, and read data from files.

## 4.1 Introduction to object-oriented programming

Object-oriented programming is about isolating concepts into their own entities — that is, creating **abstractions**. You have used objects already: a `std::string` is an object that contains characters and knows how to tell its length, find a substring or append text. A `std::vector` is an object that holds values and knows how to add and remove them. You did not need to know *how* they do these things; it was enough to know *what* they can do.

When we create our own classes, we can do the same for the concepts of our own problem domain: a bank account, a student, a course, a game character.

### Classes and objects

A **class** is a blueprint that describes a kind of object: which data each object holds, and what operations it offers. An **object** is a concrete instance of a class.

The classic analogy is a house blueprint. The blueprint (the class) says that a house has rooms, doors and windows; actual houses built from it (objects) each have their own rooms, doors and windows, and each can be painted a different colour.

The data an object holds is stored in **member variables** (also called *instance variables* or *fields*). The operations are **member functions** (also called *methods*).

Here is how we might use a ready-made `Account` class:

```cpp
#include <print>
#include "Account.h"

int main() {
    Account artosAccount("Arto's account", 100.00);
    Account artosSwissAccount("Arto's account in Switzerland", 1000000.00);

    std::println("Initial state");
    std::println("{}", artosAccount.toString());
    std::println("{}", artosSwissAccount.toString());

    artosAccount.withdraw(20);
    std::println("The balance of Arto's account is now: {}", artosAccount.balance());
    artosSwissAccount.deposit(200);
    std::println("The balance of Arto's other account is now: {}", artosSwissAccount.balance());

    std::println("End state");
    std::println("{}", artosAccount.toString());
    std::println("{}", artosSwissAccount.toString());
}
```

```
Initial state
Arto's account 100
Arto's account in Switzerland 1000000
The balance of Arto's account is now: 80
The balance of Arto's other account is now: 1000200
End state
Arto's account 80
Arto's account in Switzerland 1000200
```

The line `#include "Account.h"` brings in the class definition from the file `Account.h` in the same folder. (Quotes are used for your own files, angle brackets for the standard library.)

`Account artosAccount("Arto's account", 100.00);` creates an object of type `Account`, named `artosAccount`, and passes two values to its **constructor**, which sets up the new object. Member functions are called with a dot: `artosAccount.withdraw(20)`.

> **Coming from Java?** In Java, objects are always created with `new` and variables hold *references* to them. In C++, `Account a("x", 1.0);` creates the object *right there*, inside the variable, just like `int x = 5;` creates an integer. There is no `new` and no garbage collector: the object is destroyed automatically when the variable goes out of scope. Chapter 5 explores what this means.

### Exercise 4.1: Your First Account

*Template: `exercises/part04/04_01_YourFirstAccount`*

The template contains the `Account` class shown above. Write a program that creates an account with a balance of 100.0, deposits 20.0 into it, and finally prints the account. Perform the operations in exactly this order.

### Exercise 4.2: Your First Bank Transfer

*Template: `exercises/part04/04_02_YourFirstBankTransfer`*

Write a program that:

1. creates an account named `"Matthew's account"` with the balance 1000,
2. creates an account named `"My account"` with the balance 0,
3. withdraws 100.0 from Matthew's account,
4. deposits 100.0 into My account,
5. prints both accounts.

### Creating classes

A class is defined with the keyword `class`. By convention each class gets its own header file named after the class. Let's create a class that represents a person — the file `Person.h`:

```cpp
#pragma once

#include <string>

class Person {
private:
    std::string name;
    int age;
};
```

- `#pragma once` at the top of a header prevents it from being included twice into the same file (which would be an error). Put it in every header you write.
- The member variables `name` and `age` are listed inside the class.
- `private:` means that the members below it can be used **only inside the class itself**. Hiding the internal data and offering access only through member functions is called **encapsulation**, and it is one of the central ideas of object-oriented programming.
- Note the **semicolon after the closing brace** of a class. Forgetting it causes baffling error messages.

A class can be pictured as a **class diagram**: a box with the class name at the top, the member variables in the middle and the member functions at the bottom. A `-` marks private members and a `+` public ones.

```
+---------------------+
|       Person        |
+---------------------+
| - name: string      |
| - age: int          |
+---------------------+
```

### Exercise 4.3: Dog Attributes

*Template: `exercises/part04/04_03_DogAttributes`*

Create a file `Dog.h` in the exercise folder, and in it a class `Dog` with the private member variables `std::string name`, `std::string breed` and `int age`. Include `Dog.h` from `main.cpp` to check that it compiles. The class does not do anything yet — creating the file and the class is the exercise.

### Defining a constructor

A **constructor** is a special member function that initialises a new object. It has the same name as the class and no return type:

```cpp
#pragma once

#include <string>

class Person {
public:
    Person(const std::string& initialName)
        : name(initialName), age(0) {
    }

private:
    std::string name;
    int age;
};
```

The constructor is `public` so that code outside the class can create persons. The part after the colon, `: name(initialName), age(0)`, is the **member initialiser list**. It initialises each member variable before the constructor's body runs. This is the preferred way to set member variables in C++. The body `{ }` is empty here because there is nothing more to do.

Now we can create objects:

```cpp
Person ada("Ada");
```

The string parameter is taken as `const std::string&` — a read-only reference — to avoid copying the string just to pass it in. This is the usual way to pass strings and other objects to functions.

> **Uninitialised variables.** If a constructor does not initialise an `int` or `double` member, its value is *indeterminate*: whatever bits happened to be in memory. Reading it is undefined behaviour. Always initialise every member, either in the initialiser list or directly at the declaration: `int age = 0;`.

### Exercise 4.4: Room

*Template: `exercises/part04/04_04_Room`*

Create a class `Room` (in `Room.h`) with the private members `std::string code` and `int seats`, and a constructor `Room(const std::string& classCode, int numberOfSeats)` that initialises them.

### Defining member functions

Member functions are defined inside the class, usually in the `public` section:

```cpp
class Person {
public:
    Person(const std::string& initialName)
        : name(initialName), age(0) {
    }

    void printPerson() const {
        std::println("{}, age {} years", name, age);
    }

private:
    std::string name;
    int age;
};
```

A member function can use the member variables of the object it is called on directly: `name` and `age` here are *this* person's name and age. If you want to make that explicit, you can write `this->name`; the pointer `this` refers to the current object.

The word `const` after the parameter list promises that the function does not change the object. Functions that only *look* at the object (printing, returning values) should always be marked `const`. It documents intent, lets the compiler catch mistakes, and allows the function to be called on `const` objects.

```cpp
Person ada("Ada");
Person grace("Grace");
ada.printPerson();
grace.printPerson();
```

```
Ada, age 0 years
Grace, age 0 years
```

### Exercise 4.5: Whistle

*Template: `exercises/part04/04_05_Whistle`*

Create a class `Whistle` with a private member `std::string sound`, a constructor `Whistle(const std::string& whistleSound)`, and a member function `void sound() const` that prints the sound.

```cpp
Whistle duckWhistle("Kvaak");
Whistle roosterWhistle("Peef");
duckWhistle.sound();
roosterWhistle.sound();
duckWhistle.sound();
```

```
Kvaak
Peef
Kvaak
```

(Can a member variable and a member function both be called `sound`? No — they would clash. Call the variable something else, such as `soundText`.)

### Exercise 4.6: Door

*Template: `exercises/part04/04_06_Door`*

Create a class `Door` with no member variables and a member function `void knock() const` that prints `Who's there?`. You do not need to write a constructor: a class without one gets a *default constructor* automatically.

```cpp
Door alexander;
alexander.knock();
alexander.knock();
```

### Exercise 4.7: Product

*Template: `exercises/part04/04_07_Product`*

Create a class `Product` with a name (`std::string`), a price (`double`) and a quantity (`int`), a constructor `Product(const std::string& initialName, double initialPrice, int initialQuantity)`, and a member function `void printProduct() const` that prints:

```
Banana, price 1.1, 13 pcs
```

### Changing a member variable's value in a member function

Member functions that are *not* `const` can change the object:

```cpp
void growOlder() {
    age = age + 1;
}
```

```cpp
Person ada("Ada");
ada.printPerson();
ada.growOlder();
ada.growOlder();
ada.printPerson();
```

```
Ada, age 0 years
Ada, age 2 years
```

Each object has its own member variables. Calling `growOlder` on `ada` changes only `ada`'s age.

Member functions can also contain conditions, so that an object protects its own consistency:

```cpp
void growOlder() {
    if (age < 30) {
        age = age + 1;
    }
}
```

### Exercise 4.8: Decreasing Counter (3 parts)

*Template: `exercises/part04/04_08_DecreasingCounter`*

The template contains a partly finished class `DecreasingCounter`:

```cpp
class DecreasingCounter {
public:
    DecreasingCounter(int initialValue) : value(initialValue) {
    }

    void printValue() const {
        std::println("value: {}", value);
    }

    void decrement() {
        // write the implementation here
        // the aim is to decrement the value of the counter by one
    }

    // and the other member functions go here

private:
    int value;   // the counter's value
};
```

**Part 1.** Implement `decrement()` so that it decreases the value by one.

```cpp
DecreasingCounter counter(10);
counter.printValue();
counter.decrement();
counter.printValue();
counter.decrement();
counter.printValue();
```

```
value: 10
value: 9
value: 8
```

**Part 2.** Change `decrement()` so that the value never becomes negative: when it is 0, decrementing does nothing.

**Part 3.** Add a member function `void reset()` that sets the value to 0.

### Exercise 4.9: Debt

*Template: `exercises/part04/04_09_Debt`*

Create a class `Debt` with `double` members `balance` and `interestRate`, set through the constructor `Debt(double initialBalance, double initialInterestRate)`. Add `void printBalance() const`, which prints the balance, and `void waitOneYear()`, which multiplies the balance by the interest rate.

```cpp
Debt mortgage(120000.0, 1.01);
mortgage.printBalance();

mortgage.waitOneYear();
mortgage.printBalance();

int years = 0;
while (years < 20) {
    mortgage.waitOneYear();
    years = years + 1;
}
mortgage.printBalance();
```

```
120000
121200
147887.0328416936
```

Then try the same with the interest rates of the early 1990s Finnish recession, about 1.13 — the result is sobering.

### Returning a value from a member function

Member functions can return values just like ordinary functions. A common kind of member function simply returns the value of a member variable; such functions are called **getters**:

```cpp
class Person {
public:
    // ...
    int getAge() const {
        return age;
    }

    std::string getName() const {
        return name;
    }

    bool isOfLegalAge() const {
        return age >= 18;
    }
    // ...
};
```

Getters let code outside the class *read* private data without being able to change it. In this book we name getters either `getAge()` or simply `age()`, following what the exercise asks for. (A member variable and a member function cannot share a name, so in the latter case the member variable needs a different name, for example `age_` or `ageInYears`. A trailing underscore is a common C++ convention for member variables.)

### Exercise 4.10: Song

*Template: `exercises/part04/04_10_Song`*

Create a class `Song` with a name (`std::string`) and a length in seconds (`int`), both set in the constructor `Song(const std::string& name, int length)`. Add the member functions `std::string name() const` and `int length() const`.

```cpp
Song garden("In The Garden", 10910);
std::println("The song {} has a length of {} seconds.", garden.name(), garden.length());
```

```
The song In The Garden has a length of 10910 seconds.
```

### Exercise 4.11: Film

*Template: `exercises/part04/04_11_Film`*

Create a class `Film` with a name and an age rating, the constructor `Film(const std::string& filmName, int filmAgeRating)`, and the member functions `std::string name() const` and `int ageRating() const`.

```cpp
Film chipmunks("Alvin and the Chipmunks: The Squeakquel", 0);

std::println("How old are you?");
std::string line;
std::getline(std::cin, line);
int age = std::stoi(line);

std::println("");
if (age >= chipmunks.ageRating()) {
    std::println("You may watch the film {}", chipmunks.name());
} else {
    std::println("You may not watch the film {}", chipmunks.name());
}
```

### Exercise 4.12: Gauge

*Template: `exercises/part04/04_12_Gauge`*

Create a class `Gauge` with a private `int` member (initially 0) and the member functions:

- `void increase()` — increases the value by one, but never above five,
- `void decrease()` — decreases the value by one, but never below zero,
- `int value() const` — returns the value,
- `bool full() const` — returns `true` when the value is five.

```cpp
Gauge g;
while (!g.full()) {
    std::println("Not full! Value: {}", g.value());
    g.increase();
}
std::println("Full! Value: {}", g.value());
g.decrease();
std::println("Not full! Value: {}", g.value());
```

```
Not full! Value: 0
Not full! Value: 1
Not full! Value: 2
Not full! Value: 3
Not full! Value: 4
Full! Value: 5
Not full! Value: 4
```

### A string representation of an object

Printing an object with a dedicated `print` function is inflexible: what if we want to write the description into a file, or combine it with other text? A more useful approach is a member function that *returns* the description as a string. We call it `toString`:

```cpp
std::string toString() const {
    return std::format("{}, age {} years", name, age);
}
```

`std::format` (from the header `<format>`) works like `std::println` but returns the formatted text as a `std::string` instead of printing it. Now the caller decides what to do with the text:

```cpp
Person ada("Ada");
std::println("{}", ada.toString());
std::string description = "Person: " + ada.toString();
```

(Chapter 10 shows how to teach `std::println` to print our own objects directly, so that `std::println("{}", ada)` works.)

### Exercise 4.13: Agent

*Template: `exercises/part04/04_13_Agent`*

The template contains a class `Agent` with a first name and a last name, and a `print` member function:

```cpp
Agent bond("James", "Bond");
bond.print();
```

```
My name is Bond, James Bond
```

Remove `print` and write `std::string toString() const` instead, returning the same text.

```cpp
Agent bond("James", "Bond");
bond.toString();   // prints nothing
std::println("{}", bond.toString());

Agent ionic("Ionic", "Bond");
std::println("{}", ionic.toString());
```

```
My name is Bond, James Bond
My name is Bond, Ionic Bond
```

### Member function parameters

Member functions can take parameters:

```cpp
void growOlder(int years) {
    if (years >= 0) {
        age = age + years;
    }
}
```

### A parameter and a member variable with the same name

What if a parameter has the same name as a member variable?

```cpp
void setHeight(int height) {
    height = height;   // does nothing useful!
}
```

Inside the function, `height` means the *parameter*, which hides the member. The assignment copies the parameter onto itself. To reach the member, write `this->height`:

```cpp
void setHeight(int height) {
    this->height = height;
}
```

Or avoid the problem altogether with a naming convention such as `height_` for members.

### Exercise 4.14: Multiplier

*Template: `exercises/part04/04_14_Multiplier`*

Create a class `Multiplier` with a constructor `Multiplier(int number)` and a member function `int multiply(int number) const` that returns its parameter multiplied by the number given to the constructor.

```cpp
Multiplier multiplyByThree(3);
std::println("multiplyByThree.multiply(2): {}", multiplyByThree.multiply(2));
Multiplier multiplyByFour(4);
std::println("multiplyByFour.multiply(2): {}", multiplyByFour.multiply(2));
std::println("multiplyByThree.multiply(1): {}", multiplyByThree.multiply(1));
std::println("multiplyByFour.multiply(1): {}", multiplyByFour.multiply(1));
```

```
multiplyByThree.multiply(2): 6
multiplyByFour.multiply(2): 8
multiplyByThree.multiply(1): 3
multiplyByFour.multiply(1): 4
```

### Calling another member function

A member function can call other member functions of the same object simply by name:

```cpp
bool isAdult() const {
    return age >= 18;
}

std::string toString() const {
    std::string status = isAdult() ? "an adult" : "a minor";
    return std::format("{} is {}", name, status);
}
```

The expression `condition ? a : b` is the **conditional operator**: it evaluates to `a` if the condition is true and to `b` otherwise. It is convenient for choosing between two values.

### Exercise 4.15: Statistics (4 parts)

*Template: `exercises/part04/04_15_NumberStatistics`*

**Part 1: Count.** The template has a file `Statistics.h` with the outline of a class `Statistics`. Implement:

- `void addNumber(int number)` — adds a number to the statistics,
- `int getCount() const` — returns how many numbers have been added.

The class does not need to store the numbers; it is enough to count them.

```cpp
Statistics statistics;
statistics.addNumber(3);
statistics.addNumber(5);
statistics.addNumber(1);
statistics.addNumber(2);
std::println("Count: {}", statistics.getCount());
```

```
Count: 4
```

**Part 2: Sum and average.** Add `int sum() const` and `double average() const`. Both return 0 when no numbers have been added. For the example above the sum is 11 and the average 2.75.

**Part 3: Sum of user input.** Without changing the class, write a `main` that reads numbers from the user until `-1` and prints their sum using a `Statistics` object.

```
Enter numbers:
> 4
> 2
> 5
> 4
> -1
Sum: 15
```

**Part 4: Multiple sums.** Use *three* `Statistics` objects: one for all numbers, one for even numbers and one for odd numbers.

```
Enter numbers:
> 4
> 2
> 5
> 2
> -1
Sum: 13
Sum of even numbers: 8
Sum of odd numbers: 5
```

### Exercise 4.16: Payment Card (6 parts)

*Template: `exercises/part04/04_16_PaymentCard`*

At the University of Helsinki's student canteen, students pay for lunch with a payment card. In this exercise you build a class `PaymentCard` that mimics it.

**Part 1: The class.** Create `PaymentCard.h` with a class `PaymentCard`. Its constructor `PaymentCard(double openingBalance)` stores the balance. Its member function `std::string toString() const` returns `The card has a balance of X euros`, with the balance printed with one decimal (use the format specification `{:.1f}`).

```cpp
PaymentCard card(50);
std::println("{}", card.toString());
```

```
The card has a balance of 50.0 euros
```

**Part 2: Making transactions.** Add `void eatAffordably()`, which reduces the balance by €2.60, and `void eatHeartily()`, which reduces it by €4.60.

```cpp
PaymentCard card(50);
card.eatAffordably();
std::println("{}", card.toString());
card.eatHeartily();
card.eatAffordably();
std::println("{}", card.toString());
```

```
The card has a balance of 47.4 euros
The card has a balance of 40.2 euros
```

**Part 3: Non-negative balance.** Change both functions so that they do nothing if the balance is not sufficient for the meal.

**Part 4: Topping up.** Add `void addMoney(double amount)`, which increases the balance — but never above 150 euros. Anything beyond that is lost.

**Part 5: Negative top-ups.** If `amount` is negative, `addMoney` does nothing.

**Part 6: Multiple cards.** In `main`, write the following sequence:

1. Create Paul's card with an opening balance of 20 euros.
2. Create Matt's card with an opening balance of 30 euros.
3. Paul eats heartily.
4. Matt eats affordably.
5. Print both cards (prefix each line with the owner's name, like `Paul: The card has...`).
6. Paul tops up 20 euros.
7. Matt eats heartily.
8. Print both cards.
9. Paul eats affordably twice.
10. Matt tops up 50 euros.
11. Print both cards.

```
Paul: The card has a balance of 15.4 euros
Matt: The card has a balance of 27.4 euros
Paul: The card has a balance of 35.4 euros
Matt: The card has a balance of 22.8 euros
Paul: The card has a balance of 30.2 euros
Matt: The card has a balance of 72.8 euros
```

> **Money and floating-point numbers.** Floating-point numbers cannot represent most decimal fractions exactly: `0.1 + 0.2` is `0.30000000000000004`. That is fine for this exercise, but real financial software stores money as an integer number of cents.

## 4.2 Objects in a vector

Vectors can hold objects of any type, including our own classes:

```cpp
std::vector<Person> persons;
persons.push_back(Person("Ada"));
persons.emplace_back("Grace");   // constructs the Person directly inside the vector

for (const Person& person : persons) {
    std::println("{}", person.toString());
}
```

`push_back` takes a ready object; `emplace_back` takes the constructor's arguments and builds the object in place. Both are fine.

Note that the vector stores **copies** of the objects. Changing `persons[0]` changes the object inside the vector; it has nothing to do with any other `Person` variable in the program.

### Adding user-inputted objects to a vector

```cpp
std::vector<Person> persons;
std::string name;
while (true) {
    std::println("Enter a name, empty will stop:");
    std::getline(std::cin, name);
    if (name.empty()) {
        break;
    }
    persons.emplace_back(name);
}

std::println("");
std::println("Persons in total: {}", persons.size());
for (const Person& person : persons) {
    std::println("{}", person.toString());
}
```

### Exercise 4.17: Items

*Template: `exercises/part04/04_17_Items`*

The template contains a class `Item` (do not change it), which remembers its name and the time it was created. Write a program that reads item names until an empty line, creates an `Item` for each, and stores them in a vector. Then print all the items using `toString`.

```
Name:
> Hammer
Name:
> Collar
Name:
>
Hammer (created at: 06.07.2026 12:34:56)
Collar (created at: 06.07.2026 12:34:57)
```

### Multiple constructor parameters

### Exercise 4.18: Personal Information

*Template: `exercises/part04/04_18_PersonalInformation`*

The template contains a class `PersonalInformation` (do not change it) with a first name, a last name and an identification number. Write a program that reads people until the first name is empty, and then prints each person's first and last names.

```
First name:
> Jean
Last name:
> Bartik
Identification number:
> 271224
First name:
> Betty
Last name:
> Holberton
Identification number:
> 070317
First name:
>

Jean Bartik
Betty Holberton
```

### Filtered printing from a vector

Combining a loop and a condition lets us print only some of the objects:

```cpp
for (const Person& person : persons) {
    if (person.getAge() >= 18) {
        std::println("{}", person.toString());
    }
}
```

### Exercise 4.19: Television Programs

*Template: `exercises/part04/04_19_TelevisionPrograms`*

The template contains a class `TelevisionProgram` with a name and a duration. Read programs until the name is empty. Then ask for a maximum duration and print the programs whose duration is at most that.

```
Name:
> Rick and Morty
Duration:
> 25
Name:
> Two and a Half Men
Duration:
> 30
Name:
> Love it or list it
Duration:
> 60
Name:
>

Program's maximum duration?
> 30
Rick and Morty, 25 minutes
Two and a Half Men, 30 minutes
```

### Exercise 4.20: Books (2 parts)

*Template: `exercises/part04/04_20_Books`*

Write a program that reads books — title, number of pages, publication year — until the title is empty. Then ask what to print. If the user answers `everything`, print all details; if `name`, print only the titles. Create a class `Book` for the job.

```
Title:
> To Kill a Mockingbird
Pages:
> 281
Publication year:
> 1960
Title:
> Beautiful Code
Pages:
> 593
Publication year:
> 2007
Title:
>

What information will be printed?
> everything
To Kill a Mockingbird, 281 pages, 1960
Beautiful Code, 593 pages, 2007
```

```
What information will be printed?
> name
To Kill a Mockingbird
Beautiful Code
```

## 4.3 Files and reading data

Programs often need data that does not come from the keyboard: a list of names, a table of measurements, the saved state of a game. Such data is stored in **files**.

### Reading from the keyboard, revisited

Reading from the keyboard and reading from a file work almost identically in C++: both are *input streams*. `std::cin` is the input stream connected to the keyboard, and `std::getline` reads a line from any input stream.

Here is a pattern you already know — read until a terminating word:

```cpp
std::string line;
while (true) {
    std::getline(std::cin, line);
    if (line == "end") {
        break;
    }
    // handle the line
}
```

### Exercise 4.21: Number of Strings

*Template: `exercises/part04/04_21_NumberOfStrings`*

Read strings until the user enters `end`, then print how many strings were read (`end` not included).

```
> I
> have
> a
> feeling
> end
4
```

### Exercise 4.22: Cubes

*Template: `exercises/part04/04_22_Cubes`*

Read strings until `end`. Treat every other input as an integer and print its cube.

```
> 3
27
> -1
-1
> 11
1331
> end
```

### Files and the file system

Files live in a **file system**, organised into folders (directories). A file is identified by its **path**: `/home/ada/notes.txt` on Linux or `C:\Users\ada\notes.txt` on Windows. A *relative* path like `notes.txt` or `data/notes.txt` is interpreted relative to the program's **working directory** — the folder in which the program was started.

That is why, as explained in the preface, the exercise programs that use files should be run from their own build folder: the build copies the data files there.

### Exercise 4.23: Creating a New File

*Template: `exercises/part04/04_23_CreatingANewFile`*

This exercise has no programming. Using your editor, create a file called `file.txt` in the exercise folder, containing the text `Hello, world!`. Then run CMake again (the build copies `.txt` files to the program's folder) and check that the file appears in the build folder.

### Reading from a file

Files are read with `std::ifstream` ("input file stream") from the header `<fstream>`:

```cpp
#include <fstream>
#include <print>
#include <string>

int main() {
    std::ifstream file("file.txt");
    if (!file) {
        std::println("Could not open file.txt");
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::println("{}", line);
    }
}
```

- `std::ifstream file("file.txt");` opens the file for reading.
- `if (!file)` checks whether opening succeeded. It fails, for example, when the file does not exist. Returning `1` from `main` tells the operating system that the program ended with an error.
- `while (std::getline(file, line))` reads one line per round. `std::getline` returns the stream, which converts to `false` when there are no more lines, ending the loop.

The file is closed automatically when `file` goes out of scope — at the end of `main` here. This automatic cleanup is a cornerstone of C++ called **RAII** ("Resource Acquisition Is Initialisation"): an object that acquires a resource (a file, memory, a network connection) releases it in its *destructor*, which runs automatically when the object's lifetime ends.

### Exercise 4.24: Printing a File

*Template: `exercises/part04/04_24_PrintingAFile`*

Print the contents of the file `data.txt`, line by line.

### Exercise 4.25: Printing a Specified File

*Template: `exercises/part04/04_25_PrintingASpecifiedFile`*

Ask the user for a file name and print that file. You may assume the file exists. The exercise folder contains `data.txt` and `song.txt` for testing.

```
Which file should have its contents printed?
> data.txt
In a
world
```

### Exercise 4.26: Guest List from a File

*Template: `exercises/part04/04_26_GuestListFromAFile`*

The template contains a guest list program that checks whether names typed by the user are on the list. It is missing the part that reads the list from a file. Implement it: ask for the name of the file and read each line as a name into the vector.

```
Name of the file:
> guestlist.txt
Enter names, an empty line quits.
> Chuck Norris
The name is not on the list.
> Jack Bauer
The name is on the list.
>
Thank you!
```

### Exercise 4.27: Is It in the File?

*Template: `exercises/part04/04_27_IsItInTheFile`*

Ask for a file name and a search string. Print `Found!` if a line of the file equals the string, and `Not found.` otherwise. If the file cannot be opened, print `Reading the file <name> failed.`

```
Name of the file:
> names.txt
Search for:
> ada
Found!
```

```
Name of the file:
> nonexistent.txt
Search for:
> test
Reading the file nonexistent.txt failed.
```

### Exercise 4.28: Numbers from a File

*Template: `exercises/part04/04_28_NumbersFromAFile`*

Ask for a file name and a lower and an upper bound. The file contains one integer per line. Print how many of the numbers are within the bounds (inclusive).

```
File?
> numbers-1.txt
Lower bound?
> 15
Upper bound?
> 20
Numbers: 2
```

### Reading data of a specific format from a file

Files often contain records in a format like **CSV** ("comma-separated values"), where each line is one record and the fields are separated by commas:

```
lily,3
anton,5
levi,4
amy,1
```

Reading such a file combines file reading with the `split` function from Chapter 3:

```cpp
std::ifstream file("data.txt");
std::string line;
while (std::getline(file, line)) {
    std::vector<std::string> parts = split(line, ',');
    std::string name = parts[0];
    int age = std::stoi(parts[1]);
    std::println("Name: {}, age: {}", name, age);
}
```

Real files often contain an empty line at the end. A robust program skips lines it cannot understand — for now, `if (line.empty()) { continue; }` is enough.

### Exercise 4.29: Records from a File

*Template: `exercises/part04/04_29_RecordsFromAFile`*

Ask for the name of a CSV file of names and ages, and print its records as follows. Note the singular `year` for the age 1.

```
Name of the file:
> data.txt
lily, age: 3 years
anton, age: 5 years
levi, age: 4 years
amy, age: 1 year
```

### Reading objects from a file

Usually each record becomes an object:

```cpp
std::vector<Person> readPersons(const std::string& fileName) {
    std::vector<Person> persons;
    std::ifstream file(fileName);
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        std::vector<std::string> parts = split(line, ',');
        persons.emplace_back(parts[0], std::stoi(parts[1]));
    }
    return persons;
}
```

Returning a vector from a function is efficient in modern C++: the vector is *moved* to the caller rather than copied.

### Exercise 4.30: Storing Records

*Template: `exercises/part04/04_30_StoringRecords`*

The template contains a class `Person` and a function `std::vector<Person> readRecordsFromFile(const std::string& fileName)` with an empty body. Implement the function so that it reads the people from the given CSV file. Modify only that function; `main` is there for testing.

### Exercise 4.31: Sport Statistics (2 parts)

*Template: `exercises/part04/04_31_SportStatistics`*

The file `data.csv` contains match results. Each line has the home team, the visiting team, the home team's points and the visiting team's points:

```
ENCE,Vitality,9,16
ENCE,Vitality,16,12
ENCE,Vitality,9,16
ENCE,Heroic,10,16
SJ,ENCE,0,16
SJ,ENCE,3,16
FURIA,NRG,7,16
FURIA,Prospects,16,1
```

Ask for a file name and a team name.

**Part 1: Games played.** Print how many games the team played.

```
File:
> data.csv
Team:
> FURIA
Games: 2
```

**Part 2: Wins and losses.** Also print the team's wins and losses. The team with more points wins.

```
File:
> data.csv
Team:
> ENCE
Games: 6
Wins: 3
Losses: 3
```

## 4.4 Summary

This chapter introduced the central ideas of object-oriented programming. You learned to:

- define classes with private member variables, constructors and member functions,
- initialise members with the member initialiser list,
- mark member functions that do not change the object as `const`,
- write getters and a `toString` member function, using `std::format`,
- keep objects in a `std::vector` and process them with loops,
- read text files with `std::ifstream` and `std::getline`, including CSV data.

The idea of bundling data together with the operations that keep it consistent — encapsulation — will be with us for the rest of the book.
