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

    Player(ICreature &creature);

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
    void move(position direction);

    position get_pos(); //Получение положения в пространстве

    ~Player();

private:

    ICreature &race; //Раса (существо). Отвечает за характеристики и "персонажность" игрока
    int level;
    int xp;

};

#endif //RPG_MINIPROJECT_PLAYER_H
