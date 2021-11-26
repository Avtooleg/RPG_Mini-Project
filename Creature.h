#ifndef RPG_MINIPROJECT_CREATURE_H
#define RPG_MINIPROJECT_CREATURE_H

#include "Utils.h"


class Map;

//Родительский класс для всех существ. Изначально планировался абстрактным,
//но в итоге геттеры, сеттеры и ещё пара функций перестали быть виртуальными,
//ибо все равно у всех одни и те же будут.
class ICreature{
    public:

        ICreature(char mark, std::vector<int> init_stats, Map &init_map);

        //Вызывается из main(), тем самым передавая ход существу. Также содержит ИИ (Ну, должна)
        virtual void do_turn();
        //Передвигает существо на новое место по вектору direction
        void move(position direction);
        //Отвечает за действие атаки.
        // Потенциально поддерживает различную логику боя (уход в защиту/атаки),
        // но пока лишь заглушка
        virtual void attack(ICreature &target);

        //Геттеры
        int get_hp(); //Здоровье
        int get_str(); //Сила
        int get_stam(); // Выносливость
        int get_agil(); // Ловкость
        int get_luck(); // Удача
        int get_int(); // Интеллект
        int get_perc(); // Восприятие
        std::vector<int> get_stats(); // Получить весь массив
        position get_pos(); // Положение в пространстве
        char get_marker(); // Значок на карте ('W' - слабый, 'S' - сильный и т.д.)
        int get_move_points(); // Возвращает move_points - очки движения

        //Сеттеры
        void set_hp(int val);
        void set_str(int val);
        void set_stam(int val);
        void set_agil(int val);
        void set_luck(int val);
        void set_int(int val);
        void set_perc(int val);
        void set_pos(position new_pos);

        void init_move_points();//Инициализирует очки движения на основе характеристик. Ловкости, например.

        virtual ~ICreature() = default;

    protected:

        int hp;
        int move_points; // Очки передвижения
        std::vector<int> stats; //Вектор статов
        //Для передвижения move(...) требуется обновить состояние на карте. Потому нужна карта
        // Потенциально, можно реализовать пещеры/порталы
        Map &global_map;
        position pos; //Положение на карте
        char marker;  //Собственно, значок

};

//Тестовый зверь, нужен был для попытки запустить все это дело, но, увы - ошибки интеграции
class Test_creature : public ICreature{

    public:

    Test_creature(char mark, std::vector<int> init_stats, Map &init_map);

    void move(position direction);
    void do_turn();
    void attack(ICreature &target);

    ~Test_creature() = default;
};

#endif //RPG_MINIPROJECT_CREATURE_H
