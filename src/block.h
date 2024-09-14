#pragma once
#include "vector"
#include "map"
#include "position.h"
#include "colors.h"

class Block
{
public:
    Block();
    void Draw(int offsetX, int offsetY);
    void Move(int rows, int cols);
    std::vector<Position> GetCellPosition();
    int id;
    std::map<int, std::vector<Position>> cells;
    void Rotate();
    void UndoRotate();



private:
    int cellSize;
    int rotationState;
    std::vector<Color> colors;
    int rowOffset;
    int colOffset;

};