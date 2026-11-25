# Chapter 12: Templates, Containers, Randomness and Grids

This chapter looks under the hood of the containers you have used all along. You will learn to write **templates** — classes and functions that work with any type — and use them to build simplified versions of `std::vector` and `std::unordered_map` yourself. Then we look at random numbers and at two-dimensional data.

## 12.1 Type parameters: templates

`std::vector<int>`, `std::vector<std::string>`, `std::vector<Person>`: the same container works with any element type. It is written once, as a **class template**, and the compiler generates a concrete class for each type you use it with.

Writing your own class template looks like this:

```cpp
template <typename T>
class Locker {
public:
    void setValue(const T& value) {
        element = value;
    }

    T getValue() const {
        return element;
    }

private:
    T element{};
};
```

`template <typename T>` introduces a **type parameter** named `T`. Inside the class, `T` stands for whatever type the user chooses:

```cpp
Locker<std::string> stringLocker;
stringLocker.setValue(":)");
std::println("{}", stringLocker.getValue());

Locker<int> intLocker;
intLocker.setValue(5);
std::println("{}", intLocker.getValue());
```

When the compiler sees `Locker<int>`, it **instantiates** the template: it generates a class in which every `T` is replaced by `int`, and compiles that. This has consequences:

- Templates cost nothing at run time: `Locker<int>` is as efficient as a hand-written `IntLocker`.
- The whole template must be visible where it is used, so templates are written **entirely in headers**.
- Errors in templates show up when they are instantiated, and the error messages can be long. Read them from the top, and look for the line in *your* code.

The type `T` must support everything the template does with it. `Locker` copies and default-constructs `T` (`T element{}`), so a `Locker<Book>` works only if `Book` can be copied and has a default constructor.

A template can have several type parameters, like `std::unordered_map<K, V>`:

```cpp
template <typename K, typename V>
class Pair {
public:
    Pair(const K& key, const V& value) : key(key), value(value) {}
    K getKey() const { return key; }
    V getValue() const { return value; }

private:
    K key;
    V value;
};
```

Thanks to **class template argument deduction**, you can often leave out the type arguments when constructing an object: `Pair p(std::string("ada"), 36);` deduces `Pair<std::string, int>`.

### Function templates

Functions can be templates too:

```cpp
template <typename T>
T largest(const T& a, const T& b) {
    return (a < b) ? b : a;
}

std::println("{}", largest(3, 7));                                   // 7
std::println("{}", largest(std::string("apple"), std::string("pear")));  // pear
```

The type `T` is deduced from the arguments. As Chapter 9 showed, an `auto` parameter is shorthand for a function template: `auto largest(const auto& a, const auto& b)`.

### Constraining type parameters with concepts

What happens if you call `largest` with a type that has no `<`? You get an error deep inside the template. C++20 **concepts** let a template state its requirements up front:

```cpp
#include <concepts>

template <std::totally_ordered T>
T largest(const T& a, const T& b) {
    return (a < b) ? b : a;
}
```

Now `largest` accepts only types that support `<`, `>`, `<=`, `>=`, `==` and `!=`, and calling it with something else produces a short, clear error. The standard library defines many concepts — `std::integral`, `std::floating_point`, `std::copyable`, `std::equality_comparable`, … — and you can define your own. Concepts are optional, but they make template code easier to use.

### Exercise 12.1: Hideout

*Template: `exercises/part12/12_01_Hideout`*

Implement a class template `Hideout<T>` that can hide one object at a time:

- `void putIntoHideout(const T& toHide)` — hides the object; an object already in the hideout disappears,
- `std::optional<T> takeFromHideout()` — takes the object out and returns it; returns an empty optional if the hideout is empty,
- `bool isInHideout() const`.

```cpp
Hideout<std::string> den;
std::println("{}", den.isInHideout());
den.putIntoHideout("peekaboo");
std::println("{}", den.isInHideout());
std::println("{}", den.takeFromHideout().value_or("-"));
std::println("{}", den.isInHideout());
den.putIntoHideout("toodaloo");
den.putIntoHideout("heelloo");
std::println("{}", den.isInHideout());
std::println("{}", den.takeFromHideout().value_or("-"));
std::println("{}", den.isInHideout());
```

```
false
true
peekaboo
false
true
heelloo
false
```

(Storing the hidden object as a `std::optional<T>` member makes the implementation short.)

### Exercise 12.2: Pipe

*Template: `exercises/part12/12_02_Pipe`*

Implement a class template `Pipe<T>`. Values go in at one end and come out at the other, oldest first:

- `void putIntoPipe(const T& value)`,
- `std::optional<T> takeFromPipe()` — removes and returns the value that has been in the pipe the longest, or an empty optional,
- `bool isInPipe() const`.

```cpp
Pipe<int> numberPipe;
numberPipe.putIntoPipe(1);
numberPipe.putIntoPipe(2);
numberPipe.putIntoPipe(3);

int sum = 0;
while (numberPipe.isInPipe()) {
    sum += *numberPipe.takeFromPipe();
}
std::println("{}", sum);                                        // 6
std::println("{}", numberPipe.takeFromPipe().has_value());     // false
```

Use a `std::vector<T>` inside. (The standard library has a ready-made container for exactly this, `std::deque`, and an adaptor `std::queue`. A data structure that takes out the oldest value first is called a *queue*, or *FIFO* — first in, first out.)

## 12.2 How vectors and hash maps work

Let's build simplified versions of `std::vector` and `std::unordered_map` to understand what they do and why they are fast.

### A brief recap of arrays

A `std::array<T, N>` is a block of `N` elements placed next to each other in memory. Accessing element `i` is a single, constant-time operation: the computer computes the address `start + i × sizeof(T)` and reads it. But the size is fixed when the program is compiled.

### Exercise 12.3: Sum These for Me

*Template: `exercises/part12/12_03_SumTheseForMe`*

Implement `int sum(std::span<const int> numbers, int fromWhere, int toWhere, int smallest, int largest)`. It returns the sum of the elements between the indices `fromWhere` and `toWhere` (inclusive) whose values are between `smallest` and `largest` (inclusive). If `fromWhere` is negative, use 0 instead; if `toWhere` is past the end, use the last index instead.

```cpp
std::array<int, 4> numbers = {3, -1, 8, 4};
std::println("{}", sum(numbers, 0, 0, 0, 0));       // 0
std::println("{}", sum(numbers, 0, 0, 0, 10));      // 3
std::println("{}", sum(numbers, 0, 1, 0, 10));      // 3
std::println("{}", sum(numbers, 0, 1, -10, 10));    // 2
std::println("{}", sum(numbers, -1, 999, -10, 10)); // 14
```

### Dynamic memory

A list that can grow needs memory whose size is decided while the program runs. Such memory comes from the **heap** (also called the *free store*). In modern C++ we let a `std::unique_ptr` own it:

```cpp
std::unique_ptr<int[]> numbers = std::make_unique<int[]>(10);   // ten ints, all zero
numbers[3] = 42;
```

`std::unique_ptr<T[]>` owns a dynamically allocated array and frees it automatically. Unlike a vector, it does not know its own size and cannot grow — we have to do that ourselves.

### Building a list

Our `List<T>` keeps an array with room for `capacity` values, of which the first `count` are in use:

```cpp
template <typename T>
class List {
public:
    List() : values(std::make_unique<T[]>(10)), capacity(10) {
    }

    void add(const T& value) {
        if (count == capacity) {
            grow();
        }
        values[count] = value;
        count++;
    }

    T value(std::size_t index) const {
        if (index >= count) {
            throw std::out_of_range("Index out of bounds");
        }
        return values[index];
    }

    std::size_t size() const {
        return count;
    }

private:
    void grow() {
        std::size_t newCapacity = capacity + capacity / 2;
        auto newValues = std::make_unique<T[]>(newCapacity);
        for (std::size_t i = 0; i < count; i++) {
            newValues[i] = std::move(values[i]);
        }
        values = std::move(newValues);   // the old array is freed here
        capacity = newCapacity;
    }

    std::unique_ptr<T[]> values;
    std::size_t capacity;
    std::size_t count = 0;
};
```

When the array is full, `grow` allocates a new array 1.5 times as large, **moves** the old values over (`std::move` lets the elements hand over their contents instead of being copied — cheap for strings and other objects that own memory), and replaces the old array. Assigning to `values` frees the old array automatically.

Growing is expensive — every element is moved — but it happens rarely: after growing from 10 to 15, the next 5 additions are free; after growing to 22, the next 7 are free, and so on. On average, adding is a constant-time operation. `std::vector` works the same way (its growth factor is 1.5 or 2, depending on the library), and `reserve(n)` lets you allocate enough capacity in advance.

Checking whether a value exists means looking at every element in turn — a linear search:

```cpp
bool contains(const T& value) const {
    return indexOfValue(value) >= 0;
}

int indexOfValue(const T& value) const {
    for (std::size_t i = 0; i < count; i++) {
        if (values[i] == value) {
            return static_cast<int>(i);
        }
    }
    return -1;
}
```

Removing a value shifts every following element one step to the left:

```cpp
void remove(const T& value) {
    int index = indexOfValue(value);
    if (index < 0) {
        return;
    }
    for (std::size_t i = index; i + 1 < count; i++) {
        values[i] = std::move(values[i + 1]);
    }
    count--;
}
```

Both are *O(n)* operations: there is no way to search an unsorted list faster than looking at the elements one by one. (`std::vector` offers this search through the separate algorithms `std::ranges::find` and `std::ranges::contains`.)

> **Copying our List.** Because `List` contains a `std::unique_ptr`, which cannot be copied, `List` cannot be copied either — the compiler stops you. Making it copyable would require writing a *copy constructor* and *copy assignment operator* that allocate a new array and copy the elements. This is one of the details that `std::vector` handles for you.

### Exercise 12.4: List (2 parts)

*Template: `exercises/part12/12_04_List`*

**Part 1.** Implement the class template `List<T>` described above, with `add`, `value`, `size` and the growth logic.

**Part 2.** Add `contains`, `indexOfValue` and `remove`.

Test your list with values of type `int` and `std::string`, and with enough values to make it grow several times.

### Hash maps

Searching a list is slow because we might have to look at every element. A **hash table** avoids that. Its idea:

1. Keep an array of **buckets**. Each bucket is a small list of key–value pairs.
2. To find the bucket for a key, compute the key's **hash value** — an integer computed from the key — and take it modulo the number of buckets: `bucket = hash(key) % buckets.size()`.
3. Search only that one bucket.

If the hash function spreads the keys evenly and there are about as many buckets as pairs, each bucket holds only one or two pairs, and every operation takes constant time on average.

```cpp
template <typename K, typename V>
class HashMap {
public:
    HashMap() : buckets(32) {
    }

    std::optional<V> get(const K& key) const {
        const auto& bucket = buckets[indexOf(key)];
        for (const auto& [storedKey, value] : bucket) {
            if (storedKey == key) {
                return value;
            }
        }
        return std::nullopt;
    }

    void add(const K& key, const V& value) {
        auto& bucket = buckets[indexOf(key)];
        for (auto& [storedKey, storedValue] : bucket) {
            if (storedKey == key) {
                storedValue = value;   // replace the old value
                return;
            }
        }
        bucket.emplace_back(key, value);
        count++;
        if (count > 0.75 * buckets.size()) {
            grow();
        }
    }

private:
    std::size_t indexOf(const K& key) const {
        return std::hash<K>{}(key) % buckets.size();
    }

    void grow();   // see the exercise

    std::vector<std::vector<std::pair<K, V>>> buckets;
    std::size_t count = 0;
};
```

When the table gets too full (here, more than 0.75 pairs per bucket on average), it **grows**: it creates twice as many buckets and moves every pair into its new bucket — the bucket index depends on the number of buckets, so every pair must be re-placed. Like vector growth, this is expensive but rare.

`std::hash<K>` is the same hash function object you specialised for your own types in Chapter 8. `std::unordered_map` is built on exactly these ideas.

### Exercise 12.5: Hash Map (3 parts)

*Template: `exercises/part12/12_05_HashMap`*

**Part 1: Getting and adding.** Implement `HashMap<K, V>` with `get` and `add` as above, using `std::vector` for the buckets.

**Part 2: Growing.** Implement `grow`: double the number of buckets and move every pair into its new bucket.

**Part 3: Removing.** Add `std::optional<V> remove(const K& key)`, which removes the pair and returns its value (or an empty optional if the key is not there).

### On search performance

| Operation | `std::vector` (unsorted) | sorted vector + binary search | `std::unordered_map` |
|---|---|---|---|
| add | *O(1)* amortised | *O(n)* (keep sorted) | *O(1)* average |
| find | *O(n)* | *O(log n)* | *O(1)* average |
| remove | *O(n)* | *O(n)* | *O(1)* average |

For small collections — a few dozen elements — a plain vector is often fastest in practice, because its elements sit next to each other in memory, which modern processors love. Measure before you optimise.

## 12.3 Randomness

Games, simulations, tests and security all need random numbers. C++'s `<random>` header separates two concerns:

- An **engine** produces a stream of raw pseudo-random bits. `std::mt19937` (the *Mersenne Twister*) is a good general-purpose engine.
- A **distribution** turns those bits into numbers of the desired kind: `std::uniform_int_distribution<int>(a, b)` gives integers from `a` to `b` inclusive, `std::uniform_real_distribution<double>(a, b)` gives doubles in `[a, b)`, `std::normal_distribution<double>(mean, deviation)` gives normally distributed values, and `std::bernoulli_distribution(p)` gives `true` with probability `p`.

```cpp
#include <random>

std::random_device seedSource;
std::mt19937 engine(seedSource());

std::uniform_int_distribution<int> die(1, 6);
for (int i = 0; i < 5; i++) {
    std::println("{}", die(engine));
}

std::normal_distribution<double> heights(175.0, 7.0);
std::println("A random height: {:.1f}", heights(engine));
```

### Pseudo-random numbers and seeds

The numbers from an engine are not truly random: they are computed by a deterministic formula from a starting value, the **seed**. The same seed always produces the same sequence. `std::random_device` asks the system for an unpredictable seed. (On all mainstream platforms it is backed by the operating system's random source, although the C++ standard does not strictly require that.)

Determinism is often useful: give the engine a fixed seed — `std::mt19937 engine(42);` — and a simulation or a test produces the same "random" results every run, which makes bugs reproducible.

Create the engine **once** (for example, as a member variable) and reuse it. Creating a new engine for every number is slow and, with a fixed seed, would produce the same number every time.

> **Security.** Pseudo-random engines like `std::mt19937` are predictable to anyone who sees enough of their output. Never use them for passwords, keys or tokens; use your operating system's cryptographic random number facilities instead.

Shuffling and picking random elements are common enough to have their own algorithms:

```cpp
std::vector<int> cards = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
std::ranges::shuffle(cards, engine);

std::vector<int> hand;
std::ranges::sample(cards, std::back_inserter(hand), 3, engine);   // pick 3 at random
```

### Exercise 12.6: Numbers

*Template: `exercises/part12/12_06_Numbers`*

Ask how many random numbers to print, then print that many random integers from 0 to 10.

```
How many random numbers should be printed?
> 4
9
1
4
3
```

### Exercise 12.7: Die

*Template: `exercises/part12/12_07_Die`*

The template contains a class `Die` with an engine member. Complete the constructor `Die(int numberOfFaces)` and `int throwDie()`, which returns a random number from 1 to the number of faces.

### Exercise 12.8: Lottery

*Template: `exercises/part12/12_08_Lottery`*

Complete the class `LotteryRow`, which draws seven different numbers from 1 to 40:

- the constructor draws a new row,
- `const std::vector<int>& numbers() const` returns the drawn numbers,
- `bool containsNumber(int number) const` tells whether the number is in the row,
- `void randomizeNumbers()` draws a new row. Draw numbers one at a time, and use `containsNumber` to reject duplicates.

```
Lottery numbers:
3 5 10 14 15 27 37
```

Then think of another solution: shuffle the numbers 1–40 (`std::views::iota(1, 41) | std::ranges::to<std::vector>()`) and take the first seven.

## 12.4 Multidimensional data

Many kinds of data are naturally two-dimensional: a chessboard, an image, a spreadsheet, a game map. The simplest representation in C++ is a vector of vectors:

```cpp
int rows = 2;
int columns = 3;
std::vector<std::vector<int>> matrix(rows, std::vector<int>(columns, 0));

matrix[0][1] = 5;
matrix[1][0] = 3;
matrix[1][2] = 7;

for (const auto& row : matrix) {
    for (int value : row) {
        std::print("{} ", value);
    }
    std::println("");
}
```

```
0 5 0
3 0 7
```

`matrix[y][x]` reads "row `y`, column `x`". The constructor `std::vector<std::vector<int>>(rows, std::vector<int>(columns, 0))` creates `rows` copies of a row of `columns` zeros.

When the size is fixed at compile time, nested `std::array`s work too: `std::array<std::array<int, 3>, 2> matrix{};`.

A vector of vectors allows rows of different lengths, and each row is a separate allocation. For large grids it is often better to store all values in **one** vector and compute the index yourself:

```cpp
class Grid {
public:
    Grid(int width, int height) : width(width), height(height), cells(width * height) {}

    int& at(int x, int y) { return cells[y * width + x]; }
    int at(int x, int y) const { return cells[y * width + x]; }

private:
    int width;
    int height;
    std::vector<int> cells;
};
```

(C++23's `std::mdspan` provides exactly this kind of multidimensional view over a flat array, but library support is still arriving.)

### Exercise 12.9: Array as a String

*Template: `exercises/part12/12_09_ArrayAsAString`*

Implement `std::string arrayAsString(const std::vector<std::vector<int>>& array)`, which returns the grid as text: each row on its own line, with the numbers written next to each other without separators.

```cpp
std::vector<std::vector<int>> matrix = {
    {3, 2, 7, 6},
    {2, 4, 1, 0},
    {3, 2, 1, 0},
};
std::println("{}", arrayAsString(matrix));
```

```
3276
2410
3210
```

### Exercise 12.10: Magic Square (4 parts)

*Template: `exercises/part12/12_10_MagicSquare`*

A **magic square** is a square grid of numbers in which every row, every column and both diagonals have the same sum. For example:

```
8 1 6
3 5 7
4 9 2
```

The template contains a class `MagicSquare` with a grid and an `isMagicSquare` function that uses the functions you will write.

**Part 1: Sums of rows.** Implement `std::vector<int> sumsOfRows() const`. For the square above it returns `[15, 15, 15]`.

**Part 2: Sums of columns.** Implement `std::vector<int> sumsOfColumns() const`.

**Part 3: Sums of diagonals.** Implement `std::vector<int> sumsOfDiagonals() const`, returning the sums of the two diagonals (top-left to bottom-right first).

**Part 4: Creating a magic square.** The template also contains a class `MagicSquareFactory` with a function `MagicSquare createMagicSquare(int size) const`. Implement it using the *Siamese method*, which works for odd sizes:

1. Place `1` in the middle of the top row.
2. Move one step up and one step right, wrapping around the edges, and place the next number there.
3. If that cell is already taken, move one step **down** from the previous number instead.
4. Repeat until the square is full.

```cpp
MagicSquareFactory factory;
std::println("{}", factory.createMagicSquare(3).toString());
```

```
8 1 6
3 5 7
4 9 2
```

## 12.5 Summary

- **Templates** let you write classes and functions once, for any type: `template <typename T>`. The compiler instantiates them for each type used, so they live in headers and have no run-time cost.
- **Concepts** (`template <std::totally_ordered T>`) state what a template requires of its types.
- A growable list keeps an array on the heap (`std::unique_ptr<T[]>`), grows it geometrically and moves the elements over. Adding is amortised constant time; searching and removing are linear.
- A hash table distributes key–value pairs into buckets by hash value. With a good hash function and enough buckets, lookups, insertions and removals take constant time on average.
- `<random>` provides engines (`std::mt19937`) and distributions (`uniform_int_distribution` and others). Seed with `std::random_device` for unpredictability, or with a fixed number for reproducibility.
- Two-dimensional data can be stored as a vector of vectors, nested arrays, or a single vector indexed with `y * width + x`.
