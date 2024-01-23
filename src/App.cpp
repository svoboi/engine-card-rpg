
#include "App.h"

App::App(const Menu &menu, const GameBuilder &gameBuilder)
        : m_menu(menu), m_gameBuilder(gameBuilder) {}

bool App::setUpApp(bool &startWithSavedGame) {
    startWithSavedGame = m_menu.shouldStartWithSavedGame();
    std::string fileName = m_menu.getfileName();
    if (fileName == "") {
        return false;
    }
    m_game = m_gameBuilder.buildFromFile(fileName, !startWithSavedGame);
    if (m_game == nullptr || (!startWithSavedGame && !m_game->canBeSetUp())) {
        return false;
    }
    return true;
}

void App::run(bool &startWithSavedGame) {
    while (1) {
        m_game->setUpGame(startWithSavedGame);
        while (m_game->running()) {
            m_game->print();
            m_game->nextTurn();
        }
        // if winner is empty - EndCommand was used, so we want to close app
        if (m_game->winner().empty() || !m_menu.winnerAndAskIfNewGame(m_game->winner())) {
            return;
        }
        startWithSavedGame = false;
    }
}