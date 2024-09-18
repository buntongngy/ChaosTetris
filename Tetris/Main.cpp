#include "raylib.h"
#include "game.h"
#include "color.h"
#include "GameState.h"
#include "ChaosEffects.h"
#include "DrawUI.h"
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
    
    DrawTextEx(font, "Score", { 600, 15 }, 38, 2, WHITE);
    DrawTextEx(font, "Next", { 600, 125 }, 38, 2, WHITE);
    DrawTextEx(font, "Hold", { 50, 15 }, 38, 2, WHITE);

    DrawRectangleRounded({ 600,55,170, 60 }, 0.3, 6, lightBlack);

    char scoreText[10];
    sprintf_s(scoreText, "%d", game.score);
    Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

    DrawTextEx(font, scoreText, { 620, 65 }, 38, 2, WHITE);

    DrawRectangleRounded({ 600,175,170, 180 }, 0.3, 6, lightBlack);
    DrawRectangleRounded({ 15, 65, 170,180 }, 0.3, 6, lightBlack);

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
        DrawTextEx(font, "Chaos", { 20, 400 }, 38, 2, WHITE);

        char chaosTimerText[20];
        sprintf_s(chaosTimerText, "Timer %.1f", chaosTimer);
        DrawTextEx(font, chaosTimerText, { 20, 450 }, 38, 2, WHITE);


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

    InitWindow(800, 620, "ChaosTris");
    SetTargetFPS(60);

    Font font = LoadFontEx("Font/tetris.ttf", 64, 0, 0);
    DrawUI drawUI(font);

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
            drawUI.DrawMenu();
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

            drawUI.DrawGameOver(game);
        }
         

        EndDrawing();

        if (gameState == MENU)
        {
            if (IsKeyPressed(KEY_E)) {
                gameState = GAME;
                game.Reset();
                PlayMusicStream(game.music);
            }
            else if (IsKeyPressed(KEY_R))
            {
                gameState = CHAOS_MOD;
            }
            else if (IsKeyPressed(KEY_ESCAPE)) {
                break;
            }
        }
        else if (gameState == GAME_OVER)
        {
            if (IsKeyPressed(KEY_E)) {
                gameState = GAME;
                game.Reset();
                PlayMusicStream(game.music);
            }
            else if (IsKeyPressed(KEY_R))
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