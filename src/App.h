#ifndef SEMESTRALKA_APP_H
#define SEMESTRALKA_APP_H

#include <string>
#include <memory>
#include "Game.h"
#include "Menu.h"
#include "Player.h"
#include "Card.h"
#include "Deck.h"
#include "CardsVisibility.h"
#include "GameBuilder.h"

/**
 * @class App
 * @brief Represents the application that runs the game.
 *
 * The App class is responsible for setting up the game and running the game loop.
 */

class App {
public:
    App(const Menu &menu, const GameBuilder &gameBuilder);

    App(const App &other) = delete;

    App &operator=(const App &other) = delete;

    ~App() = default;

    /**
     * @brief Sets up app by getting configuration or save files.
     * Reads given deck and cards files, then loads save file if needed
     * Lastly, calls setUpGame.
     * @return True if game is ready to run
    */
    bool setUpApp(bool &startWithSavedGame);

    /**
     * @brief Runs the game, until user decides to close the application
    */
    void run(bool &startWithSavedGame);

private:
    Menu m_menu;
    GameBuilder m_gameBuilder;
    std::unique_ptr<Game> m_game = nullptr;
};


#endif //SEMESTRALKA_APP_H
