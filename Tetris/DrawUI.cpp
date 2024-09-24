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
    Vector2 enterTextPosition = { 290, 300 };
    Vector2 chaosTextPosition = { 180, 400 };
    Vector2 escTextPosition = { 290, 500 };
    
    //Measure the length of the text
    Vector2 enterTextSize = MeasureTextEx(font, "Press to Start", 32, 2);
    Vector2 chaosTextSize = MeasureTextEx(font, "Press to enter Chaos Mod", 32, 2);
    Vector2 escTextSize = MeasureTextEx(font, "Press to Exit", 32, 2);

    //Draw the rectangle behind the text
    DrawRectangleRounded({ 240, 290, enterTextSize.x + 80, enterTextSize.y + 20 }, 0.3, 6, lightBlack);
    DrawRectangleRounded({ 140, 390, chaosTextSize.x + 80, chaosTextSize.y + 20 }, 0.3, 6, lightBlack);
    DrawRectangleRounded({ 240, 490, escTextSize.x + 100, escTextSize.y + 20 }, 0.3, 6, lightBlack);

    //Draw the text, and it position
    DrawTextEx(font, "Press to Start", enterTextPosition, 32, 2, WHITE);
    DrawTextEx(font, "Press to enter Chaos Mod", chaosTextPosition, 32, 2, WHITE);
    DrawTextEx(font, "Press to Exit", escTextPosition, 32, 2, WHITE);
}

//Draw Game Over User Interface
void DrawUI::DrawGameOver(const Game& game)
{
    DrawTextEx(font, "Game Over", { 245, 100 }, 64, 2, RED);

    //Declare the lenght of the score text
    char scoreText[50];
    sprintf_s(scoreText, "Score %d", game.score);

    //Text Positio
    Vector2 enterTextPosition = { 260, 300 };
    Vector2 chaosTextPosition = { 180, 400 };
    Vector2 escTextPosition = { 290, 500 };

    //Measure the text lenght
    Vector2 enterTextSize = MeasureTextEx(font, "Press to Restart", 32, 2);
    Vector2 chaosTextSize = MeasureTextEx(font, "Press to enter Chaos Mod", 32, 2);
    Vector2 escTextSize = MeasureTextEx(font, "Press to Exit", 32, 2);

    //Draw the rectangle behind the text
    DrawRectangleRounded({ 230, 290, enterTextSize.x + 50, enterTextSize.y + 20 }, 0.3, 6, lightBlack);
    DrawRectangleRounded({ 140, 390, chaosTextSize.x + 80, chaosTextSize.y + 20 }, 0.3, 6, lightBlack);
    DrawRectangleRounded({ 240, 490, escTextSize.x + 100, escTextSize.y + 20 }, 0.3, 6, lightBlack);

    //Draw the text and it position
    DrawTextEx(font, scoreText, { 255, 175 }, 38, 2, WHITE);
    DrawTextEx(font, "Press to Restart", enterTextPosition, 32, 2, WHITE);
    DrawTextEx(font, "Press to enter Chaos Mod", chaosTextPosition, 32, 2, WHITE);
    DrawTextEx(font, "Press to Exit", escTextPosition, 32, 2, WHITE);
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


