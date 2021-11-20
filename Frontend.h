#ifndef RPG_MINIPROJECT_FRONTEND_H
#define RPG_MINIPROJECT_FRONTEND_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

class Map;
struct position;

//Список неполный. Ожидаются ещё, как минимум, стартовый и конечный экраны, а также очистка консоли.

//Ожидает нажатия клавишы из keys, и возвращает нажатую. Рассчитан на windows
char get_player_input(const std::vector<int> &keys);
//Выводит кусок карты rad*rad вокруг center
void map_output(Map map, position center, int rad);
#endif //RPG_MINIPROJECT_FRONTEND_H
