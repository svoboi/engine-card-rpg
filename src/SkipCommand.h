#ifndef SEMESTRALKA_SKIPCOMMAND_H
#define SEMESTRALKA_SKIPCOMMAND_H

#include "Command.h"

/**
 * @class SkipCommand
 * @brief The SkipCommand class represents a command to skip the player's turn in the game.
 *
 * The SkipCommand class inherits from the Command class and implements the execute() method to skip the player's turn.
 * When executed, this command does not perform any actions and simply moves the game to the next player's turn.
 */
class SkipCommand : public Command {
public:
    /**
     * @brief Executes the skip command in the game.
     *
     * @param game The game interface.
     * @return True if the command was successfully executed, false otherwise.
     */
    virtual bool execute(GameInterface &game) const override;
};

#endif //SEMESTRALKA_SKIPCOMMAND_H
