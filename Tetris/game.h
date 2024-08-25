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
	void DropBlock();
	void MoveBlockDown();
	void updateScore(int lineClear, int movePoint);
	void Reset();
	void SetSpeed(double speed) { this->speed = speed; }
	void SetBigBlockMod(bool isActive);
	void SetLineBlock(bool isActive);
	void SetSZBlock(bool isActive);
	void ReverseControl(bool isActive);



	double GetSpeed() const {
		return speed;
	}

	bool gameOver;
	bool heldBlock;
	bool canHold;
	bool canRotate;
	bool canDrop;
	bool bigBlockEffect = false;
	bool isLineBlock = false;
	bool isSZBlock = false;
	bool reverseControl = false;

	std::vector<Block> GetAllBlocks();
	
	Block holdBlock;
	Block previousBlock;
	Block GetRandomBlock();
	Block currentBlock;
	Block nextBlock;

	Music music;

	static double chaosTimer;

private:
	double lockDelay = 0.05;
	double lockTime = 0;
	double speed = 0.2;
	int moveCounter = 0;
	int moveLimit = 5;

	Grid grid;

	void MoveBlockLeft();
	void MoveBlockRight();

	void RotateBlock();
	void LockBlock();
	

	bool isOutofBound();
	bool BlockFits();
	bool isDropping;

	std::vector<Block> blocks;



	Sound rotateSound;
	Sound clearSound;
	Sound gameOverSound;
};

