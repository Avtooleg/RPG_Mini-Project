#include "Creature.h"
#include "Frontend.h"
#include "Map.h"
#include "Utils.h"

ICreature::ICreature(char mark, std::vector<int> init_stats, Map &init_map) 
    : marker(mark)
    , stats(init_stats)
    , global_map(init_map) {};

void ICreature::do_turn() {
    std::cout << "Error! There is an ICreature here!";
};

void ICreature::attack(ICreature &target) {
    std::cout << "Error! There is an ICreature here!";
};

void ICreature::move(position direction){
    position new_pos;
    new_pos.x = pos.x + direction.x;
    new_pos.y = pos.y + direction.y;
    //global_map.map_monster_update(pos, new_pos); //TODO: error on function call
    pos = new_pos;
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

void ICreature::init_move_points(){
    move_points = stats[3]/2 + 1;
};

Test_creature::Test_creature(char mark, std::vector<int> init_stats, Map &init_map) /*: marker(mark), stats(init_stats), global_map(init_map) - нельзя инициализировать родительские переменные через список инициализации !*/ 
    : ICreature(mark, init_stats, init_map)
{
        move_points = 0;
        hp = 0;
        pos = position({0,0});// position(0,0); - так вызывается конструктор, но его нет, поэтому синтаксическая ошибка
};

void Test_creature::attack(ICreature &target) {
    target.set_hp(target.get_hp() - 1);
};

//Перегружает движение. Костыль. Была та же ошибка, что сейчас в do_turn()
//у init_move_points()
void Test_creature::move(position direction){
    position new_pos;
    new_pos.x = pos.x + direction.x;
    new_pos.y = pos.y + direction.y;
    global_map.map_monster_update(pos, new_pos, marker);
    pos = new_pos;
};

//Тестовый вариант, без особого смысла
void Test_creature::do_turn(){
    position direction;
    init_move_points();
    direction.x = 1;
    direction.y = 1;
    move(direction);
}
