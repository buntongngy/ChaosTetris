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
	int id;
	std::map<int, std::vector<Position>> cells;
	std::vector<Position> GetCellPosition();

private:
	int cellSize;
	int rotationState;
	std::vector<Color> colors;
	int rowOffSet;
	int colOffSet;
};