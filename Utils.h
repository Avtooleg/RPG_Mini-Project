#ifndef RPG_MINIPROJECT_UTILS_H
#define RPG_MINIPROJECT_UTILS_H

#include <random>
#include <ctime>
#include <algorithm>

class ICreature;

//Проверяет удачу
bool luck_check(int luck);
//Определяет урон, наносимый существом (игроком).
//Планируются аналоги для защиты и уклонения

//Точка на поле
struct position {
    int x;
    int y;

    bool operator<(position pos) const;
};

enum class Exceptions{
    FORBIDDEN_MOVE = 1,
    NOT_ENOUGH_POINTS,
    QUIT
};

enum class Attack_results{
    HIT = 1,
    DEFENDED,
    EVADED,
    CRIT
};

struct damage_result{
    int power;
    Attack_results callback;
};

damage_result get_damage(ICreature* predator, ICreature* target);

int sign(float val);


bool is_in(char x, const std::vector<char>& vec);

int get_random_int(int min, int max);

int get_view_dist(int perc);

#endif //RPG_MINIPROJECT_UTILS_H