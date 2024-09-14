#include "particle.h"


const int screenWidth = 300;
const int screenHeight = 600;

Particle::Particle(Vector2 pos, Color c, float particleSize)
{
    position = pos;
    color = c;
    size = particleSize;
    int randomMultiplier = GetRandomValue(1, 5);
    gravity = .98f * randomMultiplier;
    speed = 0.f;
    outOfScreen = false;
    
}

bool Particle::IfOutOfScreen()
{
    if(position.y >= screenHeight + 100)
    {
        outOfScreen = true;
    }
    else
    {
        outOfScreen = false;
    }
    return outOfScreen;
}

void Particle::Draw()
{   
    if(!outOfScreen)
    {
        DrawRectangle(position.x, position.y, size, size, color);
    }
}

void Particle::Update(float deltaTime)
{
    speed += gravity;
    position.y += speed * deltaTime;
}
