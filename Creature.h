#include "Frontend.h"
#include <vector>
#include "Map.h"

class ICreature{
    public:

        Icreature() = default;
        virtual void do_turn();
        virtual void move();
        virtual void regen();
        virtual void attack(ICreature &target);

        virtual int get_hp();
        virtual int get_str(); //Сила
        virtual int get_stam(); // Выносливость
        virtual int get_agil(); // Ловкость
        virtual int get_luck(); // Удача
        virtual int get_int(); // Интеллект
        virtual int get_perc(); // Восприяте

        virtual void set_hp(int hp);
        virtual void set_str(int hp);
        virtual void set_stam(int hp);
        virtual void set_agil(int hp);
        virtual void set_luck(int hp);
        virtual void set_int(int hp);
        virtual void set_perc(int hp);

        ~ICreature() = default;

    private:

        std::vector<int> stats;
        position pos;

};

#ifndef RPG_MINIPROJECT_CREATURE_H
#define RPG_MINIPROJECT_CREATURE_H

#endif //RPG_MINIPROJECT_CREATURE_H
