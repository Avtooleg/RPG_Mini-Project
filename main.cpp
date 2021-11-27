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
    std::vector<int> stats = {1, 1, 1, 1, 1, 2};
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
    Map global_map = Map(_map);
    Test_creature *test = new Test_creature('M', stats, global_map);
    std::vector<ICreature*> creatures = {test};
    std::vector<ICreature*> pass_vec = {};
    global_map.add_monsters('M', 3, global_map.get_center(), creatures);
    Test_creature* race = new Test_creature('P', stats, global_map);
    Player player(race, global_map.get_center());
    global_map.add_player(player);
    while(run){
        int view_rad = get_view_dist(player.get_perc());
        map_output(global_map, player.get_pos(), view_rad);
        for (int i = 0; i < creatures.size(); i++){
            Sleep(500);
            creatures[i]->do_turn();
            map_output(global_map, player.get_pos(), view_rad);
        }
        player.do_turn();
        map_output(global_map, player.get_pos(), view_rad);
    }
    return 0;
}
