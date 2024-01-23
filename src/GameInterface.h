//
// Created by svobi on 14.05.2023.
//

#ifndef SEMESTRALKA_GAMEINTERFACE_H
#define SEMESTRALKA_GAMEINTERFACE_H

#include <string>

/**
 * @class GameInterface
 * @brief Interface for the game logic and operations.
 *
 * The GameInterface class provides an interface for interacting with the game logic and performing various operations.
 * It defines pure virtual functions that must be implemented by concrete game classes.
 */

class GameInterface {
public:
    virtual ~GameInterface() = default;

    /**
      * @brief Takes away card cardNumber from player and gives them new one
      * Moves card on cardNumber from players hand to m_usedCards.
      * Gives them new card from m_cardsInDeck, then moves onTurn to the next
      * and calls take card.
      */
    virtual void throwCard(const int cardNumber) = 0;

    /**
     * @brief Plays card, calls all of its effects.
     * Calls applyEffects on card cardNumber from player on playerIndex deck,
     * then calls throwCard. Only gives an error message if card cant be played
     */
    virtual bool playCard(const size_t enemyIndex, const int cardNumber) = 0;

    /**
     * @brief Moves onTurn to the next.
     */
    virtual void moveOnTurn() = 0;

    /**
     * @brief Saves the game to given fileName
     * Saves game to file of given name, but doesnt move onTurn to the next
    */
    virtual bool saveGame(const std::string &fileName) const = 0;

    /**
     * @brief Closes the game by setting m_running to false
     * Sets m_running to false, so that App knows to shut it down
     */
    virtual void endGame() = 0;

    /**
     * @brief Reduces or gives more offense to player on given position
     */
    virtual void changeOffense(const int offenseChange, const size_t playerIndex) = 0;

    /**
     * @brief Reduces or gives more defense to player on given position
     */
    virtual void changeDefense(const int defenseChange, const size_t playerIndex) = 0;

    /**
     * @brief Reduces or gives more mana to player on given position
     */
    virtual void changeMana(const int manaChange, const size_t playerIndex) = 0;

    /**
     * @brief First lowers defense and then HP of player
     */
    virtual void attack(const int attackStrength, const size_t playerIndex) = 0;

    /**
     * @brief Reduces or gives more HP to player on given position
     * Checks if final HP is zero - if yes, calls killPlayer.
     */
    virtual void changeHP(const int HPChange, const size_t playerIndex) = 0;

    /**
     * @brief Returns how many players are alive
     *
     * @return How many players are alive in m_activePlayers
     */
    virtual size_t noOfActivePlayer() const = 0;

    /**
     * @brief Finds the index of the least healthy enemy player.
     *
     * @return The index of the least healthy enemy player.
     */
    virtual size_t findLeastHealthyEnemy() const = 0;
};


#endif //SEMESTRALKA_GAMEINTERFACE_H
