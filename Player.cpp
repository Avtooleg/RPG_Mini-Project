#include <vector>
#include "Player.h"
#include <string>
#include "Creature.h"
#include "Map.h"
#include "Frontend.h"

#if defined _WIN32
#include <windows.h>
#else
#define VK_LEFT     0xf702
#define VK_UP       0xf700
#define VK_RIGHT    0xf703
#define VK_DOWN     0xf701
#define VK_ESCAPE   0x1B
#define VK_SPACE    0x1C
#endif

Player::Player(ICreature &creature): race(creature){
    xp = 0;
    level = 1;
}

Player::~Player(){
    delete &race;
}

void Player::level_up(){
    level += level;
    static const std::vector<int> keys = {'S', 'T', 'A', 'L', 'I', 'P'};
    std::vector<int> stats = race.get_stats();
    static const std::vector<std::string> names = {"strength(s)", "stamina(t)", "agility(a)", "luck(l)", "intellect(i)", "perception(p)"};
    std::cout << "You have got a level up! Now, you need to decide,\nWhat will you train?";
    //Вывод вариантов
    for(int i = 0; i < stats.size(); i++){
        std::cout << "Your " << names[i] << ": " << stats[i] << "\n";
    }
    //Старый, копипастный код.
    /*std::cout << "Your strength(s): " << race->get_str(); //Сила
    std::cout << "Your stamina(t): " << race->get_stam(); // Выносливость
    std::cout << "Your agility(a): " << race->get_agil(); // Ловкость
    std::cout << "Your luck(l): " << race->get_luck(); // Удача
    std::cout << "Your intellect(i): " << race->get_int(); // Интеллект
    std::cout << "Your perception(p): " << race->get_perc(); // Восприятие*/

    //Обработка ответа игрока
    char ch = get_player_input(keys);
    switch(ch) {
        case 'S':
            race.set_str(race.get_str() + 1);
            std::cout << "Your strength is now " << race.get_str() << " !\n";
            break;
        case 'T':
            race.set_stam(race.get_stam() + 1);
            std::cout << "Your stamina is now " << race.get_str() << " !\n";
            break;
        case 'A':
            race.set_agil(race.get_agil() + 1);
            std::cout << "Your agility is now " << race.get_str() << " !\n";
            break;
        case 'L':
            race.set_luck(race.get_luck() + 1);
            std::cout << "Your luck is now " << race.get_str() << " !\n";
            break;
        case 'I':
            race.set_int(race.get_int() + 1);
            std::cout << "Your intellect is now " << race.get_str() << " !\n";
            break;
        case 'P':
            race.set_perc(race.get_perc() + 1);
            std::cout << "Your perception is now " << race.get_str() << " !\n";
            break;
    }
}

void Player::attack(ICreature &target) {
    target.set_hp(target.get_hp() - get_damage(race));
}

void Player::set_hp(int val){
    race.set_hp(val);
}

void Player::move(position direction){
    if(race.get_move_points() > 0){
        race.move(direction);
    }
    else{
        std::cout << "You are out of moves!\n";
    }
}

position Player::get_pos(){
    return race.get_pos();
}

void Player::do_turn() {
    //Добавляем очки движения на этот ход
    race.init_move_points();
    //Возможные варианты действий(клавиши)
    static const std::vector<int> keys = {VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, VK_SPACE, 'Q', 'I', 'D'};
    static const std::vector<std::string> names = {"strength(s)", "stamina(t)", "agility(a)", "luck(l)", "intellect(i)", "perception(p)"};
    //Обработка ответа игрока
    char ch = get_player_input(keys);
    position direction;
    switch (ch){
            case VK_UP: {
                direction.y = -1;
                move(direction);
                break;
            }
            case VK_DOWN: {
                direction.y = 1;
                move(direction);
                break;
            }
            case VK_LEFT: {
                direction.x = -1;
                move(direction);
                break;
            }
            case VK_RIGHT: {
                direction.x = 1;
                move(direction);
                break;
            }
            //Вывести характеристики
            case 'I': {
                std::vector<int> stats = race.get_stats();
                for (int i = 0; i < stats.size(); i++) {
                    std::cout << "Your " << names[i] << ": " << stats[i] << "\n";
                }
                break;
            }
            //Планируется реализовать выход через исключения
            case 'Q': {
                std::cout << "You are quitting the game.";
                //quit();
                break;
            }
            //Будет обработка боевки на пробел, вероятно, вызовом attack()
            default:
                break;
        }
    }

