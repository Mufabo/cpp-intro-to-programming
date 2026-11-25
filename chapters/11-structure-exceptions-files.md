# Chapter 11: Program Structure, Exceptions and Files

As programs grow, their organisation matters more and more. This chapter covers how to *describe* a program's structure with class diagrams, how to *organise* C++ code into header and source files, folders and namespaces, how to handle errors with **exceptions**, and how to write files as well as read them.

## 11.1 Class diagrams

A **class diagram** describes the classes of a program and the relationships between them. Class diagrams are part of the **UML** (Unified Modeling Language), a standard notation for describing software. They are useful for planning a program before writing it, and for explaining an existing program to others.

In this book we draw class diagrams as text. A class is a box with three compartments: the name, the member variables, and the member functions.

```
+---------------------------+
|          Person           |
+---------------------------+
| - name: string            |
| - age: int                |
+---------------------------+
| + Person(name: string)    |
| + printPerson(): void     |
| + getName(): string       |
+---------------------------+
```

- `-` marks a `private` member, `+` a `public` one (and `#` a `protected` one).
- A member variable is written `name: type`.
- A member function is written `name(parameters): return type`. A constructor has no return type.

The diagram describes the *design*, not every detail: it uses language-neutral type names (`string`, not `std::string`), and it is fine to leave out obvious members.

### Exercise 11.1: Customer

*Template: `exercises/part11/11_01_Customer`*

Implement the class in this diagram, with a constructor that sets all members:

```
+---------------------+
|      Customer       |
+---------------------+
| - name: string      |
| - address: string   |
| - email: string     |
+---------------------+
```

### Exercise 11.2: A Book and a Plane

*Template: `exercises/part11/11_02_ABookAndAPlane`*

Implement both classes:

```
+----------------------+      +-----------------------------+
|         Book         |      |            Plane            |
+----------------------+      +-----------------------------+
| - name: string       |      | - id: string                |
| - author: string     |      | - model: string             |
| - pageCount: int     |      | - yearOfIntroduction: int   |
+----------------------+      +-----------------------------+
```

### Connections between classes

A line between two classes shows that they are connected. An arrow shows the direction of the connection: which class knows about the other. A number or a star `*` at the end of a line tells how many objects are involved (`*` means "any number").

```
+------------------+  *          +-------------------+
|      Ticket      |------------>|       Show        |
+------------------+             +-------------------+
| - seat: int      |             | - movie: string   |
| - code: int      |             | - time: string    |
+------------------+             +-------------------+
```

This says: a `Ticket` knows its `Show` (the arrow points to the show), and there can be many tickets for one show (the star at the ticket end). In C++ the ticket would have a member that identifies its show. Since a show outlives its tickets and is shared by many of them, a `Ticket` could store a `const Show&` or `const Show*`, or a copy of the show if shows never change.

A line without arrowheads means both classes know about each other. A filled diamond (drawn here as `<>`) at one end means **composition**: the object at the diamond end *owns* the other, and they live and die together. In C++, composition is a member object or a `std::unique_ptr` member.

### Exercise 11.3: Show and Ticket

*Template: `exercises/part11/11_03_ShowAndTicket`*

Implement the classes and the connection shown above. Store the show in the ticket by value (a copy).

### Exercise 11.4: Student and University

*Template: `exercises/part11/11_04_StudentAndUniversity`*

```
+---------------------+  *        +--------------------+
|       Student       |-----------|     University     |
+---------------------+           +--------------------+
| - studentId: int    |           | - name: string     |
| - name: string      |           +--------------------+
+---------------------+
```

A student knows their university. Implement both classes; give `Student` a member `std::string university` holding the university's name, so that both directions of the connection could be added later without ownership questions.

### Describing inheritance

Inheritance is drawn as an arrow with a hollow triangle (written here as `--|>`) pointing to the base class:

```
+-------------------------+
|           Bot           |
+-------------------------+
|                         |
+-------------------------+
| + play(): void          |
| + addMove(move: string) |
+-------------------------+
             |
             |  (inherits)
             V
+-------------------------+
|         Player          |
+-------------------------+
| - name: string          |
+-------------------------+
| + play(): void          |
| + printName(): void     |
+-------------------------+
```

`Bot` inherits from `Player` and overrides `play`.

### Exercise 11.5: The Player and the Bot

*Template: `exercises/part11/11_05_ThePlayerAndTheBot`*

Implement the classes above. `Player::play` should be virtual. The function bodies can be simple: `play` might print a move, and `addMove` might store moves in a vector.

### Describing interfaces

An interface is marked `<<interface>>`, and a class that implements it is connected with a dashed arrow with a hollow triangle (`..|>`):

```
+------------------------------+
|        <<interface>>         |
|           Saveable           |
+------------------------------+
| + save(): void               |
| + remove(): void             |
| + load(address: string): void|
+------------------------------+
               ^
               :  (implements)
+------------------------------+
|            Person            |
+------------------------------+
| - name: string               |
| - address: string            |
+------------------------------+
```

(The original diagram calls the second function `delete`, but `delete` is a reserved word in C++, so we call it `remove`.)

### Exercise 11.6: Saveable Person

*Template: `exercises/part11/11_06_SaveablePerson`*

Implement the interface `Saveable` (an abstract class) and the class `Person` that implements it. The function bodies may simply print what they would do.

### Exercise 11.7: Bigger Class Diagram

*Template: `exercises/part11/11_07_BiggerClassDiagram`*

Implement the following design. `IA`, `IB` and `IC` are interfaces without functions (give each just a virtual destructor).

- `A` implements `IA`; `B` implements `IB`; `C` implements `IC`.
- `C` inherits from `B`, and `B` inherits from `A`.
- `D` has a member that refers to an `IA` object (use `std::unique_ptr<IA>`).
- `E` and `C` are connected many-to-many: an `E` holds a vector of `C`s.

Does `C` now implement all three interfaces? (Yes: it inherits `IA` and `IB` through its base classes.)

## 11.2 Organising code: headers, source files and namespaces

Until now, every class has lived in a header file that contained the whole class, member functions included, and every program had one `.cpp` file. That works well for small programs. Real C++ projects split code differently, for reasons of compile time, clarity and name management.

### Header files and source files

The standard practice is to split each class into two files:

- the **header** (`.h`) contains the class definition: members and the *declarations* of member functions,
- the **source file** (`.cpp`) contains the *definitions* — the bodies — of the member functions.

`Counter.h`:

```cpp
#pragma once

class Counter {
public:
    Counter(int start);
    void increase();
    int value() const;

private:
    int count;
};
```

`Counter.cpp`:

```cpp
#include "Counter.h"

Counter::Counter(int start) : count(start) {
}

void Counter::increase() {
    count++;
}

int Counter::value() const {
    return count;
}
```

In the source file, each member function is written with the class name and `::` in front: `Counter::increase` means "the `increase` that belongs to `Counter`".

Why bother? Every `.cpp` file is compiled separately into an *object file*; the **linker** then combines the object files into the program. Code that uses `Counter` only needs to see the header to compile. If you change the body of `Counter::increase`, only `Counter.cpp` is recompiled. In large projects this saves a lot of time. The header also becomes a clean summary of the class's interface.

Two rules keep the system working:

- **Include what you use.** Each file includes the headers it needs, and every header has `#pragma once`.
- **Define each function exactly once.** A function defined in a header outside a class would be compiled into every `.cpp` that includes it, and the linker would complain about multiple definitions. (Member functions defined *inside* the class body, as we have done so far, are automatically `inline` and exempt from this rule; so are functions explicitly marked `inline`.)

Small classes and templates (Chapter 12) are often kept entirely in headers. Larger classes are usually split.

### Namespaces

As a program grows, names start to clash: your `Item` class and a library's `Item` class cannot both be called `Item` — unless they live in different **namespaces**:

```cpp
namespace library {
    class Item {
        // ...
    };
}

namespace shop {
    class Item {
        // ...
    };
}

library::Item book;
shop::Item product;
```

You have used a namespace since the first page: `std`, which contains the whole standard library. Namespaces can be nested — `std::ranges::views` — and in C++17 and later a nested namespace can be written in one go: `namespace mooc::ui { ... }`.

Inside a source file, a **using declaration** lets you leave out the prefix for specific names:

```cpp
using std::string;
string name = "Ada";
```

You will also see `using namespace std;`, which pulls in *everything* from `std`. Avoid it, especially in headers: `std` contains thousands of names, and pulling them all in invites clashes with your own names.

### Directory structure

Namespaces are a language feature; folders are a file-system feature. A common convention mirrors one in the other:

```
FlightControl/
├── main.cpp
├── domain/
│   ├── Airplane.h
│   ├── Airplane.cpp
│   ├── Flight.h
│   └── Flight.cpp
├── logic/
│   ├── FlightControl.h
│   └── FlightControl.cpp
└── ui/
    ├── TextUI.h
    └── TextUI.cpp
```

The classes in `domain/` are in the namespace `flightcontrol::domain`, and so on. A file includes others by their path relative to the project root, for example `#include "domain/Airplane.h"`. (In the exercise build, the exercise folder is on the include path, and all `.cpp` files in its subfolders are compiled automatically.)

> **What about Java packages?** Java packages combine three things: a namespace, a folder, and a visibility level ("package-private"). C++ separates them: namespaces for names, folders for files, and access specifiers for visibility. C++ has no package-private visibility. Functions and variables that should not be visible outside one `.cpp` file can be put in an **unnamed namespace** (`namespace { ... }`) inside that file.

> **Modules.** C++20 introduced **modules** (`import std;`, `export module mylib;`), a modern replacement for headers that compiles faster and isolates names better. Compiler and build-tool support is still maturing, so this book sticks to headers, but expect to see modules more and more.

### Exercise 11.8: First Namespaces (3 parts)

*Template: `exercises/part11/11_08_FirstPackages`*

Create the following structure in the exercise folder, with the namespaces `mooc::ui` and `mooc::logic`, and split each class into a header and a source file.

**Part 1: UserInterface.** In the folder `mooc/ui`, create the interface `UserInterface` with `virtual void update() = 0;`.

**Part 2: Text interface.** In the same folder, create `TextInterface`, which implements `UserInterface`; `update` prints `Updating UI`.

**Part 3: Application logic.** In the folder `mooc/logic`, create `ApplicationLogic`, whose constructor takes a `UserInterface&`, and whose `void execute(int times)` prints `Application logic is working` `times` times, calling the user interface's `update` after each print.

```cpp
#include "mooc/logic/ApplicationLogic.h"
#include "mooc/ui/TextInterface.h"

int main() {
    mooc::ui::TextInterface ui;
    mooc::logic::ApplicationLogic(ui).execute(3);
}
```

```
Application logic is working
Updating UI
Application logic is working
Updating UI
Application logic is working
Updating UI
```

### Exercise 11.9: Three Namespaces

*Template: `exercises/part11/11_09_TheThreePackages`*

Create three folders `a`, `b` and `c`, with a class `A` in namespace `a`, `B` in `b` and `C` in `c`, each in its own header and source file. The classes need no members. Create one object of each in `main`.

### Access control within a larger program

Use access specifiers to make the *public interface* of each class as small as possible. Everything that is `public` is a promise: other code will start depending on it, and you can no longer change it freely. Keep member variables `private`; make helper functions `private`; and put free helper functions that only one source file needs into an unnamed namespace in that file.

### A larger example: flight control

Let's design a program for an airport. The system knows **airplanes** (an identifier such as `HA-LOL` and a passenger capacity) and **flights** (an airplane, a departure airport and a destination airport). The same airplane can fly many flights.

The program has two phases. In the *asset control* phase, the user adds airplanes and flights. In the *flight service* phase, the user can print airplanes, print flights, and look up a single airplane.

Following the separation of concerns from Chapter 6, we split the program into three layers:

- **Domain classes** in `domain/`: `Airplane` and `Flight`. They represent concepts and know nothing about the user interface.
- **Application logic** in `logic/`: a class `FlightControl` that owns the airplanes and flights and offers operations such as `addAirplane(id, capacity)`, `addFlight(airplaneId, departure, destination)`, `getAirplanes()`, `getFlights()` and `getAirplane(id)`.
- **User interface** in `ui/`: a class `TextUI` that reads commands from a `std::istream&` and calls the application logic.

Who owns the airplanes? `FlightControl` does — say, in a `std::map<std::string, Airplane>` keyed by identifier. A `Flight` must refer to its airplane. It could store a copy, but then a change to the airplane would not be reflected; it could store a pointer to the airplane inside the map (pointers into a `std::map` stay valid as long as the element exists); or it could simply store the airplane's identifier and let `FlightControl` look it up. Each choice is reasonable; the identifier is the simplest and safest.

### Exercise 11.10: Flight Control (2 parts)

*Template: `exercises/part11/11_10_FlightControl`*

Implement the flight control application. You may design the structure as you wish; the outline above is a good starting point. Use folders and namespaces, and split classes into headers and source files.

**Part 1: Airport asset control.**

```
Airport Asset Control
--------------------

Choose an action:
[1] Add an airplane
[2] Add a flight
[x] Exit Airport Asset Control
> 1
Give the airplane id: HA-LOL
Give the airplane capacity: 42
Choose an action:
[1] Add an airplane
[2] Add a flight
[x] Exit Airport Asset Control
> 2
Give the airplane id: HA-LOL
Give the departure airport id: HEL
Give the target airport id: BAL
Choose an action:
[1] Add an airplane
[2] Add a flight
[x] Exit Airport Asset Control
> x
```

(In this exercise the prompts and the user's input are on the same line; the program prints `> ` itself as the prompt.)

**Part 2: Flight service.**

```
Flight Control
------------

Choose an action:
[1] Print airplanes
[2] Print flights
[3] Print airplane details
[x] Quit
> 1
G-OWAC (101 capacity)
HA-LOL (42 capacity)
Choose an action:
[1] Print airplanes
[2] Print flights
[3] Print airplane details
[x] Quit
> 2
HA-LOL (42 capacity) (HEL-BAL)
G-OWAC (101 capacity) (JFK-BAL)
Choose an action:
[1] Print airplanes
[2] Print flights
[3] Print airplane details
[x] Quit
> 3
Give the airplane id: G-OWAC
G-OWAC (101 capacity)
Choose an action:
[1] Print airplanes
[2] Print flights
[3] Print airplane details
[x] Quit
> x
```

## 11.3 Exceptions

Things go wrong while programs run: a file is missing, the user types `abc` where a number was expected, a network connection drops. An **exception** is C++'s mechanism for signalling such an error from the place where it is *detected* to a place where it can be *handled*.

### Handling exceptions

You have seen exceptions stop programs: `std::stoi("abc")` throws `std::invalid_argument`, and `vec.at(100)` throws `std::out_of_range`. To handle an exception instead, put the code that may fail in a `try` block, followed by one or more `catch` blocks:

```cpp
std::string line;
std::getline(std::cin, line);
try {
    int number = std::stoi(line);
    std::println("You gave {}", number);
} catch (const std::invalid_argument& error) {
    std::println("That was not a number.");
}
```

When an exception is thrown inside the `try` block, the rest of the block is skipped and execution jumps to the first `catch` whose type matches. If no `catch` matches, the exception continues outward to the calling function, and so on up the call stack. If nothing catches it, the program terminates.

Catch exceptions **by const reference**: `catch (const std::exception& e)`. The member function `what()` returns a description:

```cpp
try {
    std::vector<int> numbers = {1, 2, 3};
    std::println("{}", numbers.at(10));
} catch (const std::exception& error) {
    std::println("Error: {}", error.what());
}
```

Standard exceptions form a hierarchy, with `std::exception` at the top. Catching a base class catches all derived exceptions too:

```
std::exception
├── std::logic_error          (errors in program logic, could have been prevented)
│   ├── std::invalid_argument
│   ├── std::domain_error
│   ├── std::length_error
│   └── std::out_of_range
├── std::runtime_error        (errors that can only be detected while running)
│   ├── std::range_error
│   ├── std::overflow_error
│   └── std::system_error     (e.g. file system errors)
└── std::bad_alloc, std::bad_optional_access, ...
```

A useful pattern for reading numbers robustly:

```cpp
int readNumber(std::istream& input) {
    std::string line;
    while (true) {
        std::getline(input, line);
        try {
            return std::stoi(line);
        } catch (const std::exception&) {
            std::println("Not a number, try again:");
        }
    }
}
```

(`std::stoi` throws `std::invalid_argument` for text and `std::out_of_range` for numbers too large for an `int`; catching `std::exception` handles both.)

### Exceptions and resources

What happens to open files and other resources when an exception jumps out of a function? Thanks to **RAII** (Chapter 4), they are cleaned up automatically: as the exception leaves each scope, the destructors of all local objects run. An `std::ifstream` closes its file, a `std::vector` frees its memory, a `std::unique_ptr` deletes its object. This is called **stack unwinding**, and it is the main reason modern C++ code almost never needs explicit cleanup code.

This is also why you should never manage resources with raw `new`/`delete` or manual open/close calls: an exception between the two would skip the cleanup.

### Shifting the responsibility

A function does not have to handle an exception itself. If it cannot do anything sensible about an error, it should let the exception pass to its caller, which knows more about the situation. A file-reading function cannot know whether a missing file means "use defaults" or "ask the user again"; its caller can.

Unlike Java, C++ does not require functions to declare which exceptions they may throw. Document it in a comment instead. Functions that are guaranteed **never** to throw can be marked `noexcept`; destructors are `noexcept` automatically, and should never throw.

### Throwing exceptions

You throw an exception with `throw`:

```cpp
class Person {
public:
    Person(const std::string& name, int age) : name(name), age(age) {
        if (name.empty() || name.size() > 40) {
            throw std::invalid_argument("Name must be 1-40 characters long");
        }
        if (age < 0 || age > 120) {
            throw std::invalid_argument("Age must be between 0 and 120");
        }
    }
    // ...
};
```

Throwing from a constructor is the standard way to refuse to create an invalid object: if the constructor throws, the object never comes into existence. That guarantees every `Person` that exists is valid.

When should you throw, and when should you return a value such as `std::optional` or `false`? A rule of thumb: use exceptions for **exceptional** situations that the immediate caller usually cannot handle (invalid arguments, missing resources); use return values for **expected** outcomes ("the word was not in the dictionary").

You can also define your own exception types by inheriting from a standard exception:

```cpp
class InsufficientFunds : public std::runtime_error {
public:
    InsufficientFunds() : std::runtime_error("Not enough money on the account") {}
};
```

### Exercise 11.11: Validating Parameters (2 parts)

*Template: `exercises/part11/11_11_ValidatingParameters`*

The template contains the classes `Person` and `Calculator`.

**Part 1: Validating a person.** The constructor of `Person` must throw `std::invalid_argument` if the name is empty or longer than 40 characters, or if the age is not between 0 and 120.

**Part 2: Validating the calculator.** `int factorial(int num)` must throw `std::invalid_argument` if `num` is negative. `int binomialCoefficient(int setSize, int subsetSize)` must throw if either is negative or if `subsetSize` is larger than `setSize`.

### Exceptions and interfaces

An interface should document which exceptions its functions may throw, so that every implementation follows the same rules and callers know what to expect. In the next exercise, reading a sensor that is off throws `std::logic_error` — calling `read` in that state is an error in the calling program's logic.

### Details of an exception

The `what()` message is the main detail an exception carries, but your own exception types can carry more: a file name, an error code, a line number. And when debugging, remember that the debugger can be told to stop when an exception is thrown, showing you exactly where it came from.

### Exercise 11.12: Sensors and Temperature (4 parts)

*Template: `exercises/part11/11_12_SensorsAndTemperature`*

The template contains the interface:

```cpp
class Sensor {
public:
    virtual ~Sensor() = default;
    virtual bool isOn() const = 0;   // true if the sensor is on
    virtual void setOn() = 0;        // sets the sensor on
    virtual void setOff() = 0;       // sets the sensor off
    virtual int read() = 0;          // returns the sensor's value if it is on;
                                     // if it is off, throws std::logic_error
};
```

**Part 1: Standard sensor.** Create `StandardSensor`, which is always on (`setOn` and `setOff` do nothing). Its constructor takes an integer, which `read` always returns.

```cpp
StandardSensor ten(10);
StandardSensor minusFive(-5);
std::println("{}", ten.read());
std::println("{}", minusFive.read());
std::println("{}", ten.isOn());
ten.setOff();
std::println("{}", ten.isOn());
```

```
10
-5
true
true
```

**Part 2: Temperature sensor.** Create `TemperatureSensor`, which starts off. When on, `read` returns a random integer from −30 to 30; when off, it throws `std::logic_error`.

**Part 3: Average sensor.** Create `AverageSensor`, which contains other sensors: `void addSensor(std::unique_ptr<Sensor> toAdd)`. It is on when *all* its sensors are on; `setOn` turns all of them on; `setOff` turns at least one off. `read` returns the integer average of its sensors' readings, and throws `std::logic_error` if the average sensor is off or has no sensors.

```cpp
AverageSensor helsinkiRegion;
helsinkiRegion.addSensor(std::make_unique<TemperatureSensor>());
helsinkiRegion.addSensor(std::make_unique<TemperatureSensor>());
helsinkiRegion.addSensor(std::make_unique<TemperatureSensor>());
helsinkiRegion.setOn();
std::println("The temperature in Helsinki region is {} degrees Celsius", helsinkiRegion.read());
```

**Part 4: All readings.** Add `std::vector<int> readings() const` to `AverageSensor`, returning the results of all the `read` calls made so far on the average sensor (each call adds one value).

## 11.4 Processing files

Chapter 4 showed how to read files. Writing is just as easy, with `std::ofstream` ("output file stream"):

```cpp
#include <fstream>

std::ofstream file("output.txt");
if (!file) {
    std::println("Could not open the file for writing");
    return;
}
std::println(file, "First line");
std::println(file, "The answer is {}", 42);
```

`std::println` and `std::print` accept a stream as their first argument and write to it instead of the screen. (Older code writes with `file << "First line\n";`, which works too.) The file is closed and its contents flushed to disk when `file` is destroyed.

Opening a file for writing **replaces** its contents. To add to the end instead, open it in append mode: `std::ofstream file("log.txt", std::ios::app);`.

### Files and errors

By default, file streams do not throw exceptions: they just enter a failed state, which you check with `if (!file)`. A function that cannot complete its job because of a file error can then report it — by returning `false`, returning an empty optional, or throwing an exception:

```cpp
std::vector<std::string> readLinesOrThrow(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file) {
        throw std::runtime_error("Cannot open " + fileName);
    }
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}
```

### The file system

The `<filesystem>` library works with paths, folders and file metadata:

```cpp
#include <filesystem>
namespace fs = std::filesystem;

if (fs::exists("data.txt")) {
    std::println("Size: {} bytes", fs::file_size("data.txt"));
}

for (const auto& entry : fs::directory_iterator(".")) {
    std::println("{}", entry.path().string());
}
```

`namespace fs = std::filesystem;` is a **namespace alias**: a shorter name for a long namespace. Operations that fail throw `std::filesystem::filesystem_error`.

### Exercise 11.13: Saveable Dictionary (4 parts)

*Template: `exercises/part11/11_13_SaveableDictionary`*

Build a dictionary that translates in both directions (Finnish ↔ another language) and can be loaded from and saved to a file.

**Part 1: Basic functionality.** Create `SaveableDictionary` with a default constructor and:

- `void add(const std::string& word, const std::string& translation)` — adds a word pair; if the word already exists, nothing happens,
- `std::optional<std::string> translate(const std::string& word) const` — translates in either direction.

```cpp
SaveableDictionary dictionary;
dictionary.add("apina", "monkey");
dictionary.add("banaani", "banana");
dictionary.add("apina", "apfe");

std::println("{}", dictionary.translate("apina").value_or("-"));
std::println("{}", dictionary.translate("monkey").value_or("-"));
std::println("{}", dictionary.translate("ohjelmointi").value_or("-"));
std::println("{}", dictionary.translate("banana").value_or("-"));
```

```
monkey
apina
-
banaani
```

**Part 2: Deleting words.** Add `void remove(const std::string& word)`, which deletes the word and its translation (whichever side is given).

**Part 3: Loading from a file.** Add a constructor `SaveableDictionary(const std::string& fileName)` and `bool load()`. The constructor only remembers the file name; `load` reads the file, which has one `word:translation` pair per line, and returns `false` if the file cannot be read. The template folder contains `words.txt`:

```
apina:monkey
alla oleva:below
olut:beer
```

**Part 4: Saving to a file.** Add `bool save() const`, which writes all word pairs to the file (each pair once, in the `word:translation` format) and returns whether it succeeded.

```cpp
SaveableDictionary dictionary("new.txt");
dictionary.add("tietokone", "computer");
dictionary.save();
```

## 11.5 Conclusion

- **Class diagrams** describe classes (members with `-`/`+`), connections (arrows, multiplicities), inheritance (`--|>`) and interfaces (`..|>`).
- Split larger classes into a **header** with declarations and a **source file** with definitions; every header has `#pragma once`.
- **Namespaces** prevent name clashes; folders organise files; access specifiers control visibility. Avoid `using namespace std;`.
- **Exceptions** separate error detection from error handling: `throw`, `try`, `catch (const T& e)`. Standard exceptions derive from `std::exception`. Throw from constructors to refuse invalid objects.
- Stack unwinding runs destructors, so RAII objects clean up even when exceptions fly.
- `std::ofstream` writes files; `std::println(file, ...)` prints into them. `<filesystem>` works with paths and directories.
