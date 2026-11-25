# Chapter 6: Building Larger Programs and Testing Them

Real programs consist of many cooperating objects. In this chapter you will build objects that contain vectors of other objects, separate a program's user interface from its logic, and write automated tests that check your code for you.

## 6.1 Objects containing vectors of objects

A member variable can be any type — including a `std::vector`. Let's model a playlist:

```cpp
#pragma once

#include <print>
#include <string>
#include <vector>

class Playlist {
public:
    void addSong(const std::string& song) {
        songs.push_back(song);
    }

    void removeSong(const std::string& song) {
        std::erase(songs, song);
    }

    void printSongs() const {
        for (const std::string& song : songs) {
            std::println("{}", song);
        }
    }

private:
    std::vector<std::string> songs;
};
```

A `std::vector` member starts out empty automatically, so `Playlist` needs no constructor. The playlist object *owns* its vector, and the vector is destroyed together with the playlist.

```cpp
Playlist list;
list.addSong("Sorateiden kuningas");
list.addSong("Teuvo, maanteiden kuningas");
list.printSongs();
```

```
Sorateiden kuningas
Teuvo, maanteiden kuningas
```

### Exercise 6.1: Menu (3 parts)

*Template: `exercises/part06/06_01_Menu`*

The campus restaurant needs a program for managing its menu. The template has a class `Menu` with a `std::vector<std::string> meals` member.

**Part 1: Adding a meal.** Implement `void addMeal(const std::string& meal)`. If the meal is already on the menu, it is not added again.

**Part 2: Printing the meals.** Implement `void printMeals() const`.

**Part 3: Clearing the menu.** Implement `void clearMenu()`. (Vectors have a member function for this.)

```cpp
Menu menu;
menu.addMeal("Tofu ratatouille");
menu.addMeal("Chilli coconut chicken");
menu.addMeal("Chilli coconut chicken");
menu.addMeal("Meatballs with mustard sauce");
menu.printMeals();
menu.clearMenu();

std::println("");
menu.addMeal("Tomato and mozzarella salad");
menu.printMeals();
```

```
Tofu ratatouille
Chilli coconut chicken
Meatballs with mustard sauce

Tomato and mozzarella salad
```

### Exercise 6.2: Stack (2 parts)

*Template: `exercises/part06/06_02_Stack`*

A **stack** is a data structure where values are always added to and taken from the top — like a stack of plates.

**Part 1: Adding and checking emptiness.** Create a class `Stack` that stores strings in a vector, with:

- `bool isEmpty() const`,
- `void add(const std::string& value)` — puts the value on top,
- `std::vector<std::string> values() const` — returns the values in the stack.

```cpp
Stack s;
std::println("{}", s.isEmpty());
std::println("{}", s.values());
s.add("Value");
std::println("{}", s.isEmpty());
std::println("{}", s.values());
```

```
true
[]
false
["Value"]
```

**Part 2: Taking from the stack.** Add `std::string take()`, which removes the topmost (most recently added) value and returns it.

```cpp
Stack s;
s.add("1");
s.add("2");
s.add("3");
while (!s.isEmpty()) {
    std::println("{}", s.take());
}
```

```
3
2
1
```

*Tip:* the most recently added value is at the end of the vector: `back()` reads it and `pop_back()` removes it.

### Objects in a member vector

A member vector can just as well contain objects of our own classes:

```cpp
class AmusementParkRide {
public:
    AmusementParkRide(const std::string& name, int lowestHeight)
        : name(name), lowestHeight(lowestHeight) {
    }

    bool isAllowedOn(const Person& person) {
        if (person.getHeight() < lowestHeight) {
            return false;
        }
        riding.push_back(person);
        return true;
    }

    void removeEveryoneOnRide() {
        riding.clear();
    }

private:
    std::string name;
    int lowestHeight;
    std::vector<Person> riding;
};
```

`riding.push_back(person)` stores a **copy** of the person in the ride's vector. That is fine here: the ride only needs to know who is on board. If the program needed to see later changes to the same person (say, their height after a birthday) through the ride, we would have to store something else — an identifier, or a pointer to an object that is guaranteed to outlive the ride. Chapter 9 returns to this.

### Exercise 6.3: Messaging Service

*Template: `exercises/part06/06_03_MessagingService`*

The template contains a class `Message` with a sender and some content. Create a class `MessagingService` containing a vector of messages, with:

- `void add(const Message& message)` — adds the message if its content is at most 280 characters long,
- `const std::vector<Message>& getMessages() const` — returns the messages.

Note the return type: returning a `const&` to the member vector gives the caller read-only access without copying. It is safe as long as the caller does not keep the reference longer than the `MessagingService` object lives.

### Printing an object from a vector

`toString` functions compose: a container's `toString` can call the `toString` of each element.

### Exercise 6.4: Printing a Collection

*Template: `exercises/part06/06_04_PrintingACollection`*

The template's class `SimpleCollection` has a name and a vector of strings. Implement `std::string toString() const`:

```cpp
SimpleCollection s("alphabet");
std::println("{}", s.toString());
std::println("");

s.add("a");
std::println("{}", s.toString());
std::println("");

s.add("b");
std::println("{}", s.toString());
```

```
The collection alphabet is empty.

The collection alphabet has 1 element:
a

The collection alphabet has 2 elements:
a
b
```

Note the singular `element` when there is exactly one. Join lines with the newline character `'\n'`.

### Exercise 6.5: Santa's Workshop (2 parts)

*Template: `exercises/part06/06_05_SantasWorkshop`*

**Part 1: Gift.** Create a class `Gift` with a name and a weight in kilograms, `getName()`, `getWeight()` and `toString()` returning `"name (weight kg)"`.

```cpp
Gift book("Harry Potter and the Philosopher's Stone", 2);
std::println("Gift's name: {}", book.getName());
std::println("Gift's weight: {}", book.getWeight());
std::println("Gift: {}", book.toString());
```

```
Gift's name: Harry Potter and the Philosopher's Stone
Gift's weight: 2
Gift: Harry Potter and the Philosopher's Stone (2 kg)
```

**Part 2: Package.** Create a class `Package` with `void addGift(const Gift& gift)` and `int totalWeight() const`.

### Retrieving a specific object from a vector

Finding "the best" object in a vector follows the same pattern as finding the greatest number, but what should a function return when the vector is empty? In C++ we have two good options:

1. Return a `std::optional<Person>` — "a person, or nothing".
2. Return a pointer `const Person*` to the element inside the vector, or `nullptr`.

```cpp
std::optional<Person> oldest() const {
    if (persons.empty()) {
        return std::nullopt;
    }
    Person oldest = persons[0];
    for (const Person& person : persons) {
        if (person.getAge() > oldest.getAge()) {
            oldest = person;
        }
    }
    return oldest;
}
```

```cpp
std::optional<Person> result = club.oldest();
if (result) {
    std::println("Oldest: {}", result->toString());
} else {
    std::println("The club is empty");
}
```

An `optional` converts to `true` when it holds a value, and `->` reaches the contained object's members.

### Exercise 6.6: Longest in Collection

*Template: `exercises/part06/06_06_LongestInCollection`*

Implement `std::optional<std::string> longest() const` in the `SimpleCollection` class. It returns the longest string, or an empty optional if the collection is empty. If several strings are equally long, return any of them.

```cpp
SimpleCollection j("characters");
std::println("Longest: {}", j.longest().value_or("none"));

j.add("magneto");
j.add("mystique");
j.add("phoenix");
std::println("Longest: {}", j.longest().value_or("none"));
```

```
Longest: none
Longest: mystique
```

`value_or(x)` returns the contained value, or `x` if there is none.

### Exercise 6.7: Height Order (3 parts)

*Template: `exercises/part06/06_07_HeightOrder`*

The template contains a class `Person` with a name and a height.

**Part 1: Room.** Create a class `Room` with `void add(const Person& person)`, `bool isEmpty() const` and `const std::vector<Person>& getPersons() const`.

```cpp
Room room;
std::println("Empty room? {}", room.isEmpty());
room.add(Person("Lea", 183));
room.add(Person("Kenya", 182));
room.add(Person("Auli", 186));
room.add(Person("Nina", 172));
room.add(Person("Terhi", 185));
std::println("Empty room? {}", room.isEmpty());
std::println("");
for (const Person& person : room.getPersons()) {
    std::println("{}", person.toString());
}
```

```
Empty room? true
Empty room? false

Lea (183 cm)
Kenya (182 cm)
Auli (186 cm)
Nina (172 cm)
Terhi (185 cm)
```

**Part 2: Shortest person.** Add `std::optional<Person> shortest() const`, which returns the shortest person without removing them. For an empty room it returns an empty optional.

**Part 3: Taking a person.** Add `std::optional<Person> take()`, which *removes* the shortest person from the room and returns them. Using `take` repeatedly, a program can print the people in height order:

```cpp
while (!room.isEmpty()) {
    std::println("{}", room.take()->toString());
}
```

```
Nina (172 cm)
Kenya (182 cm)
Lea (183 cm)
Terhi (185 cm)
Auli (186 cm)
```

### Exercise 6.8: Cargo Hold (7 parts)

*Template: `exercises/part06/06_08_CargoHold`*

Practise objects inside objects inside objects: items go into suitcases, and suitcases go into a cargo hold.

**Part 1: Item.** Create a class `Item` with a name and a weight (kg), `getName()`, `getWeight()` and `toString()` returning `"name (weight kg)"`.

**Part 2: Suitcase.** Create a class `Suitcase` with a maximum weight given to the constructor, `void addItem(const Item& item)` and `std::string toString() const` returning `"x items (y kg)"`. An item is not added if the total weight would exceed the maximum.

```cpp
Item book("Lord of the rings", 2);
Item phone("Nokia 3210", 1);
Item brick("brick", 4);

Suitcase suitcase(5);
std::println("{}", suitcase.toString());
suitcase.addItem(book);
std::println("{}", suitcase.toString());
suitcase.addItem(phone);
std::println("{}", suitcase.toString());
suitcase.addItem(brick);
std::println("{}", suitcase.toString());
```

```
0 items (0 kg)
1 items (2 kg)
2 items (3 kg)
2 items (3 kg)
```

**Part 3: Language.** "0 items" and "1 items" are clumsy. Change `toString` to print `no items (0 kg)` for an empty suitcase and `1 item (2 kg)` for a single item.

**Part 4: All items.** Add `void printItems() const`, which prints every item, and `int totalWeight() const`.

**Part 5: Heaviest item.** Add `std::optional<Item> heaviestItem() const`.

**Part 6: Hold.** Create a class `Hold` with a maximum weight, `void addSuitcase(const Suitcase& suitcase)` (not added if the hold would become too heavy) and `std::string toString() const` returning `"x suitcases (y kg)"`.

**Part 7: Hold contents.** Add `void printItems() const` to `Hold`, which prints every item in every suitcase.

## 6.2 Separating the user interface from program logic

So far our programs have mixed reading input, printing output and the actual logic. As programs grow, that becomes a problem: the logic cannot be reused with a different interface (a graphical one, a web page, a test), and it is hard to see what the program actually *does*.

The solution is to separate the program into:

- **program logic**: classes that model the problem domain and know nothing about input or output, and
- a **user interface**: a class that talks to the user and calls the logic.

### Example: a word set

Suppose we want a program that reads words until the user repeats one:

```
Enter a word: carrot
Enter a word: celery
Enter a word: turnip
Enter a word: carrot
You gave the same word twice!
```

The *logic* — remembering words and checking for repeats — goes into a class of its own:

```cpp
class WordSet {
public:
    void add(const std::string& word) {
        words.push_back(word);
    }

    bool contains(const std::string& word) const {
        return std::ranges::contains(words, word);
    }

private:
    std::vector<std::string> words;
};
```

The *user interface* reads input and uses the logic:

```cpp
class UserInterface {
public:
    UserInterface(std::istream& input, WordSet& wordSet)
        : input(input), wordSet(wordSet) {
    }

    void start() {
        std::string word;
        while (true) {
            std::print("Enter a word: ");
            std::getline(input, word);
            if (wordSet.contains(word)) {
                break;
            }
            wordSet.add(word);
        }
        std::println("You gave the same word twice!");
    }

private:
    std::istream& input;
    WordSet& wordSet;
};
```

```cpp
int main() {
    WordSet set;
    UserInterface ui(std::cin, set);
    ui.start();
}
```

Two details deserve attention:

- The user interface reads from a `std::istream&` given to its constructor, rather than from `std::cin` directly. `std::istream` is the general type of input streams: `std::cin`, an `std::ifstream` reading a file, or an `std::istringstream` reading from a string all qualify. This makes the class easy to test, as you will see in the next section.
- The members `input` and `wordSet` are **references**. The user interface does not own the stream or the word set; it uses objects that `main` owns and that live longer than the interface. A reference member must be initialised in the constructor's initialiser list.

### Using an earlier solution as part of an implementation

Separating logic from the interface pays off when requirements change. Suppose the program should treat `Carrot` and `carrot` as the same word, or ignore punctuation. Only `WordSet` needs to change — and the interface does not notice.

### Changing the implementation of a class

We could, for example, replace the vector inside `WordSet` with a faster data structure (Chapter 8). As long as `add` and `contains` behave the same, no other code changes. This is the real benefit of encapsulation: the **interface** of a class — its public member functions — is a promise, and the **implementation** behind it is free to change.

### Implementing new functionality: palindromes

New features slot in naturally. Suppose the program should also count the palindromes — words that read the same backwards. We add a function to the logic:

```cpp
#include <algorithm>
#include <ranges>

bool isPalindrome(const std::string& word) {
    return std::ranges::equal(word, word | std::views::reverse);
}
```

`word | std::views::reverse` is a reversed *view* of the string; `std::ranges::equal` compares the two sequences element by element. Views and the `|` notation return in Chapter 10.

### Programming tips

- **Work in small steps.** Write a little code, compile, run, check. Then the next step.
- **Write your code tidily.** Indentation, names and small functions are for you as much as for others.
- **Make it work first, then make it nice.** Once the program works, *refactor*: rename variables, extract functions, remove duplication. Run it again after every change.
- **When you are stuck, simplify.** Write a tiny test program with just the part that puzzles you.

### Exercise 6.9: Simple Dictionary (4 parts)

*Template: `exercises/part06/06_09_SimpleDictionary`*

The template contains a class `SimpleDictionary` that stores words and their translations:

```cpp
SimpleDictionary book;
book.add("one", "yksi");
book.add("two", "kaksi");
std::println("{}", book.translate("one").value_or("(none)"));
std::println("{}", book.translate("two").value_or("(none)"));
std::println("{}", book.translate("three").value_or("(none)"));
```

```
yksi
kaksi
(none)
```

In this exercise you write a text user interface for it — and maybe learn a few Finnish words.

**Part 1: Starting and stopping.** Create a class `TextUI` whose constructor takes a `std::istream&` and a `SimpleDictionary&`, with a member function `void start()`:

1. Ask the user for a command (`Command: `).
2. If the command is `end`, print `Bye bye!` and return from `start`.
3. Otherwise print `Unknown command` and go back to step 1.

```
Command: something
Unknown command
Command: end
Bye bye!
```

**Part 2: Adding a translation.** Add the command `add`: it asks for a word and its translation, each on its own line, and stores them in the dictionary.

```
Command: add
Word: pike
Translation: hauki
Command: end
Bye bye!
```

**Part 3: Translating.** Add the command `search`: it asks for a word and prints its translation, or `Word <word> was not found` if there is none.

```
Command: search
To be translated: pike
Translation: hauki
Command: search
To be translated: carp
Word carp was not found
```

**Part 4: Tidy up.** Move the handling of each command into its own private member function, so that `start` stays short and readable.

### Exercise 6.10: To-Do List (2 parts)

*Template: `exercises/part06/06_10_TodoList`*

**Part 1: TodoList.** Create a class `TodoList` with:

- `void add(const std::string& task)`,
- `void print() const` — prints the tasks, numbered from 1,
- `void remove(int number)` — removes the task with the given number (as shown by `print`).

```cpp
TodoList list;
list.add("read the course material");
list.add("watch the latest fool us");
list.add("take it easy");
list.print();
list.remove(2);
list.print();
```

```
1: read the course material
2: watch the latest fool us
3: take it easy
1: read the course material
2: take it easy
```

**Part 2: User interface.** Create a class `UserInterface` taking a `TodoList&` and a `std::istream&`, with `void start()` supporting the commands `stop`, `add`, `list` and `remove`:

```
Command: add
To add: go to the store
Command: add
To add: vacuum clean
Command: list
1: go to the store
2: vacuum clean
Command: remove
Which one is removed? 1
Command: list
1: vacuum clean
Command: stop
```

### From one entity to many parts

Let's look at a larger example: a program that reads exam points and prints a grade distribution. A first version written entirely in `main` works, but mixes everything together. We split it into:

**Program logic** — a `GradeRegister` that converts points to grades and remembers them:

```cpp
class GradeRegister {
public:
    void addGradeBasedOnPoints(int points) {
        grades.push_back(pointsToGrade(points));
    }

    int numberOfGrades(int grade) const {
        int count = 0;
        for (int received : grades) {
            if (received == grade) {
                count++;
            }
        }
        return count;
    }

    static int pointsToGrade(int points) {
        if (points < 50) return 0;
        if (points < 60) return 1;
        if (points < 70) return 2;
        if (points < 80) return 3;
        if (points < 90) return 4;
        return 5;
    }

private:
    std::vector<int> grades;
};
```

`pointsToGrade` is a **static member function**: it belongs to the class but does not use any object's data, so it can be called without an object as `GradeRegister::pointsToGrade(75)`.

**User interface** — reads points and prints the distribution as rows of stars:

```cpp
class UserInterface {
public:
    UserInterface(GradeRegister& reg, std::istream& input) : reg(reg), input(input) {}

    void start() {
        readPoints();
        std::println("");
        printGradeDistribution();
    }

private:
    void readPoints() {
        std::string line;
        while (true) {
            std::print("Points: ");
            std::getline(input, line);
            if (line.empty()) {
                break;
            }
            int points = std::stoi(line);
            if (points < 0 || points > 100) {
                std::println("Impossible number.");
                continue;
            }
            reg.addGradeBasedOnPoints(points);
        }
    }

    void printGradeDistribution() {
        for (int grade = 5; grade >= 0; grade--) {
            std::println("{}: {}", grade, std::string(reg.numberOfGrades(grade), '*'));
        }
    }

    GradeRegister& reg;
    std::istream& input;
};
```

`std::string(n, '*')` creates a string of `n` stars.

### Exercise 6.11: Averages (3 parts)

*Template: `exercises/part06/06_11_Averages`*

The template contains the grade program above.

**Part 1: Average grade.** Add `double averageOfGrades() const` to `GradeRegister`. It returns `-1` if there are no grades.

```cpp
GradeRegister reg;
reg.addGradeBasedOnPoints(93);
reg.addGradeBasedOnPoints(91);
reg.addGradeBasedOnPoints(92);
reg.addGradeBasedOnPoints(88);
std::println("{}", reg.averageOfGrades());   // 4.75
```

**Part 2: Average points.** Store also the points in a second vector, and add `double averageOfPoints() const` (also `-1` when empty).

**Part 3: The user interface.** Print both averages after the distribution:

```
Points: 82
Points: 83
Points: 96
Points: 51
Points: 48
Points: 56
Points: 61
Points:

5: *
4: **
3:
2: *
1: **
0: *
The average of points: 68.14285714285714
The average of grades: 2.4285714285714284
```

### Exercise 6.12: Joke Manager (2 parts)

*Template: `exercises/part06/06_12_JokeManager`*

The template contains a joke program written entirely in `main`. Split it up.

**Part 1: JokeManager.** Create a class `JokeManager` with `void addJoke(const std::string& joke)`, `std::string drawJoke()` (returns a random joke, or `Jokes are in short supply.` if there are none) and `void printJokes() const`.

Random numbers in C++ come from the header `<random>`. A *random engine* produces raw randomness, and a *distribution* shapes it into the values you want:

```cpp
#include <random>

std::mt19937 engine{std::random_device{}()};          // seeded randomly
std::uniform_int_distribution<int> dice(1, 6);        // integers from 1 to 6
int roll = dice(engine);
```

Keep the engine as a member of `JokeManager`, so it is created once.

**Part 2: User interface.** Create a class `UserInterface` taking a `JokeManager&` and a `std::istream&`. Its `start()` shows the commands and handles them:

```
Commands:
 1 - add a joke
 2 - draw a joke
 3 - list jokes
 X - stop
> 1
Write the joke to be added:
> Did you hear about the claustrophobic astronaut? -- He just needed a little space.
Commands:
 1 - add a joke
 2 - draw a joke
 3 - list jokes
 X - stop
> 3
Printing the jokes.
Did you hear about the claustrophobic astronaut? -- He just needed a little space.
Commands:
 1 - add a joke
 2 - draw a joke
 3 - list jokes
 X - stop
> X
```

## 6.3 Introduction to testing

How do we know a program works? By trying it. But trying it by hand after every change is slow and unreliable. **Automated tests** are programs that check other programs.

### Error situations and solving problems step by step

When a program misbehaves, proceed methodically:

1. **Reproduce** the problem: find an input that makes it happen every time.
2. **Isolate** it: which function produces the first wrong value? Print debugging and the debugger help here.
3. **Understand** it: why does the code do that? Do not change code before you can explain the error.
4. **Fix** it, and **check** that the fix works — and that nothing else broke.

### When a program crashes

When a C++ program crashes, the information you get depends on the cause. An uncaught exception prints its type and message:

```
terminate called after throwing an instance of 'std::out_of_range'
  what():  vector::_M_range_check: __n (which is 5) >= this->size() (which is 3)
```

A crash due to undefined behaviour — a null pointer dereference, say — may print only `Segmentation fault`. In both cases, run the program in the **debugger**: it stops at the crash and shows the *call stack*, the chain of function calls that led to it. That tells you exactly where to look. (Languages like Java print this *stack trace* automatically; in C++ the debugger shows it to you.)

**Sanitizers** are an even more powerful tool. Compiling with `-fsanitize=address,undefined` (GCC and Clang) makes the program check itself as it runs and report many kinds of undefined behaviour — out-of-bounds access, use of destroyed objects, integer overflow — with a precise description and stack trace. Turn them on whenever you hunt a mysterious bug.

### A checklist for troubleshooting

- Read the **first** compiler error first.
- Is every variable initialised before it is used?
- Are your loop bounds right — `<` or `<=`? Starting at 0 or 1?
- Did you mean `==` and write `=`?
- Is a function parameter a copy when it should be a reference (or vice versa)?
- Are you reading a `std::size_t` minus something that might go below zero?
- Does the program behave the same with sanitizers on?

### Feeding test input to a program

Because our user interfaces read from a `std::istream&`, we can give them input from a string instead of the keyboard, using `std::istringstream` from `<sstream>`:

```cpp
#include <sstream>

std::istringstream input("carrot\ncelery\ncarrot\n");
WordSet set;
UserInterface ui(input, set);
ui.start();
```

The `\n` characters are line breaks. The program runs as if a user had typed the three words. This is how the interface can be tested automatically.

### Unit testing

**Unit testing** means writing small tests for individual units of code — usually functions and classes. A unit test sets up a situation, calls the code, and checks that the result is what it should be.

C++ has no unit testing framework in its standard library, but several excellent free ones exist. In this book we use **Catch2**. The exercises that need it fetch it automatically through CMake.

Suppose we have a class `Calculator`:

```cpp
class Calculator {
public:
    void add(int number) { value += number; }
    void subtract(int number) { value -= number; }
    int getValue() const { return value; }

private:
    int value = 0;
};
```

A test file looks like this:

```cpp
#include <catch2/catch_test_macros.hpp>
#include "Calculator.h"

TEST_CASE("calculator starts at zero") {
    Calculator calculator;
    REQUIRE(calculator.getValue() == 0);
}

TEST_CASE("adding five gives five") {
    Calculator calculator;
    calculator.add(5);
    REQUIRE(calculator.getValue() == 5);
}

TEST_CASE("subtracting works") {
    Calculator calculator;
    calculator.add(5);
    calculator.subtract(2);
    REQUIRE(calculator.getValue() == 3);
}
```

Each `TEST_CASE` is an independent test with a descriptive name. `REQUIRE(condition)` checks a condition; if it is false, the test fails and Catch2 reports the expression and the actual values:

```
test.cpp:14: FAILED:
  REQUIRE( calculator.getValue() == 5 )
with expansion:
  4 == 5
```

The tests are compiled into a separate program. In an exercise with tests, the target `..._tests` runs them; with CMake you can also run all tests of the project with `ctest --test-dir build`.

A good test suite checks normal cases, **edge cases** (empty input, zero, the largest allowed value) and error cases. Writing tests forces you to think precisely about what your code should do.

### Test-driven development

**Test-driven development** (TDD) turns the order around: you write a test *before* the code. The cycle is:

1. **Red** — write a small test for a feature that does not exist yet. Compile and run: the test fails (or does not even compile).
2. **Green** — write the simplest code that makes the test pass.
3. **Refactor** — clean up the code, keeping all tests passing.

Then repeat with the next small feature.

Let's develop a small exercise-tracking class this way. The first requirement: a new `ExerciseManagement` has no exercises.

```cpp
TEST_CASE("exercise list is empty in the beginning") {
    ExerciseManagement management;
    REQUIRE(management.exerciseList().empty());
}
```

This does not compile, since the class does not exist. We write just enough:

```cpp
class ExerciseManagement {
public:
    std::vector<std::string> exerciseList() const {
        return {};
    }
};
```

Green. Next requirement: adding an exercise grows the list.

```cpp
TEST_CASE("adding an exercise grows the list by one") {
    ExerciseManagement management;
    management.add("Exercise 1");
    REQUIRE(management.exerciseList().size() == 1);
}

TEST_CASE("an added exercise is in the list") {
    ExerciseManagement management;
    management.add("Exercise 1");
    REQUIRE(std::ranges::contains(management.exerciseList(), "Exercise 1"));
}
```

Now a vector member is needed:

```cpp
class ExerciseManagement {
public:
    std::vector<std::string> exerciseList() const { return exercises; }
    void add(const std::string& exercise) { exercises.push_back(exercise); }

private:
    std::vector<std::string> exercises;
};
```

Next: marking an exercise as completed.

```cpp
TEST_CASE("an exercise can be marked as completed") {
    ExerciseManagement management;
    management.add("New exercise");
    management.markAsCompleted("New exercise");
    REQUIRE(management.isCompleted("New exercise"));
}

TEST_CASE("an exercise that is not marked is not completed") {
    ExerciseManagement management;
    management.add("New exercise");
    management.markAsCompleted("New exercise");
    REQUIRE_FALSE(management.isCompleted("Some exercise"));
}
```

A list of strings cannot store completion. Time to **refactor**: introduce a class `Exercise` with a name and a `completed` flag, and make `ExerciseManagement` store `Exercise` objects. The existing tests tell us immediately whether the refactoring broke anything. That safety net is the real reward of having tests.

### Exercise 6.13: Exercises (2 parts)

*Template: `exercises/part06/06_13_Exercises`*

The template contains a CMake project with Catch2, an empty `ExerciseManagement.h` and an empty test file `ExerciseManagementTest.cpp`.

**Part 1.** Follow the TDD example above, writing each test first and then the code, up to the point where the `Exercise` class is needed.

**Part 2.** Do the refactoring: create the class `Exercise`, store `Exercise` objects in `ExerciseManagement`, and implement `markAsCompleted` and `isCompleted`. All tests must pass.

If you want more practice, use TDD to add the removal of exercises.

## 6.4 Complex programs

You now have the tools to build programs consisting of many classes. Typically:

- **domain classes** model the concepts (`Item`, `Suitcase`, `Hold`),
- **service classes** manage collections of domain objects and implement the operations (`GradeRegister`, `JokeManager`),
- a **user interface class** reads commands and prints results,
- `main` creates the objects, connects them, and starts the user interface.

Each class has one clear responsibility. When a change is needed, it is clear where it belongs. And because the logic does not depend on `std::cin` and `std::cout`, it can be tested automatically.

### Summary

- Objects can contain vectors of other objects; containers of objects store copies.
- `std::optional` is a clean way to return "an object or nothing".
- Separate program logic from the user interface. Pass the input stream (`std::istream&`) in, so the interface can be tested with `std::istringstream`.
- Reference members let an object use other objects it does not own.
- Debuggers, sanitizers and a systematic method make bugs findable.
- Unit tests check code automatically; Catch2 makes them easy to write. Test-driven development writes the test first.
