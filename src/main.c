#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

#define WIDTH 800
#define HEIGHT 600

#define FONTSIZE 64
#define BACKGROUNDCOLOUR CLITERAL(Color){ 30, 30, 30, 255 }

void AddNewCharsToFontEx(Font *font, const char *fileName, int fontSize, char *newChars)
{
  int codepointCount = 0;
  int *codepoints = LoadCodepoints(newChars, &codepointCount);

  int newCount = font->glyphCount + codepointCount;

  int *newCodepoints = MemAlloc(newCount * sizeof(int));
  for (int i=0; i<font->glyphCount; i++) {
    newCodepoints[i] = font->glyphs[i].value;
  }
  for (int i=font->glyphCount; i<newCount; i++) {
    newCodepoints[i] = codepoints[i-font->glyphCount];
  }

  *font = LoadFontEx(fileName, fontSize, newCodepoints, newCount);

  MemFree(newCodepoints);
}

int main(void) {
  InitWindow(WIDTH, HEIGHT, "Testing fonts");

  char *font_file_path = "fonts/Alegreya-VariableFont_wght.ttf";
  Font font = LoadFontEx(font_file_path, FONTSIZE, NULL, 0);

  char *text = "abcdefghijklmnopqrstuvwxyzåäö";

  AddNewCharsToFontEx(&font, font_file_path, FONTSIZE, "öäå");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BACKGROUNDCOLOUR);

    Vector2 text_size = MeasureTextEx(font, text, FONTSIZE, 0.5);
    Vector2 centre = { .x = WIDTH/2.0 - text_size.x/2.0, .y = HEIGHT/2.0 - text_size.y/2.0 };
    DrawTextEx(font, text, centre, FONTSIZE, 0, YELLOW);

    EndDrawing();
  }

  return 0;
}
