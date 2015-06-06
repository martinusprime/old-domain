#pragma once

#include <random>

class Random {
public:
    static int get_int(int min, int max)
    {
        static std::random_device rd;     // only used once to initialise (seed) engine
        static std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
        static std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased

        return uni(rng);
    }

    static float get_float(float min, float max)
    {
        static std::tr1::mt19937 eng;  // a core engine class 
        static std::tr1::normal_distribution<float> dist(min, max);

        return dist(eng);
    }
 };