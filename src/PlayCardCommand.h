#ifndef SEMESTRALKA_PLAYCARDCOMMAND_H
#define SEMESTRALKA_PLAYCARDCOMMAND_H


#include "Command.h"

/**
 * @class PlayCardCommand
 * @brief Command to play a card in the game.
 *
 * The PlayCardCommand class is a concrete implementation of the Command interface.
 * It encapsulates the information necessary to execute the play card command,
 * including the index of the enemy and the index of the card to be played.
 * When executed, the command applies the effects of the played card in the game.
 */
class PlayCardCommand : public Command {
public:
    PlayCardCommand(const size_t enemyIndex, const size_t cardIndex);

    /**
     * @brief Executes the play card command in the game.
     *
     * @param game The game interface.
     * @return True if the command was successfully executed, false otherwise.
     */
    virtual bool execute(GameInterface &game) const override;

private:
    size_t m_enemyIndex;
    size_t m_cardIndex;
};

#endif //SEMESTRALKA_PLAYCARDCOMMAND_H
