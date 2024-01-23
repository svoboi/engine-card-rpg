#ifndef SEMESTRALKA_DECK_H
#define SEMESTRALKA_DECK_H


#include <vector>
#include "Card.h"
#include "../libs/json.hpp"
#include <ctime>

/**
 * @class Deck
 * @brief Represents a deck of cards.
 *
 * The Deck class manages a collection of cards and provides various operations for manipulating the deck.
 */
class Deck {
public:
    Deck() = default;

    Deck(std::vector<std::shared_ptr<Card>> &cards);

    /**
     * @brief Checks if the deck is empty.
     *
     * @return True if the deck is empty, false otherwise.
     */
    bool empty() const;

    /**
     * @brief Returns the number of cards in the container.
     *
     * @return The number of cards in the container.
     */
    size_t noOfCards() const;

    /**
     * @brief Adds a card to the deck.
     *
     * @param card Card to add to the deck.
     */
    void addCard(const std::shared_ptr<Card> &card);

    /**
     * @brief Adds a vector of cards to the deck.
     *
     * @param newCards The vector of cards to add to the deck.
     */
    void addCards(const std::vector<std::shared_ptr<Card>> &newCards);

    /**
     * @brief Randomly mixes the cards in the deck.
     */
    void mixCards();

    /**
     * @brief Extracts and returns a card from the deck.
     *
     * @return a shared pointer to the extracted card.
     */
    std::shared_ptr<Card> extractCard();

    /**
     * @brief Extracts and returns a card from the deck at the specified index.
     *
     * @param index The index of the card to extract.
     * @return A shared pointer to the extracted card.
     */
    std::shared_ptr<Card> extractCardOnIndex(const size_t index);

    /**
     * @brief Extracts and returns all the cards from the deck.
     *
     * @return A vector of shared pointers to the extracted cards.
     */
    std::vector<std::shared_ptr<Card>> extractCards();

    /**
     * @brief Returns the card at the specified index in the deck.
     *
     * @param index The index of the card to retrieve.
     * @return A shared pointer to the card at the specified index.
     */
    std::shared_ptr<Card> cardOnIndex(const size_t index) const;

    /**
     * @brief Chooses the index of the card with the highest healing effect in the deck.
     *
     * @return The index of the card with the highest healing effect.
     */
    size_t chooseMostHealingCard() const;

    /**
     * @brief Chooses the index of the card with the highest damaging effect in the deck.
     *
     * @return The index of the card with the highest damaging effect.
     */
    size_t chooseMostDamagingCard() const;

    /**
     * @brief Prints the information of each card in the deck.
     */
    void print() const;

    /**
     * @brief Transforms Deck into given json
     *
     * @param deckJSON result json
     */
    void toJSON(nlohmann::json &deckJSON) const;

private:
    std::vector<std::shared_ptr<Card>> m_cards;
};


#endif //SEMESTRALKA_DECK_H
