#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <random>

class Randomizer

{
private:
    /* data */
public:
    static int genRand(int min, int max);
  
  
};

int Randomizer::genRand(int min, int max){

    std::random_device dev;
    std::mt19937 eng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(min,max);
    return distribution(eng);
}


#endif