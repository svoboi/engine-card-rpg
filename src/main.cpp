#include <iostream>
#include "App.h"


int main() {
    Menu menu = Menu(std::cin, std::cout);
    GameBuilder gameBuilder;

    App app(menu, gameBuilder);
    bool startWithSavedGame;
    if (!app.setUpApp(startWithSavedGame))
        return 1;
    app.run(startWithSavedGame);
    return 0;
}