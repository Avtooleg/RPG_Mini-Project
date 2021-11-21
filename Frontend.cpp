#include "Frontend.h"
#include <iostream>
//#include <windows.h>

#include "Utils.h"
#include "Map.h"

#if defined _WIN32
#include <windows.h>
#endif

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

char get_player_input(const std::vector<int> &keys){
    bool see = true;
    while(see) {
        for (int i = 0; i < keys.size(); i++) {
            if (GetKeyState(keys[i]) & 0x8000) {
                see = false;
                return keys[i];
            }
        }
    }
}

void map_output(Map map, position center, int rad){
    space area = map.get_area(center, rad);
    for (int i = 0; i < area.size(); i++){
        std::cout << area[i] << '\n';
    }
}

void clear_console(){
    system("cls");
}