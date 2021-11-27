#include "Utils.h"
#include "Creature.h"

std::mt19937 mersenne(time(NULL));

int get_damage(ICreature &creature){
    creature.set_hp(creature.get_hp() - 1);
    return 0;
};//TODO: return some damage value

bool position::operator<(position pos) const {
    return (x * x + y * y < pos.x * pos.x + pos.y * pos.y);
}

int sign(float val){
    return (val>=0) - (val<0);
};

bool is_in(char x, const std::vector<char>& vec){
    return std::find(vec.begin(), vec.end(), x)!=vec.end();
};

int get_random_int(int min, int max){
    static const unsigned int mersenne_max = ~0;
    unsigned int initial = mersenne();
    static const double fraction = 1.0 / (static_cast<double>(mersenne_max) + 1.0);
    return static_cast<int>(initial * fraction * (max - min + 1) + min);
};

int get_view_dist(int perc){
    return static_cast<int>(cbrt(perc)*2);
}