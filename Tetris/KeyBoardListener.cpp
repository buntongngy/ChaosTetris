#include "ChaosBlock.cpp"
#include "ChaosEffects.h"
#include "GameState.h"
#include <random>
#include <iostream>


void Game::MoveBlockLeft()
{
	if (!gameOver)
	{
		currentBlock.Move(0, -1);
		if (isOutofBound() || BlockFits() == false)
		{
			currentBlock.Move(0, 1);
		}
		else {
			lockTime = 0;
			moveCounter++;
		}
	}
}

void Game::MoveBlockRight()
{
	if (!gameOver)
	{
		currentBlock.Move(0, 1);
		if (isOutofBound() || BlockFits() == false)
		{
			currentBlock.Move(0, -1);

		}
		else {
			lockTime = 0;
			moveCounter++;
		}
	}
}

void Game::MoveBlockDown() {

	if (!gameOver)
	{
		currentBlock.Move(1, 0);
		if (isOutofBound() || BlockFits() == false)
		{
			currentBlock.Move(-1, 0);
			if (IsKeyDown(KEY_DOWN))
			{
				LockBlock();
			}
			else {
				lockTime += GetFrameTime();
				if (lockTime >= lockDelay || moveCounter >= moveLimit)
				{
					LockBlock();
					lockTime = 0;
					moveCounter = 0;
				}
			}

		}
		else {
			lockTime = 0;
			moveCounter = 0;
		}
	}
}



void Game::DropBlock() {
	if (!gameOver && canDrop) {

		if (!isDropping) {

			isDropping = true;

			while (!isOutofBound() && BlockFits()) {
				currentBlock.Move(1, 0);
			}

			currentBlock.Move(-1, 0);

			LockBlock();
			isDropping = false;
		}


	}
}


void Game::RotateBlock()
{
	if (!gameOver && canRotate)
	{
		currentBlock.Rotate();
		if (isOutofBound() || BlockFits() == false)
		{
			currentBlock.undo_Rotate();
		}
		else
		{
			lockTime = 0;
			moveCounter++;
			PlaySound(rotateSound);
		}
	}
}
