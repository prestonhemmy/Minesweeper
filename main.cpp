#include <iostream>
#include "WelcomeWindow.h"

using namespace std;

int main() {

    WelcomeWindow myWindow;
    Game* game = myWindow.run();

    if (game != nullptr) {
        game->run();
        delete game;
    }

    return 0;
}