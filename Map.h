#ifndef RPG_MINIPROJECT_MAP_H
#define RPG_MINIPROJECT_MAP_H


#include <vector>
#include <string>
#include <map>

class ICreature;
class Player;
struct position;

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

    Map(std::vector<std::string> _map,
        std::vector<ICreature> &low_level,
        std::vector<ICreature> &middle_level,
        std::vector<ICreature> &high_level,
        int low_rad,
        int middle_rad,
        int high_rad);

    //Возвращает "срез" карты размером rad*rad вокруг pos (ограничивает видимость игрока)
    space get_area (position pos, int rad);
    char get_init_value(position pos);//Возвращает клетку на коорд. pos на "пустой" карте (без существ)
    char get_value(position pos);//Возвращает клетку на коорд. pos на текущей карте
    //Размещает монстров monsters с значком marker с заданной
    //запрещенной зоной forbidden_rad вокруг center
    void add_monsters(char marker, int forbidden_rad, position center, std::vector<ICreature> &monsters);
    //Обновляет всю карту с учетом текущего положения всех существ
    //(изначальная идея обновления карты
    void map_update(std::vector<ICreature> &creatures, Player player);
    //Разово сдвигает одного монстра (игрока)
    //(более новая идея обновления карты, так сказать, in real time)
    void map_monster_update(position old_pos, position new_pos, char marker);

private:

    int map_size;
    space my_start_map;//"Пустая" карты
    space my_map;//Текущая карта
    std::map<position, ICreature*> my_monsters;//словарь (место -> существо). Нужен для выбора цели атаки (чтобы всех не обзванивать).

};

#endif //RPG_MINIPROJECT_MAP_H
