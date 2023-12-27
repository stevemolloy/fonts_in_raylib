#include <stdio.h>

#include "raylib.h"

#define WIDTH 800
#define HEIGHT 600

#define FONTSIZE 64
#define BACKGROUNDCOLOUR CLITERAL(Color){ 30, 30, 30, 255 }

int main(void) {
  InitWindow(WIDTH, HEIGHT, "Testing fonts");

  char *text = "Hello world!";
  Font font = LoadFontEx("fonts/Alegreya-VariableFont_wght.ttf", FONTSIZE, NULL, 0);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BACKGROUNDCOLOUR);
    Vector2 text_size = MeasureTextEx(font, text, FONTSIZE, 0);
    Vector2 centre = { .x = WIDTH/2.0 - text_size.x/2.0, .y = HEIGHT/2.0 - text_size.y/2.0 };
    DrawTextEx(font, text, centre, FONTSIZE, 0, YELLOW);
    EndDrawing();
  }

  return 0;
}
