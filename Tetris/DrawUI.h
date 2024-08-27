#pragma once
#include "raylib.h"
#include "game.h"
#include "color.h"
#include "GameState.h"
#include "ChaosEffects.h"
#include <iostream>

class DrawUI {
public:
	Game game();
	Font font;
	DrawUI(Font font);
	void DrawMenu();
	void DrawGameOver(const Game& game);

private:
	
	Color lightBlue = { 59, 85, 162, 255 };
};