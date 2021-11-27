#ifndef RPG_MINIPROJECT_MAP_H
#define RPG_MINIPROJECT_MAP_H


#include <vector>
#include <string>
#include <map>
#include "Utils.h"

class ICreature;
class Player;

//Клетки, на которые запрещено вставать (горы, другие монстры)
const std::vector<char> forbidden_chars = {'^', 'P', 'W', 'A', 'S'};
//"Число делений" генератора случайных чисел
const int max_def = 1e9;

//Просто заколебался писать
typedef std::vector<std::string> space;

// Возвращает случайное положение на карте, начиная от расстояния forbidden_rad от center
position get_random_position(int map_size, int forbidden_rad, position center);

//Координаты задаются от верхнего левого угла
class Map{
public:

    Map(std::vector<std::string> _map);

    //Возвращает "срез" карты размером rad*rad вокруг pos (ограничивает видимость игрока)
    space get_area (position pos, int rad);
    int get_size(); // Возвращает размер карты
    char get_init_value(position pos);//Возвращает клетку на коорд. pos на "пустой" карте (без существ)
    char get_value(position pos);//Возвращает клетку на коорд. pos на текущей карте
    //Размещает монстров monsters с значком marker с заданной
    //запрещенной зоной forbidden_rad вокруг center
    void add_monsters(int forbidden_rad, position center, std::vector<ICreature*> &monsters);
    //Добавляет ссылку на игрока
    void add_player(Player &player);
    //Добавляет монстров по их собственным координатам и маркерам
    void add_positional_monsters(std::vector<ICreature*> monsters);
    //Возвращает позицию игрока
    position get_player_pos();
    //Обновляет всю карту с учетом текущего положения всех существ
    std::vector<ICreature*> get_monsters_around(position center);
    //(изначальная идея обновления карты
    void map_update(std::vector<ICreature> &creatures, Player player);
    //Разово сдвигает одного монстра (игрока)
    //(более новая идея обновления карты, так сказать, in real time)
    void map_monster_update(bool deletion,  char marker, position *old_pos, position *new_pos = NULL);
    //Выдаёт центр карты
    position get_center();

private:

    int map_size;
    position map_center;
    space my_start_map;//"Пустая" карты
    space my_map;//Текущая карта
    std::map<position, ICreature*> my_monsters;//словарь (место -> существо). Нужен для выбора цели атаки (чтобы всех не обзванивать).
    Player *my_player; //указатель на игрока, для доступа остальных существ

};

#endif //RPG_MINIPROJECT_MAP_H
