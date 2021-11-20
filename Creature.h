#ifndef RPG_MINIPROJECT_CREATURE_H
#define RPG_MINIPROJECT_CREATURE_H

#include "Frontend.h"
#include <vector>
#include "Map.h"
#include "Utils.h"

class ICreature{
    public:

        ICreature() = default;
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
        int get_perc(); // Восприятие
        std::vector<int> get_stats(); // Получить весь массив
        position get_pos();
        char get_marker();

        void set_hp(int val);
        void set_str(int val);
        void set_stam(int val);
        void set_agil(int val);
        void set_luck(int val);
        void set_int(int val);
        void set_perc(int val);

        ~ICreature() = default;

    private:

        int hp;
        int move_points;
        std::vector<int> stats;
        position pos;
        char marker;

};

#endif //RPG_MINIPROJECT_CREATURE_H
