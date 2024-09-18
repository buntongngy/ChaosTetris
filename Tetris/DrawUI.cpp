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

//Draw Menu User Interface
void DrawUI::DrawMenu()
{

    DrawTextEx(font, "ChaosTris", { 245, 100 }, 64, 2, WHITE);

    //Text position
    Vector2 enterTextPosition = { 255, 300 };
    Vector2 chaosTextPosition = { 160, 400 };
    Vector2 escTextPosition = { 250, 500 };
    
    //Measure the length of the text
    Vector2 enterTextSize = MeasureTextEx(font, "Press E to Start", 32, 2);
    Vector2 chaosTextSize = MeasureTextEx(font, "Press R to enter Chaos Mod", 32, 2);
    Vector2 escTextSize = MeasureTextEx(font, "Press Esc to Exit", 32, 2);

    //Draw the rectangle behind the text
    DrawRectangleRounded({ enterTextPosition.x - 40, enterTextPosition.y - 10, enterTextSize.x + 80, enterTextSize.y + 20 }, 0.3, 6, lightBlack);
    DrawRectangleRounded({ chaosTextPosition.x - 40, chaosTextPosition.y - 10, chaosTextSize.x + 80, chaosTextSize.y + 20 }, 0.3, 6, lightBlack);
    DrawRectangleRounded({ escTextPosition.x - 40 , escTextPosition.y - 10, escTextSize.x + 80, escTextSize.y + 20 }, 0.3, 6, lightBlack);

    //Draw the text, and it position
    DrawTextEx(font, "Press E to Start", enterTextPosition, 32, 2, WHITE);
    DrawTextEx(font, "Press R to enter Chaos Mod", chaosTextPosition, 32, 2, WHITE);
    DrawTextEx(font, "Press Esc to Exit", escTextPosition, 32, 2, WHITE);
}

//Draw Game Over User Interface
void DrawUI::DrawGameOver(const Game& game)
{
    DrawTextEx(font, "Game Over", { 245, 100 }, 64, 2, RED);

    //Declare the lenght of the score text
    char scoreText[50];
    sprintf_s(scoreText, "Score %d", game.score);

    //Text Positio
    Vector2 enterTextPosition = { 255, 300 };
    Vector2 chaosTextPosition = { 160, 400 };
    Vector2 escTextPosition = { 250, 500 };

    //Measure the text lenght
    Vector2 enterTextSize = MeasureTextEx(font, "Press E to Restart", 32, 2);
    Vector2 chaosTextSize = MeasureTextEx(font, "Press R to enter Chaos Mod", 32, 2);
    Vector2 escTextSize = MeasureTextEx(font, "Press Esc to Exit", 32, 2);

    //Draw the rectangle behind the text
    DrawRectangleRounded({ enterTextPosition.x - 50, enterTextPosition.y - 10, enterTextSize.x + 80, enterTextSize.y + 20 }, 0.3, 6, lightBlack);
    DrawRectangleRounded({ chaosTextPosition.x - 40, chaosTextPosition.y - 10, chaosTextSize.x + 80, chaosTextSize.y + 20 }, 0.3, 6, lightBlack);
    DrawRectangleRounded({ escTextPosition.x - 40 , escTextPosition.y - 10, escTextSize.x + 80, escTextSize.y + 20 }, 0.3, 6, lightBlack);

    //Draw the text and it position
    DrawTextEx(font, scoreText, { 255, 175 }, 38, 2, WHITE);
    DrawTextEx(font, "Press E to Restart", enterTextPosition, 32, 2, WHITE);
    DrawTextEx(font, "Press R to enter Chaos Mod", chaosTextPosition, 32, 2, WHITE);
    DrawTextEx(font, "Press Esc to Exit", escTextPosition, 32, 2, WHITE);
}

//Draw the chaos effect User Interface
void ChaosEffects::DrawChaosEffectUI(Font font) const {
    if (IsEffectActive()) {
        
        // Draw effect name
        const char* effectName = GetEffectName(currentEffect);
        DrawTextEx(font, effectName, { 20, 500 }, 26, 2, WHITE);

        // Calculate remaining time
        float remainingTime = activeEffects.front().timeRemaining;
        char effectTimerText[20];
        sprintf_s(effectTimerText, "Time: %.1f", remainingTime);
        DrawTextEx(font, effectTimerText, { 20, 550 }, 26, 2, WHITE);

    }
}


