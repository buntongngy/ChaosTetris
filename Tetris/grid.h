#pragma once
#include <vector>
#include <raylib.h>


class Grid {

public:
    Grid();
    void Initialize();
    void Print();
    void Draw();
    bool isOutOfBound(int row, int cols);
    bool isCellEmpty(int row, int cols);
    int ClearFullRow();
    int grid[20][10];

private:
   
    int numRows;
    int numCols;
    int cellSize;
    std::vector<Color> colors;
    bool isRowFull(int row);
    void clearRow(int row);
    void MoveRowDown(int row, int numRow);
};


