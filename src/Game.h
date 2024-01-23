#ifndef SEMESTRALKA_GAMESTATE_H
#define SEMESTRALKA_GAMESTATE_H

#include <vector>
#include <string>
#include <memory>
#include <fstream>

#include "Player.h"
#include "Card.h"
#include "Deck.h"
#include "CardsVisibility.h"
#include "GameInterface.h"
#include "../libs/json.hpp"

/**
 * @class Game
 * @brief Represents a game with players, cards, and game-related operations.
 */
class Game : public GameInterface {
public:
    /**
     * Constructor for new game
     * @param players All players taking part in the game
     * @param cardsInDeck Cards usable during the game
     * @param cardsVisibility OPEN or CLOSED depending on the mode of the game
     * @param numberOfCardsInHand Number of cards that players should hold during the game
     */
    Game(const std::vector<std::shared_ptr<Player>> &players, const Deck &cardsInDeck,
         const CardsVisibility cardsVisibility, const int numberOfCardsInHand);

    Game(const std::vector<std::shared_ptr<Player>> &activePlayers,
         const std::vector<std::shared_ptr<Player>> &players,
         const size_t onTurn, const Deck &cardsInDeck, const Deck &usedCards,
         const CardsVisibility cardsVisibility, const int numberOfCardsInHand);

    ~Game() {}

    /**
     * @brief Prints the current state of the game.
     *
     * If the cards are visible (CardsVisibility::OPEN), it prints the information and cards of all active players.
     * Otherwise, it prompts the user to press enter to take over for the current player, and then prints the information
     * of all active players, and the cards of the player on turn.
     * Displays the name of the player currently on turn.
     */
    void print() const;

    /**
     * @brief Checks if the game can be set up based on number of cards and number of players
     * @return true if game can be set up,
     */
    bool canBeSetUp() const;

    /**
     * @brief Sets up the game.
     *
     * This function is responsible for setting up the game by initializing various game-related variables and
     * distributing cards to the active players.
     */
    void setUpGame(bool &startWithSavedGame);

    /**
     * @brief Advances the game to the next turn.
     *
     * This function progresses the game to the next turn by obtaining a command from the player on turn
     * or generating one for AI players. The command is executed, and the process repeats until a valid command
     * is executed. Doesnt move m_onTurn, that happens in only some commands, since player can also save game
     */
    void nextTurn();


    /**
     * @brief Returns if the game should be running.
     */
    bool running() const;

    /**
     * @brief Returns name of the winner.
     */
    std::string winner() const;

    /**
     * @brief Takes away card cardNumber from player and gives them new one, moves on Turn
     */
    virtual void throwCard(const int cardNumber) override;

    /**
     * @brief Plays card, calls all of its effects.
     * Calls applyEffects on card cardNumber from player on playerIndex deck,
     * then calls throwCard. Only gives an error message if card cant be played
     */
    virtual bool playCard(const size_t enemyIndex, const int cardNumber) override;

    /**
     * @brief Saves the game to given fileName
     * Saves game to file of given name, but doesnt move onTurn to the next
    */
    virtual bool saveGame(const std::string &filePath) const override;

    /**
     * @brief Closes the game by setting m_running to false
     * Sets m_running to false, so that App knows to shut it down
     */
    virtual void endGame() override;

    /**
     * @brief First lowers defense and then HP of player
     */
    virtual void attack(const int attackStrength, const size_t playerIndex) override;

    /**
     * @brief Reduces or gives more HP to player on given position
     * Checks if final HP is zero - if yes, calls killPlayer.
     */
    virtual void changeHP(const int HPChange, const size_t playerIndex) override;

    /**
     * @brief Reduces or gives more offense to player on given position
     */
    virtual void changeOffense(const int offenseChange, const size_t playerIndex) override;

    /**
     * @brief Reduces or gives more defense to player on given position
     */
    virtual void changeDefense(const int defenseChange, const size_t playerIndex) override;

    /**
     * @brief Reduces or gives more mana to player on given position
     */
    virtual void changeMana(const int manaChange, const size_t playerIndex) override;

    /**
     * @brief Returns how many players are alive
     * @return How many players are alive in m_activePlayers
     */
    virtual size_t noOfActivePlayer() const override;

private:
    /**
     * @brief Kills a player in the game.
     * Takes away their cards and then erases them from active players.
     * If only one player is alive, set winner and sets running to false.
     */
    void killPlayer(const size_t playerIndex);

    /**
     * @brief Moves onTurn to the next.
     */
    void moveOnTurn() override;

    /**
     * @brief Gives last card from deck to player on turn.
     */
    void takeCard();

    /**
     * @brief Finds the index of the least healthy enemy player.
     *
     * This function searches for the player with the lowest health points among the active players,
     * excluding the current player on turn. It returns the index of the least healthy enemy player.
     *
     * @return The index of the least healthy enemy player.
     */
    virtual size_t findLeastHealthyEnemy() const override;

    /**
     * @brief Reconstructs the active players list from the original players list.
     */
    void reconstructPlayers();

    bool m_running;
    std::vector<std::shared_ptr<Player>> m_activePlayers;
    std::vector<std::shared_ptr<Player>> m_players;
    size_t m_onTurn = 0;
    std::string m_winner;
    Deck m_cardsInDeck;
    Deck m_usedCards;
    CardsVisibility m_cardsVisibility = CardsVisibility::CLOSED;
    int m_noOfCardsInHand;
};


#endif //SEMESTRALKA_GAMESTATE_H
