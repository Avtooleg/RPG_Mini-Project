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
    // str, stam, agil, luck, int, perc
    std::vector<int> stats = {1, 1, 4, 1, 1, 2};
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
    global_map.add_monsters(3, global_map.get_center(), creatures);
    Test_creature* race = new Test_creature('P', stats, global_map);
    Player player(race, global_map.get_center());
    global_map.add_player(player);
    //Just a test from here
    std::vector<ICreature*> attack_level_up_test;
    position curr_pos;
    static const int low = 0x0001;
    static const int high = 0x0002;
    for(int i = 0; i<4; i++) {
        bool low_bit = i & low;
        bool high_bit = i & high;
        curr_pos.x = global_map.get_center().x + high_bit * (low_bit - !low_bit);
        curr_pos.y = global_map.get_center().y + !high_bit * (low_bit - !low_bit);
        Test_creature *xp_bag = new Test_creature('M', stats, global_map);
        xp_bag->set_pos(curr_pos);
        attack_level_up_test.push_back(xp_bag);
    }
    global_map.add_positional_monsters(attack_level_up_test);
    //To here
    try {
        while (run) {
            int view_rad = get_view_dist(player.get_perc());
            map_output(global_map, player.get_pos(), view_rad);
            for (int i = 0; i < creatures.size(); i++) {
                Sleep(500);
                creatures[i]->do_turn();
                map_output(global_map, player.get_pos(), view_rad);
            }
            player.do_turn();
        }
    }
    catch(Exceptions QUIT){
        run = false;
    }
    return 0;
}
