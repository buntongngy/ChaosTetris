#include "grid.h"
#include "color.h"
#include "GameState.h"
#include <iostream>

Grid::Grid() {

	numRows = 20;
	numCols = 12;
	cellSize = 30;
	Initialize();
	colors = GetCellColor();
}

void Grid::Initialize() {
	for (int row = 0; row < numRows; row++) {
		for (int colum = 0; colum < numCols; colum++) {
			grid[row][colum] = 0;
		}
	}
}

void Grid::Print()
{
	for (int row = 0; row < numRows; row++) {
		for (int colum = 0; colum < numCols; colum++) {
			std::cout << grid[row][colum] << " ";
		}
		std::cout << std::endl;
	}
}

void Grid::Draw()
{
	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols; col++) {
			int cellValue = grid[row][col];
			DrawRectangle(col * cellSize + 220, row * cellSize + 11, cellSize - 1, cellSize - 1, colors[cellValue]);
		}
	}
}

bool Grid::isOutOfBound(int row, int cols)
{
	if (row >= 0 && row < numRows && cols >= 0 && cols < numCols) {
		return false;
	} 
	return true;
}

bool Grid::isCellEmpty(int row, int cols)
{
	if (grid[row][cols] == 0)
	{
		return true;
	}
	return false;
}

int Grid::ClearFullRow()
{
	int complete = 0;
	for (int row = numRows - 1; row >= 0; row--)
	{
		if (isRowFull(row))
		{
			clearRow(row);
			complete++;
		}
		else if (complete > 0) {
			MoveRowDown(row, complete);
		}
	}
	return complete;
}

bool Grid::isRowFull(int row)
{
	for (int col = 0; col < numCols; col++)
	{
		if (grid[row][col] == 0)
		{
			return false;
		}
		
	}
	return true;
}

void Grid::clearRow(int row)
{
	for (int col = 0; col < numCols; col++)
	{
		grid[row][col] = 0;
	}
}

void Grid::MoveRowDown(int row, int numRow)
{
	for (int col = 0; col < numCols; col++)
	{
		grid[row + numRow][col] = grid[row][col];
		grid[row][col] = 0;
	}
}


