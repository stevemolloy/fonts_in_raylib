#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

#define WIDTH 800
#define HEIGHT 600

#define FONTSIZE 64
#define BACKGROUNDCOLOUR CLITERAL(Color){ 30, 30, 30, 255 }

// Reload the font after adding the new characters to the list of desired characters
void AddNewCharsToFontEx(Font *font, const char *fileName, int fontSize, char *newChars)
{
    // Get the codepoints of the newChars
    int codepointCount = 0;
    int *codepoints = LoadCodepoints(newChars, &codepointCount);

    // Maximum value of the number of codepoints in the updated Font
    int newCount = font->glyphCount + codepointCount;

    // Allocate space for the new codepoints and populate it
    int *newCodepoints = MemAlloc(newCount * sizeof(int));

    int codepointCountWithNoDupes = 0;  // We don't need to assign chars that already exist in the Font
    for (int i = 0; i < font->glyphCount; i++)
    {
        newCodepoints[i] = font->glyphs[i].value;
        codepointCountWithNoDupes += 1;
    }

    for (int i = font->glyphCount; i < newCount; i++)
    {
        bool codepointIsUnique = true;
        int cp = codepoints[i-font->glyphCount];

        // This loop checks for the existence of the newChars in the input Font, and skips them if necessary
        for (int j = 0; j < font->glyphCount; j++)
        {
            if (cp == font->glyphs[j].value)
            {
              codepointIsUnique = false;
              break;
            }
        }
        if (codepointIsUnique)
        {
            newCodepoints[codepointCountWithNoDupes] = cp;
            codepointCountWithNoDupes += 1;
        }
    }

    // Unload the Font and then reassign the newly built Font
    UnloadFont(*font);
    *font = LoadFontEx(fileName, fontSize, newCodepoints, codepointCountWithNoDupes);

    MemFree(newCodepoints);
}

int main(void) {
  InitWindow(WIDTH, HEIGHT, "Testing fonts");

  SetTextLineSpacing(FONTSIZE);

  char *font_file_path = "fonts/Alegreya-VariableFont_wght.ttf";
  Font font = LoadFontEx(font_file_path, FONTSIZE, NULL, 0);

  char *text = "• A bulleted list\n• To demo the new function";

  AddNewCharsToFontEx(&font, font_file_path, FONTSIZE, "ab•c");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BACKGROUNDCOLOUR);

    Vector2 text_size = MeasureTextEx(font, text, FONTSIZE, 0.5);
    Vector2 centre = { .x = WIDTH/2.0 - text_size.x/2.0, .y = HEIGHT/2.0 - text_size.y/2.0 };
    DrawTextEx(font, text, centre, FONTSIZE, 0.5, YELLOW);

    EndDrawing();
  }

  return 0;
}
