#ifndef RPG_MINIPROJECT_PLAYER_H
#define RPG_MINIPROJECT_PLAYER_H

//#include "Creature.h"
//#include "Frontend.h"
#include <vector>
//#include "Map.h"

class ICreature;
struct position;

//Класс игрока. Не наследуется, ибо выбор расы.
class Player{
public:

    Player(ICreature *creature, position init_pos);

    void do_turn();//Аналог do_turn() у ICreature, но с обращением к игроку.
    //Повышает уровень, вместе с выбором характеристики для роста.
    //Вызывать только по достижении нужного кол-ва опыта!
    void level_up();
    //Аналог attack() у ICreature. Пока заглушка.
    void attack(ICreature &target);

    //Сеттер хп. Возможно, уберется за ненадобностью, либо будет использоваться
    //монстрами для нанесения урона.
    void set_hp(int val);
    //Передвижение. С учетом обновлений в карте (универсальность перемещения значка),
    //возможно, будет убран и заменён обращению к race.
    void set_xp(int val);
    void move(position direction);

    //Геттеры
    int get_xp(); //Опыт
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
    ICreature* get_race_pointer(); // Возвращает ссылку на расу

    ~Player();

private:

    ICreature* race; //Раса (существо). Отвечает за характеристики и "персонажность" игрока
    int level;
    int xp;

};

#endif //RPG_MINIPROJECT_PLAYER_H
