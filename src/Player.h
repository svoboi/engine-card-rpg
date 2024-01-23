#ifndef SEMESTRALKA_PLAYER_H
#define SEMESTRALKA_PLAYER_H


#include <vector>
#include <sstream>
#include "Effect.h"
#include "Card.h"
#include "Deck.h"
#include "PlayCardCommand.h"
#include "SaveCommand.h"
#include "SkipCommand.h"
#include "ThrowCommand.h"
#include "EndCommand.h"
#include "../libs/json.hpp"

/**
 * @class Player
 * @brief Represents a player in the game.
 *
 * The Player class represents a player in the game. It encapsulates the player's name, health points, mana, offense,
 * defense and cards in hand.
 * The class provides various methods to interact with the player, such as playing cards, changing resources,
 * and retrieving player information.
 */
class Player {
public:
    Player(const std::string &name, const int healthPoints, const int healthPointsMax, const int mana,
           const int manaMax,
           const int manaRefillSpeed, const int offense, const int offenseMax, const int offenseRefillSpeed,
           const int defense, const int defenseMax, const Deck &cardsInHand);

    Player(const std::string &name, const int healthPoints, const int healthPointsMax, const int mana,
           const int manaMax,
           const int manaRefillSpeed, const int offense, const int offenseMax, const int offenseRefillSpeed,
           const int defense, const int defenseMax);

    virtual ~Player() = default;

    /**
     * @brief Parses players input to generate the corresponding command object.
     *
     * The player can choose to play a card, throw away a card, skip the round, save the game, or end the game.
     *
     * @param myPlayerIndex The index of the player.
     * @return A shared pointer to the generated command.
     */
    virtual std::shared_ptr<Command> play(size_t myPlayerIndex, GameInterface &game) const = 0;

    /**
     * @brief Takes a card from the player's hand and returns it.
     *
     * @param cardNumber The index of the card to be given.
     * @return A shared pointer to the extracted card.
     */
    std::shared_ptr<Card> giveCard(const int cardNumber);

    /**
     * @brief Accepts a card and adds it to the player's hand.
     *
     * @param card A shared pointer to the card to be accepted.
     */
    void acceptCard(const std::shared_ptr<Card> &card);

    /**
     * @brief Refills the player's mana and offense.
     */
    void refill();

    /**
     * @brief Changes the player's health points by the amount specified in diff.
     *
     * @param diff The amount by which to change the player's health points.
     */
    void changeHP(const int diff);

    /**
     * @brief Changes the player's mana by the amount specified in diff.
     *
     * @param diff The amount by which to change the player's mana.
     */
    void changeMana(const int diff);

    /**
     * @brief Changes the player's offense by the amount specified in diff.
     *
     * @param diff The amount by which to change the player's offense.
     */
    void changeOffense(const int diff);

    /**
     * @brief Changes the player's defense by the amount specified in diff.
     *
     * @param diff The amount by which to change the player's defense.
     */
    void changeDefense(const int diff);

    /**
     * @brief Retrieves the name of the player.
     *
     * @return The name of the player.
     */
    std::string name() const;

    /**
     * @brief Retrieves the current health points of the player.
     *
     * @return The current health points of the player.
     */
    int healthPoints() const;

    /**
     * @brief Retrieves the defense value of the player.
     *
     * @return The defense value of the player.
     */
    int defense() const;

    /**
     * @brief Prints player's stats.
     */
    void printInfo() const;

    /**
     * @brief Prints player's cards.
     */
    void printCards() const;

    /**
     * @brief Transforms Player into given json
     *
     * @param playerJSON result json
     */
    virtual void toJSON(nlohmann::json &playerJSON) const = 0;

    /**
     * @brief Creates new copy of player
     * @return shared_ptr for the new player
     */
    virtual std::shared_ptr<Player> clone() const = 0;

protected:
    /**
     * @brief Checks if the player can play a card.
     *
     * @param cardNumber The index of the card in the player's hand.
     * @return True if the player can play the card, false otherwise.
     */
    bool canPlayCard(const size_t cardNumber) const;

    std::string m_name;
    int m_healthPoints;
    int m_healthPointsMax;
    int m_mana;
    int m_manaMax;
    int m_manaRefillSpeed;
    int m_offense;
    int m_offenseMax;
    int m_offenseRefillSpeed;
    int m_defense;
    int m_defenseMax;
    Deck m_cardsInHand;
};


#endif //SEMESTRALKA_PLAYER_H
