#ifndef RPG_MINIPROJECT_UTILS_H
#define RPG_MINIPROJECT_UTILS_H

#include <random>
#include <ctime>
#include <algorithm>

class ICreature;

std::mt19937 mersenne(time(0));

//Определяет урон, наносимый существом (игроком).
//Планируются аналоги для защиты и уклонения
int get_damage(ICreature &creature);

//Точка на поле
struct position;

int sign(float val);


bool is_in(char x, const std::vector<char>& vec);

int get_random_int(int min, int max);

#endif //RPG_MINIPROJECT_UTILS_H