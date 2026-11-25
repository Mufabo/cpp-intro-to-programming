# Chapter 5: Classes in Depth — Overloading, Values and References

This chapter deepens your understanding of classes. You will learn to give a class several constructors, to overload member functions, and — most importantly — how C++ objects behave when they are assigned, passed to functions and returned from them. This is where C++ differs most from languages like Java and Python, so read the middle sections carefully.

## 5.1 Learning object-oriented programming

Object-oriented programming is not about syntax; it is a way of *thinking* about a problem. We look at the problem domain, find its concepts, and model each concept as a class that hides its details behind a small set of operations.

Consider a clock that shows hours, minutes and seconds. Each of the three "hands" behaves the same way: it counts up to a limit and then wraps around to zero. That behaviour is a concept of its own, so let's write a class for it:

```cpp
#pragma once

#include <format>
#include <string>

class ClockHand {
public:
    ClockHand(int limit) : value(0), limit(limit) {
    }

    void advance() {
        value = value + 1;
        if (value >= limit) {
            value = 0;
        }
    }

    int getValue() const {
        return value;
    }

    std::string toString() const {
        return std::format("{:02}", value);
    }

private:
    int value;
    int limit;
};
```

The format specification `{:02}` prints the number with at least two digits, padding with zeros: `5` becomes `05`.

A clock is then built from three hands:

```cpp
class Clock {
public:
    Clock() : hours(24), minutes(60), seconds(60) {
    }

    void advance() {
        seconds.advance();
        if (seconds.getValue() == 0) {
            minutes.advance();
            if (minutes.getValue() == 0) {
                hours.advance();
            }
        }
    }

    std::string toString() const {
        return hours.toString() + ":" + minutes.toString() + ":" + seconds.toString();
    }

private:
    ClockHand hours;
    ClockHand minutes;
    ClockHand seconds;
};
```

```cpp
Clock clock;
for (int i = 0; i < 3; i++) {
    std::println("{}", clock.toString());
    clock.advance();
}
```

```
00:00:00
00:00:01
00:00:02
```

Each part of the program is simple. `ClockHand` knows nothing about clocks; `Clock` knows nothing about how a hand wraps around. Programs built from small, focused classes are easier to understand, test and change.

### Exercise 5.1: One Minute

*Template: `exercises/part05/05_01_OneMinute`*

The template contains `ClockHand`. Implement a class `Timer` with two hands: hundredths of a second (limit 100) and seconds (limit 60). When the hundredths hand wraps around to zero, the seconds hand advances.

- `Timer()` creates a timer.
- `std::string toString() const` returns `"seconds:hundredths"`, both with two digits, e.g. `"19:83"`.
- `void advance()` moves the timer forward by one hundredth of a second.

You can watch your timer run with this `main` (stop it with `Ctrl+C`):

```cpp
#include <chrono>
#include <thread>
// ...
Timer timer;
while (true) {
    std::println("{}", timer.toString());
    timer.advance();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}
```

### Object

An **object** is an independent entity that has **state** (its member variables) and **behaviour** (its member functions). Two objects of the same class have separate state: advancing one clock does not advance another.

### Class

A **class** defines a *type*. It specifies what data its objects contain and which operations they offer. Writing a class means designing a small vocabulary for talking about one concept: "advance the clock", "deposit into the account", "add a number to the statistics".

### Exercise 5.2: Book

*Template: `exercises/part05/05_02_Book`*

Create a class `Book` with an author, a name and a page count. Add:

- the constructor `Book(const std::string& author, const std::string& name, int pages)`,
- `std::string getAuthor() const`, `std::string getName() const`, `int getPages() const`,
- `std::string toString() const`, which returns for example

```
J. K. Rowling, Harry Potter and the Sorcerer's Stone, 223 pages
```

### Exercise 5.3: Cube

*Template: `exercises/part05/05_03_Cube`*

Create a class `Cube` with the constructor `Cube(int edgeLength)`, a member function `int volume() const` (edge × edge × edge) and `std::string toString() const`.

```cpp
Cube oSheaJackson(4);
std::println("{}", oSheaJackson.volume());
std::println("{}", oSheaJackson.toString());
```

```
64
The length of the edge is 4 and the volume 64
```

### Exercise 5.4: FitByte

*Template: `exercises/part05/05_04_FitByte`*

The Karvonen method calculates a target heart rate for exercise:

```
(maximum heart rate − resting heart rate) × (target percentage) + resting heart rate
```

The maximum heart rate can be estimated with `206.3 − (0.711 × age)`.

Create a class `Fitbyte` with the constructor `Fitbyte(int age, int restingHeartRate)` and the member function `double targetHeartRate(double percentageOfMaximum) const`, where the percentage is given as a fraction (0.75 for 75 %).

```cpp
Fitbyte assistant(30, 60);
double percentage = 0.5;
while (percentage < 1.0) {
    double target = assistant.targetHeartRate(percentage);
    std::println("Target {:.0f}% of maximum: {:.3f}", percentage * 100, target);
    percentage = percentage + 0.1;
}
```

```
Target 50% of maximum: 122.485
Target 60% of maximum: 134.982
Target 70% of maximum: 147.479
Target 80% of maximum: 159.976
Target 90% of maximum: 172.473
Target 100% of maximum: 184.970
```

## 5.2 Removing repetitive code: overloading

### Constructor overloading

A class can have several constructors, as long as their parameter lists differ. This is called **overloading**:

```cpp
class Person {
public:
    Person(const std::string& name, int age, int height, int weight)
        : name(name), age(age), height(height), weight(weight) {
    }

    Person(const std::string& name)
        : name(name), age(0), height(0), weight(0) {
    }
    // ...
};
```

```cpp
Person paul("Paul", 24, 180, 90);
Person ada("Ada");   // a newborn
```

The compiler chooses the constructor whose parameters match the arguments.

### Calling another constructor

The two constructors above repeat the same initialisations. A constructor can **delegate** to another constructor in its initialiser list:

```cpp
Person(const std::string& name)
    : Person(name, 0, 0, 0) {
}
```

Now all the real work happens in one place.

Often an even simpler solution is a **default member initialiser**: a value written directly at the member's declaration. Every constructor that does not initialise that member explicitly uses this value:

```cpp
class Person {
public:
    Person(const std::string& name) : name(name) {
    }

private:
    std::string name;
    int age = 0;
    int height = 0;
    int weight = 0;
};
```

### Exercise 5.5: Constructor Overload

*Template: `exercises/part05/05_05_ConstructorOverload`*

The template contains a class `Product` with a name, a location and a weight. Add three constructors:

- `Product(const std::string& name)` — location `"shelf"`, weight 1,
- `Product(const std::string& name, const std::string& location)` — weight 1,
- `Product(const std::string& name, int weight)` — location `"shelf"`.

```cpp
Product tapeMeasure("Tape measure");
Product plaster("Plaster", "home improvement section");
Product tyre("Tyre", 5);

std::println("{}", tapeMeasure.toString());
std::println("{}", plaster.toString());
std::println("{}", tyre.toString());
```

```
Tape measure (1 kg) can be found from the shelf
Plaster (1 kg) can be found from the home improvement section
Tyre (5 kg) can be found from the shelf
```

> **A classic C++ trap.** `Product p("Hammer", "toolbox");` calls the `(string, string)` constructor, as you would hope. But suppose the class also had a constructor `Product(const std::string& name, bool fragile)`. Then the same line would call the **`bool`** version! A string literal converts to `bool` (any non-null pointer is `true`) through a built-in conversion, and the compiler prefers built-in conversions over converting to `std::string`. Be careful when overloads take `bool`, and when in doubt, test.

### Function overloading

Ordinary functions and member functions can be overloaded the same way:

```cpp
void growOlder() {
    age = age + 1;
}

void growOlder(int years) {
    age = age + years;
}
```

An even shorter alternative here is a **default argument**: `void growOlder(int years = 1)` can be called both as `growOlder()` and as `growOlder(5)`.

### Exercise 5.6: Overloaded Counter (2 parts)

*Template: `exercises/part05/05_06_OverloadedCounter`*

**Part 1: Multiple constructors.** Create a class `Counter` with the constructors `Counter(int startValue)` and `Counter()` (which starts at 0), and the member functions `int value() const`, `void increase()` and `void decrease()`.

**Part 2: Alternative member functions.** Add `void increase(int increaseBy)` and `void decrease(int decreaseBy)`. If the argument is negative, the value does not change.

## 5.3 Values, references and pointers

This section explains the most important difference between C++ and many other languages.

### C++ objects are values

In C++, a variable **contains** its object. That is true for `int` and equally true for `std::string`, `std::vector` and your own classes. Assignment **copies** the object:

```cpp
int a = 10;
int b = a;     // b is a copy of a
b = 20;
std::println("{} {}", a, b);   // 10 20

Person ada("Ada");
Person copy = ada;    // copy is a separate Person with the same data
copy.growOlder();
std::println("{}", ada.toString());    // Ada, age 0 years
std::println("{}", copy.toString());   // Ada, age 1 years
```

This is called **value semantics**. Each variable owns its own independent object, and you can reason about each variable on its own: changing `copy` can never change `ada`.

> **Coming from Java or Python?** In those languages, a variable of a class type holds a *reference* to an object stored elsewhere, and `Person copy = ada;` makes both variables refer to the *same* object. The Java version of this course spends a whole section on this distinction between "primitive" and "reference" variables. In C++ there is no such split: everything behaves like an `int` by default. When you want sharing, you ask for it explicitly, as described next.

### References

A **reference** is an alias — another name for an existing object. It is declared with `&`:

```cpp
Person ada("Ada");
Person& alias = ada;   // alias IS ada, under another name
alias.growOlder();
std::println("{}", ada.toString());   // Ada, age 1 years
```

A reference must be initialised when it is created, and it can never be made to refer to another object. You have already used references for function parameters:

```cpp
void celebrate(Person& person) {   // works on the caller's object
    person.growOlder();
}

void show(const Person& person) {  // read-only access, no copy
    std::println("{}", person.toString());
}

void tryToCelebrate(Person person) {   // works on a copy
    person.growOlder();                // the caller never sees this
}
```

| Parameter | The function gets | Typical use |
|---|---|---|
| `T x` | its own copy | small types (`int`, `double`), or when a copy is needed anyway |
| `const T& x` | read-only access to the caller's object | reading objects (strings, vectors, classes) |
| `T& x` | read-write access to the caller's object | modifying the caller's object |

### Pointers

A **pointer** is a variable that holds the *address* of an object. It is declared with `*`, the address of an object is taken with `&`, and the object a pointer points to is reached with `*` or, for members, `->`:

```cpp
Person ada("Ada");
Person* pointer = &ada;          // pointer holds the address of ada
pointer->growOlder();            // same as (*pointer).growOlder()
std::println("{}", pointer->toString());
```

Unlike a reference, a pointer can be changed to point somewhere else, and it can point **nowhere** — it can hold the special value `nullptr`:

```cpp
Person* nobody = nullptr;
```

Dereferencing a null pointer (`nobody->growOlder()`) is **undefined behaviour**. On most systems the program crashes with a *segmentation fault*; the infamous "null pointer exception" of other languages is C++'s "null pointer crash". Before using a pointer that might be null, check it:

```cpp
if (nobody != nullptr) {
    nobody->growOlder();
}
```

In modern C++, ordinary code uses pointers much less than older C++ did. Use values by default, references for parameters, and the tools of later chapters (`std::unique_ptr`, containers) when objects must be shared or created dynamically. Raw pointers are mainly used as optional, non-owning "this might refer to something" handles.

### "Maybe a value": `std::optional`

A frequent reason to use a null pointer in other languages is to say "there might not be a value". C++ has a dedicated, safer tool for that: `std::optional` from the header `<optional>`.

```cpp
#include <optional>

std::optional<int> findIndex(const std::vector<int>& numbers, int searched) {
    for (std::size_t i = 0; i < numbers.size(); i++) {
        if (numbers[i] == searched) {
            return static_cast<int>(i);
        }
    }
    return std::nullopt;   // no value
}

int main() {
    std::vector<int> numbers = {4, 8, 15};
    std::optional<int> index = findIndex(numbers, 8);
    if (index.has_value()) {
        std::println("Found at {}", *index);
    } else {
        std::println("Not found");
    }
}
```

`*index` gives the contained value. `index.value()` does the same but **checks** first: if the optional is empty, it throws an `std::bad_optional_access` exception instead of invoking undefined behaviour.

### Exercise 5.7: Empty Optional

*Template: `exercises/part05/05_07_EmptyOptional`*

Write a program that stops with an `std::bad_optional_access` error immediately when it starts, without reading any input. (Hint: create an empty `std::optional` and call `value()` on it.)

### Objects and lifetimes

Every C++ object has a **lifetime**. A local variable is created when execution reaches its declaration and destroyed when execution leaves the enclosing block:

```cpp
{
    Person ada("Ada");
    // ada exists here
}
// ada has been destroyed here
```

This is why you never need to free memory or close files manually in modern C++: objects clean up after themselves at the end of their lifetime. It is also why you must never keep a reference or pointer to an object after its lifetime has ended — a **dangling reference**:

```cpp
Person& makePerson() {
    Person p("Temporary");
    return p;   // WRONG: p is destroyed when the function returns
}
```

Compilers warn about this case. The fix is simple: return the object itself (`Person makePerson()`), which is efficient thanks to *move semantics* and *copy elision*.

## 5.4 Objects as parameters, members and return values

### An object as a member variable

Objects can contain other objects. A `Clock` contained `ClockHand`s; similarly a person may have a pet:

```cpp
class Pet {
public:
    Pet(const std::string& name, const std::string& breed) : name(name), breed(breed) {}
    std::string getName() const { return name; }
    std::string getBreed() const { return breed; }

private:
    std::string name;
    std::string breed;
};

class Person {
public:
    Person(const std::string& name, const Pet& pet) : name(name), pet(pet) {}

private:
    std::string name;
    Pet pet;   // the person's own Pet object
};
```

Because objects are values, a `Person` *contains* its own copy of the `Pet`. That is exactly right when the contained object belongs to its owner, as a clock's hands belong to the clock.

### Exercise 5.8: Biggest Pet Shop

*Template: `exercises/part05/05_08_BiggestPetShop`*

The template contains the classes `Person` and `Pet`. Change `Person::toString` so that it also tells about the pet:

```cpp
Pet lucy("Lucy", "golden retriever");
Person leo("Leo", lucy);
std::println("{}", leo.toString());
```

```
Leo, has a friend called Lucy (golden retriever)
```

### An object as a function parameter

Objects are passed to functions like any other value, by copy or by reference. A function that should modify the caller's object must take a reference:

```cpp
class AmusementParkRide {
public:
    AmusementParkRide(const std::string& name, int lowestHeight)
        : name(name), lowestHeight(lowestHeight) {
    }

    bool allowedToRide(const Person& person) {
        if (person.getHeight() < lowestHeight) {
            return false;
        }
        visitors++;
        return true;
    }

private:
    std::string name;
    int lowestHeight;
    int visitors = 0;
};
```

`allowedToRide` only reads the person, so it takes `const Person&`.

### Exercise 5.9: Health Station (3 parts)

*Template: `exercises/part05/05_09_HealthStation`*

The template contains the familiar class `Person` and an outline of a class `HealthStation`.

**Part 1: Weighing.** Implement `int weigh(const Person& person)`, which returns the person's weight.

```cpp
HealthStation childrensHospital;
Person ethan("Ethan", 1, 110, 7);
Person peter("Peter", 33, 176, 85);

std::println("{}'s weight: {} kilos", ethan.getName(), childrensHospital.weigh(ethan));
std::println("{}'s weight: {} kilos", peter.getName(), childrensHospital.weigh(peter));
```

```
Ethan's weight: 7 kilos
Peter's weight: 85 kilos
```

**Part 2: Feeding.** Implement `void feed(Person& person)`, which increases the person's weight by one. Why must the parameter be a reference?

**Part 3: Counting weighings.** Implement `int weighings() const`, which returns how many times the station has weighed someone.

### Exercise 5.10: Card Payments (4 parts)

*Template: `exercises/part05/05_10_CardPayments`*

In Chapter 4 the payment card knew the meal prices. That is poor design: when prices change, every card would have to change. Let's make the card "dumb" and move the knowledge to a payment terminal.

**Part 1: A dumb payment card.** The template's `PaymentCard` has `double balance() const` and `void addMoney(double increase)`. Implement `bool takeMoney(double amount)`, which takes money from the card only if the balance is at least `amount`, and returns whether it did.

```cpp
PaymentCard petesCard(10);
std::println("money {}", petesCard.balance());
bool wasSuccessful = petesCard.takeMoney(8);
std::println("successfully took: {}", wasSuccessful);
std::println("money {}", petesCard.balance());
wasSuccessful = petesCard.takeMoney(4);
std::println("successfully took: {}", wasSuccessful);
std::println("money {}", petesCard.balance());
```

```
money 10
successfully took: true
money 2
successfully took: false
money 2
```

**Part 2: Payment terminal and cash.** Implement the class `PaymentTerminal` from the template. It starts with 1000 euros of cash. An affordable meal costs €2.50 and a hearty meal €4.30.

- `double eatAffordably(double payment)` — if the payment is enough, add the price to the cash, count the sale and return the change; otherwise return the whole payment.
- `double eatHeartily(double payment)` — the same for hearty meals.

```cpp
PaymentTerminal unicafeExactum;
double change = unicafeExactum.eatAffordably(10);
std::println("remaining change: {}", change);
change = unicafeExactum.eatAffordably(5);
std::println("remaining change: {}", change);
change = unicafeExactum.eatHeartily(4.3);
std::println("remaining change: {}", change);
std::println("{}", unicafeExactum.toString());
```

```
remaining change: 7.5
remaining change: 2.5
remaining change: 0
money: 1009.3, number of sold affordable meals: 2, number of sold hearty meals: 1
```

**Part 3: Card payments.** Add *overloads* that take a card: `bool eatAffordably(PaymentCard& card)` and `bool eatHeartily(PaymentCard& card)`. If the card has enough money, take the price from it, count the sale and return `true`; otherwise return `false`. Card payments do not change the amount of cash.

**Part 4: Topping up the card.** Add `void addMoneyToCard(PaymentCard& card, double sum)`, which adds `sum` to the card and to the terminal's cash. Negative sums are ignored.

### An object of the same type as a parameter

A member function can take another object of its own class as a parameter. It can then access that object's private members too — privacy in C++ is per *class*, not per object:

```cpp
bool olderThan(const Person& compared) const {
    return age > compared.age;
}
```

### Exercise 5.11: Comparing Apartments (3 parts)

*Template: `exercises/part05/05_11_ComparingApartments`*

The template contains a class `Apartment` with the number of rooms, the area in square metres and the price per square metre.

**Part 1: Comparing sizes.** Implement `bool largerThan(const Apartment& compared) const`, which returns `true` if this apartment's area is larger.

```cpp
Apartment manhattanStudioApt(1, 16, 5500);
Apartment atlantaTwoBedroomApt(2, 38, 4200);
Apartment bangorThreeBedroomApt(3, 78, 2500);

std::println("{}", manhattanStudioApt.largerThan(atlantaTwoBedroomApt));     // false
std::println("{}", bangorThreeBedroomApt.largerThan(atlantaTwoBedroomApt));  // true
```

**Part 2: Price difference.** Implement `int priceDifference(const Apartment& compared) const`, which returns the absolute difference of the total prices (area × price per square metre). For the studio and the two-bedroom apartment it is 71600; for the three-bedroom and the two-bedroom 35400.

**Part 3: More expensive?** Implement `bool moreExpensiveThan(const Apartment& compared) const`.

### Comparing objects for equality

`==` works for `int`s and `std::string`s. For our own classes, we have to tell the compiler what equality means by defining `operator==`. If two objects are equal exactly when all their members are equal, C++20 can write the operator for us:

```cpp
class Song {
public:
    // ...
    bool operator==(const Song& other) const = default;

private:
    std::string artist;
    std::string name;
    int durationInSeconds;
};
```

`= default` asks the compiler to compare the members one by one, in declaration order. Defining `==` also gives you `!=` for free.

When equality should consider only some members, write the operator yourself:

```cpp
bool operator==(const Book& other) const {
    return name == other.name && publicationYear == other.publicationYear;
}
```

> **Coming from Java?** Java's `equals(Object)` can be called with any object, so `song.equals("text")` compiles and returns `false`. In C++, comparing a `Song` with a string simply does not compile. The type system rules out the question.

### Exercise 5.12: Song

*Template: `exercises/part05/05_12_Song`*

Add equality to the class `Song` in the template, so that two songs are equal when all their data is equal.

```cpp
Song jackSparrow("The Lonely Island", "Jack Sparrow", 196);
Song anotherSparrow("The Lonely Island", "Jack Sparrow", 196);

if (jackSparrow == anotherSparrow) {
    std::println("Songs are equal.");
}
```

### Exercise 5.13: Identical Twins

*Template: `exercises/part05/05_13_IdenticalTwins`*

The template contains a class `Person` that holds a `SimpleDate` birthday, a height and a weight. Add `operator==` to `Person` so that two persons are equal when all their data is equal. You will need equality for `SimpleDate` too.

```cpp
SimpleDate date(24, 3, 2017);
SimpleDate date2(23, 7, 2017);

Person leo("Leo", date, 62, 9);
Person lily("Lily", date2, 65, 8);
if (leo == lily) {
    std::println("Is this quite correct?");
}

Person leoWithDifferentWeight("Leo", date, 62, 10);
if (leo == leoWithDifferentWeight) {
    std::println("Is this quite correct?");
}
```

Nothing should be printed.

### Object equality and vectors

Algorithms such as `std::ranges::contains`, `std::ranges::find` and `std::erase` use `==` to compare elements. Once a class has `operator==`, these algorithms work with vectors of that class.

### Exercise 5.14: Books

*Template: `exercises/part05/05_14_Books`*

The template reads books from the user and adds them to a vector. Change it so that a book that is already in the vector is not added again. Two books are the same if they have the same name and publication year.

```
Name (empty will stop):
> Bossypants
Publication year:
> 2013
Name (empty will stop):
> Seriously...I'm Kidding
Publication year:
> 2012
Name (empty will stop):
> Seriously...I'm Kidding
Publication year:
> 2012
The book is already on the list. Let's not add the same book again.
Name (empty will stop):
>
Thank you! Books added: 2
```

### Exercise 5.15: Archive (2 parts)

*Template: `exercises/part05/05_15_Archive`*

**Part 1: Adding and listing.** Read items — an identifier and a name — until either is empty. Then print all items in the format `identifier: name`.

```
Identifier? (empty will stop)
> B07H8ND8HH
Name? (empty will stop)
> He-Man figure
Identifier? (empty will stop)
> B07NQFMZYG
Name? (empty will stop)
> He-Man figure
Identifier? (empty will stop)
> B07H8ND8HH
Name? (empty will stop)
> He-Man
Identifier? (empty will stop)
>
==Items==
B07H8ND8HH: He-Man figure
B07NQFMZYG: He-Man figure
B07H8ND8HH: He-Man
```

**Part 2: Print each item once.** Two items are the same if their identifiers are the same. Print each item only once, keeping the one that was added first. For the input above, the output lists only the first two items.

### An object as a return value

Functions can return objects. The returned object is a new value owned by the caller:

```cpp
class Factory {
public:
    Car produceCar() {
        produced++;
        return Car("Model " + std::to_string(produced));
    }

private:
    int produced = 0;
};
```

`std::to_string` converts a number into a string.

A typical use is a member function that creates a new, modified object instead of changing the existing one:

```cpp
SimpleDate afterOneWeek = today.afterNumberOfDays(7);
```

### Exercise 5.16: Dating App (3 parts)

*Template: `exercises/part05/05_16_DatingApp`*

The template contains a class `SimpleDate` with a day, a month and a year. For simplicity, **every month has 30 days**.

**Part 1: The next day.** Implement `void advance()`, which moves the date forward by one day.

**Part 2: A given number of days.** Implement `void advance(int howManyDays)`, which moves the date forward by the given number of days. Use the previous overload.

**Part 3: Time passes.** Implement `SimpleDate afterNumberOfDays(int days) const`, which returns a *new* date that many days later, leaving the original unchanged. Use the copy and `advance`.

```cpp
SimpleDate date(13, 2, 2015);
std::println("Friday of the examined week is {}", date.toString());

SimpleDate newDate = date.afterNumberOfDays(7);
int week = 1;
while (week <= 7) {
    std::println("Friday after {} weeks is {}", week, newDate.toString());
    newDate = newDate.afterNumberOfDays(7);
    week = week + 1;
}
```

```
Friday of the examined week is 13.2.2015
Friday after 1 weeks is 20.2.2015
Friday after 2 weeks is 27.2.2015
Friday after 3 weeks is 4.3.2015
Friday after 4 weeks is 11.3.2015
Friday after 5 weeks is 18.3.2015
Friday after 6 weeks is 25.3.2015
Friday after 7 weeks is 2.4.2015
```

Value semantics makes the difference between `advance` and `afterNumberOfDays` easy to see:

```cpp
SimpleDate now(13, 2, 2015);
SimpleDate afterOneWeek = now;    // a copy
afterOneWeek.advance(7);
std::println("Now: {}", now.toString());                     // 13.2.2015
std::println("After one week: {}", afterOneWeek.toString()); // 20.2.2015
```

(In the Java version of this exercise, both lines print `20.2.2015`, because both variables refer to the same object. Can you change one line of the C++ program to get that behaviour? Hint: `&`.)

### Exercise 5.17: Money (3 parts)

*Template: `exercises/part05/05_17_Money`*

Floating-point numbers are a poor fit for money. The template's class `Money` stores euros and cents as integers. Its members are private and it offers no member function that changes them, so a `Money` object never changes after it has been created — it is **immutable**. Operations return new objects instead.

**Part 1: Plus.** Implement `Money plus(const Money& addition) const`, which returns a new `Money` worth the sum.

```cpp
Money a(10, 0);
Money b(5, 0);
Money c = a.plus(b);
std::println("{}", c.toString());   // 15.00e
a = a.plus(c);                       // see below
std::println("{}", a.toString());   // 25.00e
```

**Part 2: Less than.** Implement `bool lessThan(const Money& compared) const`.

**Part 3: Minus.** Implement `Money minus(const Money& decreaser) const`. If the result would be negative, return a `Money` worth zero.

```cpp
Money a(10, 0);
Money b(3, 50);
Money c = a.minus(b);
std::println("{}", c.toString());   // 6.50e
c = c.minus(a);
std::println("{}", c.toString());   // 0.00e
```

> **Why not make the members `const`?** It is tempting to declare `const int euros;` to enforce immutability. But then an assignment such as `a = a.plus(c);` no longer compiles, because assigning to `a` would have to change its `const` members. In C++, immutability is usually a property of the class's *interface*: private members and no modifying member functions.

## 5.5 Conclusion

This chapter contained some of the most important ideas in the book:

- constructors and functions can be overloaded, and constructors can delegate to each other,
- default member initialisers and default arguments reduce repetition,
- **C++ objects are values**: assignment and pass-by-value copy them,
- references (`&`) give another name to an existing object; pointers (`*`) hold addresses and may be `nullptr`,
- `std::optional` expresses "maybe a value" without null pointers,
- objects have lifetimes, and references must never outlive the objects they refer to,
- objects can be parameters, members and return values,
- equality for your own classes is defined with `operator==`, often simply `= default`.
