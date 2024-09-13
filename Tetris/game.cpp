#include "game.h"
#include "ChaosBlock.cpp"
#include "ChaosEffects.h"
#include "GameState.h"
#include <random>
#include <iostream>
#include <ctime>



Game::Game()
{
	
	srand(time(nullptr));

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
	clearSound = LoadSound("Sound/Clear.wav");
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
	canHold = true;
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

	if (isSZBlock)
	{
		std::vector<Block> SZBlock = { SBlock(), ZBlock() };
		int index = rand() % SZBlock.size();
		return SZBlock[index];
	}

	if (isPentrix)
	{
		std::vector<Block> PentrixBlock = { PenTBlock(), PBlock(), PenIBlock(), UBlock(), PenSBlock(), PenZBlock(), PenLBlock(), PenJBlock() };
		int index = rand() % PentrixBlock.size();
		return PentrixBlock[index];
	}

	if (isRain)
	{
		std::vector<Block> rainBlock = { DotBlock(),CommaBlock()};
		int index = rand() % rainBlock.size();
		return rainBlock[index];
	}

	if (blocks.empty())
	{
		blocks = GetAllBlocks();
	}
	
	int randomIndex = rand() % blocks.size();
	Block block = blocks[randomIndex];
	blocks.erase(blocks.begin() + randomIndex);
	return block;
}


std::vector<Block> Game::GetAllBlocks()
{
	std::vector<Block> blocks;

	if (gameState == CHAOS_MOD) {
		blocks = { IBlock(), JBlock(), SBlock(), TBlock(), LBlock(), ZBlock(), OBlock(), FBlock(), };
	}
	else {
		blocks = { IBlock(), JBlock(), SBlock(), TBlock(), LBlock(), ZBlock(), OBlock() };

		if (isSZBlock) {
			blocks.insert(blocks.end(), { SBlock(), ZBlock() });
		}
		if (bigBlockEffect) {
			blocks.insert(blocks.end(), { BigOBlock(), BigLBlock(), BigJBlock(), BigSBlock(), BigZBlock(), BigTBlock(), BigIBlock() });
		}
		if (isLineBlock) {
			blocks.push_back(IBlock());
		}
		if (isPentrix) {
			blocks.insert(blocks.end(), { PenTBlock(), PBlock(), PenIBlock(), UBlock(), PenSBlock(), PenZBlock(), PenLBlock(), PenJBlock()});
		}
		if (isRain)
		{
			blocks.insert(blocks.end(), { DotBlock(), CommaBlock()});
		}
	}

	return blocks;
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

		HoldBlockOffSet();
		
		PlaySound(rotateSound);
	}
	
}

//Method that handle the move function of the kyeboard

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
