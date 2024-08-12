#include "raylib.h"
#include "game.h"
#include "color.h"
#include <iostream>

enum GameState { MENU, GAME, GAME_OVER };

double lastUpdateTime = 0;

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

int main() {

	InitWindow(500, 620, "raylib tetis");
	SetTargetFPS(60);

	Font font = LoadFontEx("Font/TetrisFont.ttf", 64, 0, 0);

	Game game = Game();
	GameState gameState = MENU;

	while (WindowShouldClose() == false) {



		if (gameState == GAME)
		{
			UpdateMusicStream(game.music);
			game.HandleInput();
			//Handle the game speed
			if (EventTriggered(0.2))
			{
				game.MoveBlockDown();
			}
		}




		//Draw Interface
		BeginDrawing();
		ClearBackground(darkBlue);

		if (gameState == MENU)
		{
			DrawTextEx(font, "Tetris", { 150, 100 }, 64, 2, WHITE);

			Vector2 enterTextPosition = { 60, 300 };
			Vector2 escTextPosition = { 80, 400 };

			Vector2 enterTextSize = MeasureTextEx(font, "Press Enter to Start", 32, 2);
			Vector2 escTextSize = MeasureTextEx(font, "Press Esc to Exit", 32, 2);

			// Draw rectangles behind the text
			DrawRectangleRounded({ enterTextPosition.x - 10, enterTextPosition.y - 10, enterTextSize.x + 20, enterTextSize.y + 20 }, 0.3, 6, lightBlue);
			DrawRectangleRounded({ escTextPosition.x - 10, escTextPosition.y - 10, escTextSize.x + 20, escTextSize.y + 20 }, 0.3, 6, lightBlue);

			// Draw the text
			DrawTextEx(font, "Press Enter to Start", enterTextPosition, 32, 2, WHITE);
			DrawTextEx(font, "Press Esc to Exit", escTextPosition, 32, 2, WHITE);
		}
		else if (gameState == GAME)
		{
			DrawTextEx(font, "Score", { 365, 15 }, 38, 2, WHITE);
			DrawTextEx(font, "Next", { 370, 125 }, 38, 2, WHITE);
			DrawTextEx(font, "Hold", { 370, 375 }, 38, 2, WHITE);
			if (game.gameOver)
			{
				gameState = GAME_OVER;
			}

			DrawRectangleRounded({ 320,55,170, 60 }, 0.3, 6, lightBlue);
			

			char scoreText[10];
			sprintf_s(scoreText, "%d", game.score);
			Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);


			DrawTextEx(font, scoreText, { 320 + (170 - textSize.x) / 2, 65 }, 38, 2, WHITE);
			DrawRectangleRounded({ 320,175,170, 180 }, 0.3, 6, lightBlue);
			DrawRectangleRounded({ 320, 415, 170,180 }, 0.3, 6, lightBlue);

			if (game.heldBlock)
			{

				game.holdBlock.Draw(275 , 400); 
			}

			game.Draw();

		
		}
		else if (gameState == GAME_OVER)
		{

			char scoreText[50];
			sprintf_s(scoreText, "Score   %d", game.score);


			DrawTextEx(font, "Game Over", { 100, 200 }, 64, 2, WHITE);
			DrawTextEx(font, scoreText, { 150, 275 }, 38, 2, WHITE);
			DrawTextEx(font, "Press Enter to restart", { 30, 350 }, 38, 2, WHITE);
			DrawTextEx(font, "Press Esc to Exit", { 110, 400 }, 32, 2, WHITE);
		}
		
		EndDrawing();

		if (gameState == MENU)
		{
			if (IsKeyPressed(KEY_ENTER)) {
				gameState = GAME;
				game.Reset();
				PlayMusicStream(game.music);
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
			else if (IsKeyPressed(KEY_ESCAPE)) {
				break;
			}
		}

	}

	CloseWindow();
}