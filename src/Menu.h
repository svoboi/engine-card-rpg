#ifndef SEMESTRALKA_INTERFACE_H
#define SEMESTRALKA_INTERFACE_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <fstream>

/**
 * @class Menu
 * @brief Represents a menu for displaying game-related information and interacting with the player.
 *
 * The Menu class provides functionality for displaying game-related information and interacting with the player through input and output streams.
 * It is responsible for presenting the game's menu options, displaying the winner of the game, and handling user input.
 * The class uses input and output streams to communicate with the player.
 */

class Menu {
public:
    Menu(std::istream &in, std::ostream &out);

    /**
     * @brief Displays the winner of the game and asks if the player wants to start a new game.
     *
     * @param name The name of the winning player.
     * @return True if the player wants to start a new game, false otherwise.
     */
    bool winnerAndAskIfNewGame(const std::string &name) const;

    /**
     * @brief Asks user whether they want new game or load from save file.
     * @return True if user wants to play new game.
     */
    bool shouldStartWithSavedGame() const;

    /**
     * @brief Asks user to give the path to their save file or config file
     * @return path to the needed file
     */
    std::string getfileName() const;

private:
    std::istream &m_in;
    std::ostream &m_out;

};

#endif //SEMESTRALKA_INTERFACE_H
