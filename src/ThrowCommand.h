#ifndef SEMESTRALKA_THROWCOMMAND_H
#define SEMESTRALKA_THROWCOMMAND_H

#include "Command.h"

/**
 * @class ThrowCommand
 * @brief The ThrowCommand class represents a command to throw away a card in the game.
 *
 * The ThrowCommand class inherits from the Command class and implements the execute() method to throw away a card from the player's hand.
 * When executed, this command removes the specified card from the player's hand and moves it to the discard pile.
 */
class ThrowCommand : public Command {
public:
    ThrowCommand(const size_t cardIndex);

    /**
     * @brief Executes the throw command in the game.
     *
     * @param game The game interface.
     * @return True if the command was successfully executed, false otherwise.
     */
    virtual bool execute(GameInterface &game) const override;

private:
    size_t m_cardIndex;
};

#endif //SEMESTRALKA_THROWCOMMAND_H
