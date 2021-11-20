#ifndef RPG_MINIPROJECT_MAP_H
#define RPG_MINIPROJECT_MAP_H


#include <vector>
#include <string.h>
#include <map>

class ICreature;
class Player;
struct position;

const std::vector<char> forbidden_chars = {'^', 'P', 'W', 'A', 'S'};
const int max_def = 1e9;

typedef std::vector<std::string> space;

position get_random_position(int map_size, int forbidden_rad, position center);

//Координаты задаются от верхнего левого угла
class Map{
public:

    Map(std::vector<std::string> _map,
        std::vector<ICreature> &low_level,
        std::vector<ICreature> &middle_level,
        std::vector<ICreature> &high_level,
        int low_rad,
        int middle_rad,
        int high_rad);

    space get_area (position pos, int rad);
    char get_init_value(position pos);
    char get_value(position pos);
    position add_monsters(char marker, int forbidden_rad, position center, std::vector<ICreature> &monsters);
    void map_update(std::vector<ICreature> &creatures, Player player);
    void map_monster_update(position old_pos, position new_pos, char marker);

private:

    int map_size;
    space my_start_map;
    space my_map;
    std::map<position, ICreature&> my_monsters;

};

#endif //RPG_MINIPROJECT_MAP_H
