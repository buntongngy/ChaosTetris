#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game
{
public:
	Game();
	~Game();
	int score;
	std::vector<Block> GetAllBlocks();
	void Draw();
	void HandleInput();
	void MoveBlockDown();
	bool gameOver;
	Music music;
	void Reset();

private:
	Block GetRandomBlock();
	std::vector<Block> blocks;
	Grid grid;
	void MoveBlockLeft();
	void MoveBlockRight();
	void RotateBlock();
	void LockBlock();

	void updateScore(int lineClear, int movePoint);
	bool BlockFits();
	Block currentBlock;
	Block nextBlock;
	bool isOutofBound();
	Sound rotateSound;
	Sound clearSound;
	Sound gameOverSound;
};

