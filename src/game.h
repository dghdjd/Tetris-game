#pragma once 
#include "grid.h"
#include "blocks.cpp"
#include "particle_system.h"

class Game
{
    public:
    Game();
    ~Game();
    void Draw();
    void HandleInput();
    
    void MoveBlockDown();
    
    bool gameOver;
    bool shouldStartGame;
    int score;

    Music music;

    void CreateUI(Font font);
    void updateParticles(float deltaTime);

private:
    void MoveBlockLeft();
    void MoveBlockRight();
    Block GetRandomBlock();
    std::vector<Block> ResetBlocks();
    bool IsBlockOutside();
    void RotateBlock();
    void LockBlock();
    bool BlockFits();
    void RestartGame();
    void UpdateScore(int linesCleared, int moveDownPoints);
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    Grid grid;
    Sound rotateSound;
    Sound clearSound;
    ParticleSystem particleSystem;
};