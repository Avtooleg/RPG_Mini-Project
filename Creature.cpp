#include "Creature.h"
#include "Frontend.h"
#include "Map.h"
#include "Utils.h"
#include <cmath>

ICreature::ICreature(char mark, std::vector<int> init_stats, Map &init_map) 
    : marker(mark)
    , stats(init_stats)
    , global_map(init_map) {};

void ICreature::do_turn() {
    std::cout << "Error! There is an ICreature here!";
};

void ICreature::attack(ICreature &target) {
    damage_result damage = get_damage(this, &target);
    switch(damage.callback){
        case Attack_results::HIT: {
            std::cout << marker << "got direct hit on " << target.get_marker() <<  " with " << damage.power << " damage";
            target.set_hp(target.get_hp() - damage.power);
            break;
        }
        case Attack_results::CRIT: {
            std::cout << marker << "got critical hit on " << target.get_marker() <<  " with " << damage.power << " damage";
            target.set_hp(target.get_hp() - damage.power);
            break;
        }
        case Attack_results::DEFENDED: {
            std::cout << target.get_marker() << " fully blocked hit by " << marker;
            break;
        }
        case Attack_results::EVADED: {
            std::cout << target.get_marker() << " evaded attack by " << marker;
            break;
        }
    }
};

void ICreature::move(position direction){
    position new_pos;
    new_pos.x = pos.x + direction.x;
    new_pos.y = pos.y + direction.y;
    if (new_pos.x >= global_map.get_size() || new_pos.y >= global_map.get_size() ||
    new_pos.x < 0 || new_pos.y < 0){
    }
    else {
        global_map.map_monster_update(false, marker, &pos, &new_pos);
        pos = new_pos;
    }
    move_points -= 1;
};
int ICreature::get_hp(){
    return hp;
};
int ICreature::get_str(){
    return stats[0];
};
int ICreature::get_stam(){
    return stats[1];
};
int ICreature::get_agil(){
    return stats[2];
};
int ICreature::get_luck(){
    return stats[3];
};
int ICreature::get_int(){
    return stats[4];
};
int ICreature::get_perc(){
    return stats[5];
};
std::vector<int> ICreature::get_stats(){
    std::vector<int> result = stats;
    return result;
};
position ICreature::get_pos(){
    return pos;
};
char ICreature::get_marker(){
    return marker;
};
int ICreature::get_move_points(){
    return move_points;
};

Map* ICreature::get_map() {
    return &global_map;
}

void ICreature::set_hp(int val){
    hp = val;
};
void ICreature::set_str(int val){
    stats[0] = val;
};
void ICreature::set_stam(int val){
    stats[1] = val;
};
void ICreature::set_agil(int val){
    stats[2] = val;
};
void ICreature::set_luck(int val){
    stats[3] = val;
};
void ICreature::set_int(int val){
    stats[4] = val;
};
void ICreature::set_perc(int val){
    stats[5] = val;
};
void ICreature::set_pos(position new_pos){
    pos = new_pos;
}

void ICreature::update_hp() {};

void ICreature::init_move_points(){
    move_points = stats[2]/2 + 1;
};
//TODO:: make normal function of xp
int ICreature::get_xp_given() {
    int xp = 0;
    for (int i = 0; i < stats.size(); i++){
        xp+=stats[i];
    }
    return xp*10 + 10;
}

ICreature::~ICreature() noexcept {
    global_map.map_monster_update(true, marker, &pos);
}

Test_creature::Test_creature(char mark, std::vector<int> init_stats, Map &init_map) /*: marker(mark), stats(init_stats), global_map(init_map) - нельзя инициализировать родительские переменные через список инициализации !*/ 
    : ICreature(mark, init_stats, init_map)
{
        move_points = 0;
        hp = init_stats[1]*10 + 10;
        pos = position({0,0});// position(0,0); - так вызывается конструктор, но его нет, поэтому синтаксическая ошибка
};

//Перегружает движение. Костыль. Была та же ошибка, что сейчас в do_turn()
//у init_move_points()
/*
void Test_creature::move(position direction){
    position new_pos;
    new_pos.x = pos.x + direction.x;
    new_pos.y = pos.y + direction.y;
    if (new_pos.x >= global_map.get_size() || new_pos.y >= global_map.get_size()){
    }
    else {
        global_map.map_monster_update(pos, new_pos, marker);
        pos = new_pos;
    }
};*/

//Тестовый вариант, без особого смысла
void Test_creature::do_turn(){
    init_move_points();
    while(move_points > 0){
        position to_player = global_map.get_player_pos() - pos;
        float player_dist = abs(to_player);

        if(player_dist != 1){

        const int low = 0x0001;
        const int high = 0x0002;
        const int feel_rad = 5;
        bool see = true;
        int tries = 0;
        position init_dir;
        while(see) {
            tries += 1;
            if (tries > 100){
                see = false;
            }
            int dir = get_random_int(0, 3);

            bool high_bit = dir & high;
            bool low_bit = dir & low;
            init_dir.x = high_bit * (low_bit - !low_bit);
            init_dir.y = !high_bit * (low_bit - !low_bit);
            init_dir = init_dir + to_player * (feel_rad / pow(abs(to_player), 2));
            if(pos.x + init_dir.x >= global_map.get_size() || pos.y + init_dir.y >= global_map.get_size()
            || pos.x + init_dir.x < 0 || pos.y + init_dir.y < 0){
                continue;
            }
            if(!is_in(global_map.get_value(pos + init_dir), forbidden_chars)){
                see = false;
            }
        }
        move(init_dir);
        move_points -= 1;
        }
        else {
            attack(*global_map.get_player_race_pointer());
            move_points -= 1;
        }
    }
}

void Test_creature::update_hp() {
    hp = stats[1]*10 + 10;
}

Test_creature::~Test_creature() noexcept {
    global_map.map_monster_update(true, marker, &pos);
}