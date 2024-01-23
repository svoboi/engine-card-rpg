#ifndef SEMESTRALKA_COMMAND_H
#define SEMESTRALKA_COMMAND_H

#include "GameInterface.h"
#include <memory>
#include <iostream>

/**
 * @class Command
 * @brief Represents a game command.
 *
 * The Command class is an abstract base class that provides an interface for executing an effect in the game.
 * Derived classes must implement the execute() method to define the specific effect of the command.
 */
class Command {
public:
    virtual ~Command() = default;

    /**
     * Executes the effect in the game.
     *
     * @param game The game interface to apply the effect on.
     * @return True if the execution was successful, false otherwise.
     */
    virtual bool execute(GameInterface &game) const = 0;
};

#endif //SEMESTRALKA_COMMAND_H
