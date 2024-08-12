#include "block.h"

Block::Block()
{
	cellSize = 30;
	rotationState = 0;
	colors = GetCellColor();
	rowOffSet = 0;
	colOffSet = 0;
}


void Block:: Draw(int xOffSet, int yOffSet)
{
	std::vector<Position> tiles = GetCellPosition();
	for (Position item : tiles)
	{
		DrawRectangle(item.col * cellSize + xOffSet, item.row * cellSize + yOffSet, cellSize -1, cellSize - 1, colors[id]);
	}
}

void Block::Move(int row, int cols)
{
	rowOffSet += row;
	colOffSet += cols;

}

std::vector<Position> Block::GetCellPosition()
{
	std::vector<Position> tiles = cells[rotationState];
	std::vector<Position> moveTiles;
	for (Position item : tiles)
	{
		Position newPos = Position(item.row + rowOffSet, item.col + colOffSet);
		moveTiles.push_back(newPos);
	}
	return moveTiles;
}

void Block::Rotate()
{
	rotationState++;
	if (rotationState == (int)cells.size()) 
	{
		rotationState = 0;
	}

}

void Block::undo_Rotate()
{

	rotationState--;
	if (rotationState == -1)
	{
		rotationState = cells.size() - 1;
	}
}

void Block::heldRotate()
{
	rotationState = 0;
}
