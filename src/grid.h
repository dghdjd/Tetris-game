#pragma once
#include "vector"
#include "raylib.h"
#include "particle_system.h"
class Grid{

    public:

    int grid[20][10];
    Grid();
    void initialize();
    void print();
    void Draw();
    bool IsCellOutside(int row, int col);
    bool IsCellEmpty(int row, int col);
    int ClearFullRow(ParticleSystem& ps);


    private:
    int numRows;
    int numCols;
    int cellSize;
    std::vector<Color> colors;
    bool IsRowFull(int row);
    void ClearRow(int row, ParticleSystem& ps);
    void MoveRowDown(int row, int numRows);


};