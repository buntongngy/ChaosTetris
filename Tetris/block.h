#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "color.h"


class Block
{
public:
	Block();
	void Draw(int xOffSet, int yOffSet);
	void Move(int row, int cols);
	void Rotate();
	void undo_Rotate();
	void heldRotate();
	int id;
	std::map<int, std::vector<Position>> cells;
	std::vector<Position> GetCellPosition();
	int rowOffSet;
	int colOffSet;
	int cellSize;

private:
	
	int rotationState;
	std::vector<Color> colors;
	
};