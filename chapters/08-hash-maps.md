# Chapter 8: Hash Maps

This chapter begins with a short recap of the first half of the book, and then introduces one of the most useful data structures in programming: the **hash map**, which finds a value by its key almost instantly. You will also learn what it takes for your own classes to work as keys.

## 8.1 Short recap

Before moving on, let's practise the core skills once more. The exercises in this section repeat earlier ones; solve them without looking at your old solutions. If something feels unfamiliar, go back to the relevant chapter.

A few reminders:

- A program runs statement by statement, from top to bottom, inside `main`.
- Variables have a type, a name and a value. Objects are values too.
- `std::getline` reads a line; `std::stoi` and `std::stod` convert text to numbers.
- `while (true)` with `break` handles "repeat until"; `for` handles "repeat n times" and "go through a vector".
- Functions take parameters (by value, `const&` or `&`) and may return a value.
- Classes bundle data with the member functions that keep it consistent.

### Exercise 8.1: Cubes

*Template: `exercises/part08/08_01_Cubes`*

Read strings until `end`. Treat every other input as an integer and print its cube.

```
> 3
27
> -1
-1
> end
```

### Exercise 8.2: Average of Positive Numbers

*Template: `exercises/part08/08_02_AverageOfPositiveNumbers`*

Read numbers until `0`, then print the average of the positive numbers, or `Cannot calculate the average` if there were none.

### Exercise 8.3: Liquid Containers (3 parts)

*Template: `exercises/part08/08_03_LiquidContainers`*

Solve Exercise 7.1 again, procedurally, in `main`.

### Exercise 8.4: Liquid Containers 2.0 (2 parts)

*Template: `exercises/part08/08_04_LiquidContainers2`*

Solve Exercise 7.2 again, with a `Container` class.

### Exercise 8.5: To-Do List (2 parts)

*Template: `exercises/part08/08_05_TodoList`*

Solve Exercise 6.10 again: a `TodoList` class with `add`, `print` and `remove`, and a `UserInterface` class that reads commands from a `std::istream&`.

## 8.2 Hash maps

A vector stores values by **position**: to find something, we either know its index or search through the elements. Often, though, we want to find a value by something meaningful — a person's details by their username, a word's translation by the word, a product's price by its code.

A **map** stores **key–value pairs**. Given a key, it finds the value. The C++ standard library has two kinds:

- `std::unordered_map` (header `<unordered_map>`) is a **hash map**. It finds values in constant time on average, no matter how many entries it has. Its keys are in no particular order.
- `std::map` (header `<map>`) keeps its keys **sorted**. Finding a value takes logarithmic time, which is still very fast.

Both have almost the same interface. We use `std::unordered_map` first.

```cpp
#include <print>
#include <string>
#include <unordered_map>

int main() {
    std::unordered_map<std::string, std::string> postalCodes;
    postalCodes["00710"] = "Helsinki";
    postalCodes["90014"] = "Oulu";
    postalCodes["33720"] = "Tampere";
    postalCodes["33014"] = "Tampere";

    std::println("{}", postalCodes.size());       // 4
    std::println("{}", postalCodes["33720"]);     // Tampere
}
```

The type `std::unordered_map<std::string, std::string>` has two type parameters: the type of the **keys** and the type of the **values**. `map[key] = value` stores a pair, and `map[key]` reads the value.

### Looking up a key that does not exist

Here C++ has a surprise. Reading `map[key]` for a key that is **not** in the map **inserts** it, with a default value (an empty string, zero, …), and returns that:

```cpp
std::println("[{}]", postalCodes["99999"]);   // prints [] — and adds "99999" to the map!
std::println("{}", postalCodes.size());       // 5
```

So use `[]` for storing, and for reading only when you are sure the key exists. To *check* or *find* without inserting, use:

```cpp
if (postalCodes.contains("00710")) {           // C++20
    std::println("Found");
}

auto found = postalCodes.find("00100");
if (found != postalCodes.end()) {
    std::println("Value: {}", found->second);
} else {
    std::println("No such postal code");
}

std::println("{}", postalCodes.at("90014"));   // throws std::out_of_range if missing
```

`find` returns an *iterator* to the key–value pair, or `end()` if the key is not there. A pair's key is `first` and its value is `second`.

### Exercise 8.6: Nicknames

*Template: `exercises/part08/08_06_Nicknames`*

In `main`, create a `std::unordered_map<std::string, std::string>` and store these names (keys) and nicknames (values), all in lower case:

- matthew's nickname is matt,
- michael's nickname is mix,
- arthur's nickname is artie.

Then look up Matthew's nickname and print it.

### A key corresponds to at most one value

Each key appears in a map at most once. Assigning to an existing key replaces its value:

```cpp
std::unordered_map<std::string, int> numbers;
numbers["One"] = 1;
numbers["One"] = 42;
std::println("{}", numbers["One"]);   // 42
```

Many keys may, however, have the same value — `33720` and `33014` both map to `Tampere`.

### Objects as values

Values can be any type, including your own classes:

```cpp
std::unordered_map<std::string, Book> library;
library.emplace("sense", Book("Sense and Sensibility", 1811, "..."));
library.emplace("prejudice", Book("Pride and Prejudice", 1813, "..."));

auto found = library.find("sense");
if (found != library.end()) {
    std::println("{}", found->second.toString());
}
```

`emplace(key, value)` inserts a pair if the key is not there yet. We use it instead of `library["sense"] = ...` because `[]` needs a default constructor for the value type (to create a value when the key is missing), and `Book` does not have one.

### When should hash maps be used?

Use a map whenever you need to find things by a key: lookups by name, by code, by identifier. Searching a vector of a million books for a title takes up to a million comparisons; finding it in a hash map takes a handful of operations.

As an example, let's compare looking up a book in a vector and in a map:

```cpp
// with a vector: linear search
for (const Book& book : books) {
    if (book.getName() == searched) {
        std::println("{}", book.toString());
    }
}

// with a map keyed by name: direct lookup
if (auto found = booksByName.find(searched); found != booksByName.end()) {
    std::println("{}", found->second.toString());
}
```

The second `if` uses an **if with initialiser**: `if (init; condition)`. The variable `found` exists only inside the `if` and its `else`.

Keys are compared exactly, so `"Sense and sensibility"` does not find `"Sense and Sensibility"`. A common technique is to **normalise** keys — for example, store and look up everything in lower case:

```cpp
#include <algorithm>
#include <cctype>

std::string toLower(std::string text) {
    std::ranges::transform(text, text.begin(),
                           [](unsigned char c) { return std::tolower(c); });
    return text;
}
```

(`std::ranges::transform` applies a function to every character. The `[](unsigned char c) { ... }` part is a *lambda*, a small unnamed function — Chapter 10 explains them. For now you can copy this helper as it is.)

### A hash map as a member variable

Maps are often members of classes that offer a convenient interface over them:

```cpp
class Library {
public:
    void addBook(const Book& book) {
        books.insert_or_assign(toLower(book.getName()), book);
    }

    std::optional<Book> getBook(const std::string& name) const {
        auto found = books.find(toLower(name));
        if (found == books.end()) {
            return std::nullopt;
        }
        return found->second;
    }

    void removeBook(const std::string& name) {
        books.erase(toLower(name));
    }

private:
    std::unordered_map<std::string, Book> books;
};
```

`insert_or_assign` inserts or replaces, like `[]` assignment, but does not need a default constructor. `erase(key)` removes a key and its value (and does nothing if the key is not there).

### Exercise 8.7: Abbreviations

*Template: `exercises/part08/08_07_Abbreviations`*

Create a class `Abbreviations` with:

- `void addAbbreviation(const std::string& abbreviation, const std::string& explanation)`,
- `bool hasAbbreviation(const std::string& abbreviation) const`,
- `std::optional<std::string> findExplanationFor(const std::string& abbreviation) const` — empty if the abbreviation has not been added.

```cpp
Abbreviations abbreviations;
abbreviations.addAbbreviation("e.g.", "for example");
abbreviations.addAbbreviation("etc.", "and so on");
abbreviations.addAbbreviation("i.e.", "more precisely");

std::string text = "e.g. i.e. etc. lol";
for (std::string part : split(text, ' ')) {
    if (abbreviations.hasAbbreviation(part)) {
        part = *abbreviations.findExplanationFor(part);
    }
    std::print("{} ", part);
}
std::println("");
```

```
for example more precisely and so on lol
```

### Going through a map's keys

A range-based `for` loop visits every key–value pair. **Structured bindings** give names to the two parts of each pair:

```cpp
for (const auto& [code, city] : postalCodes) {
    std::println("{}: {}", code, city);
}
```

The order of an `unordered_map` is unspecified and may differ between compilers and even runs. If the order matters, use `std::map`, which visits its keys in sorted order.

### Exercise 8.8: Print Me My Hash Map

*Template: `exercises/part08/08_08_PrintMeMyHashmap`*

Implement the following functions. Each takes a `const std::map<std::string, std::string>&` (a `std::map`, so that the output order is predictable).

- `void printKeys(const std::map<std::string, std::string>& map)` — prints every key,
- `void printKeysWhere(const std::map<std::string, std::string>& map, const std::string& text)` — prints the keys that contain `text`,
- `void printValuesOfKeysWhere(const std::map<std::string, std::string>& map, const std::string& text)` — prints the values whose keys contain `text`.

```cpp
std::map<std::string, std::string> map;
map["f.e"] = "for example";
map["etc."] = "and so on";
map["i.e"] = "more precisely";

printKeys(map);
std::println("---");
printKeysWhere(map, "i");
std::println("---");
printValuesOfKeysWhere(map, ".e");
```

```
etc.
f.e
i.e
---
i.e
---
for example
more precisely
```

### Exercise 8.9: Print Me Another Hash Map

*Template: `exercises/part08/08_09_PrintMeAnotherHashmap`*

The template contains a class `Book`. Implement:

- `void printValues(const std::map<std::string, Book>& map)` — prints every book using `toString`,
- `void printValueIfNameContains(const std::map<std::string, Book>& map, const std::string& text)` — prints the books whose *name* contains `text`.

```cpp
std::map<std::string, Book> map;
map.emplace("sense", Book("Sense and Sensibility", 1811, "..."));
map.emplace("prejudice", Book("Pride and prejudice", 1813, "...."));

printValues(map);
std::println("---");
printValueIfNameContains(map, "prejud");
```

```
Name: Pride and prejudice (1813)
Contents: ....
Name: Sense and Sensibility (1811)
Contents: ...
---
Name: Pride and prejudice (1813)
Contents: ....
```

### Numbers as values, and counting

A map from keys to numbers is perfect for counting:

```cpp
std::unordered_map<std::string, int> wordCounts;
for (const std::string& word : words) {
    wordCounts[word]++;
}
```

This is one place where the inserting behaviour of `[]` is exactly right: the first time a word appears, `wordCounts[word]` creates the entry with the value 0, and `++` makes it 1.

### Exercise 8.10: I Owe You

*Template: `exercises/part08/08_10_IOweYou`*

Create a class `IOU` with:

- `void setSum(const std::string& toWhom, double amount)` — records that you owe `amount` to `toWhom`. A new sum replaces any earlier one.
- `double howMuchDoIOweTo(const std::string& toWhom) const` — returns the amount, or 0 if there is no record.

```cpp
IOU mattsIOU;
mattsIOU.setSum("Arthur", 51.5);
mattsIOU.setSum("Michael", 30);

std::println("{}", mattsIOU.howMuchDoIOweTo("Arthur"));
std::println("{}", mattsIOU.howMuchDoIOweTo("Michael"));
```

```
51.5
30
```

Note that `howMuchDoIOweTo` is `const`, so it cannot use `[]` (which might insert). Use `find` or `contains`.

## 8.3 Similarity of objects

### Equality: `operator==`

Chapter 5 showed how to define `operator==` for a class, so that `==`, `std::ranges::contains` and friends work with it. Let's recall the two forms:

```cpp
// equal when all members are equal
bool operator==(const Song& other) const = default;

// equal by a custom rule
bool operator==(const Book& other) const {
    return name == other.name && publicationYear == other.publicationYear;
}
```

### Objects as keys: hashing

A hash map does not compare a key with every stored key. Instead, it computes a **hash value** — a number derived from the key — and uses it to jump directly to a small *bucket* where that key can be. Only the few keys in the bucket are compared with `==`.

For this to work, two things are required of a key type:

1. `==` must be defined, and
2. there must be a **hash function**, and equal keys must produce equal hash values.

`std::string`, `int` and other standard types come with hash functions. For our own classes, we provide one by **specialising** the standard template `std::hash`:

```cpp
#include <functional>

class GridPoint {
public:
    GridPoint(int x, int y) : x(x), y(y) {}

    bool operator==(const GridPoint& other) const = default;

    std::size_t hashCode() const {
        return std::hash<int>{}(x) * 31 + std::hash<int>{}(y);
    }

private:
    int x;
    int y;
};

template <>
struct std::hash<GridPoint> {
    std::size_t operator()(const GridPoint& point) const {
        return point.hashCode();
    }
};

std::unordered_map<GridPoint, std::string> map;
map[GridPoint(2, 3)] = "treasure";
```

The `template <> struct std::hash<GridPoint>` block tells the standard library "this is how to hash a `GridPoint`". It must appear after the class and before any `std::unordered_map<GridPoint, ...>` is used. You do not need to understand templates yet (they come in Chapter 12); treat this as a recipe.

What makes a good hash function? Equal objects **must** have equal hashes. Unequal objects *should* usually have different hashes; if many keys share a hash, they pile up in the same bucket and lookups slow down. Combining the members with multiplication by a prime such as 31, as above, is a simple and reasonable technique — but think about the ranges of your values: if `x * 31 + y` can produce the same number for two different points, those points collide.

> **Do you even need a hash map?** If a key type can be ordered (it has `<`, or C++20's `<=>`), `std::map` works with it without any hash function. For small programs, that is often the simpler choice.

### Exercise 8.11: Same Date

*Template: `exercises/part08/08_11_SameDate`*

The template contains a class `SimpleDate`. Add `operator==` so that two dates are equal when their day, month and year are equal.

```cpp
SimpleDate d(1, 2, 2000);
std::println("{}", d == SimpleDate(1, 2, 2000));   // true
std::println("{}", d == SimpleDate(5, 2, 2012));   // false
std::println("{}", d == SimpleDate(1, 2, 2001));   // false
```

### Exercise 8.12: Hash for Date

*Template: `exercises/part08/08_12_HashedDate`*

Add a member function `std::size_t hashCode() const` to `SimpleDate` and specialise `std::hash<SimpleDate>`, so that dates can be used as keys of an `std::unordered_map`. Make hash collisions rare: dates between the years 1900 and 2100 should have different hashes as often as possible. The template's `main` checks how many distinct hash values you get for all the dates of those two centuries.

### Exercise 8.13: Vehicle Registry (3 parts)

*Template: `exercises/part08/08_13_VehicleRegistry`*

European licence plates have a two-letter country code and a national number. The template contains a class `LicensePlate`:

```cpp
class LicensePlate {
public:
    LicensePlate(const std::string& country, const std::string& liNumber)
        : liNumber(liNumber), country(country) {
    }

    std::string toString() const {
        return country + " " + liNumber;
    }

private:
    std::string liNumber;
    std::string country;
};
```

**Part 1: Equality and hash.** Add `operator==` and a `std::hash<LicensePlate>` specialisation. Then this program behaves correctly:

```cpp
LicensePlate li1("FI", "ABC-123");
LicensePlate li2("FI", "UXE-465");
LicensePlate li3("D", "B WQ-431");

std::vector<LicensePlate> finnishPlates = {li1, li2};
LicensePlate newLi("FI", "ABC-123");
if (!std::ranges::contains(finnishPlates, newLi)) {
    finnishPlates.push_back(newLi);
}
std::println("finnish: {}", finnishPlates.size());   // 2

std::unordered_map<LicensePlate, std::string> owners;
owners[li1] = "Arto";
owners[li3] = "Jürgen";
owners[LicensePlate("FI", "ABC-123")] = "Arto";
std::println("owners: {}", owners.size());           // 2
```

*Hint:* to hash a combination of strings, hash each with `std::hash<std::string>{}` and combine the results, for example `h1 * 31 + h2`.

**Part 2: VehicleRegistry.** Create a class `VehicleRegistry` with:

- `bool add(const LicensePlate& licensePlate, const std::string& owner)` — adds the plate with its owner if the plate is not registered yet; returns whether it was added,
- `std::optional<std::string> get(const LicensePlate& licensePlate) const` — returns the owner, if any,
- `bool remove(const LicensePlate& licensePlate)` — removes the plate; returns whether it was there.

**Part 3: Printing.** Add `void printLicensePlates() const`, which prints every registered plate, and `void printOwners() const`, which prints every owner **once**, even if they own several cars.

## 8.4 Grouping data with hash maps

A map's values can themselves be containers. A map from keys to vectors **groups** data: all the values that belong together are found under one key.

```cpp
std::unordered_map<std::string, std::vector<std::string>> coursesByStudent;
coursesByStudent["ada"].push_back("Programming I");
coursesByStudent["ada"].push_back("Discrete Mathematics");
coursesByStudent["grace"].push_back("Programming I");

for (const std::string& course : coursesByStudent["ada"]) {
    std::println("{}", course);
}
```

Again `[]` is handy: `coursesByStudent["ada"]` creates an empty vector the first time, and `push_back` adds to it.

Grouping is extremely common: orders by customer, emails by sender, words by first letter, transactions by month.

### Exercise 8.14: Dictionary of Many Translations

*Template: `exercises/part08/08_14_DictionaryOfManyTranslations`*

Create a class `DictionaryOfManyTranslations` that stores one or more translations for each word:

- `void add(const std::string& word, const std::string& translation)` — adds a translation, keeping the old ones,
- `std::vector<std::string> translate(const std::string& word) const` — returns the translations, or an empty vector,
- `void remove(const std::string& word)` — removes the word and all its translations.

```cpp
DictionaryOfManyTranslations dictionary;
dictionary.add("lie", "maata");
dictionary.add("lie", "valehdella");
dictionary.add("bow", "jousi");
dictionary.add("bow", "kumartaa");

std::println("{}", dictionary.translate("lie"));
dictionary.remove("bow");
std::println("{}", dictionary.translate("bow"));
```

```
["maata", "valehdella"]
[]
```

### Exercise 8.15: Storage Facility (2 parts)

*Template: `exercises/part08/08_15_StorageFacility`*

**Part 1: Adding items and examining contents.** Create a class `StorageFacility` with:

- `void add(const std::string& unit, const std::string& item)` — adds the item to the storage unit,
- `std::vector<std::string> contents(const std::string& storageUnit) const` — returns the items in the unit (empty if the unit does not exist).

```cpp
StorageFacility facility;
facility.add("a14", "ice skates");
facility.add("a14", "ice hockey stick");
facility.add("a14", "ice skates");
facility.add("f156", "rollerblades");
facility.add("f156", "rollerblades");
facility.add("g63", "six");
facility.add("g63", "pi");

std::println("{}", facility.contents("a14"));
std::println("{}", facility.contents("f156"));
```

```
["ice skates", "ice hockey stick", "ice skates"]
["rollerblades", "rollerblades"]
```

**Part 2: Listing units and removing items.** Add:

- `void remove(const std::string& storageUnit, const std::string& item)` — removes **one** occurrence of the item. If the unit becomes empty, the unit itself is removed.
- `std::vector<std::string> storageUnits() const` — returns the names of the units that contain items, in alphabetical order.

```cpp
facility.remove("f156", "rollerblades");
std::println("{}", facility.contents("f156"));
facility.remove("f156", "rollerblades");
std::println("{}", facility.storageUnits());
```

```
["rollerblades"]
["a14", "g63"]
```

## 8.5 Fast data fetching and grouping information

Hash maps are among the most important tools for writing fast programs. Whenever you find yourself searching a vector over and over for an element with some property, ask whether a map keyed by that property would do the job instantly.

| Need | Data structure |
|---|---|
| a sequence, accessed by position | `std::vector` |
| a fixed number of values | `std::array` |
| look up values by key, order irrelevant | `std::unordered_map` |
| look up values by key, sorted traversal | `std::map` |
| a set of unique values | `std::unordered_set` / `std::set` |

The last row is new: a **set** is like a map with only keys. `std::unordered_set<std::string>` (header `<unordered_set>`) stores each string at most once and answers `contains` instantly — ideal for questions like "have I seen this word before?".

```cpp
std::unordered_set<std::string> seen;
seen.insert("carrot");
seen.insert("celery");
seen.insert("carrot");                  // already there: nothing happens
std::println("{}", seen.size());         // 2
std::println("{}", seen.contains("celery"));   // true
```

### Summary

- `std::unordered_map<K, V>` maps keys to values with constant average lookup time; `std::map<K, V>` keeps keys sorted.
- `map[key]` stores and reads, but **inserts** a default value when the key is missing. Use `contains`, `find` or `at` to look up without inserting.
- Iterate over a map with `for (const auto& [key, value] : map)`.
- Maps from keys to numbers count things; maps from keys to vectors group things.
- Your own classes can be map keys: `std::map` needs `<` (or `<=>`), `std::unordered_map` needs `==` and a `std::hash` specialisation.
- Sets store unique values.
