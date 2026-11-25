# Chapter 13: Graphical User Interfaces

So far our programs have talked to their users through text. In this chapter we build programs with windows, buttons, text fields and multiple views. Along the way we meet a new way of structuring a program: around an **event loop** that runs many times per second.

## 13.1 Graphical user interfaces in C++

The C++ standard library has no graphics. Graphical programs use a **library**. There are many to choose from: large frameworks such as Qt and wxWidgets, game-oriented libraries such as SFML and SDL, and lightweight *immediate-mode* GUI libraries such as Dear ImGui.

In this book we use **raylib**, a small, friendly library for graphics, input and sound, together with **raygui**, its companion library of user interface controls. They are easy to set up, run on Windows, macOS and Linux, and are well suited both to the user interfaces of this chapter and to the visualisations and game of the next.

### Setting up

The exercises of chapters 13 and 14 are not built by default, because raylib needs a few extra system packages. To build them:

- **Linux:** install the X11 and OpenGL development packages, for example on Ubuntu: `sudo apt install libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl1-mesa-dev`.
- **Windows and macOS:** nothing extra is needed.

Then configure the exercises with the graphical option switched on:

```
cmake -S exercises -B build -DBUILD_GRAPHICAL_EXERCISES=ON
cmake --build build
```

CMake downloads raylib and raygui automatically the first time (this takes a minute).

### The first window

```cpp
#include "raylib.h"

int main() {
    InitWindow(400, 300, "Hello raylib");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello world!", 120, 130, 24, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
}
```

- `InitWindow(width, height, title)` opens a window. Sizes and positions are in **pixels**; `(0, 0)` is the top-left corner, *x* grows to the right and *y* grows **downwards**.
- `SetTargetFPS(60)` makes the program draw 60 frames per second.
- The `while` loop is the **main loop**, or *game loop*. Each round draws one *frame*: `BeginDrawing()` starts it, `ClearBackground` erases the previous frame, the drawing functions paint the new one, and `EndDrawing()` shows it on the screen.
- `WindowShouldClose()` becomes `true` when the user closes the window or presses Escape.
- `CloseWindow()` releases the window.

raylib is a C library, so its functions are free functions with names like `DrawText`, and its types are simple structs such as `Rectangle`, `Vector2` and `Color`. It works seamlessly from C++.

### Exercise 13.1: My First Application

*Template: `exercises/part13/13_01_MyFirstApplication`*

Create a program that opens a window with the title `My first application`.

### The structure of a user interface

Most GUI frameworks you will meet — Qt, JavaFX, the web's HTML — are **retained-mode**: you create a tree of component objects (a window containing a panel containing a button), give each component an event handler, and the framework draws the components and calls your handlers when something happens.

raygui is **immediate-mode**. There are no component objects. Every frame, your code simply *says* which controls exist, and each control function both draws the control and tells you whether the user just interacted with it:

```cpp
if (GuiButton(Rectangle{20, 20, 120, 40}, "Press me")) {
    // the button was clicked during this frame
}
```

The state of the user interface — the text in a text field, which view is visible, whose turn it is — lives in **your** variables. Each frame, the interface is drawn from that state. This style is popular in games and tools because it is simple: there is no hidden state to keep in sync.

Both styles teach the same ideas: components, layout, events, and keeping the user interface separate from the program logic.

## 13.2 UI components and their layout

### Labels and buttons

The basic raygui controls are:

| Function | Control | Returns |
|---|---|---|
| `GuiLabel(bounds, text)` | a piece of text | — |
| `GuiButton(bounds, text)` | a push button | `true` when clicked |
| `GuiTextBox(bounds, buffer, size, editMode)` | a single-line text field | `true` when clicked or Enter is pressed |
| `GuiCheckBox(bounds, text, &checked)` | a check box | — |
| `GuiSlider(bounds, left, right, &value, min, max)` | a slider | — |

Every control takes its **bounds**, a `Rectangle{x, y, width, height}`. Including raygui takes one extra line: exactly one source file of the program must define `RAYGUI_IMPLEMENTATION` before including `raygui.h`, which compiles the library's code into that file.

```cpp
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main() {
    InitWindow(300, 120, "Label and button");
    SetTargetFPS(60);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);   // larger text for all controls

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        GuiLabel(Rectangle{20, 20, 260, 30}, "This is a label");
        GuiButton(Rectangle{20, 60, 260, 40}, "This is a button");
        EndDrawing();
    }

    CloseWindow();
}
```

### Exercise 13.2: Button and Label

*Template: `exercises/part13/13_02_ButtonAndLabel`*

Create a user interface with a button and a label. The label must be above or to the left of the button.

### Text fields

A text field needs two pieces of state: a **buffer** of characters holding the text, and whether the field is currently being **edited**. raygui is a C library, so the buffer is a C-style character array; convert it to a `std::string` when you need to process the text:

```cpp
char text[128] = "";          // the buffer, initially empty
bool editing = false;

// inside the main loop:
if (GuiTextBox(Rectangle{20, 20, 260, 40}, text, sizeof(text), editing)) {
    editing = !editing;       // clicking the field (or pressing Enter) toggles editing
}
std::string content = text;   // now an ordinary std::string
```

### Exercise 13.3: Button and Text Field

*Template: `exercises/part13/13_03_ButtonAndTextField`*

Create a user interface with a button and a text field.

### Layout

Placing every control by hand with pixel coordinates is tedious and fragile: what if the window is resized, or a label grows? Retained-mode frameworks offer **layout managers** that arrange components automatically. Two classic ones are:

- a **border layout**, which divides the window into *top*, *bottom*, *left*, *right* and *center* areas, and
- a **box layout**, which stacks components in a row (*HBox*) or a column (*VBox*), and a **grid layout**, which arranges them in rows and columns.

With raygui, we compute the rectangles ourselves — but we can write small helper functions that do the arithmetic, which is exactly what a layout manager does. The exercise templates of this chapter include a header `layout.h` with these helpers:

```cpp
struct BorderAreas {
    Rectangle top, bottom, left, right, center;
};

// Divides `area` into a border layout. The sizes give the height of the top and
// bottom areas and the width of the left and right areas.
BorderAreas borderLayout(Rectangle area, float top, float bottom, float left, float right);

// Divides `area` into `count` equal parts side by side, with `gap` pixels between them.
std::vector<Rectangle> hbox(Rectangle area, int count, float gap = 8);

// Divides `area` into `count` equal parts on top of each other.
std::vector<Rectangle> vbox(Rectangle area, int count, float gap = 8);

// The rectangle of the cell (column, row) in a grid of the given size.
Rectangle gridCell(Rectangle area, int columns, int rows, int column, int row, float gap = 4);

// The whole window as a rectangle, minus a margin.
Rectangle windowArea(float margin = 10);
```

For example, a window with a title at the top, three buttons in a row at the bottom and a big area in the middle:

```cpp
BorderAreas areas = borderLayout(windowArea(), 40, 50, 0, 0);
GuiLabel(areas.top, "My application");
std::vector<Rectangle> buttons = hbox(areas.bottom, 3);
GuiButton(buttons[0], "First");
GuiButton(buttons[1], "Second");
GuiButton(buttons[2], "Third");
DrawRectangleLinesEx(areas.center, 1, GRAY);
```

Because the rectangles are computed from the window size every frame, the layout adapts automatically if the window is resized (allow resizing with `SetConfigFlags(FLAG_WINDOW_RESIZABLE)` before `InitWindow`). Open `layout.h` and read it — it is short.

### Exercise 13.4: Border Layout

*Template: `exercises/part13/13_04_BorderPane`*

Create a user interface laid out with `borderLayout`. Put a label with the text `NORTH` in the top area, `EAST` in the right area and `SOUTH` in the bottom area.

### Combining layouts

Layouts nest: a part of a border layout can itself be divided with `hbox`, and so on, just as in the example above.

### Exercise 13.5: Text Statistics

*Template: `exercises/part13/13_05_TextStatistics`*

Create an application with a border layout. In the center, place a text field. At the bottom, place three labels in a row: `Letters: 0`, `Words: 0` and `The longest word is:`.

## 13.3 Event handling

In a retained-mode framework, you attach **event handlers** to components: functions that the framework calls when the user clicks a button or types in a field. In immediate mode, events show up as return values: `if (GuiButton(...))` is the event handler. Other input is read directly from raylib:

| Function | Meaning |
|---|---|
| `IsKeyPressed(KEY_ENTER)` | the key went down during this frame |
| `IsKeyDown(KEY_LEFT)` | the key is held down |
| `IsMouseButtonPressed(MOUSE_BUTTON_LEFT)` | the mouse button was clicked this frame |
| `GetMousePosition()` | the mouse position as a `Vector2` |
| `CheckCollisionPointRec(point, rect)` | is the point inside the rectangle? |

Here a button copies the text field's content into a label:

```cpp
char input[128] = "";
bool editing = false;
std::string shown;

while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (GuiTextBox(Rectangle{20, 20, 260, 40}, input, sizeof(input), editing)) {
        editing = !editing;
    }
    if (GuiButton(Rectangle{20, 70, 260, 40}, "Copy")) {
        shown = input;
    }
    GuiLabel(Rectangle{20, 120, 260, 30}, shown.c_str());

    EndDrawing();
}
```

`shown.c_str()` gives a C-style pointer to the string's characters, which is what raygui's functions expect.

Some events are not caused by the user at all but by a **change in data**. In immediate mode, reacting to changing data is trivial: since everything is drawn from the current state every frame, the display is always up to date. For example, to show statistics of the text as the user types, simply compute them every frame:

```cpp
std::string text = input;
std::vector<std::string> words = split(text, ' ');
GuiLabel(statsArea, std::format("Words: {}", words.size()).c_str());
```

(If a computation is expensive, compute it only when the text changes, by remembering the previous text.)

### Exercise 13.6: Notifier

*Template: `exercises/part13/13_06_Notifier`*

Create a user interface with three controls stacked vertically: a text field, a button with the text `Update`, and a label. Pressing the button copies the text from the text field into the label.

### Exercise 13.7: Text Statistics, Part II

*Template: `exercises/part13/13_07_TextStatisticsPart2`*

Copy your solution to the previous Text Statistics exercise and make the labels show live statistics of the text: the number of letters (characters, not counting spaces), the number of words, and the longest word.

## 13.4 Launch parameters

Programs can receive **command-line arguments** when they are started, like `cp source.txt target.txt`. In C++, `main` can take two parameters to receive them:

```cpp
int main(int argc, char* argv[]) {
    for (int i = 0; i < argc; i++) {
        std::println("Argument {}: {}", i, argv[i]);
    }
}
```

`argc` is the number of arguments and `argv` an array of C-style strings. `argv[0]` is the program's own name, and the actual arguments start from `argv[1]`. It is convenient to copy them into a vector of strings first:

```cpp
std::vector<std::string> args(argv + 1, argv + argc);
```

A graphical program can also simply ask questions in the terminal before opening its window.

### Exercise 13.8: User Title

*Template: `exercises/part13/13_08_UserTitle`*

Write a program that asks for a window title in the terminal. After the user has typed it and pressed Enter, the program opens a window with that title. If a title is given as a command-line argument, use it and do not ask.

## 13.5 Multiple views

Applications often have several **views**: a login screen and the main screen, a settings page, the views of a wizard. In retained-mode frameworks, each view is a separate tree of components, and the window switches which tree it displays.

In immediate mode, a view is simply a **function that draws it**, and the current view is a **variable**. An `enum class` is perfect for the variable:

```cpp
enum class View { First, Second };

int main() {
    InitWindow(400, 200, "Views");
    SetTargetFPS(60);
    View view = View::First;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (view) {
            case View::First:
                GuiLabel(Rectangle{20, 20, 360, 30}, "First view!");
                if (GuiButton(Rectangle{20, 60, 360, 40}, "To the second view")) {
                    view = View::Second;
                }
                break;
            case View::Second:
                GuiLabel(Rectangle{20, 20, 360, 30}, "Second view!");
                if (GuiButton(Rectangle{20, 60, 360, 40}, "Back to the first view")) {
                    view = View::First;
                }
                break;
        }

        EndDrawing();
    }
    CloseWindow();
}
```

This structure — the program is always in one of a fixed set of states, and events move it from one state to another — is called a **state machine**. It is everywhere in interactive programs and games.

### Exercise 13.9: Multiple Views

*Template: `exercises/part13/13_09_MultipleViews`*

Create an application with three views:

- The first view uses a border layout. The top shows the text `First view!` and the center a button `To the second view!`.
- The second view is a vertical box. The first element is a button `To the third view!`, and below it is the text `Second view!`.
- The third view is a grid. Its top-left cell shows `Third view!` and its bottom-right cell has a button `To the first view!`.

### A separate drawing function for each view

As the views grow, give each its own function, and keep the shared state in a struct passed to the functions:

```cpp
struct AppState {
    View view = View::Input;
    char name[64] = "";
    bool editingName = false;
};

void drawInputView(AppState& state);
void drawWelcomeView(AppState& state);
```

### Exercise 13.10: Greeter

*Template: `exercises/part13/13_10_Greeter`*

Create an application with two views. The first view asks for the user's name with a text field and has a button `Start`. When the button is pressed, the second view shows the text `Welcome <name>!`.

### Views with a shared main layout

Often the views share a frame — a menu at the top, say — and only the content area changes. Draw the shared parts every frame, and only the content area depends on the current view.

### Exercise 13.11: Joke

*Template: `exercises/part13/13_11_Joke`*

Create an application that explains a joke. At the top there is a menu of three buttons: `Joke`, `Answer` and `Explanation`. Below the menu, the content area shows:

- after `Joke` (and when the program starts): `What do you call a bear with no teeth?`
- after `Answer`: `A gummy bear.`
- after `Explanation`: an explanation of your own.

## 13.6 Separating application logic from the user interface

The lessons of Chapter 6 apply fully to graphical programs. The drawing code should *only* draw and react to input; the actual logic belongs in ordinary classes that know nothing about raylib. Then the logic can be tested with Catch2, reused in a text interface, and reasoned about separately.

### A larger example: vocabulary practice

Let's sketch an application for practising vocabulary. It has two views: one for **entering** new words with their translations, and one for **practising** them.

The logic consists of a `Dictionary` that stores word pairs and can pick a random word:

```cpp
class Dictionary {
public:
    void add(const std::string& word, const std::string& translation);
    std::optional<std::string> get(const std::string& word) const;
    std::string randomWord();

private:
    std::vector<std::string> words;
    std::unordered_map<std::string, std::string> translations;
    std::mt19937 engine{std::random_device{}()};
};
```

The user interface keeps its own state — which view is shown, the contents of the text fields, the word currently being asked, and the feedback message — and uses the dictionary:

- In the **input view**, two text fields (word and translation) and a button `Add the word pair` call `dictionary.add`, then clear the fields.
- In the **practice view**, a label shows `Translate the word '<word>'`, a text field takes the user's answer, and a button `Check` compares it with the dictionary's translation, sets the feedback to `Correct!` or `Incorrect! The translation for the word '<word>' is '<translation>'.`, and picks a new word when the answer was correct.
- A menu at the top switches between the views.

### Exercise 13.12: Vocabulary Practice

*Template: `exercises/part13/13_12_VocabularyPractice`*

Implement the vocabulary practice application described above. Keep `Dictionary` free of any raylib code.

### Exercise 13.13: Tic-Tac-Toe (3 parts)

*Template: `exercises/part13/13_13_TicTacToe`*

Create a 3×3 tic-tac-toe game.

**Part 1: The user interface.** Use a border layout: the top shows whose turn it is (`Turn: X`), and the center is a 3×3 grid of buttons (use `gridCell`). Make the button text large, for example with `GuiSetStyle(DEFAULT, TEXT_SIZE, 40)` while drawing the grid.

**Part 2: Taking turns.** Player X starts. Clicking an empty square writes the current player's mark in it and passes the turn to the other player. Clicking an occupied square does nothing. Keep the board in a class `Board` (with a `std::array<char, 9>` or a 3×3 array) that knows nothing about the user interface.

**Part 3: Ending the game.** When a player gets three in a row (horizontally, vertically or diagonally), or the board is full, the game ends: the top text shows `The end!` and no more moves are possible. Give `Board` a member function that checks for a winner, and test it with Catch2 if you like.

## 13.7 Summary

- C++ has no standard graphics; we use the **raylib** library and its controls library **raygui**.
- A graphical program runs a **main loop** that draws one frame per round: `BeginDrawing`, `ClearBackground`, drawing, `EndDrawing`.
- raygui is **immediate-mode**: control functions such as `GuiButton` draw the control and return whether it was used. The interface's state lives in your own variables.
- Layout means computing rectangles; small helper functions (`borderLayout`, `hbox`, `vbox`, `gridCell`) play the role of layout managers.
- Input comes from control return values and raylib's keyboard and mouse functions.
- `main(int argc, char* argv[])` receives command-line arguments.
- Multiple views are a **state machine**: an `enum class` variable and a `switch` that draws the current view.
- Keep application logic in ordinary classes, separate from the drawing code.
