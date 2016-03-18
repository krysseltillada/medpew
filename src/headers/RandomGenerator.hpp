#ifndef RANDOM_GENERATOR
#define RANDOM_GENERATOR

#include <random>

#include <SFML/Graphics.hpp>

#include <windows.h>

#include <iostream>

class RandomGenerator {
public:

    RandomGenerator () :
        rEngine (GetTickCount ()) { }

    RandomGenerator (const int &lb, const int &ub) :
        lowerBound (lb), upperBound (ub), rEngine (GetTickCount ()),
        range (lowerBound, upperBound) { }


    int generate () {
       return range (rEngine);
    }

    int generate (const int &lb, const int &ub) {
        static std::uniform_int_distribution <int> r (lb, ub);
        static std::default_random_engine rE (GetTickCount ());
        return r (rE);
    }



private:
    unsigned int lowerBound;
    unsigned int upperBound;

    std::default_random_engine rEngine;
    std::uniform_int_distribution <int> range;

};


#endif // RANDOM_GENERATOR
