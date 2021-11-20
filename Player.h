#ifndef RPG_MINIPROJECT_PLAYER_H
#define RPG_MINIPROJECT_PLAYER_H

#include "Creature.h"
#include "Frontend.h"
#include <vector>
#include "Map.h"

class Player{
public:

    Player(ICreature &creature);

    void do_turn();
    //Вызывать только по достижении нужного кол-ва опыта!
    void level_up();
    void attack(ICreature &target);
    void set_hp(int val);
    //Вызывать только после проверки того, что есть очки хода!
    void move();

    position get_pos();

    ~Player();

private:

    ICreature &race;
    int level;
    int xp;

};

#endif //RPG_MINIPROJECT_PLAYER_H
