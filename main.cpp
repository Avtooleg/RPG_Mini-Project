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

    const int low_count = 5;
    const int aver_count = 4;
    const int high_count = 2;
    const int low_stat_sum = 10;
    const int aver_stat_sum = 15;
    const int high_stat_sum = 20;
    const int low_rad = 2;
    const int aver_rad = 3;
    const int high_rad = 4;
    const std::vector<int> player_stats = {1, 1, 4, 1, 1, 2};
    space _map = load_map("MAP2.txt");
    /*const space _map = {
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
    };*/
    std::vector<char> forbidden_chars = {'L', 'A', 'M', 'P', 'S'};
    Map global_map = Map(_map);
    std::vector<ICreature*> low_level = get_monsters_group(low_count, low_stat_sum, 3, 'L', &global_map);
    std::vector<ICreature*> aver_level = get_monsters_group(aver_count, aver_stat_sum, 3, 'A', &global_map);
    std::vector<ICreature*> high_level = get_monsters_group(high_count, high_stat_sum, 3, 'S', &global_map);
    global_map.add_monsters(low_rad, global_map.get_center(), low_level);
    global_map.add_monsters(aver_rad, global_map.get_center(), aver_level);
    global_map.add_monsters(high_rad, global_map.get_center(), high_level);
    std::vector<ICreature*> creatures = low_level;
    creatures.insert(creatures.end(), aver_level.begin(), aver_level.end());
    creatures.insert(creatures.end(), high_level.begin(), high_level.end());
    Test_creature* race = new Test_creature('P', player_stats, global_map);
    Player player(race, global_map.get_center());
    global_map.add_player(player);
    try {
        while (run) {
            int view_rad = get_view_dist(player.get_perc());
            map_output(global_map, player.get_pos(), view_rad);
            for (int i = 0; i < creatures.size(); i++) {
                Sleep(500);
                creatures[i]->do_turn();
                map_output(global_map, player.get_pos(), view_rad);
                std::cout << '\n';
            }
            player.do_turn();
        }
    }
    catch(Exceptions QUIT){
        run = true;
    }
    return 0;
}
