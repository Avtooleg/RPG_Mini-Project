#include <iostream>
#include "Frontend.h"
#include <vector>
#include "Player.h"
#include "Creature.h"
#include "Map.h"

bool run = true;

void quit(){
    run = false;
}

int main() {
    std::vector<ICreature> creatures = {};
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
    Map global_map = Map(_map, creatures, pass_vec, pass_vec, 1, 0, 0);

    while(run){
    }
    return 0;
}
