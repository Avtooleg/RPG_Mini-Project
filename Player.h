#ifndef RPG_MINIPROJECT_PLAYER_H
#define RPG_MINIPROJECT_PLAYER_H

#include "Creature.h"
#include "Frontend.h"
#include <vector>
#include "Map.h"

class Player{
public:

    Player(Icreature &creature);

    void do_turn() override;
    void level_up();
    void attack(ICreature &target);
    void set_hp(int hp);
    void move();

    int get_pos();

    ~Player();

private:

    ICreature &race;
    int level;

};

#endif //RPG_MINIPROJECT_PLAYER_H
