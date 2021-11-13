#include "Creature.h"
#include <vector>
#include <string.h>

const std::string *arr = {

};

struct position{
    double x;
    double y;
};

class Map{
public:

    Map(std::vector<std::string> map);
    std::vector<std::string> get_slice (position pos, int rad)

private:

    std::vector<std::string> map;

};

Map gen_map(std::vector<ICreature> light, std::vector<ICreature> mid, std::vector<ICreature> hard, int mid_rad, int hard_rad);

#ifndef RPG_MINIPROJECT_MAP_H
#define RPG_MINIPROJECT_MAP_H

#endif //RPG_MINIPROJECT_MAP_H
