# Chapter 9: Inheritance and Polymorphism

Classes can build on other classes. In this chapter you will learn **inheritance**, which lets a class reuse and extend another class; **virtual functions**, which let a program decide at run time which version of a function to call; and **abstract classes**, which describe what objects can do without saying how. Together these give us **polymorphism**: code that works with many different types of objects through a common interface. Along the way you will meet `std::unique_ptr`, the standard way to own objects whose exact type is known only at run time.

## 9.1 Class inheritance

Suppose a university system has a class `Person` with a name and an address. Students and teachers are persons too, but they have extra data: a student has study credits, a teacher has a salary. Instead of copying `Person`'s code into two new classes, we can **derive** them from `Person`.

```cpp
class Person {
public:
    Person(const std::string& name, const std::string& address)
        : name(name), address(address) {
    }

    std::string getName() const { return name; }
    std::string getAddress() const { return address; }

private:
    std::string name;
    std::string address;
};

class Student : public Person {
public:
    Student(const std::string& name, const std::string& address)
        : Person(name, address) {
    }

    void study() { credits++; }
    int getCredits() const { return credits; }

private:
    int credits = 0;
};
```

`class Student : public Person` says that `Student` **inherits** from `Person`. `Person` is the **base class** (or *superclass*), `Student` the **derived class** (or *subclass*). A `Student` object contains everything a `Person` contains, plus its own members, and it has all of `Person`'s public member functions:

```cpp
Student ollie("Ollie", "6381 Hollywood Blvd. Los Angeles 90028");
std::println("{}", ollie.getName());   // inherited from Person
ollie.study();                          // Student's own member function
```

Use the keyword `public` in `: public Person`. (Without it, inheritance from a `class` is *private*, which hides the base class's interface — rarely what you want.)

### Exercise 9.1: ABC (2 parts)

*Template: `exercises/part09/09_01_ABC`*

**Part 1: Creating classes.** Create three classes without member variables or constructors: `A` with the member function `void a() const` that prints `A`, `B` with `void b() const` printing `B`, and `C` with `void c() const` printing `C`.

**Part 2: Inheritance.** Make `B` inherit from `A` and `C` inherit from `B`. Then:

```cpp
C c;
c.a();
c.b();
c.c();
```

```
A
B
C
```

### Access specifiers: `private`, `protected` and `public`

A derived class **cannot** access its base class's `private` members, even though its objects contain them. `Student` cannot write `name = "x";` — it must go through `Person`'s public interface.

A third access level, `protected`, makes members visible to derived classes but not to other code:

| Specifier | Accessible from |
|---|---|
| `public` | everywhere |
| `protected` | the class itself and classes derived from it |
| `private` | the class itself only |

Prefer `private` with public or protected member functions. Protected data couples derived classes tightly to the base class's internals.

### Calling the base class constructor

A derived class's constructor must make sure the base part is initialised. It does that by calling a base class constructor first in its initialiser list: `: Person(name, address)`. If it does not, the base class's default constructor is used — and `Person` has none, so the code would not compile.

Construction always happens from the base towards the derived class: first the `Person` part is constructed, then `Student`'s own members. Destruction happens in the reverse order.

### Calling a base class member function

A derived class can **override** a member function — provide its own version — and still call the base version by qualifying it with the base class name:

```cpp
std::string Student::toString() const {
    return Person::toString() + "\n  Study credits " + std::to_string(credits);
}
```

### Exercise 9.2: Person and Subclasses (5 parts)

*Template: `exercises/part09/09_02_PersonAndSubclasses`*

**Part 1: Person.** Create a class `Person` with a name and an address, and a `toString` that returns the name and, on the next line indented by two spaces, the address:

```cpp
Person ada("Ada Lovelace", "24 Maddox St. London W1S 2QN");
std::println("{}", ada.toString());
```

```
Ada Lovelace
  24 Maddox St. London W1S 2QN
```

**Part 2: Student.** Create a class `Student` deriving from `Person`. A student starts with 0 study credits; `void study()` adds one, and `int credits() const` returns them.

**Part 3: Student's toString.** Give `Student` its own `toString` that adds the credits:

```
Ollie
  6381 Hollywood Blvd. Los Angeles 90028
  Study credits 1
```

**Part 4: Teacher.** Create a class `Teacher` deriving from `Person`, with a salary given to the constructor, and a `toString`:

```
Ada Lovelace
  24 Maddox St. London W1S 2QN
  salary 1200 euro/month
```

**Part 5: Listing all persons.** Write a function `void printPersons(const std::vector<std::unique_ptr<Person>>& persons)` that prints every person with `toString`. Each person must be printed with the `toString` of their *actual* class — so a student's credits and a teacher's salary appear. You will need what the next sections explain: `virtual` functions and `std::unique_ptr`.

### The actual type of an object decides which function runs

A derived class object can be used wherever a base class object is expected, through a **reference** or a **pointer** to the base:

```cpp
Student ollie("Ollie", "...");
Person& asPerson = ollie;   // fine: a Student is a Person
```

But which `toString` does `asPerson.toString()` call — `Person`'s or `Student`'s? By default, C++ decides at *compile time* from the type of the reference: it calls `Person::toString`. To make C++ decide at *run time* from the actual type of the object, the base class must declare the function **virtual**:

```cpp
class Person {
public:
    // ...
    virtual ~Person() = default;

    virtual std::string toString() const {
        return name + "\n  " + address;
    }
    // ...
};

class Student : public Person {
public:
    // ...
    std::string toString() const override {
        return Person::toString() + "\n  Study credits " + std::to_string(credits);
    }
    // ...
};
```

Now `asPerson.toString()` calls `Student::toString`. This run-time choice is called **dynamic dispatch**, and the ability of one piece of code to work with objects of many types this way is **polymorphism** ("many forms").

Three rules go with it:

- Write **`override`** after a function that overrides a virtual function. The compiler then checks that there really is a matching virtual function in the base class. Without it, a small typo (say, forgetting `const`) silently creates a new, unrelated function.
- A class with virtual functions should have a **virtual destructor**: `virtual ~Person() = default;`. Otherwise destroying a derived object through a base pointer is undefined behaviour.
- Polymorphism works only through **references and pointers**, never through plain values. See below.

> **Coming from Java?** In Java every method is virtual. In C++ you choose: non-virtual functions are slightly faster and cannot be overridden by accident; virtual functions enable polymorphism.

### The slicing problem

What happens if we store a `Student` in a plain `Person` variable?

```cpp
Student ollie("Ollie", "...");
ollie.study();
Person p = ollie;            // copies only the Person part!
std::println("{}", p.toString());   // no study credits
```

`p` is a `Person` object, so only the `Person` part of `ollie` is copied into it — the student part is "sliced off". The same happens with `std::vector<Person>`: pushing a `Student` into it stores only a `Person`.

To keep objects of different derived types in one container, store **pointers** to them. The modern way is `std::unique_ptr`.

### Owning objects through `std::unique_ptr`

`std::unique_ptr<T>` (header `<memory>`) is a **smart pointer** that *owns* an object created on the heap. When the `unique_ptr` is destroyed, it destroys the object automatically. Objects are created with `std::make_unique`:

```cpp
#include <memory>

std::vector<std::unique_ptr<Person>> persons;
persons.push_back(std::make_unique<Person>("Ada Lovelace", "24 Maddox St."));
persons.push_back(std::make_unique<Student>("Ollie", "6381 Hollywood Blvd."));
persons.push_back(std::make_unique<Teacher>("Esko Ukkonen", "Mannerheimintie 15", 5400));

for (const auto& person : persons) {
    std::println("{}", person->toString());   // each object's own toString
}
```

`std::make_unique<Student>(...)` creates a `Student` and returns a `std::unique_ptr<Student>`, which converts automatically to `std::unique_ptr<Person>`. The arrow `->` calls a member function through the pointer.

A `unique_ptr` is **unique**: it cannot be copied (that would create two owners). It can be **moved**, which transfers ownership:

```cpp
auto p = std::make_unique<Student>("Ollie", "...");
persons.push_back(std::move(p));   // p is now empty; the vector owns the student
```

When `persons` is destroyed, every `unique_ptr` in it is destroyed, and each destroys its object — calling the right destructor thanks to the virtual destructor in `Person`. No manual cleanup, no leaks.

> **Never use `new` and `delete` directly** in modern C++ code. `std::make_unique` (and, for shared ownership, `std::make_shared`) do the job safely.

If you just need to *refer to* an existing object polymorphically, without owning it, a reference (`Person&`) or a raw pointer (`Person*`) is fine — as long as the object outlives the reference.

### When is inheritance worth using?

Inheritance expresses an **"is-a"** relationship: a student *is a* person; a teacher *is a* person. If you cannot honestly say "every X is a Y", do not make X inherit from Y.

#### An example of misusing inheritance

Consider a class `Customer` with a name and an address, and a class `Order` with a product, a quantity and — because an order is delivered to a customer — also a name and an address. It is tempting to write `class Order : public Customer` to reuse the name and address. But an order is not a customer! The design falls apart as soon as one customer places two orders: their address would be stored twice, and changing it in one place would not change it in the other.

The right design uses **composition**: an order *has* a customer (or refers to one):

```cpp
class Order {
public:
    Order(const Customer& customer, const std::string& product, int count);
    // ...
private:
    Customer customer;   // or an identifier that refers to a customer
    std::string product;
    int count;
};
```

A good rule of thumb: **prefer composition to inheritance**. Use inheritance when you need polymorphism over an "is-a" hierarchy.

### Exercise 9.3: Warehousing (7 parts)

*Template: `exercises/part09/09_03_Warehousing`*

The template contains a class `Warehouse` that tracks an amount of some product:

- `Warehouse(double capacity)` — an empty warehouse with the given capacity (a non-positive capacity becomes 0),
- `double getBalance() const`, `double getCapacity() const`, `double howMuchSpaceLeft() const`,
- `void addToWarehouse(double amount)` — adds as much as fits; negative amounts are ignored,
- `double takeFromWarehouse(double amount)` — takes as much as there is and returns the amount taken,
- `std::string toString() const` — e.g. `balance = 64.5, space left 123.5` (both with one decimal, since `1000 - 988.7` is not exactly `11.3` in floating point).

Make `toString`, `addToWarehouse` and `takeFromWarehouse` virtual, and give the class a virtual destructor.

**Part 1: Product warehouse, step 1.** Create `ProductWarehouse` deriving from `Warehouse`, with the constructor `ProductWarehouse(const std::string& productName, double capacity)` and `std::string getName() const`.

```cpp
ProductWarehouse juice("Juice", 1000.0);
juice.addToWarehouse(1000.0);
juice.takeFromWarehouse(11.3);
std::println("{}", juice.getName());
std::println("{}", juice.toString());
```

```
Juice
balance = 988.7, space left 11.3
```

**Part 2: Product warehouse, step 2.** Add `void setName(const std::string& newName)` and override `toString` so that it returns e.g. `Juice: balance = 64.5, space left 123.5`. Use the base class's `toString`.

**Part 3: Change history, step 1.** Create a class `ChangeHistory` that remembers a series of `double` values, with `void add(double status)`, `void clear()` and `std::string toString() const` (the format of `std::format("{}", vector)` is fine, e.g. `[1000, 988.7]`).

**Part 4: Change history, step 2.** Add `double maxValue() const`, `double minValue() const` and `double average() const`. Each returns 0 for an empty history.

**Part 5: Product warehouse with history, step 1.** Create `ProductWarehouseWithHistory` deriving from `ProductWarehouse`, with the constructor `ProductWarehouseWithHistory(const std::string& productName, double capacity, double initialBalance)` and `std::string history() const`, which returns the history as a string. The initial balance is the first entry of the history.

**Part 6: Product warehouse with history, step 2.** Override `addToWarehouse` and `takeFromWarehouse` so that they also record the **new balance** in the history.

```cpp
ProductWarehouseWithHistory juice("Juice", 1000.0, 1000.0);
juice.takeFromWarehouse(11.3);
juice.addToWarehouse(1.0);
std::println("{}", juice.history());   // [1000, 988.7, 989.7]
```

**Part 7: Product warehouse with history, step 3.** Add `void printAnalysis() const`. Print the average with one decimal (`{:.1f}`):

```
Product: Juice
History: [1000, 988.7, 989.7]
Largest amount of product: 1000
Smallest amount of product: 988.7
Average: 992.8
```

### Abstract classes

Sometimes a base class represents a concept too general to have objects of its own. What would a plain "shape" look like, or a plain "box"? Such a class can declare a function without implementing it, by making it **pure virtual** with `= 0`:

```cpp
class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;   // pure virtual: no implementation here
    virtual std::string name() const = 0;

    std::string describe() const {
        return name() + " with area " + std::to_string(area());
    }
};
```

A class with at least one pure virtual function is **abstract**: you cannot create objects of it (`Shape s;` does not compile). It exists to be inherited from. A derived class that implements all the pure virtual functions is **concrete**:

```cpp
class Circle : public Shape {
public:
    Circle(double radius) : radius(radius) {}
    double area() const override { return 3.14159265358979 * radius * radius; }
    std::string name() const override { return "circle"; }

private:
    double radius;
};
```

Note how `describe` in the base class calls `name()` and `area()` — functions that the base class itself does not implement. At run time the derived class's versions run. This pattern, a base class defining the overall algorithm and derived classes filling in the steps, is called the *template method* pattern.

### Exercise 9.4: Different Kinds of Boxes (3 parts)

*Template: `exercises/part09/09_04_DifferentKindsOfBoxes`*

The template contains a class `Item` (a name and a weight) and an abstract class `Box`:

```cpp
class Box {
public:
    virtual ~Box() = default;

    virtual void add(const Item& item) = 0;

    void add(const std::vector<Item>& items) {
        for (const Item& item : items) {
            add(item);
        }
    }

    virtual bool isInBox(const Item& item) const = 0;
};
```

**Part 1: Item equality.** Add `operator==` to `Item` so that two items are equal when their **names** are equal (the weight is ignored). `Item` also has a constructor taking only a name, which sets the weight to 0.

**Part 2: Box with a maximum weight.** Implement `BoxWithMaxWeight`, deriving from `Box`, with the constructor `BoxWithMaxWeight(int capacity)`. An item is added only if the box's total weight stays within the capacity.

```cpp
BoxWithMaxWeight coffeeBox(10);
coffeeBox.add(Item("Saludo", 5));
coffeeBox.add(Item("Pirkka", 5));
coffeeBox.add(Item("Kopi Luwak", 5));

std::println("{}", coffeeBox.isInBox(Item("Saludo")));      // true
std::println("{}", coffeeBox.isInBox(Item("Pirkka")));      // true
std::println("{}", coffeeBox.isInBox(Item("Kopi Luwak")));  // false
```

> **A name-hiding surprise.** If `BoxWithMaxWeight` declares only `add(const Item&)`, the inherited `add(const std::vector<Item>&)` becomes *hidden* in `BoxWithMaxWeight` — C++ looks up a name in the derived class first and stops there. Bring it back with `using Box::add;` in the derived class.

**Part 3: One-item box and misplacing box.** Implement `OneItemBox`, which holds at most one item (the first one added stays), and `MisplacingBox`, which accepts every item but whose `isInBox` always returns `false`.

## 9.2 Interfaces

An **interface** describes *what* an object can do — a set of member functions — without saying anything about *how*. Java and C# have a dedicated `interface` keyword. In C++, an interface is simply an abstract class that has only pure virtual functions (and a virtual destructor):

```cpp
class Readable {
public:
    virtual ~Readable() = default;
    virtual std::string read() const = 0;
};
```

Any class that inherits from `Readable` and implements `read` "implements the interface":

```cpp
class TextMessage : public Readable {
public:
    TextMessage(const std::string& sender, const std::string& content)
        : sender(sender), content(content) {}

    std::string read() const override { return content; }

private:
    std::string sender;
    std::string content;
};

class Ebook : public Readable {
public:
    Ebook(const std::string& name, const std::vector<std::string>& pages)
        : name(name), pages(pages) {}

    std::string read() const override {
        std::string text = pages[currentPage];
        currentPage = (currentPage + 1) % pages.size();
        return text;
    }

private:
    std::string name;
    std::vector<std::string> pages;
    mutable std::size_t currentPage = 0;
};
```

(`mutable` allows a member to change even inside a `const` member function. Use it sparingly — here, reading a book "turns the page" without changing the book's content.)

A class can implement several interfaces by inheriting from several abstract classes: `class Ebook : public Readable, public Searchable { ... };`. C++ supports such **multiple inheritance**; using it only for interfaces keeps it simple.

### Exercise 9.5: Taco Boxes (2 parts)

*Template: `exercises/part09/09_05_TacoBoxes`*

The template contains the interface `TacoBox`:

```cpp
class TacoBox {
public:
    virtual ~TacoBox() = default;
    virtual int tacosRemaining() const = 0;
    virtual void eat() = 0;
};
```

`eat` reduces the number of tacos by one, but never below zero.

**Part 1: Triple taco box.** Implement `TripleTacoBox`, which starts with three tacos.

**Part 2: Custom taco box.** Implement `CustomTacoBox`, whose constructor takes the initial number of tacos.

### An interface as a variable type

Variables can't be of an abstract type, but references and pointers can:

```cpp
TextMessage message("ope", "It's going great!");
Readable& readable = message;
std::println("{}", readable.read());

std::vector<std::unique_ptr<Readable>> inbox;
inbox.push_back(std::make_unique<TextMessage>("ope", "Hi"));
inbox.push_back(std::make_unique<Ebook>("Book", std::vector<std::string>{"page 1", "page 2"}));
for (const auto& item : inbox) {
    std::println("{}", item->read());
}
```

### Interfaces as function parameters

The real power of interfaces shows in function parameters. A function that takes a `const Readable&` works with **every** class that implements `Readable` — including classes written years later:

```cpp
class Printer {
public:
    void print(const Readable& readable) const {
        std::println("{}", readable.read());
    }
};
```

`Printer` does not know or care which concrete type it receives. Code written against interfaces is flexible, reusable and easy to test (a test can pass in a simple fake implementation).

### Exercise 9.6: Interface in a Box (4 parts)

*Template: `exercises/part09/09_06_InterfaceInABox`*

Moving house means packing everything into boxes. All packable things implement this interface:

```cpp
class Packable {
public:
    virtual ~Packable() = default;
    virtual double weight() const = 0;
};
```

**Part 1: Packables.** Create the classes `Book` (author, name, weight) and `CD` (artist, name, publication year; every CD weighs 0.1 kg), both implementing `Packable`, with `toString`:

```
Fyodor Dostoevsky: Crime and Punishment
Pink Floyd: Dark Side of the Moon (1973)
```

**Part 2: Box.** Create a class `Box` with a maximum capacity in kilograms. `void add(std::unique_ptr<Packable> item)` adds the item if the total weight stays within the capacity (otherwise the item is simply discarded). `std::string toString() const` returns e.g. `Box: 6 items, total weight 4 kg`.

```cpp
Box box(10);
box.add(std::make_unique<Book>("Fyodor Dostoevsky", "Crime and Punishment", 2));
box.add(std::make_unique<Book>("Robert Martin", "Clean Code", 1));
box.add(std::make_unique<Book>("Kent Beck", "Test Driven Development", 0.7));
box.add(std::make_unique<CD>("Pink Floyd", "Dark Side of the Moon", 1973));
box.add(std::make_unique<CD>("Wigwam", "Nuclear Nightclub", 1975));
box.add(std::make_unique<CD>("Rendezvous Park", "Closer to Being Here", 2012));
std::println("{}", box.toString());
```

```
Box: 6 items, total weight 4 kg
```

**Part 3: Box weight.** Give `Box` a member function `double weight() const` returning the total weight of its contents.

**Part 4: A box is packable too!** Make `Box` implement `Packable`. Now boxes can be packed into boxes. Try it: what happens when you put a box into a box?

### An interface as a return type

Functions can return interface types too — as a `std::unique_ptr` when they create a new object for the caller to own:

```cpp
std::unique_ptr<Readable> makeGreeting(bool longVersion) {
    if (longVersion) {
        return std::make_unique<Ebook>("Greetings", std::vector<std::string>{"Hello,", "world!"});
    }
    return std::make_unique<TextMessage>("system", "Hi!");
}
```

The caller gets "some `Readable`" and does not need to know which one. Functions like this are called *factories*.

### Containers and generic code

Java's standard library organises its collections into interfaces: `List`, `Map`, `Set`, `Collection`. A Java method can take "any `List`".

The C++ standard library takes a different approach. Its containers do **not** inherit from common base classes. Instead they follow common **conventions**: every container has `size()`, `begin()`, `end()`, and so on. Code that should work with any container is written as a **template** — a function whose parameter type is filled in by the compiler for each use. The simplest way to write one is with an `auto` parameter:

```cpp
std::size_t returnSize(const auto& container) {
    return container.size();
}
```

```cpp
std::vector<std::string> names = {"First", "Second", "Third"};
std::map<std::string, std::string> nicknames = {{"1", "first"}, {"2", "second"}};
std::set<std::string> unique = {"first", "first", "second"};

std::println("{}", returnSize(names));       // 3
std::println("{}", returnSize(nicknames));   // 2
std::println("{}", returnSize(unique));      // 2
```

The compiler generates a separate version of `returnSize` for each container type. This is **compile-time polymorphism**, as opposed to the **run-time polymorphism** of virtual functions. It has no run-time cost, and it works with any type that has a suitable `size()` — but every use must be visible to the compiler, and error messages can be long. Chapter 12 explores templates properly.

### Exercise 9.7: List as a Function Parameter

*Template: `exercises/part09/09_07_ListAsAMethodParameter`*

Write a function `int returnSize(const std::vector<std::string>& names)` that returns the size of the vector. Then generalise it: change the parameter to `const auto&`, and check that it also works with a `std::vector<int>`.

### Exercise 9.8: Map as a Function Parameter

*Template: `exercises/part09/09_08_MapAsAMethodParameter`*

Write a function `returnSize` that returns the size of a `std::map<std::string, std::string>`. Use your generic version from the previous exercise and check that it works with `std::unordered_map` as well.

### Exercise 9.9: Set as a Function Parameter

*Template: `exercises/part09/09_09_SetAsMethodParameter`*

The template creates a `std::set<std::string>` and inserts `first` twice and `second` three times. Print its size with `returnSize` (it is 2: a set stores each value once).

### Exercise 9.10: Online Shop (8 parts)

*Template: `exercises/part09/09_10_OnlineShop`*

Build the components of an online shop.

**Part 1: Warehouse.** Create a class `Warehouse` with `void addProduct(const std::string& product, int price, int stock)` and `int price(const std::string& product) const`, which returns `-99` if the product is unknown. Store the prices in a `std::map<std::string, int>`.

```cpp
Warehouse warehouse;
warehouse.addProduct("milk", 3, 10);
warehouse.addProduct("coffee", 5, 7);
std::println("prices:");
std::println("milk: {}", warehouse.price("milk"));
std::println("coffee: {}", warehouse.price("coffee"));
std::println("sugar: {}", warehouse.price("sugar"));
```

```
prices:
milk: 3
coffee: 5
sugar: -99
```

**Part 2: Stock.** Store the stock in another map and add `int stock(const std::string& product) const` (0 if unknown) and `bool take(const std::string& product)`, which decreases the stock by one and returns `true` if there was stock left, and otherwise returns `false`.

**Part 3: Listing the products.** Add `std::set<std::string> products() const`, returning the names of all products.

**Part 4: Item.** Create a class `Item` (a product in a shopping cart) with the constructor `Item(const std::string& product, int qty, int unitPrice)`, `int price() const` (unit price × quantity), `void increaseQuantity()` and `std::string toString() const`, e.g. `milk: 2`.

**Part 5: Shopping cart.** Create a class `ShoppingCart` with `void add(const std::string& product, int price)`, which adds an `Item` with quantity 1, and `int price() const`, the total.

**Part 6: Printing the cart.** Add `void print() const`, which prints the items.

**Part 7: One item per product.** Change `add` so that adding a product that is already in the cart increases that item's quantity instead of adding a new item. (A `std::map<std::string, Item>` is handy.)

```cpp
ShoppingCart cart;
cart.add("milk", 3);
cart.add("buttermilk", 2);
cart.add("milk", 3);
cart.print();
std::println("cart price: {}", cart.price());
```

```
buttermilk: 1
milk: 2
cart price: 8
```

**Part 8: Store.** The template contains a class `Store` that combines a warehouse, a shopping cart and a text interface. Read it, and use it in `main` to run the shop. Check that buying a product that is out of stock does not add it to the cart.

## 9.3 Object polymorphism

Every object has a type, and through inheritance it may also *be* any of its base types. A `Student` is a `Student`, a `Person`, and — if `Person` implements `Comparable` or `Printable` — those too. Through a reference or pointer of any of these types, the object offers that type's interface, and virtual functions run the object's own implementations.

Some guidelines:

- Through a `Person&`, you can only call `Person`'s member functions — even if the object is actually a `Student`. The *static type* (of the reference) decides what you may call; the *dynamic type* (of the object) decides which override runs.
- Avoid asking "what type is this object really?" in code. If you find yourself writing chains of type checks, a virtual function is almost always the better design. (C++ does have `dynamic_cast` for the rare cases where you must ask.)
- Keep hierarchies shallow. One or two levels of inheritance below an interface is usually plenty.

### A herd example

Polymorphism shines when a container holds objects of different types that share an interface. Here is the setting of the next exercise: anything that can move implements

```cpp
class Movable {
public:
    virtual ~Movable() = default;
    virtual void move(int dx, int dy) = 0;
};
```

An organism moves itself. A *herd* moves by moving all its members — and since a herd is itself `Movable`, herds can contain other herds. This structure, where a container and its contents share an interface, is called the *composite* pattern.

### Exercise 9.11: Herds (2 parts)

*Template: `exercises/part09/09_11_Herds`*

The template contains the interface `Movable`.

**Part 1: Organism.** Create `Organism`, implementing `Movable`, with the constructor `Organism(int x, int y)`, `void move(int dx, int dy)` and `std::string toString() const` returning e.g. `x: 3; y: 6`.

```cpp
Organism organism(20, 30);
std::println("{}", organism.toString());
organism.move(-10, 5);
std::println("{}", organism.toString());
organism.move(50, 20);
std::println("{}", organism.toString());
```

```
x: 20; y: 30
x: 10; y: 35
x: 60; y: 55
```

**Part 2: Herd.** Create `Herd`, implementing `Movable`, which owns its members as `std::vector<std::unique_ptr<Movable>>`. It has `void addToHerd(std::unique_ptr<Movable> movable)`, `void move(int dx, int dy)`, which moves every member, and `std::string toString() const`, which lists the members' positions, one per line. (To print the members, `Movable` needs a `toString` too: add `virtual std::string toString() const = 0;` to the interface.)

```cpp
Herd herd;
herd.addToHerd(std::make_unique<Organism>(57, 66));
herd.addToHerd(std::make_unique<Organism>(73, 56));
herd.addToHerd(std::make_unique<Organism>(46, 52));
herd.addToHerd(std::make_unique<Organism>(19, 107));
std::println("{}", herd.toString());
```

```
x: 57; y: 66
x: 73; y: 56
x: 46; y: 52
x: 19; y: 107
```

### Exercise 9.12: Animals (4 parts)

*Template: `exercises/part09/09_12_Animals`*

**Part 1: Animal.** Create an abstract class `Animal` with a name given to the constructor, `std::string getName() const`, and the member functions `void eat() const` and `void sleep() const`, which print `(name) eats` and `(name) sleeps`. Make it abstract by giving it a protected constructor, or a pure virtual function.

**Part 2: Dog.** Create `Dog`, deriving from `Animal`, with a constructor taking a name, a default constructor that names the dog `Dog`, and `void bark() const`, which prints `(name) barks`.

```cpp
Dog dog;
dog.bark();
dog.eat();
Dog fido("Fido");
fido.bark();
```

```
Dog barks
Dog eats
Fido barks
```

**Part 3: Cat.** Create `Cat` similarly, with the default name `Cat` and `void purr() const` printing `(name) purrs`.

**Part 4: NoiseCapable.** Create the interface `NoiseCapable` with `virtual void makeNoise() const = 0;`. Make `Dog` and `Cat` implement it: a dog's noise is barking and a cat's is purring.

```cpp
std::unique_ptr<NoiseCapable> dog = std::make_unique<Dog>();
dog->makeNoise();

std::unique_ptr<NoiseCapable> cat = std::make_unique<Cat>("Garfield");
cat->makeNoise();
```

```
Dog barks
Garfield purrs
```

## 9.4 Summary

- A derived class inherits the members of its base class: `class Student : public Person`. Its constructor initialises the base part first: `: Person(name, address)`.
- `private` members are hidden even from derived classes; `protected` members are visible to them.
- Mark functions **`virtual`** in the base class to allow dynamic dispatch, write **`override`** in derived classes, and give polymorphic base classes a virtual destructor.
- Polymorphism works through references and pointers. Copying a derived object into a base object **slices** it.
- `std::unique_ptr` owns a heap object and destroys it automatically; create objects with `std::make_unique`. A `std::vector<std::unique_ptr<Base>>` holds objects of different derived types.
- Pure virtual functions (`= 0`) make a class abstract. An abstract class with only pure virtual functions is an interface.
- Prefer composition ("has-a") to inheritance; use inheritance for genuine "is-a" relationships.
- Templates (e.g. `auto` parameters) give compile-time polymorphism; virtual functions give run-time polymorphism.
