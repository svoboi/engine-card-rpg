#ifndef SEMESTRALKA_GAMEBUILDER_H
#define SEMESTRALKA_GAMEBUILDER_H

#include <vector>
#include <string>
#include <memory>
#include "Game.h"
#include "AttackEffect.h"
#include "ChangeHPEffect.h"
#include "ChangeOffenseEffect.h"
#include "ChangeDefenseEffect.h"
#include "ChangeManaEffect.h"


class GameBuilder {
public:
    /**
     * @brief Builds a game instance from a file.
     *
     * @param fileName The name of the file to read the game data from.
     * @param fromConfigFile Determines whether the file is a configuration file or a saved game file.
     * @return A unique pointer to the built game instance, or nullptr if there was an error.
     */
    std::unique_ptr<Game> buildFromFile(const std::string &fileName, const bool fromConfigFile) const;

private:
    /**
     * @brief Builds a vector of effects based on the provided JSON data.
     *
     * @param effectsJSON The JSON data containing the effects.
     * @param effects The vector to store the built effects.
     * @return True if the effects were successfully built, false otherwise.
     */
    bool buildEffects(const nlohmann::json &effectsJSON, std::vector<std::shared_ptr<Effect>> &effects) const;

    /**
     * @brief Builds a vector of cards for the deck based on the provided JSON data.
     *
     * @param deckJSON The JSON data containing the cards for the deck.
     * @param cards The vector to store the built cards.
     * @return True if the cards were successfully built, false otherwise.
     */
    bool buildDeck(const nlohmann::json &deckJSON, std::vector<std::shared_ptr<Card>> &deck) const;

    /**
     * @brief Builds players based on the provided JSON data.
     *
     * @param playersJSON The JSON data containing the player information.
     * @param noOfCardsInHand The number of cards each player should have in their hand.
     * @param players The vector to store the built players.
     * @param withCards Determines whether to include cards in the player's deck or not.
     * @return True if the players were successfully built, false otherwise.
     */
    bool buildPlayers(const nlohmann::json &playerJSON, const size_t noOfCardsInHand,
                      std::vector<std::shared_ptr<Player>> &players, const bool fromConfigFile) const;
};


#endif //SEMESTRALKA_GAMEBUILDER_H
