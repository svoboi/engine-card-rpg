#ifndef SEMESTRAL_WORK_HUMANPLAYER_H
#define SEMESTRAL_WORK_HUMANPLAYER_H

#include "Player.h"

/**
 * @class HumanPlayer
 * @brief The HumanPlayer class represents a human player in the game.
 *
 * The HumanPlayer class inherits from the Player class and provides additional functionality specific to human players.
 * It allows the human player to interact with the game by parsing their input and generating corresponding command objects.
 * The human player can choose to play a card, throw away a card, skip the round, save the game, or end the game.
 */
class HumanPlayer : public Player {
public:
    HumanPlayer(const std::string &name, const int healthPoints, const int healthPointsMax, const int mana,
                const int manaMax,
                const int manaRefillSpeed, const int offense, const int offenseMax, const int offenseRefillSpeed,
                const int defense, const int defenseMax, const Deck &cardsInHand);

    HumanPlayer(const std::string &name, const int healthPoints, const int healthPointsMax, const int mana,
                const int manaMax,
                const int manaRefillSpeed, const int offense, const int offenseMax, const int offenseRefillSpeed,
                const int defense, const int defenseMax);

    /**
     * @brief Parses players input to generate the corresponding command object.
     *
     * The player can choose to play a card, throw away a card, skip the round, save the game, or end the game.
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

protected:
    /**
     * @brief Reads a save command from the input stream.
     *
     * @param inputStream The input stream containing the save file name.
     * @return A shared pointer to the generated SaveCommand object, or nullptr if the save file name is missing.
     */
    std::shared_ptr<Command> readSaveCommand(std::stringstream &inputStream) const;

    /**
     * @brief Reads a play command from the input stream.
     *
     * @param inputStream The input stream containing the card number and (optional) enemy number.
     * @param myPlayerIndex The index of the player.
     * @return A shared pointer to the generated PlayCardCommand object, or nullptr if the card number is missing
     *         or the player does not have enough resources to play the card.
     */
    std::shared_ptr<Command> readPlayCommand(std::stringstream &inputStream, const size_t myPlayerIndex) const;

    /**
     * @brief Reads a throw command from the input stream.
     *
     * @param inputStream The input stream containing the card number.
     * @param myPlayerIndex The index of the player.
     * @return A shared pointer to the generated ThrowCommand object, or nullptr if the card number is missing.
     */
    std::shared_ptr<Command> readThrowCommand(std::stringstream &inputStream, const size_t myPlayerIndex) const;

    /**
     * @brief Creates new copy of player
     * @return shared_ptr for the new player
     */
    virtual std::shared_ptr<Player> clone() const override;
};


#endif //SEMESTRAL_WORK_HUMANPLAYER_H
