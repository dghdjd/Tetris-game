#pragma once
#include "particle.h"
#include "vector"
#include "position.h"
#include "colors.h"
class ParticleSystem
{
    public:
    void SpawnParticles(int row, int col, int colorId);
    void update(float deltaTime);
    void draw();


    private:
    std::vector<Particle> particles;
    std::vector<Color> colors = GetCellColors();


};