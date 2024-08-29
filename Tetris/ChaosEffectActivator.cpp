#include "game.h"
#include "ChaosBlock.cpp"
#include "ChaosEffects.h"
#include "GameState.h"
#include <random>
#include <iostream>


void Game::SetBigBlockMod(bool isActive)
{
	bigBlockEffect = isActive;

}

void Game::SetLineBlock(bool isActive)
{
	isLineBlock = isActive;

}

void Game::SetSZBlock(bool isActive)
{
	isSZBlock = isActive;

}

void Game::SetPentrix(bool isActive)
{
	isPentrix = isActive;

}

void Game::ReverseControl(bool isActive)
{
	reverseControl = isActive;
}
