#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <iostream>
#include "grid.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Please include init file\n";
        return 1;
    }

    Grid myGrid(argv[1]);
    
    for(int i = 0; i < 100; i++) {
        std::cout << "\033[2J\033[1;1H";
        myGrid.print();
        myGrid.updateGrid();
        usleep(400000);
    }
    return 0;
}