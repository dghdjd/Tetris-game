#pragma once
#include "raylib.h"
#include "vector"
class Particle{

    public:
    Particle(Vector2 pos, Color c, float particleSize);
    void Update(float deltaTime);
    bool IfOutOfScreen();
    void Draw();



    private:
    Vector2 position;
    float   speed;
    float   gravity;
    float   size;
    Color   color;
    bool    outOfScreen;

};