#include "Map.h"
#include "Utils.h"
#include "Creature.h"
#include "Player.h"
#include <iostream>

position get_random_position(int map_size, int forbidden_rad, position center){
    float randx = static_cast<float> (get_random_int(-max_def, max_def))/max_def; //Число между минус единицей и единицей
    float randy = static_cast<float> (get_random_int(-max_def, max_def))/max_def;
    int dx = static_cast<int> (randx*(map_size/2 - forbidden_rad) + sign(randx)*forbidden_rad); //Проецирование на отрезок [forbidden_rad, map_size/2]
    int dy = static_cast<int> (randy*(map_size/2 - forbidden_rad) + sign(randy)*forbidden_rad);
    position pos;
    pos.x = center.x + dx;
    pos.y = center.y + dy;
    return pos;
}

void Map::add_monsters(int forbidden_rad, position center, std::vector<ICreature*> &monsters){
    for(int i = 0; i<monsters.size(); i++){
        while(true) {
            position pos = get_random_position(map_size, forbidden_rad, center);
            if (!is_in(Map::get_init_value(pos), forbidden_chars)) {
                ICreature *monster = monsters[i];
                monster->set_pos(pos);
                my_map[pos.y][pos.x] = monster->get_marker();
                my_monsters.insert({pos, monster});
                break;
            }
        }
    }
}

void Map::add_player(Player &player) {
    my_player = &player;
}

void Map::add_positional_monsters(std::vector<ICreature *> monsters) {
    for(int i = 0; i<monsters.size(); i++){
        ICreature *monster = monsters[i];
        position pos = monster->get_pos();
        my_map[pos.y][pos.x] = monster->get_marker();
        my_monsters.insert({pos, monster});
    }
}

Map::Map(space _map){
    //Генерация случайного места для слабых мобов. Игрок на старте в центре
    my_start_map = _map;
    my_map = _map;
    map_size = _map.size();
    position center;
    center.x = map_size/2;
    center.y = map_size/2;
    map_center = center;

    my_map[center.y][center.x] = 'P';
    my_player = NULL;

    //Some problems with generating map and monsters because of cross-reference
    /*add_monsters('W', low_rad, center, low_level);
    add_monsters('A', middle_rad, center, middle_level);
    add_monsters('S', high_rad, center, high_level);*/
}

char Map::get_value(position pos) {
    return my_map[pos.y][pos.x];
}

char Map::get_init_value(position pos) {
    return my_start_map[pos.y][pos.x];
}

space Map::get_area (position pos, int rad){
    space area;
    for (int y = std::max(pos.y-rad, 0);
    y <= std::min(pos.y+rad, map_size - 1); y++)
    {
        std::string str = "";
        for(int x = std::max(pos.x - rad, 0);
        x <= std::min(pos.x + rad, static_cast<int> (my_start_map[0].size() - 1)); x++)
        {
            str += my_map[y][x];
        }
        area.push_back(str);
    }
    return area;
}

position Map::get_center() {
    return map_center;
}

int Map::get_size(){
    return map_size;
}

position Map::get_player_pos() {
    return my_player->get_pos();
}

ICreature* Map::get_player_race_pointer() {
    return my_player->get_race_pointer();
}

std::vector<ICreature*> Map::get_monsters_around(position center){
    std::vector<ICreature*> found_monsters = {};
    position curr_pos;
    static const int low = 0x0001;
    static const int high = 0x0002;
    std::cout << "x  y\n";
    for(int i = 0; i<4; i++){
        bool  low_bit = i & low;
        bool high_bit = i & high;
        curr_pos.x = center.x + high_bit*(low_bit - !low_bit);
        curr_pos.y = center.y + !high_bit*(low_bit - !low_bit);
        std::cout << curr_pos.x << ' ' << curr_pos.y << '\n';
        if(my_monsters.find(curr_pos) != my_monsters.end()){
            found_monsters.push_back(my_monsters[curr_pos]);
        }
        else{
            found_monsters.push_back(NULL);
        }
    }
    return found_monsters;
}

void Map::map_update(std::vector<ICreature> &creatures, Player player) {
    my_map = my_start_map;
    my_monsters.clear();
    for (int i = 0; i<creatures.size(); i++){
        ICreature *monster = &creatures[i];
        position pos = creatures[i].get_pos();
        my_map[pos.y][pos.x] = creatures[i].get_marker();
        my_monsters.insert({pos, monster});
    };
    position player_pos = player.get_pos();
    my_map[player_pos.y][player_pos.x];
}

void Map::map_monster_update(bool deletion, char marker, position *old_pos, position *new_pos){
    if (marker != 'P') {
        ICreature *monster = my_monsters[*old_pos];
        my_monsters.erase(*old_pos);
        if (!deletion) {
            my_monsters.insert({*new_pos, monster});
        }
    };
    if(my_monsters.find(*old_pos) != my_monsters.end()){
        my_map[old_pos->y][old_pos->x] = my_monsters[*old_pos]->get_marker();
    }
    else{
        my_map[old_pos->y][old_pos->x] = my_start_map[old_pos->y][old_pos->x];
    }
    if (!deletion) {
        my_map[new_pos->y][new_pos->x] = marker;
    }
}