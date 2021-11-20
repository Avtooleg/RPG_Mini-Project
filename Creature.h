#ifndef RPG_MINIPROJECT_CREATURE_H
#define RPG_MINIPROJECT_CREATURE_H

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

        int get_hp();
        int get_str(); //Сила
        int get_stam(); // Выносливость
        int get_agil(); // Ловкость
        int get_luck(); // Удача
        int get_int(); // Интеллект
        int get_perc(); // Восприяте
        position get_pos();
        char get_marker();

        void set_hp(int hp);
        void set_str(int hp);
        void set_stam(int hp);
        void set_agil(int hp);
        void set_luck(int hp);
        void set_int(int hp);
        void set_perc(int hp);

        ~ICreature() = default;

    private:

        std::vector<int> stats;
        position pos;
        char marker;

};

#endif //RPG_MINIPROJECT_CREATURE_H
