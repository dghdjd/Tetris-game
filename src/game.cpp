#include "game.h"
#include <random>

Game::Game()
{
    grid = Grid();
    blocks = ResetBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    shouldStartGame = false;
    score = 0;
    InitAudioDevice();
    music = LoadMusicStream("Sounds/music.mp3");
    rotateSound = LoadSound("Sounds/rotate.mp3");
    clearSound  = LoadSound("Sounds/clear.mp3");
    PlayMusicStream(music);
}

Game::~Game()
{
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
}



Block Game::GetRandomBlock()
{
    if (blocks.empty())
    {
        blocks = ResetBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Block> Game::ResetBlocks()
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw(11,11);
    particleSystem.draw();
    switch (nextBlock.id)
    {
        case 3: //IBlock
        nextBlock.Draw(255, 290);
        break;

        case 4: //OBlock
        nextBlock.Draw(255, 280);
        break;

        default:
        nextBlock.Draw(270, 270);
        break;
    }
}

void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();
    if(gameOver && keyPressed != 0)
    {
        gameOver = false;
        RestartGame();
    }

    if (keyPressed) shouldStartGame = true;

    switch (keyPressed)
    {
    case KEY_LEFT:
        MoveBlockLeft();
        break;

    case KEY_RIGHT:
        MoveBlockRight();
        break;

    case KEY_DOWN:
        MoveBlockDown();
        UpdateScore(0,1);
        break;

    case KEY_UP:
        RotateBlock();
        break;
    }
}

void Game::CreateUI(Font font)
{
    DrawTextEx(font, "SCORE", {360, 15}, 38, 2, raylibWhite);
        DrawTextEx(font, "NEXT", {370, 175}, 38, 2, raylibWhite);
        if (gameOver)
        DrawTextEx(font, "GAME OVER", {320, 450}, 38, 2, raylibWhite);
        else if (!shouldStartGame)
        {
            DrawTextEx(font, "PRESS ANY", {315, 450}, 38, 2, raylibWhite);
            DrawTextEx(font, "KEY", {370, 480}, 38, 2, raylibWhite);
            DrawTextEx(font, "TO START", {330, 510}, 38, 2, raylibWhite);
        }
        else 
        DrawTextEx(font, "START!", {355, 450}, 38, 2, raylibWhite);

        DrawTextEx(font, "SCORE", {360, 15}, 38, 2, raylibWhite);


        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);

        char scoreText[10];
        sprintf(scoreText, "%d", score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

        DrawTextEx(font, scoreText, {320 + (170 - textSize.x)/2, 65}, 38, 2, raylibWhite);// 170 is the width of the background rectangle
        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);

}

void Game::updateParticles(float deltaTime)
{
    
    particleSystem.update(deltaTime);
}

void Game::MoveBlockLeft()
{
    if (!gameOver)
    {
        currentBlock.Move(0, -1);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0, 1);
        }
    }
}

void Game::MoveBlockRight()
{
    if (!gameOver)
    {
        currentBlock.Move(0, 1);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0, -1);
        }
    }
}

void Game::MoveBlockDown()
{
    if (!gameOver && shouldStartGame)
    {
        currentBlock.Move(1, 0);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(-1, 0);
            LockBlock();
        }
    }
}

bool Game::IsBlockOutside()
{
    std::vector<Position> pos = currentBlock.GetCellPosition();
    for (Position p : pos)
    {
        if (grid.IsCellOutside(p.row, p.col))
        {
            return true;
        }
    }
    return false;
}

void Game::RotateBlock()
{
    if (!gameOver)
    {
        currentBlock.Rotate();
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.UndoRotate();
        }
        else 
        {
            PlaySound(rotateSound);
        }
    }
}

void Game::LockBlock()
{
    std::vector<Position> pos = currentBlock.GetCellPosition();
    for (Position p : pos)
    {
        grid.grid[p.row][p.col] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if (BlockFits() == false)
    {
        gameOver = true;
        shouldStartGame = false;
    }
    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRow(particleSystem);
    if(rowsCleared > 0)
    {
        PlaySound(clearSound);
        UpdateScore(rowsCleared, 0);
    }
    
}

bool Game::BlockFits()
{
    std::vector<Position> pos = currentBlock.GetCellPosition();
    for (Position p : pos)
    {
        if (grid.IsCellEmpty(p.row, p.col) == false)
        {
            return false;
        }
    }
    return true;
}

void Game::RestartGame()
{
    grid.initialize();
    blocks = ResetBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
    switch(linesCleared)
    {
        case 1:
        score += 10;
        break;

        case 2:
        score += 30;

        case 3:
        score += 50;
        break;

        default:
        break;
    }

    score += moveDownPoints;
}
