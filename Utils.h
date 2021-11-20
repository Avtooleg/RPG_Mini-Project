#ifndef RPG_MINIPROJECT_UTILS_H
#define RPG_MINIPROJECT_UTILS_H

#include <random>
#include <ctime>
#include <algorithm>



std::mt19937 mersenne(time(0));

class ICreature;

int get_damage(ICreature &creature);

struct position{
    int x;
    int y;
};

bool operator<(const position pos1, const position pos2){
    return (pos1.x*pos1.x + pos1.y*pos1.y < pos2.x*pos2.x + pos2.y*pos2.y);
}


int sign(float x){
    return (x>=0) - (x<0);
};


bool is_in(char x, const std::vector<char>& vec){
    return std::find(vec.begin(), vec.end(), x)!=vec.end();
}

int get_random_int(int min, int max){
    static const unsigned int mersenne_max = ~0;
    unsigned int initial = mersenne();
    static const double fraction = 1.0 / (static_cast<double>(mersenne_max) + 1.0);
    return static_cast<int>(initial * fraction * (max - min + 1) + min);
};

#endif //RPG_MINIPROJECT_UTILS_H