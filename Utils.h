#include <random>
#include <ctime>
#include <algorithm>

std::mt19937 mersenne(time(0));

int sign(float x){
    return (x>=0) - (x<0);
}

bool is_in(char x, std::vector<char> *vec){
    return std::find(vec->begin(), vec->end(), x)!=vec->end();
}

int get_random_int(int min, int max){
    static const unsigned int mersenne_max = ~0;
    unsigned int initial = mersenne();
    static const double fraction = 1.0 / (static_cast<double>(mersenne_max) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
};

#ifndef RPG_MINIPROJECT_RANDOMIZER_H
#define RPG_MINIPROJECT_RANDOMIZER_H

#endif //RPG_MINIPROJECT_RANDOMIZER_H
