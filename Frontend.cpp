#include "Frontend.h"
#include <iostream>
//#include <windows.h>

#include "Utils.h"
#include "Map.h"
#include <string>
#include <fstream>

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

space load_map(std::string filename){
    std::ifstream map_file(filename);
    space loaded_map;
    if (!map_file.is_open()){
        std::cout << "Map cannot be loaded - wrong name!";
    }
    else{
        bool see = true;
        while(see){
            if (map_file.eof()){
                break;
            }
            else{
                char new_str[100];
                map_file.getline(new_str, 100);
                loaded_map.push_back(new_str);
            }
        }
    }
    map_file.close();
    return loaded_map;
}

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

void map_output(Map &map, position center, int rad){
    clear_console();
    space area = map.get_area(center, rad);
    for (int i = 0; i < area.size(); i++){
        std::cout << area[i] << '\n';
    }
}

void clear_console(){

        HANDLE                     hStdOut;
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD                      count;
        DWORD                      cellCount;
        COORD                      homeCoords = { 0, 0 };

        hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
        if (hStdOut == INVALID_HANDLE_VALUE) return;

        /* Get the number of cells in the current buffer */
        if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
        cellCount = csbi.dwSize.X *csbi.dwSize.Y;

        /* Fill the entire buffer with spaces */
        if (!FillConsoleOutputCharacter(
                hStdOut,
                (TCHAR) ' ',
                cellCount,
                homeCoords,
                &count
        )) return;

        /* Fill the entire buffer with the current colors and attributes */
        if (!FillConsoleOutputAttribute(
                hStdOut,
                csbi.wAttributes,
                cellCount,
                homeCoords,
                &count
        )) return;

        /* Move the cursor home */
        SetConsoleCursorPosition( hStdOut, homeCoords );

}