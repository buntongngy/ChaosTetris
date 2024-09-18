#include "ChaosBlock.cpp"
#include "ChaosEffects.h"
#include "GameState.h"
#include <random>
#include <iostream>

void Game::HandleInput()
{
	int keyPress = GetKeyPressed();

	if (gameOver && keyPress != 0)
	{
		gameOver = false;
		Reset();
		PlayMusicStream(music);
	}

	if (reverseControl) {

		switch (keyPress)
		{
		case KEY_RIGHT:
			MoveBlockLeft();
			break;
		case KEY_LEFT:
			MoveBlockRight();
			break;
		case KEY_DOWN:
			MoveBlockDown();
			break;
		case KEY_SPACE:
			DropBlock();
			updateScore(0, 1);
			break;
		case KEY_UP:
			RotateBlock();
			break;
		case KEY_C:
			HoldBlock();
			break;
		}
	}
	else {
		// Normal controls
		switch (keyPress)
		{
		case KEY_LEFT:
			MoveBlockLeft();
			break;
		case KEY_RIGHT:
			MoveBlockRight();
			break;
		case KEY_DOWN:
			MoveBlockDown();
			break;
		case KEY_SPACE:
			DropBlock();
			updateScore(0, 1);
			break;
		case KEY_UP:
			RotateBlock();
			break;
		case KEY_C:
			HoldBlock();
			break;
		}
	}
}

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
