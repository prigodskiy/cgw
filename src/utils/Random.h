#pragma once
#include <random>

class Random
{
public:
    static void init(unsigned int seed = 0);
    static float range(float min, float max);
    static float value();
    static float* color();

private:
    static std::mt19937 generator;
};