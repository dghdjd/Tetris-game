#include <raylib.h>
#include "game.h"
#include "colors.h"
#include "iostream"

double lastUpdateTime = 0;
bool ShouldMoveBlockDown(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main()
{
    Color backgroundColor = {44, 44, 127, 255};
    const int uiWidth = 200;
    const int uiHeigt = 20;
    const int screenWidth = 300;
    const int screenHeight = 600;
    InitWindow(screenWidth + uiWidth, screenHeight + uiHeigt, "Tetris");
    SetTargetFPS(60);


    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

    Game game = Game();
    while (!WindowShouldClose())
    {
        UpdateMusicStream(game.music);

        game.HandleInput();
        if(ShouldMoveBlockDown(0.2))
        {
            game.MoveBlockDown();
        }
        
        BeginDrawing();
        ClearBackground(backgroundColor);
        
        game.CreateUI(font);
        game.updateParticles(GetFrameTime());
        game.Draw();
        EndDrawing();
    }

    CloseWindow();

    
    return 0;
}