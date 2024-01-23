#ifndef SEMESTRALKA_ENDCOMMAND_H
#define SEMESTRALKA_ENDCOMMAND_H


#include "Command.h"

/**
 * @class EndCommand
 * @brief Command to end the game.
 *
 * The EndCommand class is a concrete implementation of the Command interface.
 * It allows for executing the end command, which terminates the game.
 */
class EndCommand : public Command {
public:
    /**
     * @brief Executes the end command, ending the game.
     *
     * @param game The game interface.
     * @return Always returns true.
     */
    virtual bool execute(GameInterface &game) const override;
};

#endif //SEMESTRALKA_ENDCOMMAND_H
