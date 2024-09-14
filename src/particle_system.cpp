#include"particle_system.h"


const int blockSize = 30;

void ParticleSystem::SpawnParticles(int row, int col, int colorId)
{
    int gapSize = 1;  
    float availableSpace = 29.0f;  
    int particleNum = 5; 
    

    float particleSize = (availableSpace - (gapSize * (particleNum - 1))) / particleNum;


    for (int j = 0; j < particleNum; j++)
    {
        for (int i = 0; i < particleNum; i++)
    {
        float x = ((float)col * blockSize + 11) + (particleSize + gapSize) * i;
        float y = ((float)row * blockSize + 11) + (particleSize + gapSize) * j;
        particles.push_back(Particle(Vector2{x, y}, colors[colorId], particleSize));
    }
    }
    


}

void ParticleSystem::update(float deltaTime)
{
    if(particles.size() == 0) return;
    for (int i = particles.size() - 1; i >= 0; i--)
    {
        
        if(particles[i].IfOutOfScreen())
        {
            particles.erase(particles.begin() + i);
        }
        else
        {
            particles[i].Update(deltaTime);
        }
    }
}

void ParticleSystem::draw()
{
    if(particles.size() == 0) return;
    for (Particle p : particles)
    {
        p.Draw();
    }
}
