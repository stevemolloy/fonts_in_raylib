#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

#define WIDTH 800
#define HEIGHT 600

#define FONTSIZE 64
#define BACKGROUNDCOLOUR CLITERAL(Color){ 30, 30, 30, 255 }

Font AddNewCodepointsToFont(Font font, char *filePath, char *new_chars) {
  int codepointCount = 0;
  int *codepoints = LoadCodepoints(new_chars, &codepointCount);

  int newCount = font.glyphCount + codepointCount;

  int *newCodepoints = MemAlloc(newCount * sizeof(int));
  for (int i=0; i<font.glyphCount; i++) {
    newCodepoints[i] = font.glyphs[i].value;
  }
  for (int i=font.glyphCount; i<newCount; i++) {
    newCodepoints[i] = codepoints[i-font.glyphCount];
  }

  Font newFont = LoadFontEx(filePath, FONTSIZE, newCodepoints, newCount);

  MemFree(newCodepoints);

  return newFont;
}

int main(void) {
  InitWindow(WIDTH, HEIGHT, "Testing fonts");

  char *font_file_path = "fonts/Alegreya-VariableFont_wght.ttf";
  Font font = LoadFontEx(font_file_path, FONTSIZE, NULL, 0);

  char *text = "abcdefghijklmnopqrstuvwxyzåäö";

  Font new_font = AddNewCodepointsToFont(font, font_file_path, "öäå");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BACKGROUNDCOLOUR);

    Vector2 broken_text_size = MeasureTextEx(font, text, FONTSIZE, 0.5);
    Vector2 broken_centre = { .x = WIDTH/2.0 - broken_text_size.x/2.0, .y = HEIGHT/2.0 - 3*broken_text_size.y/2.0 };
    DrawTextEx(font, text, broken_centre, FONTSIZE, 0, YELLOW);

    Vector2 fixed_text_size = MeasureTextEx(new_font, text, FONTSIZE, 0.5);
    Vector2 fixed_centre = { .x = WIDTH/2.0 - fixed_text_size.x/2.0, .y = HEIGHT/2.0 - fixed_text_size.y/2.0 };
    DrawTextEx(new_font, text, fixed_centre, FONTSIZE, 0, YELLOW);

    EndDrawing();
  }

  return 0;
}
