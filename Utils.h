#ifndef RPG_MINIPROJECT_UTILS_H
#define RPG_MINIPROJECT_UTILS_H

#include <random>
#include <ctime>
#include <algorithm>

class ICreature;

//Определяет урон, наносимый существом (игроком).
//Планируются аналоги для защиты и уклонения
int get_damage(ICreature &creature);

//Точка на поле
struct position {
    int x;
    int y;

    bool operator<(position pos) const;
};

int sign(float val);


bool is_in(char x, const std::vector<char>& vec);

int get_random_int(int min, int max);

int get_view_dist(int perc);

#endif //RPG_MINIPROJECT_UTILS_H