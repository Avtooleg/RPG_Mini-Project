#include <iostream>
#include "Frontend.h"
#include <vector>
#include "Player.h"
#include "Creature.h"
#include "Map.h"
#include <windows.h>

bool run = true;

void quit(){
    run = false;
}

int main() {
    std::vector<int> stats = {1, 1, 1, 1, 1, 1};
    Map *global_map;
    std::vector<ICreature> creatures = {Test_creature('M', stats, *global_map)};
    std::cout << "We have built creatures!";
    space _map = {
            "^^###^%%%#",
            "^#####%%##",
            "^^#####%##",
            "^^^#######",
            "^^^^^##^^^",
            "^^^^^#^^^^",
            "^%%^###%%^",
            "%%%####%%%",
            "%######%%#",
            "^^####^^^^"
    };
    std::vector<ICreature> pass_vec = {};
    *global_map = Map(_map, creatures, pass_vec, pass_vec, 1, 0, 0);
    Test_creature race('P', stats, *global_map);
    Player player(race);
    std::cout << "All has built!";
    while(run){
        map_output(*global_map, player.get_pos(), 5);
        for (int i = 0; i < creatures.size(); i++){
            Sleep(500);
            clear_console();
            creatures[i].do_turn();
            map_output(*global_map, player.get_pos(), 5);
        }
        player.do_turn();
        clear_console();
        map_output(*global_map, player.get_pos(), 5);
    }
    return 0;
}
