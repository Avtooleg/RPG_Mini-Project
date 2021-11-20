#ifndef RPG_MINIPROJECT_PLAYER_H
#define RPG_MINIPROJECT_PLAYER_H

//#include "Creature.h"
//#include "Frontend.h"
#include <vector>
//#include "Map.h"

class ICreature;
struct position;

class Player{
public:

    Player(ICreature &creature);

    void do_turn();
    //Вызывать только по достижении нужного кол-ва опыта!
    void level_up();
    void attack(ICreature &target);
    void set_hp(int val);
    void move(position direction);

    position get_pos();

    ~Player();

private:

    ICreature &race;
    int level;
    int xp;

};

#endif //RPG_MINIPROJECT_PLAYER_H
