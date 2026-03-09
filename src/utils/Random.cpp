#include "Random.h"

std::mt19937 Random::generator;

void Random::init(unsigned int seed)
{
    if (seed == 0)
    {
        std::random_device rd;
        seed = rd();
    }
    generator.seed(seed);
}

float Random::range(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(generator);
}

float Random::value()
{
    return range(0.0f, 1.0f);
}

float* Random::color()
{
    static float col[3];
    col[0] = value();
    col[1] = value();
    col[2] = value();
    return col;
}