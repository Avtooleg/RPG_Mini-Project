#include "Map.h"
#include "Utils.h"

position get_random_position(int map_size, int forbidden_rad, position center){
    float randx = static_cast<float> get_random_int(-max_def, max_def)/max_def; //Число между минус единицей и единицей
    float randy = static_cast<float> get_random_int(-max_def, max_def)/max_def;
    int dx = static_cast<int> randx*(map_size/2 - forbidden_rad) + sign(rand_x)*forbidden_rad;
    int dy = static_cast<int> randy*(map_size/2 - forbidden_rad) + sign(rand_x)*forbidden_rad;
    position pos(center.x + dx, center.y + dy);
    return pos;
}

position Map::add_monsters(char marker, int forbidden_rad, std::vector<ICreature> &monsters){
    for(int i = 0; i<monsters.size(); i++){
        while(true) {
            position pos = get_random_position(map_size, low_rad, center);
            if (!is_in(Map::get_init_value(pos), forbidden_chars)) {
                my_map[pos.y][pos.x] = marker;
                break;
            }
        }
    }
}

Map::Map(std::vector<std::string> map,
         std::vector<ICreature> &low_level,
         std::vector<ICreature> &middle_level,
         std::vector<ICreature> &high_level,
         int low_rad,
         int middle_rad,
         int high_rad){
    //Генерация случайного места для слабых мобов. Игрок на старте в центре
    my_start_map = map;
    my_map = map;
    map_size = map.size();
    position center(map_size/2, map_size/2);

    my_map[center.y][center.x] = 'P';

    add_monsters('W', low_rad,low_level);
    add_monsters('A', middle_rad, middle_level);
    add_monsters('S', high_rad, high_level);
}

char Map::get_value(position pos) {
    return my_map[pos.y][pos.x];
}

char Map::get_init_value(position pos) {
    return my_start_map[pos.y][pos.x];
}

space Map::get_area (position pos, int rad){
    space area;
    for (int y = pos.y-rad; y <= pos.y+rad; y++){
        std::string str = ""
        for(int x = pos.x - rad; x <= pos.x + rad; x++){
            str += my_map[y][x];
        }
        area.push_back(str);
    }
    return area;
}

void Map::map_update(std::vector<ICreature> &creatures, Player player) {
    my_map = my_start_map;
    for (int i = 0; i<creatures.size(); i++){
        my_map[creatures[i].get_pos().x][creatures[i].get_pos().y] = creatures[i].get_marker();
    };
    position player_pos = player.get_pos();
    my_map[player_pos.y][player_pos.x];
}

