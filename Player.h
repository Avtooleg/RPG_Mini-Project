#include "Creature.h"
#include "Frontend.h"
#include <vector>
#include "Map.h"

class Player{
public:

    void do_turn() override;
    void level_up();
    void attack(ICreature &target);
    void set_hp(int hp);
    void move();

private:

    ICreature &race;
    int level;
    position pos;

};

#ifndef RPG_MINIPROJECT_PLAYER_H
#define RPG_MINIPROJECT_PLAYER_H

#endif //RPG_MINIPROJECT_PLAYER_H
