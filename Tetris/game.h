#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game
{
public:
	Game();
	~Game();
	int score;

	void Draw();
	void HandleInput();
	void HoldBlock();
	void MoveBlockDown();
	void Reset();

	bool gameOver;
	bool heldBlock;
	bool canHold;

	std::vector<Block> GetAllBlocks();
	Block holdBlock;

	Music music;

private:
	double lockDelay = 0.05;
	double lockTime = 0;
	int moveCounter = 0;
	int moveLimit = 5;

	Grid grid;

	void MoveBlockLeft();
	void MoveBlockRight();
	void RotateBlock();
	void LockBlock();
	void updateScore(int lineClear, int movePoint);

	bool isOutofBound();
	bool BlockFits();

	std::vector<Block> blocks;

	Block GetRandomBlock();
	Block currentBlock;
	Block nextBlock;
	

	Sound rotateSound;
	Sound clearSound;
	Sound gameOverSound;
};

