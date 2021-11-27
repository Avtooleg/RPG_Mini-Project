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

Player::Player(ICreature *creature, position init_pos): race(creature) {
    xp = 0;
    level = 1;
    race->set_pos(init_pos);
}

int Player::get_xp() {
    return xp;
}

int Player::get_hp(){
    return race->get_hp();
};
int Player::get_str(){
    return race->get_str();
};
int Player::get_stam(){
    return race->get_stam();
};
int Player::get_agil(){
    return race->get_agil();
};
int Player::get_luck(){
    return race->get_luck();
};
int Player::get_int(){
    return race->get_int();
};
int Player::get_perc(){
    return race->get_perc();
};
std::vector<int> Player::get_stats(){
    return race->get_stats();
};
position Player::get_pos(){
    return race->get_pos();
};
char Player::get_marker(){
    return race->get_marker();
};
int Player::get_move_points(){
    return race->get_move_points();
};

Player::~Player(){
    delete race;
}

void Player::level_up(){
    level += level;
    static const std::vector<int> keys = {'S', 'T', 'A', 'L', 'I', 'P'};
    std::vector<int> stats = race->get_stats();
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
            race->set_str(race->get_str() + 1);
            std::cout << "Your strength is now " << race->get_str() << " !\n";
            break;
        case 'T':
            race->set_stam(race->get_stam() + 1);
            std::cout << "Your stamina is now " << race->get_str() << " !\n";
            break;
        case 'A':
            race->set_agil(race->get_agil() + 1);
            std::cout << "Your agility is now " << race->get_str() << " !\n";
            break;
        case 'L':
            race->set_luck(race->get_luck() + 1);
            std::cout << "Your luck is now " << race->get_str() << " !\n";
            break;
        case 'I':
            race->set_int(race->get_int() + 1);
            std::cout << "Your intellect is now " << race->get_str() << " !\n";
            break;
        case 'P':
            race->set_perc(race->get_perc() + 1);
            std::cout << "Your perception is now " << race->get_str() << " !\n";
            break;
    }
}
//TODO: normal level_up limit
void Player::attack(ICreature &target) {
    if (race->get_move_points() > 0){
        race->attack(target);
        if (target.get_hp() <= 0){
            xp += target.get_xp_given();
            delete &target;
            if (xp > (level-1)*75 + 30){
                level_up();
            }
        }
    }
    else{
        std::cout << "You are out of moves!";
    }
}

void Player::set_hp(int val){
    race->set_hp(val);
}

void Player::set_xp(int val){
    xp = val;
}

void Player::move(position direction){
    if(race->get_move_points() > 0){
        race->move(direction);
    }
    else{
        std::cout << "You are out of moves!\n";
    }
}

void Player::do_turn() {
    //Добавляем очки движения на этот ход
    race->init_move_points();
    bool doing_turn = true;
    //Возможные варианты действий(клавиши)
    static const std::vector<int> keys = {VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, VK_SPACE, 'Q', 'I', 'D', 'E'};
    static const std::vector<std::string> names = {"strength(s)", "stamina(t)", "agility(a)", "luck(l)", "intellect(i)",
                                                   "perception(p)"};
    //Обработка ответа игрока
    while (doing_turn) {
        clear_console();
        std::cout << "It is your turn now!";
        map_output(*race->get_map(), get_pos(), get_view_dist(get_perc()));
        std::cout << "Your remaining move points: " << race->get_move_points() << '\n';
        std::cout << "Your remaining hp: " << get_hp() << '\n';
        std::cout << "press E to end turn\n";
        char ch = get_player_input(keys);
        position direction{0, 0};
        switch (ch) {
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
                std::vector<int> stats = race->get_stats();
                for (int i = 0; i < stats.size(); i++) {
                    std::cout << "Your " << names[i] << ": " << stats[i] << "\n";
                }
                std::cout << "Press E to exit\n";
                char exit = ' ';
                while (exit != 'E') {
                    exit = get_player_input(keys);
                }
                break;
            }
                //Планируется реализовать выход через исключения
            case 'Q': {
                std::cout << "You are quitting the game.";
                Sleep(2000);
                throw Exceptions::QUIT;
                break;
            }
            case 'E': {
                doing_turn = false;
                break;
            }
            case VK_SPACE: {
                std::cout << "You are in attack mode\n";
                std::cout << "Please choose a target\n";
                static const std::vector<std::string> directions = {"up", "down", "left", "right"};
                static const std::vector<int> att_keys = {VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT};
                std::vector<ICreature *> monsters = race->get_map()->get_monsters_around(get_pos());
                if (monsters[0] != NULL || monsters[1] != NULL || monsters[2] != NULL || monsters[3] != NULL ) {
                    for (int i = 0; i < monsters.size(); i++) {
                        if (monsters[i] != NULL) {
                            std::vector<int> monster_stats = monsters[i]->get_stats();
                            stats_name_output(directions[i], monster_stats, monsters[i]->get_hp());
                        }
                    }
                    char att_ch = get_player_input(att_keys);
                    switch (att_ch) {
                        case VK_UP: {
                            if(monsters[0] != NULL) {
                                attack(*monsters[0]);
                            }
                            else{
                                std::cout << "There is no one here!";
                            }
                            break;
                        }
                        case VK_DOWN: {
                            if(monsters[1] != NULL) {
                                attack(*monsters[1]);
                            }
                            else{
                                std::cout << "There is no one here!";
                            }
                            break;
                        }
                        case VK_LEFT: {
                            if(monsters[2] != NULL) {
                                attack(*monsters[2]);
                            }
                            else{
                                std::cout << "There is no one here!";
                            }
                            break;
                        }
                        case VK_RIGHT: {
                            if(monsters[3] != NULL) {
                                attack(*monsters[3]);
                            }
                            else{
                                std::cout << "There is no one here!";
                            }
                            break;
                        }
                    }
                }
                else {
                    std::cout << "There is no one here!";
                }
                Sleep(2000);
                break;
            }
        }
        Sleep(500);
    }
}
