#include "DrawUI.h"
#include "game.h"
#include "color.h"
#include "GameState.h"
#include "ChaosEffects.h"


Game DrawUI::game()
{
    return Game();
}

DrawUI::DrawUI(Font font) : font(font)	{}


void DrawUI::DrawMenu()
{
    DrawTextEx(font, "ChaosTris", { 265, 100 }, 64, 2, WHITE);

    Vector2 enterTextPosition = { 225, 300 };
    Vector2 chaosTextPosition = { 150, 400 };
    Vector2 escTextPosition = { 250, 500 };

    Vector2 enterTextSize = MeasureTextEx(font, "Press Enter to Start", 32, 2);
    Vector2 chaosTextSize = MeasureTextEx(font, "Press Shift to enter Chaos Mod", 32, 2);
    Vector2 escTextSize = MeasureTextEx(font, "Press Esc to Exit", 32, 2);

    DrawRectangleRounded({ enterTextPosition.x - 10, enterTextPosition.y - 10, enterTextSize.x + 20, enterTextSize.y + 20 }, 0.3, 6, lightBlue);
    DrawRectangleRounded({ chaosTextPosition.x - 10, chaosTextPosition.y - 10, chaosTextSize.x + 20, chaosTextSize.y + 20 }, 0.3, 6, lightBlue);
    DrawRectangleRounded({ escTextPosition.x - 10, escTextPosition.y - 10, escTextSize.x + 20, escTextSize.y + 20 }, 0.3, 6, lightBlue);

    DrawTextEx(font, "Press E to Start", enterTextPosition, 32, 2, WHITE);
    DrawTextEx(font, "Press R to enter Chaos Mod", chaosTextPosition, 32, 2, WHITE);
    DrawTextEx(font, "Press Esc to Exit", escTextPosition, 32, 2, WHITE);
}

void DrawUI::DrawGameOver(const Game& game)
{
    char scoreText[50];
    sprintf_s(scoreText, "Score   %d", game.score);

    DrawTextEx(font, "Game Over", { 250, 200 }, 64, 2, WHITE);
    DrawTextEx(font, scoreText, { 265, 275 }, 38, 2, WHITE);
    DrawTextEx(font, "Press E to restart", { 190, 350 }, 38, 2, WHITE);
    DrawTextEx(font, "Press R to enter Chaos Mod", { 100,400 }, 38, 2, WHITE);
    DrawTextEx(font, "Press Esc to Exit", { 250, 450 }, 38, 2, WHITE);
}

