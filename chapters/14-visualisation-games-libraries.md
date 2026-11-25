# Chapter 14: Visualisation, Multimedia, a Game, and Libraries

The final chapter puts graphics to work. We draw charts to visualise data, draw shapes, manipulate images and play sounds, and build a complete game step by step. We finish by looking at how C++ projects use third-party libraries, using a database as the example.

All exercises in this chapter are graphical or use downloaded libraries; build them with `-DBUILD_GRAPHICAL_EXERCISES=ON`, as explained in Chapter 13.

## 14.1 Data visualisation

Numbers in a table are hard to read; a chart shows trends at a glance. Charting libraries exist for C++ (for example ImPlot, built on Dear ImGui), but drawing a simple chart yourself is instructive and only takes a little arithmetic.

### From data coordinates to screen coordinates

A chart maps **data coordinates** (years, percentages) to **screen coordinates** (pixels). Suppose the plot occupies the rectangle `plot` on the screen, and shows *x* values from `xMin` to `xMax` and *y* values from `yMin` to `yMax`. Then a data point `(x, y)` lands at:

```cpp
float screenX = plot.x + (x - xMin) / (xMax - xMin) * plot.width;
float screenY = plot.y + plot.height - (y - yMin) / (yMax - yMin) * plot.height;
```

The *y* formula is flipped, because screen *y* grows downwards while chart *y* grows upwards.

The exercise templates of this section include a small header `chart.h` that wraps this arithmetic:

```cpp
struct Chart {
    Rectangle plot;                 // where the plot area is on the screen
    double xMin, xMax, yMin, yMax;  // the visible data range
};

Vector2 toScreen(const Chart& chart, double x, double y);

// Axes with tick marks every xStep / yStep data units, labelled with the numbers.
void drawAxes(const Chart& chart, double xStep, double yStep,
              const std::string& xLabel, const std::string& yLabel);

// A line through the points, in order.
void drawLine(const Chart& chart, const std::vector<std::pair<double, double>>& points, Color color);

// A bar from 0 up to `value`, centred on x, `width` data units wide.
void drawBar(const Chart& chart, double x, double value, double width, Color color);

// A legend: coloured boxes with names, starting at the given screen position.
void drawLegend(Vector2 position, const std::vector<std::pair<std::string, Color>>& entries);
```

### Line charts

A **line chart** shows how a value changes over an ordered dimension, usually time:

```cpp
Chart chart{Rectangle{60, 20, 500, 300}, 2000, 2010, 0, 100};
std::vector<std::pair<double, double>> values = {
    {2000, 20}, {2002, 35}, {2004, 32}, {2006, 60}, {2008, 72}, {2010, 80}};

while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    drawAxes(chart, 2, 20, "Year", "Value");
    drawLine(chart, values, BLUE);
    EndDrawing();
}
```

### Exercise 14.1: Shanghai

*Template: `exercises/part14/14_01_Shanghai`*

The Shanghai ranking compares universities worldwide every year. The University of Helsinki's positions in 2007–2017 were:

```
2007 73
2008 68
2009 72
2010 72
2011 74
2012 73
2013 76
2014 73
2015 67
2016 56
2017 56
```

Draw a line chart of the ranking. Give the window the title `University of Helsinki, Shanghai ranking`, and label the axes `Year` and `Ranking`.

### Exercise 14.2: Finnish Parties

*Template: `exercises/part14/14_02_FinnishParties`*

The file `partiesdata.tsv` contains the relative support (%) of the major Finnish parties in the municipal elections of 1968–2008. The values are separated by tab characters (`'\t'`); the first row contains the years, and each following row a party's abbreviation and its support in each year. Some cells contain `-` when the party did not take part.

```
Party	1968	1972	1976	1980	...
KOK	16.1	18.1	20.9	22.9	...
SDP	23.9	27.1	24.8	25.5	...
```

Read the file and draw a line chart with a separate line, in its own colour, for each party, and a legend that names the parties. Skip the missing values.

### Exercise 14.3: Savings Calculator (3 parts)

*Template: `exercises/part14/14_03_SavingsCalculator`*

Build a calculator that shows how savings grow over 30 years.

**Part 1: The user interface.** At the top, place two sliders with labels: *Monthly savings* from 25 to 250, and *Yearly interest rate* from 0 to 10. Show each slider's current value next to it. Below the sliders, draw an empty chart with years 0–30 on the *x* axis. Use `GuiSlider` from raygui.

**Part 2: Savings without interest.** Draw a line showing the total savings at the end of each year if the user saves the chosen amount every month and earns no interest: after year *n*, the savings are `n × 12 × monthly`. Adjust the *y* range of the chart to the data.

**Part 3: Savings with interest.** Draw a second line for savings with interest. At the end of each year, add the year's savings and then apply the interest: `balance = (balance + 12 × monthly) × (1 + rate / 100)`. Both lines must update immediately when a slider moves.

### Bar charts

A **bar chart** compares values between categories. Bars should normally start from zero: a bar's *length* is what the eye compares.

```cpp
Chart chart{Rectangle{60, 20, 500, 300}, 0, 4, 0, 100};
std::vector<std::pair<std::string, double>> data = {{"A", 40}, {"B", 75}, {"C", 55}};
for (std::size_t i = 0; i < data.size(); i++) {
    drawBar(chart, i + 1, data[i].second, 0.6, DARKBLUE);
}
```

### Exercise 14.4: Unfair Advertisement

*Template: `exercises/part14/14_04_UnfairAdvertisement`*

"There are three kinds of lies: lies, damned lies, and statistics." The template draws a bar chart from an imaginary company's advertisement, comparing the internet speeds of four operators. It makes a tiny difference look enormous by starting the *y* axis at 77 and hiding the axis labels.

Change the program so that the comparison is fair. There is no single right answer; explain your choices in a comment.

### Exercise 14.5: Cycling Statistics

*Template: `exercises/part14/14_05_CyclingStatistics`*

The template shows monthly cycling counts at measuring stations in Helsinki as a line chart. The station is chosen with a dropdown. Change the program to show the data as a bar chart instead.

### Visualising dynamic data

Because the main loop draws a fresh frame many times per second, animated charts come for free: change the data, and the next frame shows the change. For example, a chart of a value that is updated once per second:

```cpp
std::vector<std::pair<double, double>> points;
double elapsed = 0;
double value = 50;
std::mt19937 engine{std::random_device{}()};
std::uniform_real_distribution<double> step(-5, 5);

while (!WindowShouldClose()) {
    elapsed += GetFrameTime();          // seconds since the last frame
    if (elapsed >= 1.0) {
        elapsed = 0;
        value += step(engine);
        points.emplace_back(points.size(), value);
    }
    // ... draw the chart from points ...
}
```

`GetFrameTime()` returns the duration of the previous frame in seconds. Accumulating it lets a program do things at a steady rate regardless of the frame rate.

## 14.2 Multimedia

### Drawing

raylib's drawing functions paint shapes directly onto the frame:

| Function | Draws |
|---|---|
| `DrawPixel(x, y, color)` | one pixel |
| `DrawLine(x1, y1, x2, y2, color)` / `DrawLineEx(start, end, thick, color)` | a line |
| `DrawRectangle(x, y, w, h, color)` / `DrawRectangleLines(...)` | a filled / outlined rectangle |
| `DrawCircle(x, y, radius, color)` / `DrawCircleLines(...)` | a filled / outlined circle |
| `DrawTriangle(v1, v2, v3, color)` | a filled triangle (vertices counter-clockwise) |
| `DrawPoly(center, sides, radius, rotation, color)` | a regular polygon |
| `DrawText(text, x, y, size, color)` | text |

Colours are `Color{r, g, b, a}` structs with components from 0 to 255 (`a` is opacity), and raylib defines many constants: `RED`, `GOLD`, `DARKGREEN`, `SKYBLUE`, `BLACK`, `RAYWHITE`, …

Drawing happens every frame, so a drawing program must remember what to draw. Here is a tiny paint program that remembers the points the user has drawn:

```cpp
std::vector<Vector2> points;
while (!WindowShouldClose()) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        points.push_back(GetMousePosition());
    }
    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (Vector2 point : points) {
        DrawCircleV(point, 4, BLACK);
    }
    EndDrawing();
}
```

### Exercise 14.6: Smiley

*Template: `exercises/part14/14_06_Smiley`*

Draw a smiley face in the window using rectangles: draw it with filled squares, like pixel art. The point is to use the drawing functions, not to draw by hand with the mouse.

### Images

An **image** is a grid of pixels. raylib distinguishes two kinds:

- an `Image` lives in normal memory, where your program can read and change its pixels,
- a `Texture2D` lives in the graphics card's memory, where it can be drawn fast but not easily changed.

A typical program loads an image, optionally processes it, and turns it into a texture for drawing:

```cpp
Image image = LoadImage("monalisa.png");
Texture2D texture = LoadTextureFromImage(image);

while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(texture, 0, 0, WHITE);
    EndDrawing();
}

UnloadTexture(texture);
UnloadImage(image);
```

Because raylib is a C library, its resources must be released by hand with the `Unload…` functions, and the window must still be open when they are released. (A C++ programmer would wrap them in small RAII classes whose destructors call `Unload…`, so that releasing can never be forgotten. Try it!)

To work with individual pixels:

```cpp
Color color = GetImageColor(image, x, y);                  // read a pixel
Image result = GenImageColor(width, height, BLACK);        // a new image of one colour
ImageDrawPixel(&result, x, y, Color{255, 0, 0, 255});      // write a pixel
```

### Exercise 14.7: Collage (3 parts)

*Template: `exercises/part14/14_07_Collage`*

Andy Warhol was famous for collages that repeat one picture in different colours. Let's make a Warhol-style Mona Lisa. The template loads `monalisa.png` (a public-domain image) and shows it. Each part creates a new image of the same size from the original's pixels.

**Part 1: Top-left corner.** Create an image in which a half-size copy of the Mona Lisa sits in the top-left quarter: the pixel at `(x, y)` of the copy is the original's pixel at `(2x, 2y)`.

**Part 2: Grid.** Fill all four quarters with the half-size copy.

**Part 3: Negative.** Turn the colours negative: each colour component `c` becomes `255 − c` (keep the alpha unchanged).

### Sounds

raylib also plays sounds. Audio needs its own initialisation:

```cpp
InitAudioDevice();
Sound sound = LoadSound("Applause-Yannick_Lemieux.wav");

// later, for example when a button is clicked:
PlaySound(sound);

// at the end:
UnloadSound(sound);
CloseAudioDevice();
```

`Sound` is for short effects that are loaded fully into memory. For long music, `Music` streams the file while it plays (`LoadMusicStream`, `PlayMusicStream`, and `UpdateMusicStream` once per frame).

### Exercise 14.8: Hurray

*Template: `exercises/part14/14_08_Hurray`*

The exercise folder contains `Applause-Yannick_Lemieux.wav`, a recording of applause by Yannick Lemieux (licensed under CC BY 3.0). Create a program with a button `Hurray!` that plays the sound when pressed.

## 14.3 A larger application: Asteroids

Let's build a game inspired by *Asteroids*, the 1979 arcade classic: the player steers a small ship among drifting asteroids, shooting them before they collide with the ship. We build it in small steps, running the game after each one.

### The game window and the game loop

A game is a main loop, like any raylib program. Each frame it does three things:

1. **Handle input:** read the keyboard.
2. **Update:** move everything, check collisions, apply the rules.
3. **Draw** the current state.

```cpp
constexpr int WIDTH = 600;
constexpr int HEIGHT = 400;

int main() {
    InitWindow(WIDTH, HEIGHT, "Asteroids!");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // 1. input   2. update
        BeginDrawing();
        ClearBackground(BLACK);
        // 3. draw
        EndDrawing();
    }
    CloseWindow();
}
```

### The ship

The ship is a triangle. We store its **position** (a `Vector2`), the direction it faces as a **rotation** angle in degrees, and its **velocity** — how many pixels it moves per frame along each axis.

raylib's companion header `raymath.h` provides vector arithmetic: `Vector2Add`, `Vector2Scale`, `Vector2Rotate`, `Vector2Distance`, and also the operators `+`, `-` and `*` for `Vector2` when used from C++.

```cpp
#include "raymath.h"

class Ship {
public:
    Ship(Vector2 position) : position(position) {}

    void turnLeft()  { rotation -= 5; }
    void turnRight() { rotation += 5; }

    void draw() const {
        // the triangle's corners relative to the centre, pointing right (rotation 0)
        Vector2 nose  = Vector2Rotate(Vector2{15, 0},  rotation * DEG2RAD);
        Vector2 left  = Vector2Rotate(Vector2{-10, -8}, rotation * DEG2RAD);
        Vector2 right = Vector2Rotate(Vector2{-10, 8},  rotation * DEG2RAD);
        DrawTriangleLines(position + nose, position + left, position + right, RAYWHITE);
    }

private:
    Vector2 position;
    Vector2 velocity{0, 0};
    float rotation = 0;   // degrees
};
```

`Vector2Rotate` rotates a vector by an angle in **radians**; multiplying by `DEG2RAD` converts degrees to radians.

### Turning the ship: keyboard input

Input is read once per frame. `IsKeyDown` is true for as long as a key is held, which gives smooth, continuous turning:

```cpp
if (IsKeyDown(KEY_LEFT))  ship.turnLeft();
if (IsKeyDown(KEY_RIGHT)) ship.turnRight();
```

(`IsKeyPressed`, by contrast, is true only in the frame when the key goes down. It suits actions that should happen once per key press — such as firing.)

### Moving the ship

To move, the ship adds its velocity to its position every frame. Pressing *up* **accelerates** the ship in the direction it faces:

```cpp
void accelerate() {
    Vector2 direction = Vector2Rotate(Vector2{1, 0}, rotation * DEG2RAD);
    velocity = velocity + direction * 0.05f;
}

void move() {
    position = position + velocity;
}
```

Because velocity is kept between frames, the ship drifts on after the key is released, as in space. Each frame: `if (IsKeyDown(KEY_UP)) ship.accelerate(); ship.move();`

### Refactoring: a common base class

Asteroids and projectiles also have a position, a velocity, a rotation, a shape and a `move` function. Rather than repeating that code, we move it into a base class `Character`, and represent each character's shape as a polygon — a list of corner points relative to its centre:

```cpp
class Character {
public:
    Character(std::vector<Vector2> shape, Vector2 position, float radius)
        : shape(std::move(shape)), position(position), radius(radius) {}
    virtual ~Character() = default;

    void turnLeft()  { rotation -= 5; }
    void turnRight() { rotation += 5; }

    void accelerate(float amount) {
        velocity = velocity + Vector2Rotate(Vector2{1, 0}, rotation * DEG2RAD) * amount;
    }

    void move() {
        position = position + velocity;
        // wrap around the edges of the window
        if (position.x < 0) position.x += WIDTH;
        if (position.x > WIDTH) position.x -= WIDTH;
        if (position.y < 0) position.y += HEIGHT;
        if (position.y > HEIGHT) position.y -= HEIGHT;
    }

    void draw() const {
        for (std::size_t i = 0; i < shape.size(); i++) {
            Vector2 a = Vector2Rotate(shape[i], rotation * DEG2RAD);
            Vector2 b = Vector2Rotate(shape[(i + 1) % shape.size()], rotation * DEG2RAD);
            DrawLineV(position + a, position + b, RAYWHITE);
        }
    }

    bool collides(const Character& other) const {
        return CheckCollisionCircles(position, radius, other.position, other.radius);
    }

    // ... getters and setters for position, velocity and rotation ...

protected:
    std::vector<Vector2> shape;
    Vector2 position;
    Vector2 velocity{0, 0};
    float rotation = 0;
    float radius;
};

class Ship : public Character {
public:
    Ship(Vector2 position)
        : Character({{15, 0}, {-10, -8}, {-10, 8}}, position, 10) {}
};
```

The modulo `% shape.size()` connects the last corner back to the first. The ship now gets moving, wrapping and drawing for free.

### Asteroids

An asteroid is a rough, randomly shaped polygon that drifts and spins slowly. We generate a shape by placing points around a circle at slightly random distances:

```cpp
std::vector<Vector2> asteroidShape(std::mt19937& engine) {
    std::uniform_real_distribution<float> distance(15, 25);
    std::vector<Vector2> points;
    for (int i = 0; i < 10; i++) {
        float angle = i * 36.0f * DEG2RAD;
        points.push_back(Vector2Rotate(Vector2{distance(engine), 0}, angle));
    }
    return points;
}

class Asteroid : public Character {
public:
    Asteroid(Vector2 position, std::mt19937& engine)
        : Character(asteroidShape(engine), position, 20) {
        std::uniform_real_distribution<float> angle(0, 360);
        std::uniform_real_distribution<float> speed(0.5f, 1.5f);
        rotation = angle(engine);
        accelerate(speed(engine));
        spin = std::uniform_real_distribution<float>(-1, 1)(engine);
    }

    void update() {
        rotation += spin;
        move();
    }

private:
    float spin;
};
```

The game keeps its asteroids in a vector: `std::vector<Asteroid> asteroids;` — the asteroids are values, and all of them are the same type, so no pointers are needed.

### Collisions

Precise collision detection between polygons is surprisingly complicated. Games often approximate each object with a simpler shape. We use a **circle** around each character — `CheckCollisionCircles` from raylib tells whether two circles overlap. The approximation is slightly generous, but for a fast game it feels right.

```cpp
for (const Asteroid& asteroid : asteroids) {
    if (asteroid.collides(ship)) {
        gameOver = true;
    }
}
```

When the game is over, stop updating and show a message: `DrawText("Game over!", ...)`.

### Projectiles

Pressing *space* fires a small, fast projectile from the ship's position in the direction it faces:

```cpp
class Projectile : public Character {
public:
    Projectile(Vector2 position, float rotation)
        : Character({{-2, -2}, {2, -2}, {2, 2}, {-2, 2}}, position, 2) {
        this->rotation = rotation;
        accelerate(4);
    }
    // a projectile lives for a limited number of frames
    int age = 0;
};
```

```cpp
if (IsKeyPressed(KEY_SPACE) && projectiles.size() < 3) {
    projectiles.emplace_back(ship.getPosition(), ship.getRotation());
}
```

Limiting the number of projectiles keeps the game from becoming too easy.

Every frame, each projectile that hits an asteroid destroys both. Removing elements while iterating needs care (Chapter 10). A clean way is to **mark** the objects to remove first, and then remove them all with `std::erase_if`:

```cpp
for (Projectile& projectile : projectiles) {
    for (Asteroid& asteroid : asteroids) {
        if (projectile.collides(asteroid)) {
            projectile.setAlive(false);
            asteroid.setAlive(false);
        }
    }
}
std::erase_if(projectiles, [](const Projectile& p) { return !p.isAlive() || p.age > 120; });
std::erase_if(asteroids, [](const Asteroid& a) { return !a.isAlive(); });
```

(Add an `alive` flag with `isAlive()` and `setAlive()` to `Character`.)

### Points and new asteroids

Each destroyed asteroid is worth 1000 points; keep a counter and draw it in a corner with `DrawText(std::format("Points: {}", points).c_str(), 10, 10, 20, RAYWHITE)`.

To keep the game going, add new asteroids now and then — for example, with a probability of 0.5 % each frame — but never right on top of the ship:

```cpp
std::bernoulli_distribution newAsteroid(0.005);
if (newAsteroid(engine)) {
    Asteroid asteroid(Vector2{0, 0}, engine);   // the top-left corner, far from the ship's start
    if (!asteroid.collides(ship)) {
        asteroids.push_back(asteroid);
    }
}
```

That is a complete game: steer, shoot, score, and avoid the rocks. From here you can add sounds, a high-score file, lives, levels, or larger asteroids that split into smaller ones.

### Exercise 14.9: Asteroids (4 parts)

*Template: `exercises/part14/14_09_Asteroids`*

The template contains an empty game window. Build the game by following the walkthrough above. Update the function `partsCompleted()` in the template to return the number of the last part you completed.

**Part 1.** The ship is drawn, turns with the arrow keys, accelerates with the up arrow, and moves. Asteroids are drawn and drift and spin.

**Part 2.** The game ends when the ship collides with an asteroid.

**Part 3.** The ship fires projectiles with the space bar; a projectile that hits an asteroid destroys both. Everything wraps around the edges of the window.

**Part 4.** Destroyed asteroids give points, shown on the screen, and new asteroids appear over time.

## 14.4 CMake and third-party libraries

Real programs build on libraries written by others. Java has Maven and Gradle, Python has pip, Rust has Cargo. C++ has no single official package manager, but the ecosystem has converged on **CMake** for describing builds, together with a few ways of obtaining libraries.

### CMake in brief

A `CMakeLists.txt` file describes a project's **targets** — executables and libraries — and their dependencies:

```cmake
cmake_minimum_required(VERSION 3.25)
project(todo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(todo main.cpp TodoDao.cpp UserInterface.cpp)
target_compile_options(todo PRIVATE -Wall -Wextra)
```

CMake then generates the actual build files for your platform (Makefiles, Ninja, Visual Studio projects):

```
cmake -S . -B build          # configure: read CMakeLists.txt, generate the build
cmake --build build          # build
```

### Getting libraries

There are three common ways to bring in a library:

1. **`FetchContent`** downloads a library's source code when the project is configured and builds it along with your code. This is how the exercises get Catch2, raylib and raygui:

   ```cmake
   include(FetchContent)
   FetchContent_Declare(raylib
       GIT_REPOSITORY https://github.com/raysan5/raylib.git
       GIT_TAG 5.5)
   FetchContent_MakeAvailable(raylib)

   target_link_libraries(game PRIVATE raylib)
   ```

   Always pin a specific version (`GIT_TAG`), so that the build does not change under your feet.

2. **`find_package`** uses a library that is already installed on the system, for example from the Linux distribution's package manager:

   ```cmake
   find_package(SQLite3 REQUIRED)
   target_link_libraries(todo PRIVATE SQLite::SQLite3)
   ```

3. A **package manager** such as **vcpkg** or **Conan** installs libraries and their dependencies for you, in the right versions for your compiler, and makes them available to `find_package`. With vcpkg, a `vcpkg.json` file lists the dependencies:

   ```json
   {
     "dependencies": [ "sqlite3", "fmt", "nlohmann-json" ]
   }
   ```

`target_link_libraries` does more than linking: it also makes the library's headers available to your target. That is why, in the exercises, linking `raylib` is enough for `#include "raylib.h"` to work.

### Using a database

Many applications store their data in a **database**. **SQLite** is a complete database engine in a single C library, storing the whole database in one file. It is used in phones, browsers, aircraft and countless other places.

A database is controlled with **SQL** statements:

```sql
CREATE TABLE IF NOT EXISTS Todo (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT,
    description TEXT,
    done INTEGER
);
INSERT INTO Todo (name, description, done) VALUES ('Write', 'Write a book', 0);
SELECT id, name, description, done FROM Todo;
UPDATE Todo SET done = 1 WHERE id = 1;
DELETE FROM Todo WHERE id = 1;
```

SQLite's C interface works like this: open a database with `sqlite3_open`, prepare a statement with `sqlite3_prepare_v2`, **bind** values to its `?` placeholders with `sqlite3_bind_…`, run it with `sqlite3_step` (once per result row), read columns with `sqlite3_column_…`, and release it with `sqlite3_finalize`:

```cpp
void TodoDao::add(const Todo& todo) {
    sqlite3_stmt* statement = nullptr;
    sqlite3_prepare_v2(db, "INSERT INTO Todo (name, description, done) VALUES (?, ?, ?)",
                       -1, &statement, nullptr);
    sqlite3_bind_text(statement, 1, todo.getName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 2, todo.getDescription().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(statement, 3, todo.isDone() ? 1 : 0);
    sqlite3_step(statement);
    sqlite3_finalize(statement);
}
```

> **Always bind values; never paste them into SQL text.** Building SQL by concatenating user input — `"DELETE FROM Todo WHERE name = '" + name + "'"` — allows **SQL injection**: a malicious "name" can contain SQL that destroys or leaks the database. Placeholders and binding are immune to this.

A class whose job is to move objects in and out of the database is called a **DAO** (*data access object*). The rest of the program uses the DAO and never sees SQL.

### Exercise 14.10: Database

*Template: `exercises/part14/14_10_Database`*

The template is a to-do application that stores its tasks in an SQLite database file `todos.db`. CMake downloads SQLite automatically. It contains the classes:

- `Todo` — a task with an id, a name, a description and whether it is done,
- `TodoDao` — reads and writes tasks in the database; `list()` and `add()` are implemented,
- `UserInterface` — a text interface with the commands `list`, `add`, `mark as done`, `remove` and `x`.

Implement the remaining `TodoDao` member functions `markAsDone(int id)` and `remove(int id)`, using prepared statements with bound parameters.

```
Enter command:
> add
Name:
> Write
Description:
> Write a book
Enter command:
> list
Listing the database contents
1, Write, Write a book, false
Enter command:
> mark as done
Which todo should be marked as done (give the id)?
> 1
Enter command:
> list
Listing the database contents
1, Write, Write a book, true
Enter command:
> x
Thank you!
```

### Packaging applications

To give your program to others, build it in **Release** mode (`cmake -B build -DCMAKE_BUILD_TYPE=Release`), which turns on the compiler's optimisations. A C++ program is a native executable; to run elsewhere it needs the libraries it uses. Linking libraries **statically** puts them inside the executable; otherwise the shared libraries (`.dll`, `.so`, `.dylib`) must be shipped alongside. CMake's companion tool **CPack** creates installers and archives (`.zip`, `.deb`, `.msi`) from a project.

### Other development environments

Everything in this book works with any editor and the command line. Popular C++ environments include Visual Studio (Windows), CLion (all platforms), Visual Studio Code with the C/C++ and CMake Tools extensions, Xcode (macOS), and Qt Creator. Whatever you use, learn its **debugger** well, turn on **warnings**, run the **sanitizers** regularly, and let a tool like `clang-format` keep your code tidy.

## 14.5 Conclusion

You have reached the end of the book. Looking back, you have learned to:

- write programs with variables, conditions, loops and functions,
- store data in vectors, arrays, maps and sets, and process it with algorithms and ranges,
- design programs from classes and objects, with encapsulation, composition, inheritance and polymorphism,
- understand C++'s value semantics, references, pointers, lifetimes and RAII,
- handle errors with exceptions and optionals, read and write files,
- write generic code with templates, and understand how containers work inside,
- test your code, debug it, and structure larger programs,
- build graphical programs and games, and use third-party libraries.

That is a solid foundation in programming and in modern C++. Where next? Write programs of your own — the best way to learn is to build something you care about. Read other people's code. Explore topics this book only touched: move semantics and the rule of five, concurrency with `std::thread` and `std::jthread`, modules, coroutines, and the wider world of algorithms and data structures.

Happy programming!
