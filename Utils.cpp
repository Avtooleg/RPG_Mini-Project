#include "Utils.h"
#include "Creature.h"

std::mt19937 mersenne(time(NULL));

bool luck_check(int luck){
    return luck > get_random_int(0, std::max(luck + 4, 8)); //Some amortization, so there won't be only crits
}

damage_result get_damage(ICreature* predator, ICreature* target){
    if (luck_check(target->get_luck()*target->get_agil())){
        return damage_result{0, Attack_results::EVADED};
    }
    int defence = static_cast<int>(target->get_str()*1.8);
    bool crit = luck_check(predator->get_luck());
    int attack = predator->get_str()*(2 + crit*2);

    if (defence > attack){
        return damage_result{0, Attack_results::DEFENDED};
    }
    else {
        if (crit){
            return damage_result{attack, Attack_results::CRIT};
        }
        else{
            return damage_result{attack, Attack_results::HIT};
        }
    }
};

bool position::operator<(position pos) const {
    return (x * x + y * y < pos.x * pos.x + pos.y * pos.y);
}

int sign(float val){
    return (val>=0) - (val<0);
};

bool is_in(char x, const std::vector<char>& vec){
    return std::find(vec.begin(), vec.end(), x)!=vec.end();
};

int get_random_int(int min, int max){
    static const unsigned int mersenne_max = ~0;
    unsigned int initial = mersenne();
    static const double fraction = 1.0 / (static_cast<double>(mersenne_max) + 1.0);
    return static_cast<int>(initial * fraction * (max - min + 1) + min);
};

int get_view_dist(int perc){
    return static_cast<int>(cbrt(perc)*2);
}