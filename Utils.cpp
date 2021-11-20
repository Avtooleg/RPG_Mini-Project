#include "Utils.h"
#include "Creature.h"


int get_damage(ICreature &creature){
    creature.set_hp(creature.get_hp() - 1);
};
