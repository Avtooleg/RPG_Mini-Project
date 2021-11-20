#include "Frontend.h"
#include <iostream>
#include <windows.h>
#include <string>
#include <vector>

/*class keys_pressed{

    char single;
    string multiple;

    keys_pressed(bool is_single, string keys){
        if (is_single) {
            single = (char) keys;
            multiple = void;
        }
        else{
            single = void;
            multiple = keys;
        }
    }
};*/

char get_player_input(std::vector<int> keys){
    for (int i = 0; i < keys.size(); i++){
        if(GetKeyState(keys[i]) & 0x8000){
            return keys[i];
        }
    }
    return 0;
}

void map_output(Map map, position center, int rad){
    space area = map.get_area(center, rad);
    for (int i = 0; i < area.size(); i++){
        std::cout << area[i] << '\n';
    }
}