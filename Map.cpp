#include "Map.h"
#include "Utils.h"
#include "Creature.h"
#include "Player.h"

position get_random_position(int map_size, int forbidden_rad, position center){
    float randx = static_cast<float> (get_random_int(-max_def, max_def)/max_def); //Число между минус единицей и единицей
    float randy = static_cast<float> (get_random_int(-max_def, max_def)/max_def);
    int dx = static_cast<int> (randx*(map_size/2 - forbidden_rad) + sign(randx)*forbidden_rad); //Проецирование на отрезок [forbidden_rad, map_size/2]
    int dy = static_cast<int> (randy*(map_size/2 - forbidden_rad) + sign(randy)*forbidden_rad);
    position pos;
    pos.x = center.x + dx;
    pos.y = center.y + dy;
    return pos;
}

position Map::add_monsters(char marker, int forbidden_rad, position center, std::vector<ICreature> &monsters){ //TODO: What return ??
    for(int i = 0; i<monsters.size(); i++){
        while(true) {
            position pos = get_random_position(map_size, forbidden_rad, center);
            if (!is_in(Map::get_init_value(pos), forbidden_chars)) {
                ICreature monster = monsters[i];
                my_map[pos.y][pos.x] = marker;
                my_monsters.insert(std::pair<position, ICreature&>(pos, monster));
                break;
            }
        }
    }
}

Map::Map(space _map,
         std::vector<ICreature> &low_level,
         std::vector<ICreature> &middle_level,
         std::vector<ICreature> &high_level,
         int low_rad,
         int middle_rad,
         int high_rad){
    //Генерация случайного места для слабых мобов. Игрок на старте в центре
    my_start_map = _map;
    my_map = _map;
    map_size = _map.size();
    position center;
    center.x = map_size/2;
    center.y = map_size/2;

    my_map[center.y][center.x] = 'P';

    add_monsters('W', low_rad, center, low_level);
    add_monsters('A', middle_rad, center, middle_level);
    add_monsters('S', high_rad, center, high_level);
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
        std::string str = "";
        for(int x = pos.x - rad; x <= pos.x + rad; x++){
            str += my_map[y][x];
        }
        area.push_back(str);
    }
    return area;
}

void Map::map_update(std::vector<ICreature> &creatures, Player player) {
    my_map = my_start_map;
    my_monsters.clear();
    for (int i = 0; i<creatures.size(); i++){
        ICreature monster = creatures[i];
        position pos = creatures[i].get_pos();
        my_map[pos.y][pos.x] = creatures[i].get_marker();
        my_monsters.insert({pos, monster});
    };
    position player_pos = player.get_pos();
    my_map[player_pos.y][player_pos.x];
}

void Map::map_monster_update(position old_pos, position new_pos, char marker){
    if (marker != 'P') {
        ICreature monster = my_monsters[old_pos];
        my_monsters.erase(old_pos);
        my_monsters.insert({new_pos, monster});
    };
    my_map[old_pos.y][old_pos.x] = my_start_map[old_pos.y][old_pos.x];
    my_map[new_pos.y][new_pos.x] = marker;
}