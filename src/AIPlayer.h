
#ifndef SEMESTRAL_WORK_AIPLAYER_H
#define SEMESTRAL_WORK_AIPLAYER_H

#include "Player.h"

/**
 * @class AIPlayer
 * @brief The AIPlayer class represents an AI-controlled player in the game.
 *
 * The AIPlayer class inherits from the Player class and provides additional functionality specific to AI players.
 * It allows the AI player to make decisions and interact with the game by generating corresponding command objects.
 * The AIPlayer can choose to play a card or throw away a card.
 */
class AIPlayer : public Player {
public:
    AIPlayer(const std::string &name, const int healthPoints, const int healthPointsMax, const int mana,
             const int manaMax,
             const int manaRefillSpeed, const int offense, const int offenseMax, const int offenseRefillSpeed,
             const int defense, const int defenseMax, const Deck &cardsInHand);

    AIPlayer(const std::string &name, const int healthPoints, const int healthPointsMax, const int mana,
             const int manaMax,
             const int manaRefillSpeed, const int offense, const int offenseMax, const int offenseRefillSpeed,
             const int defense, const int defenseMax);

    /**
     * @brief Parses players input to generate the corresponding command object.
     *
     * The AIPlayer can choose to play a card or throw away a card.
     *
     * @param myPlayerIndex The index of the player.
     * @return A shared pointer to the generated command.
     */
    virtual std::shared_ptr<Command> play(size_t myPlayerIndex, GameInterface &game) const override;

    /**
     * @brief Transforms Player into given json
     *
     * @param playerJSON result json
     */
    virtual void toJSON(nlohmann::json &playerJSON) const override;

    /**
     * @brief Creates new copy of player
     * @return shared_ptr for the new player
     */
    virtual std::shared_ptr<Player> clone() const override;
};


#endif //SEMESTRAL_WORK_AIPLAYER_H
