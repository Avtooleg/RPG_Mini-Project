#ifndef RPG_MINIPROJECT_CREATURE_H
#define RPG_MINIPROJECT_CREATURE_H

#include <vector>
#include "Utils.h"

class ICreature{
    public:

        ICreature() = default;
        virtual void do_turn();
        void move(position direction);
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
        int get_move_points();

        void set_hp(int val);
        void set_str(int val);
        void set_stam(int val);
        void set_agil(int val);
        void set_luck(int val);
        void set_int(int val);
        void set_perc(int val);

        void init_move_points();

        ~ICreature() = default;

    protected:

        int hp;
        int move_points;
        std::vector<int> stats;
        Map &global_map;
        position pos;
        char marker;

};

class Test_creature : public ICreature{

    public:

    Test_creature(char mark, std::vector<int> init_stats, Map &init_map): marker(mark), stats(init_stats), global_map(init_map) {
        move_points = 0;
        hp = 0;
        pos = position(0,0);
    };

    void move(position direction);
    void do_turn();
    void attack(ICreature &target);
};

#endif //RPG_MINIPROJECT_CREATURE_H
