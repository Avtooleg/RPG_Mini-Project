#ifndef RPG_MINIPROJECT_FRONTEND_H
#define RPG_MINIPROJECT_FRONTEND_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "Map.h"

char get_player_input(const std::vector<int> &keys);
void map_output(Map map, position center, int rad);

#endif //RPG_MINIPROJECT_FRONTEND_H
