#include "raylib.h"
#include "game.h"
#include "color.h"
#include "GameState.h"
#include "ChaosEffects.h"
#include <iostream>

ChaosEffects chaosEffects;



double chaosTimer = 10;
double lastUpdateTime = GetTime();


bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

void DrawGame(Font font, Game& game, bool isChaosMode)
{
    DrawTextEx(font, "Score", { 565, 15 }, 38, 2, WHITE);
    DrawTextEx(font, "Next", { 570, 125 }, 38, 2, WHITE);
    DrawTextEx(font, "Hold", { 50, 15 }, 38, 2, WHITE);


    DrawRectangleRounded({ 570,55,170, 60 }, 0.3, 6, lightBlue);

    char scoreText[10];
    sprintf_s(scoreText, "%d", game.score);
    Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

    DrawTextEx(font, scoreText, { 600, 65 }, 38, 2, WHITE);

    DrawRectangleRounded({ 570,175,170, 180 }, 0.3, 6, lightBlue);
    DrawRectangleRounded({ 15, 65, 170,180 }, 0.3, 6, lightBlue);

    if (game.heldBlock)
    {
        switch (game.holdBlock.id)
        {
        case 3:
            game.holdBlock.Draw(-20, 85, false);
            break;
        case 4:
            game.holdBlock.Draw(-20, 65, false);
            break;
        case 9:
            game.holdBlock.Draw(-20, 65, false);
            break;

        default:
            game.holdBlock.Draw(-30, 65, false);
            break;
        }
    }

    game.Draw();

    if (isChaosMode) {
        DrawTextEx(font, "Chaos", { 565, 400 }, 38, 2, WHITE);

        char chaosTimerText[20];
        sprintf_s(chaosTimerText, "Timer %.1f", chaosTimer);
        DrawTextEx(font, chaosTimerText, { 565, 450 }, 38, 2, WHITE);

        
        chaosEffects.DrawChaosEffectUI(font);
    }


}

void UpdateChaosMode(Game& game) {
    static double chaosLastUpdateTime = GetTime();
    double currentTime = GetTime();

    
    chaosTimer -= (currentTime - chaosLastUpdateTime);
    chaosLastUpdateTime = currentTime;

    // Apply and update chaos effects
    chaosEffects.ApplyEffect(game);
    chaosEffects.UpdateEffect(game);

    if (chaosTimer <= 0) {
        chaosEffects.ResetEffect(game);
        chaosEffects.StartRandomEffect();
        chaosTimer = 10;
    }
}   

void ResetChaosMod(Game& game) {
    chaosEffects.ResetEffect(game);
    chaosTimer = 10;
}




int main() {

    InitWindow(800, 620, "raylib tetis");
    InitWindow(800, 620, "raylib tetis");
    SetTargetFPS(60);

    Font font = LoadFontEx("Font/tetris.ttf", 64, 0, 0);

    Game game = Game();
    gameState = MENU;

    while (WindowShouldClose() == false) {

        if (gameState == GAME )
        {
            UpdateMusicStream(game.music);
            game.HandleInput();

            // Handle the game speed
            if (EventTriggered(0.2))
            {
                game.MoveBlockDown();
            }
        }

        if (gameState == CHAOS_MOD)
        {
             UpdateMusicStream(game.music);
            game.HandleInput();

            if (EventTriggered(game.GetSpeed()))
            {
             
                game.MoveBlockDown();
            }

            UpdateChaosMode(game);
        }


        // Draw Interface
        BeginDrawing();
        ClearBackground(Background);

        if (gameState == MENU)
        {
            DrawTextEx(font, "Tetris", { 285, 100 }, 64, 2, WHITE);

            Vector2 enterTextPosition = { 225, 300 };
            Vector2 chaosTextPosition = { 150, 400 };
            Vector2 escTextPosition = { 250, 500 };

            Vector2 enterTextSize = MeasureTextEx(font, "Press Enter to Start", 32, 2);
            Vector2 chaosTextSize = MeasureTextEx(font, "Press Shift to enter Chaos Mod", 32, 2);
            Vector2 escTextSize = MeasureTextEx(font, "Press Esc to Exit", 32, 2);

            DrawRectangleRounded({ enterTextPosition.x - 10, enterTextPosition.y - 10, enterTextSize.x + 20, enterTextSize.y + 20 }, 0.3, 6, lightBlue);
            DrawRectangleRounded({ chaosTextPosition.x - 10, chaosTextPosition.y - 10, chaosTextSize.x + 20, chaosTextSize.y + 20 }, 0.3, 6, lightBlue);
            DrawRectangleRounded({ escTextPosition.x - 10, escTextPosition.y - 10, escTextSize.x + 20, escTextSize.y + 20 }, 0.3, 6, lightBlue);

            DrawTextEx(font, "Press Enter to Start", enterTextPosition, 32, 2, WHITE);
            DrawTextEx(font, "Press Shift to enter Chaos Mod", chaosTextPosition, 32, 2, WHITE);
            DrawTextEx(font, "Press Esc to Exit", escTextPosition, 32, 2, WHITE);
        }
        else if (gameState == GAME)
        {
            DrawGame(font, game, false);
            if (game.gameOver)
            {
                gameState = GAME_OVER;
            }

        }
        else if (gameState == CHAOS_MOD)
        {
            DrawGame(font, game, true);
            if (game.gameOver)
            {
                gameState = GAME_OVER;
            }

        }
        else if (gameState == GAME_OVER)
        {

          

            char scoreText[50];
            sprintf_s(scoreText, "Score   %d", game.score);

            DrawTextEx(font, "Game Over", { 250, 200 }, 64, 2, WHITE);
            DrawTextEx(font, scoreText, { 265, 275 }, 38, 2, WHITE);
            DrawTextEx(font, "Press Enter to restart", { 190, 350 }, 38, 2, WHITE);
            DrawTextEx(font, "Press Shift to enter Chaos Mod", { 100,400 }, 38, 2, WHITE);
            DrawTextEx(font, "Press Esc to Exit", { 250, 450 }, 38, 2, WHITE);
        }

        EndDrawing();

        if (gameState == MENU)
        {
            if (IsKeyPressed(KEY_ENTER)) {
                gameState = GAME;
                game.Reset();
                PlayMusicStream(game.music);
            }
            else if (IsKeyPressed(KEY_RIGHT_SHIFT))
            {
                gameState = CHAOS_MOD;
            }
            else if (IsKeyPressed(KEY_ESCAPE)) {
                break;
            }
        }
        else if (gameState == GAME_OVER)
        {
            if (IsKeyPressed(KEY_ENTER)) {
                gameState = GAME;
                game.Reset();
                PlayMusicStream(game.music);
            }
            else if (IsKeyPressed(KEY_RIGHT_SHIFT))
            {
                gameState = CHAOS_MOD;
                game.Reset();
                ResetChaosMod(game);
                PlayMusicStream(game.music);
            }
            else if (IsKeyPressed(KEY_ESCAPE)) {
                break;
            }
        }

    }

    CloseWindow();
    return 0;
}