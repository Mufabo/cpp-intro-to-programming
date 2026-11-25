// Exercise 14.7: Collage
// See chapter 14 of the book for the assignment.

#include "raylib.h"

// Returns a new image created from the pixels of the original.
// Parts 1-3: change this function.
Image createCollage(const Image& original) {
    Image result = GenImageColor(original.width, original.height, BLACK);
    for (int y = 0; y < original.height; y++) {
        for (int x = 0; x < original.width; x++) {
            ImageDrawPixel(&result, x, y, GetImageColor(original, x, y));
        }
    }
    return result;
}

int main() {
    InitWindow(800, 600, "Collage");
    SetTargetFPS(60);

    Image original = LoadImage("monalisa.png");
    Image collage = createCollage(original);
    Texture2D texture = LoadTextureFromImage(collage);
    SetWindowSize(collage.width, collage.height);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(texture, 0, 0, WHITE);
        EndDrawing();
    }

    UnloadTexture(texture);
    UnloadImage(collage);
    UnloadImage(original);
    CloseWindow();
}
