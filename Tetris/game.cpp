#include "game.h"
#include "ChaosBlock.cpp"
#include "ChaosEffects.h"
#include "GameState.h"
#include <random>
#include <iostream>



Game::Game()
{
	
	Block holdBlock;
	score = 0;
	grid = Grid();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	holdBlock = Block();
	heldBlock = false;
	gameOver = false;
	canRotate = true;
	canHold = true;
	canDrop = true;
	reverseControl = false;
	isDropping = false;
	
	InitAudioDevice();
	music = LoadMusicStream("Sound/Background.mp3");
	PlayMusicStream(music);
	rotateSound = LoadSound("Sound/Rotate.mp3");
	clearSound = LoadSound("Sound/Clear.mp3");
	gameOverSound = LoadSound("Sound/Game_Over.mp3");
}

Game::~Game()
{
	UnloadSound(rotateSound);
	UnloadSound(clearSound);
	UnloadMusicStream(music);
	CloseAudioDevice();
}




Block Game::GetRandomBlock()
{
	if (bigBlockEffect) {
		std::vector<Block> bigBlocks = { BigOBlock(), BigLBlock(), BigJBlock(), BigSBlock(), BigZBlock(), BigTBlock(), BigIBlock()};


		int randoIndex = rand() % bigBlocks.size();
		return bigBlocks[randoIndex];
	}

	if (isLineBlock)
	{
		std::vector<Block> lineBlock = { IBlock() };
		int index = 0;
		return lineBlock[index];
	}

	if (blocks.empty())
	{
		blocks = GetAllBlocks();
	}
	canHold = true;
	int randomIndex = rand() % blocks.size();
	Block block = blocks[randomIndex];
	blocks.erase(blocks.begin() + randomIndex);
	return block;
}


std::vector<Block> Game::GetAllBlocks()
{
	std::vector<Block> blocks;

	if (isSZBlock) {
		blocks = { SBlock(), ZBlock() };
	}
	else if (bigBlockEffect) {
		blocks = { BigOBlock(), BigLBlock(), BigJBlock(), BigSBlock(), BigZBlock(), BigTBlock(), BigIBlock() };
	}
	else if (isLineBlock) {
		blocks = { IBlock() };
	}
	else if (isPentrix) {
		blocks = { PenTBlock(), PBlock(), PenIBlock(), UBlock(), PenSBlock(), PenZBlock(), PenLBlock(), PenZBlock()};
	}
	else if (gameState == CHAOS_MOD) {
		blocks = { IBlock(), JBlock(), SBlock(), TBlock(), LBlock(), ZBlock(), OBlock(), FBlock(), DotBlock(), CommaBlock() };
	}
	else {
		blocks = { IBlock(), JBlock(), SBlock(), TBlock(), LBlock(), ZBlock(), OBlock() };
	}

	return blocks;
}



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
		nextBlock.Draw(525, 245, false);
		break;
	case 11:
		nextBlock.Draw(530, 230, false);
		break;

	default:
		nextBlock.Draw(555, 230, false);
		break;
	}
}


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

void Game::HoldBlock()
{
	
	if (!gameOver && canHold)
	{
		if (heldBlock)
		{
			
			
				Block temp = currentBlock;
				currentBlock = holdBlock;
				holdBlock = temp;

				currentBlock.rowOffSet = 0;
				currentBlock.colOffSet = 3;

				holdBlock.heldRotate();

				canHold = false;
			
			
		}
		else if (!gameOver && !heldBlock)
		{
			holdBlock = currentBlock;
			currentBlock = nextBlock; 
			nextBlock = GetRandomBlock();

			holdBlock.heldRotate();
			currentBlock.rowOffSet = 0;
			currentBlock.colOffSet = 3;
			
			heldBlock = true;
			canHold = false;
		}

		switch (holdBlock.id)
		{
		case 3:
			holdBlock.rowOffSet = 1;
			holdBlock.colOffSet = 2;
			break;

		case 4:
			holdBlock.rowOffSet = 2;
			holdBlock.colOffSet = 3;
			break;
		case 8:
			holdBlock.rowOffSet = 2;
			holdBlock.colOffSet = 3;
			break;
		case 9:
			holdBlock.rowOffSet = 1;
			holdBlock.colOffSet = 2;
			break;
		case 10:
			holdBlock.rowOffSet = 3;
			holdBlock.colOffSet = 3;
			break;
		case 11:
			holdBlock.rowOffSet = 2;
			holdBlock.colOffSet = 3;
			break;

		default:
			holdBlock.rowOffSet = 2;
			holdBlock.colOffSet = 3;
			break;
		}
	
		PlaySound(rotateSound);
	}
	
}

//Method that handle the move function of the kyeboard
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

bool Game::isOutofBound()
{
	std::vector<Position> tiles = currentBlock.GetCellPosition();
	for (Position item : tiles)
	{
		if (grid.isOutOfBound(item.row, item.col))
		{
			return true;
		}
	}
	return false;
}

//Method that update the score when clear the lines
void Game::updateScore(int lineClear, int movePoint)
{
	switch (lineClear)
	{
	case 1:
		score += 100;
		break;
	case 2:
		score += 300;
		break;
	case 3:
		score += 500;
		break;
	case 4:
		score += 1000;
		break;
	default:
		break;
	}

	score += movePoint;
}

bool Game::BlockFits()
{
	std::vector<Position> tiles = currentBlock.GetCellPosition();
	for (Position items:tiles)
	{
		if (grid.isCellEmpty(items.row, items.col) == false)
		{
			return false;
		}
	}
	return true;
}

void Game::LockBlock()
{
	std::vector<Position> tiles = currentBlock.GetCellPosition();
	for (Position item : tiles)
	{
		grid.grid[item.row][item.col] = currentBlock.id;
	}
	currentBlock = nextBlock;
	if (BlockFits() == false)
	{
		gameOver = true;
		PlaySound(gameOverSound);
		StopMusicStream(music);

		holdBlock = Block();
		heldBlock = false;
		canHold = true;
	}

	nextBlock = GetRandomBlock();
	int rowClear = grid.ClearFullRow();
	if (rowClear > 0)
	{
		PlaySound(clearSound);
		updateScore(rowClear, 0);
	}
	
}

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



void Game::Reset()
{
	
	grid.Initialize();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();

	holdBlock = Block();
	heldBlock = false;
	canHold = true;
	
	score = 0;
	StopMusicStream(music);
}


