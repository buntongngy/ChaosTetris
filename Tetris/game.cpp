#include "game.h"
#include <random>

Game::Game()
{
	score = 0;
	grid = Grid();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	gameOver = false;
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
	return { IBlock(), JBlock(), SBlock(), TBlock(),LBlock(), ZBlock(), OBlock(), UBlock(), FBlock(), DotBlock()};
}



void Game::Draw()
{
	grid.Draw();
	currentBlock.Draw(11,11);
	switch (nextBlock.id)
	{
	case 3:
		nextBlock.Draw(255, 280);
		break;

		case 4:
			nextBlock.Draw(255,290);
			break;
		case 8:
			nextBlock.Draw(265, 270);
				break;
		case 9:
			nextBlock.Draw(265, 230);
			break;
		
		default:
			nextBlock.Draw(255, 270);
			break;
	}
}

//Method that handle the user input from the keyboard
void Game::HandleInput()
{	
	
	int keyPress = GetKeyPressed();

	if (gameOver && keyPress != 0)
	{
		gameOver = false;
		Reset();
		PlayMusicStream(music);
	}

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
		updateScore(0,1);
		break;
		case KEY_UP:
		RotateBlock();
		break;
		
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
	}
}

void Game::MoveBlockDown() {
	if (!gameOver)
	{
		currentBlock.Move(1, 0);
		if (isOutofBound() || BlockFits() == false)
		{
			currentBlock.Move(-1, 0);
			LockBlock();
		}
	}
}

void Game::RotateBlock()
{
	if (!gameOver)
	{
		currentBlock.Rotate();
		if (isOutofBound() || BlockFits() == false)
		{
			currentBlock.undo_Rotate();
		}
		else
		{
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
	score = 0;
	StopMusicStream(music);
}