#include "block.h"

Block::Block()
{
    cellSize = 30;
    rotationState = 0;
    colors = GetCellColors(); 
    rowOffset = 0;
    colOffset = 0;
    Move(0,3);
}

void Block::Draw(int offsetX, int offsetY)
{
    std::vector<Position> pos = GetCellPosition();
    for (Position p : pos)
    {
        DrawRectangle(p.col * cellSize + offsetX, p.row * cellSize + offsetY, cellSize - 1, cellSize - 1, colors[id]);
    }
}

void Block::Move (int rows, int cols)
{
    rowOffset += rows;
    colOffset += cols;
}

std::vector<Position> Block::GetCellPosition()
{
    std::vector<Position> pos = cells[rotationState];
    std::vector<Position> movedPos;
    for (Position p : pos)
    {
        Position newPos = Position(p.row + rowOffset, p.col + colOffset);
        movedPos.push_back(newPos);
    }

    return movedPos;
}


void Block::Rotate()
{
    rotationState++;
    if(rotationState == (int)cells.size())
    {
        rotationState = 0;
    }
}

void Block::UndoRotate()
{
    rotationState--;
    if(rotationState == -1)
    {
        rotationState = cells.size() - 1;
    }
}