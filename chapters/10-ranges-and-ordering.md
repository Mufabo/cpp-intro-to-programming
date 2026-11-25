# Chapter 10: Ranges, Lambdas and Ordering

This chapter introduces a more declarative style of processing data. Instead of writing loops that say step by step *how* to compute something, we describe *what* we want: "the positive numbers", "their squares", "the sum". C++ supports this style through **lambdas** and the **ranges** library. We also learn to define an order for our own objects, and pick up several handy techniques: building strings, regular expressions, enumerations, iterators, and teaching `std::println` to print our own classes.

## 10.1 Processing collections with ranges

Here is a familiar task: read numbers until the user types `end`, then print the average of the numbers that are divisible by three. With loops, it looks like this:

```cpp
int sum = 0;
int count = 0;
for (int number : numbers) {
    if (number % 3 == 0) {
        sum += number;
        count++;
    }
}
double average = static_cast<double>(sum) / count;
```

With ranges, it looks like this:

```cpp
#include <ranges>
#include <algorithm>

auto divisibleByThree = numbers
    | std::views::filter([](int number) { return number % 3 == 0; });

int sum = std::ranges::fold_left(divisibleByThree, 0, std::plus{});
auto count = std::ranges::distance(divisibleByThree);
double average = static_cast<double>(sum) / count;
```

The second version reads almost like a description: take the numbers, keep those divisible by three, add them up, count them. Let's take the pieces apart.

### Lambda expressions

A **lambda** is a small function written right where it is needed, without a name:

```cpp
[](int number) { return number % 3 == 0; }
```

- `[]` starts the lambda (we will see what can go inside the brackets shortly),
- `(int number)` is the parameter list,
- `{ return number % 3 == 0; }` is the body.

A lambda is a value. It can be stored in a variable and called like a function:

```cpp
auto isEven = [](int number) { return number % 2 == 0; };
std::println("{}", isEven(4));   // true
```

The parameter type may be `auto`, which lets the lambda accept any type for which the body makes sense:

```cpp
auto twice = [](auto value) { return value + value; };
std::println("{} {}", twice(21), twice(std::string("ab")));   // 42 abab
```

Lambdas can use variables from the surrounding code by **capturing** them in the brackets:

```cpp
int limit = 10;
auto isBig = [limit](int number) { return number > limit; };        // captures a copy
int counter = 0;
auto countIt = [&counter](int) { counter++; };                      // captures a reference
```

`[limit]` copies `limit` into the lambda. `[&counter]` refers to the original `counter`, so the lambda can change it. `[=]` captures everything used by copy, `[&]` everything by reference. Prefer listing captures explicitly, and be careful with references: a lambda must not outlive the variables it refers to.

### Views and pipelines

A **view** is a lightweight, lazy sequence built from another range. The most important view adaptors in `<ranges>` are:

| Adaptor | Result |
|---|---|
| `std::views::filter(pred)` | the elements for which `pred` returns true |
| `std::views::transform(f)` | `f(x)` for every element `x` |
| `std::views::take(n)` | the first `n` elements |
| `std::views::drop(n)` | all but the first `n` elements |
| `std::views::reverse` | the elements in reverse order |
| `std::views::iota(a, b)` | the integers `a, a+1, …, b−1` |
| `std::views::keys`, `std::views::values` | the keys or values of a map |

Adaptors are combined with the **pipe operator** `|`, which reads left to right:

```cpp
std::vector<int> numbers = {3, 2, 17, 6, 8, 5, 9};

auto squaresOfOdd = numbers
    | std::views::filter([](int n) { return n % 2 != 0; })
    | std::views::transform([](int n) { return n * n; });

for (int value : squaresOfOdd) {
    std::print("{} ", value);   // 9 289 25 81
}
std::println("");
```

Views are **lazy**: nothing is computed when the pipeline is built. Elements are produced one at a time as the loop asks for them. Views also do not copy the underlying data — they *refer* to it, so the original vector must stay alive and unchanged while the view is used.

### Turning a view into a container

To store the results, convert the view into a container with `std::ranges::to` (C++23):

```cpp
std::vector<int> result = numbers
    | std::views::filter([](int n) { return n > 5; })
    | std::ranges::to<std::vector>();
```

### Algorithms that produce a single value

Many algorithms in `<algorithm>` and `<numeric>` "reduce" a range to one value:

| Algorithm | Result |
|---|---|
| `std::ranges::fold_left(r, init, op)` | combines all elements with `op`, starting from `init` (C++23) |
| `std::ranges::count_if(r, pred)` | how many elements satisfy `pred` |
| `std::ranges::distance(r)` | the number of elements |
| `std::ranges::any_of(r, pred)` / `all_of` / `none_of` | does some / every / no element satisfy `pred`? |
| `std::ranges::max(r)` / `min(r)` | the largest / smallest element (the range must not be empty) |
| `std::ranges::find_if(r, pred)` | an iterator to the first element satisfying `pred` |

`std::plus{}` is a ready-made function object that adds two values, so `fold_left(r, 0, std::plus{})` computes a sum. Write `fold_left(r, 0.0, std::plus{})` to sum in `double`.

### Exercise 10.1: Average of Numbers

*Template: `exercises/part10/10_01_AverageOfNumbers`*

Read numbers until the user writes `end`, then print their average. Compute the average with range algorithms, not with a hand-written loop (reading the input still needs a loop).

```
Input numbers, type "end" to stop.
> 2
> 4
> 6
> end
average of the numbers: 4
```

```
Input numbers, type "end" to stop.
> -1
> 1
> 2
> end
average of the numbers: 0.6666666666666666
```

### Exercise 10.2: Average of Selected Numbers

*Template: `exercises/part10/10_02_AverageOfSelectedNumbers`*

As before, but then ask whether to print the average of the negative or of the positive numbers. Use `std::views::filter`.

```
Input numbers, type "end" to stop.
> -1
> 1
> 2
> end
Print the average of the negative numbers or the positive numbers? (n/p)
> p
Average of the positive numbers: 1.5
```

### Exercise 10.3: Positive Numbers

*Template: `exercises/part10/10_03_PositiveNumbers`*

Implement `std::vector<int> positive(const std::vector<int>& numbers)`, which returns the positive numbers. Use `std::views::filter` and `std::ranges::to`.

### Exercise 10.4: Divisible

*Template: `exercises/part10/10_04_Divisible`*

Implement `std::vector<int> divisible(const std::vector<int>& numbers)`, which returns the numbers divisible by two, three or five.

```cpp
std::vector<int> numbers = {3, 2, -17, -5, 7};
for (int number : divisible(numbers)) {
    std::println("{}", number);
}
```

```
3
2
-5
```

### Exercise 10.5: Printing User Input

*Template: `exercises/part10/10_05_PrintingUserInput`*

Read strings until an empty line, storing them in a vector. Then print them all using `std::ranges::for_each` and a lambda.

### Exercise 10.6: Limited Numbers

*Template: `exercises/part10/10_06_LimitedNumbers`*

Read numbers until a negative number. Then print the numbers between 1 and 5 (inclusive), using a view.

```
> 7
> 14
> 4
> 5
> 4
> -1
4
5
4
```

### Exercise 10.7: Unique Last Names

*Template: `exercises/part10/10_07_UniqueLastNames`*

The template reads people (first name, last name, birth year) into a vector of `Person` objects. Extend it to print the unique last names in alphabetical order. One way: transform the people into their last names, collect them into a `std::set<std::string>` (which sorts and removes duplicates), and print the set.

```
Unique last names in alphabetical order:
Hopper
Lovelace
Turing
```

### Objects and ranges

Ranges work with objects as well. **Projections** make this especially neat: many range algorithms accept, as an extra argument, a function that is applied to each element before the algorithm looks at it. A pointer to a member function works as a projection:

```cpp
std::vector<Person> persons = ...;

// the oldest person: compare by getAge()
const Person& oldest = std::ranges::max(persons, {}, &Person::getAge);

// how many adults?
auto adults = std::ranges::count_if(persons, [](const Person& p) { return p.getAge() >= 18; });

// the names of everyone, as a vector
std::vector<std::string> names = persons
    | std::views::transform(&Person::getName)
    | std::ranges::to<std::vector>();
```

The `{}` in `std::ranges::max(persons, {}, &Person::getAge)` stands for the default comparison (`<`); the third argument is the projection.

### Exercise 10.8: Weighting (2 parts)

*Template: `exercises/part10/10_08_Weighting`*

The template contains the cargo hold program from Chapter 6. Rewrite its loops with range algorithms and views: in the end there should be no `for` or `while` loops left in `Suitcase` and `Hold`.

**Part 1.** Rewrite `Suitcase::totalWeight`, `Suitcase::printItems` and `Suitcase::heaviestItem`.

**Part 2.** Rewrite `Hold::totalWeight` and `Hold::printItems`.

### Files and ranges

Reading the lines of a file is still a loop, but once they are in a vector, ranges take over:

```cpp
std::vector<std::string> readLines(const std::string& fileName) {
    std::vector<std::string> lines;
    std::ifstream file(fileName);
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

auto persons = readLines("people.csv")
    | std::views::filter([](const std::string& line) { return !line.empty(); })
    | std::views::transform([](const std::string& line) {
          auto parts = split(line, ',');
          return Person(parts[0], std::stoi(parts[1]));
      })
    | std::ranges::to<std::vector>();
```

### Exercise 10.9: Reading Files per Line

*Template: `exercises/part10/10_09_ReadingFilesPerLine`*

Implement `std::vector<std::string> read(const std::string& fileName)`, which returns the lines of the file. If the file cannot be opened, return an empty vector.

### Exercise 10.10: Books from File

*Template: `exercises/part10/10_10_BooksFromFile`*

The template contains a class `Book`. Implement `std::vector<Book> readBooks(const std::string& fileName)`. Each line of the file has the format `name,publishing year,page count,author`:

```
Do Androids Dream of Electric Sheep?,1968,210,Philip K. Dick
Love in the Time of Cholera,1985,348,Gabriel Garcia Marquez
```

## 10.2 Ordering objects

`std::ranges::sort` sorts anything that can be compared with `<`. To sort objects of our own classes, we can either give the class an ordering, or tell `sort` how to compare.

### Defining an order: the spaceship operator

C++20 introduced the **three-way comparison operator** `<=>`, nicknamed the *spaceship operator*. Defining it gives a class all of `<`, `<=`, `>` and `>=` at once:

```cpp
#include <compare>

class Member {
public:
    Member(const std::string& name, int height) : name(name), height(height) {}

    std::strong_ordering operator<=>(const Member& other) const {
        return height <=> other.height;
    }

    bool operator==(const Member& other) const {
        return height == other.height;
    }

    // ...
private:
    std::string name;
    int height;
};
```

`a <=> b` returns a value that says whether `a` is less than, equal to, or greater than `b`. For integers and strings it is built in, so a class's `<=>` usually just delegates to its members' `<=>`. (`std::strong_ordering` is the result type for integers; for `double` it is `std::partial_ordering`. You can write `auto` as the return type and let the compiler choose.)

Note that `==` is defined separately: when `<=>` is written by hand, the compiler does not derive `==` from it. Make sure the two agree.

If the order should consider all members in declaration order, both can be defaulted:

```cpp
auto operator<=>(const Member& other) const = default;   // also gives == 
```

Now members can be sorted:

```cpp
std::vector<Member> members = {{"mikael", 182}, {"matti", 187}, {"ada", 184}};
std::ranges::sort(members);
```

To sort in **descending** order, pass a different comparison: `std::ranges::sort(members, std::greater{});`.

> **Coming from Java?** Java's `Comparable.compareTo` returns a negative number, zero or a positive number. C++'s `<=>` returns an ordering value that compares the same way with zero: `(a <=> b) < 0` means `a < b`.

### Exercise 10.11: Wage Order

*Template: `exercises/part10/10_11_WageOrder`*

The template contains a class `Human` with a name and a wage. Define `operator<=>` (and `operator==`) so that sorting a vector of humans with `std::ranges::sort` orders them by wage from the **highest** to the lowest.

### Exercise 10.12: Students in Alphabetical Order

*Template: `exercises/part10/10_12_StudentsOnAlphabeticalOrder`*

The template contains a class `Student` with a name. Define the ordering so that students sort alphabetically by name.

### Sorting with a lambda

Often an object has no single natural order: sometimes we want people by age, sometimes by name. Instead of defining `<=>`, pass a comparison lambda — or, even simpler, a projection — to `sort`:

```cpp
// by age, with a comparison lambda
std::ranges::sort(persons, [](const Person& a, const Person& b) {
    return a.getAge() < b.getAge();
});

// by age, with a projection (same result)
std::ranges::sort(persons, {}, &Person::getAge);

// by name, descending
std::ranges::sort(persons, std::greater{}, &Person::getName);
```

The comparison must behave like `<`: return `true` exactly when the first argument should come **before** the second.

### Exercise 10.13: Literacy Comparison (2 parts)

*Template: `exercises/part10/10_13_LiteracyComparison`*

The file `literacy.csv` in the template folder contains UNESCO's estimates of adult literacy rates. Each line contains: theme, age group, gender, country, year, literacy percentage:

```
Adult literacy rate, population 15+ years, female (%),United Republic of Tanzania,2015,76.08978
Adult literacy rate, population 15+ years, female (%),Zimbabwe,2015,85.28513
Adult literacy rate, population 15+ years, male (%),Honduras,2014,87.39595
```

Read the file and print the records from the lowest literacy rate to the highest, exactly in this format (the first lines of the output):

```
Niger (2015), female, 11.01572
Mali (2015), female, 22.19578
Guinea (2015), female, 22.87104
Afghanistan (2015), female, 23.87385
Central African Republic (2015), female, 24.35549
```

Note that the gender field is ` female (%)` with a leading space; extract just `female` or `male`. Print the percentage exactly as it appears in the file (keep it as a string for printing, and convert it with `std::stod` for sorting). A `trim` helper that removes spaces from both ends of a string is useful here; write one with `find_first_not_of` and `find_last_not_of`.

### Sorting by multiple criteria

To sort by one criterion and break ties with another, compare **tuples**. `std::tie` packs references to several values into a tuple, and tuples compare element by element:

```cpp
std::ranges::sort(films, [](const Film& a, const Film& b) {
    return std::tie(a.year, a.name) < std::tie(b.year, b.name);   // by year, then by name
});
```

(`std::tie` needs `<tuple>`. With getters, write `std::tuple(a.getYear(), a.getName())`.) The same trick makes a multi-criteria `<=>` easy:

```cpp
auto operator<=>(const Film& other) const {
    return std::tuple(year, name) <=> std::tuple(other.year, other.name);
}
```

Another approach is a **stable sort**: `std::ranges::stable_sort` keeps elements that compare equal in their original relative order. Sorting first by the secondary key and then *stably* by the primary key gives the same result.

### Exercise 10.14: Literature (3 parts)

*Template: `exercises/part10/10_14_Literature`*

Read books and their age recommendations until the name is empty.

**Part 1: Reading and printing.**

```
Input the name of the book, empty stops:
> The Ringing Lullaby Book
Input the age recommendation:
> 0
Input the name of the book, empty stops:
> The Snowy Forest Calls
Input the age recommendation:
> 12
Input the name of the book, empty stops:
> Litmanen 10
Input the age recommendation:
> 10
Input the name of the book, empty stops:
>

3 books in total.

Books:
The Ringing Lullaby Book (recommended for 0 year-olds or older)
The Snowy Forest Calls (recommended for 12 year-olds or older)
Litmanen 10 (recommended for 10 year-olds or older)
```

**Part 2: Ordering by age recommendation.** Print the books ordered by age recommendation.

**Part 3: Ordering by age recommendation and name.** Books with the same age recommendation are ordered alphabetically by name.

## 10.3 Other useful techniques

### Building strings

Repeatedly appending to a `std::string` with `+=` is efficient in C++: a string grows its buffer in large steps, much like a vector. (Java needs a separate `StringBuilder` class for this; C++ does not.)

```cpp
std::string numbers;
for (int i = 1; i <= 5; i++) {
    numbers += std::to_string(i);
    if (i < 5) {
        numbers += ", ";
    }
}
```

When building text from many differently typed pieces, `std::format` is often clearest. For "format into an existing string", there is `std::format_to(std::back_inserter(text), "...", ...)`. And `std::ostringstream` (header `<sstream>`) lets you write with `<<` as to `std::cout`, then take the result with `.str()`.

Joining a range of strings with a separator is a one-liner with views (C++23):

```cpp
std::vector<std::string> words = {"red", "green", "blue"};
std::string joined = words | std::views::join_with(std::string(", ")) | std::ranges::to<std::string>();
// "red, green, blue"
```

### Regular expressions

A **regular expression** describes a pattern of text. C++ supports them in `<regex>`. `std::regex_match` checks whether a whole string matches a pattern:

```cpp
#include <regex>

std::regex studentNumber("01[0-9]{7}");
if (std::regex_match("011234567", studentNumber)) {
    std::println("Correct format.");
}
```

The most important building blocks:

| Pattern | Matches |
|---|---|
| `abc` | exactly `abc` |
| `a\|b` | `a` or `b` (alternation) |
| `(ab)\|c` | parentheses group parts: `ab` or `c` |
| `x*` | zero or more `x` |
| `x+` | one or more `x` |
| `x?` | zero or one `x` |
| `x{3}` | exactly three `x` |
| `x{2,4}` | two to four `x` |
| `[abc]` | one of the characters `a`, `b`, `c` |
| `[a-z]` | one character in the range `a`–`z` |
| `[^0-9]` | one character that is *not* a digit |
| `.` | any one character |

In C++ source code, backslashes in regular expressions must be doubled (`"\\d"`), or you can use a **raw string literal**, which treats backslashes literally: `R"(\d{3}-\d{4})"`.

`std::regex_search` finds a match anywhere inside a string, and `std::sregex_iterator` iterates over all matches. Regular expressions are powerful but can be hard to read; for simple checks, string functions are often clearer.

### Exercise 10.15: Regular Expressions (3 parts)

*Template: `exercises/part10/10_15_RegularExpressions`*

Create the following functions using regular expressions. The template's `main` asks for a string and prints `The form is correct.` or `The form is incorrect.`

**Part 1: Day of week.** `bool isDayOfWeek(const std::string& text)` — true for `mon`, `tue`, `wed`, `thu`, `fri`, `sat` or `sun`.

**Part 2: Vowel check.** `bool allVowels(const std::string& text)` — true if every character is one of `a`, `e`, `i`, `o`, `u` (and the string is not empty).

**Part 3: Time of day.** `bool timeOfDay(const std::string& text)` — true if the string is a 24-hour time `hh:mm:ss` between `00:00:00` and `23:59:59`.

```
Enter a string:
> 17:23:05
The form is correct.
```

```
Enter a string:
> 33:33:33
The form is incorrect.
```

### Enumerations: `enum class`

An **enumeration** is a type with a fixed set of named values:

```cpp
enum class Suit { Club, Diamond, Heart, Spade };

Suit suit = Suit::Heart;
if (suit == Suit::Heart) {
    std::println("Hearts!");
}
```

`enum class` (a *scoped enumeration*) keeps its values inside its own name, so they are written `Suit::Heart`. Its values do not convert silently to integers, which prevents accidental mix-ups. When you need the number, convert explicitly: `static_cast<int>(Suit::Heart)` is 2 (values count from 0 in declaration order). You can also choose the numbers: `enum class Color { Red = 1, Green = 2 };`.

A `switch` statement is a natural companion to enums:

```cpp
std::string toString(Suit suit) {
    switch (suit) {
        case Suit::Club:    return "CLUB";
        case Suit::Diamond: return "DIAMOND";
        case Suit::Heart:   return "HEART";
        case Suit::Spade:   return "SPADE";
    }
    return "?";
}
```

With warnings on, the compiler tells you if a `switch` over an enum forgets a value — a big help when a new value is added later.

### Data attached to enum values

Java enums can carry fields and methods. C++ enums are plain sets of values, so data associated with each value is usually kept in a function (as `toString` above) or in an array indexed by the value:

```cpp
enum class Color { Red, Green, Blue };

constexpr std::array<std::string_view, 3> colorCodes = {"#FF0000", "#00FF00", "#0000FF"};

std::string_view code(Color color) {
    return colorCodes[static_cast<std::size_t>(color)];
}
```

`constexpr` means the array is computed at compile time, and `std::string_view` is a read-only view of characters — perfect for constant text.

### Iterators

An **iterator** is an object that points to a position in a container. You have already used them: `vec.begin()` points to the first element, `vec.end()` points *one past* the last one. An iterator is moved forward with `++` and the element it points to is read with `*`:

```cpp
std::vector<std::string> names = {"Petrus", "Arto", "Elina"};
for (auto it = names.begin(); it != names.end(); ++it) {
    std::println("{}", *it);
}
```

This is exactly what the range-based `for` loop does behind the scenes. All standard containers provide iterators, which is why the same algorithms work with vectors, maps, sets and strings.

Iterators matter when **removing** elements while traversing. Removing from a vector inside a range-based `for` loop is a bug: it invalidates the loop's iterator. The `erase` member function returns an iterator to the element after the removed one, so the correct manual loop looks like this:

```cpp
for (auto it = names.begin(); it != names.end(); ) {
    if (it->starts_with("A")) {
        it = names.erase(it);   // continue from the next element
    } else {
        ++it;
    }
}
```

In practice, use `std::erase_if`, which does the same in one line and more efficiently:

```cpp
std::erase_if(names, [](const std::string& name) { return name.starts_with("A"); });
```

### Exercise 10.16: Enum and Iterator (4 parts)

*Template: `exercises/part10/10_16_EnumAndIterator`*

**Part 1: Education.** Create `enum class Education { PHD, MA, BA, HS };` and a function `std::string toString(Education education)` returning the enumerator's name.

**Part 2: Person.** Create a class `Person` with a name and an education, `Education getEducation() const`, and `toString` returning e.g. `Anna, PHD`.

**Part 3: Employees.** Create a class `Employees` with `void add(const Person& person)`, `void add(const std::vector<Person>& people)`, `void print() const`, and `void print(Education education) const`, which prints only the people with that education. Implement the `print` functions with explicit iterators.

**Part 4: Firing.** Add `void fire(Education education)`, which removes everyone with the given education. Implement it first with an explicit iterator loop, then replace it with `std::erase_if`.

```cpp
Employees university;
university.add(Person("Petrus", Education::PHD));
university.add(Person("Arto", Education::HS));
university.add(Person("Elina", Education::PHD));

university.print();
university.fire(Education::HS);
std::println("==");
university.print();
```

```
Petrus, PHD
Arto, HS
Elina, PHD
==
Petrus, PHD
Elina, PHD
```

### Printing your own types with `std::println`

Since Chapter 4 we have printed objects with `std::println("{}", object.toString())`. To make `std::println("{}", object)` work directly, specialise `std::formatter` for the class. The shortest way reuses the formatter for strings:

```cpp
#include <format>

template <>
struct std::formatter<Card> : std::formatter<std::string> {
    auto format(const Card& card, auto& context) const {
        return std::formatter<std::string>::format(card.toString(), context);
    }
};
```

After this, `std::println("{}", card)`, `std::format("{}", card)` and even `std::println("{}", vectorOfCards)` all work. (A vector of cards prints like `["DIAMOND 2", "SPADE A"]`: the elements are formatted as strings, so they get quotes.) The `auto&` parameter matters: it lets the formatter work with every kind of format context, which is what printing containers requires. As with `std::hash` in Chapter 8, treat this as a recipe for now: replace `Card` with your class name and `card.toString()` with how your object becomes text.

### Exercise 10.17: Sort Them Cards! (6 parts)

*Template: `exercises/part10/10_17_SortThemCards`*

The template contains `enum class Suit { Club, Diamond, Heart, Spade };` and a class `Card` with a value (2–14; 11 = J, 12 = Q, 13 = K, 14 = A) and a suit. `Card` already has a formatter, so cards print directly:

```cpp
Card first(2, Suit::Diamond);
Card second(14, Suit::Spade);
Card third(12, Suit::Heart);
std::println("{}", first);
std::println("{}", second);
std::println("{}", third);
```

```
DIAMOND 2
SPADE A
HEART Q
```

**Part 1: Ordering cards.** Define `<=>` and `==` for `Card`: cards are ordered by value, and cards of equal value by suit in the order of the enum (clubs first, spades last). So the smallest card is the two of clubs and the greatest the ace of spades.

**Part 2: Hand.** Create a class `Hand` with `void add(const Card& card)` and `void print() const`, which prints the cards in the order they were added.

**Part 3: Sorting the hand.** Add `void sort()`.

```cpp
Hand hand;
hand.add(Card(2, Suit::Diamond));
hand.add(Card(14, Suit::Spade));
hand.add(Card(12, Suit::Heart));
hand.add(Card(2, Suit::Spade));
hand.sort();
hand.print();
```

```
DIAMOND 2
SPADE 2
HEART Q
SPADE A
```

**Part 4: Comparing hands.** Give `Hand` a `<=>` (and `==`) that compares hands by the **sum** of their card values.

**Part 5: Sorting by a different criterion.** Write a comparison function object (a lambda stored in a variable, or a small class with `operator()`) `bySuitInValueOrder`, which orders cards first by suit and then by value. Use it with `std::ranges::sort`.

**Part 6: Sorting the hand by suit.** Add `void sortBySuit()` to `Hand`, which uses that ordering.

```
DIAMOND 2
HEART Q
SPADE 2
SPADE A
```

## 10.4 Summary

- A **lambda** is an unnamed function written inline: `[captures](parameters) { body }`.
- **Views** such as `filter`, `transform`, `take` and `reverse` build lazy pipelines with `|`. `std::ranges::to<std::vector>()` collects the results.
- Range algorithms such as `fold_left`, `count_if`, `max`, `any_of` and `for_each` replace many hand-written loops. **Projections** like `&Person::getAge` apply a member function before comparing.
- `operator<=>` defines an ordering; `= default` orders by all members. `std::ranges::sort` also takes a comparison lambda or a projection. `std::tie`/`std::tuple` sort by multiple criteria.
- Build strings with `+=`, `std::format` and `std::views::join_with`.
- `<regex>` matches text against patterns.
- `enum class` defines a type with a fixed set of named values; `switch` handles each value.
- Iterators mark positions in containers; remove elements with `erase` returning the next iterator, or simply with `std::erase_if`.
- Specialising `std::formatter` makes `std::println` print your own types.
