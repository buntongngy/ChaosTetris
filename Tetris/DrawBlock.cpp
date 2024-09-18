#include "game.h"
#include "ChaosBlock.cpp"
#include "ChaosEffects.h"
#include "GameState.h"
#include <random>
#include <iostream>

void Game::Draw()
{
	grid.Draw();
	currentBlock.Draw(11, 11, true);


	switch (nextBlock.id)
	{
	case 3:
		nextBlock.Draw(540, 240, false);
		break;

	case 4:
		nextBlock.Draw(540, 230, false);
		break;
	case 8:
		nextBlock.Draw(550, 230, false);
		break;
	case 9:
		nextBlock.Draw(540, 210, false);
		break;
	case 10:
		nextBlock.Draw(490, 245, false);
		break;
	case 11:
		nextBlock.Draw(495, 230, false);
		break;
	case 19:
		nextBlock.Draw(520, 210, false);
		break;
	case 20:
		nextBlock.Draw(495, 220, false);
		break;
	case 21:
		nextBlock.Draw(520, 230, false);
		break;
	case 22: case 23:
		nextBlock.Draw(495, 210, false);
		break;
	case 24: case 25:
		nextBlock.Draw(500, 230, false);
		break;

	default:
		nextBlock.Draw(555, 230, false);
		break;
	}
}

void Game::HoldBlockOffSet()
{
	switch (holdBlock.id)
	{
	case 3: case 9: case 19: case 22: case 23:
		holdBlock.rowOffSet = 1;
		holdBlock.colOffSet = 2;
		break;


	case 10:
		holdBlock.rowOffSet = 2;
		holdBlock.colOffSet = 3;
		break;

	case 20:
		holdBlock.rowOffSet = 2;
		holdBlock.colOffSet = 1;
		break;

	case 21: case 24: case 25:
		holdBlock.rowOffSet = 2;
		holdBlock.colOffSet = 2;
		break;

	default:
		holdBlock.rowOffSet = 2;
		holdBlock.colOffSet = 3;
		break;
	}
}