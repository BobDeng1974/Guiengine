#include "GuiengineErrors.h"

#include <cstdlib>
#include <conio.h>
#include <iostream>
#include <SDL/SDL.h>

namespace Guiengine {

    //Prints out an error message and exits the game
    void fatalError(std::string errorString) {
        std::cout << errorString << std::endl;
        std::cout << "Enter any key to quit...";
		_getch();
        SDL_Quit();
        exit(69);
    }

}