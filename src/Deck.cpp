#include "Deck.h"

Deck::Deck(std::vector<std::shared_ptr<Card>> &cards)
        : m_cards(cards) {}

bool Deck::empty() const {
    return m_cards.empty();
}

size_t Deck::noOfCards() const {
    return m_cards.size();
}

void Deck::addCard(const std::shared_ptr<Card> &card) {
    m_cards.emplace_back(card);
}

void Deck::addCards(const std::vector<std::shared_ptr<Card>> &newCards) {
    m_cards.insert(m_cards.end(), newCards.begin(), newCards.end());
}

void Deck::mixCards() {
    size_t noOfCards = m_cards.size();
    std::srand(std::time(nullptr));
    for (size_t timesMixed = 0; timesMixed < noOfCards; timesMixed++) {
        for (size_t card1 = 0; card1 < noOfCards; card1++) {
            size_t card2 = rand() % noOfCards;
            std::swap(m_cards[card1], m_cards[card2]);
        }
    }
}

std::shared_ptr<Card> Deck::extractCard() {
    std::shared_ptr<Card> card = m_cards.back();
    m_cards.erase(m_cards.end() - 1);
    return card;
}

std::shared_ptr<Card> Deck::extractCardOnIndex(const size_t index) {
    std::shared_ptr<Card> card = m_cards.at(index);
    m_cards.erase(m_cards.begin() + index);
    return card;
}

std::vector<std::shared_ptr<Card>> Deck::extractCards() {
    std::vector<std::shared_ptr<Card>> cards(m_cards);
    m_cards.clear();
    return cards;
}

std::shared_ptr<Card> Deck::cardOnIndex(const size_t index) const {
    std::shared_ptr<Card> card = m_cards.at(index);
    return card;
}

size_t Deck::chooseMostHealingCard() const {
    size_t chosenCard = 0;
    int highestHPChange = INT32_MAX;
    size_t cardsCount = m_cards.size();
    for (size_t i = 0; i < cardsCount; i++) {
        int currentHPChange = 0, dummy = 0;
        m_cards[i]->resourcesNeeded(dummy, currentHPChange, dummy, dummy, dummy);
        if (currentHPChange <= highestHPChange) {
            chosenCard = i;
            highestHPChange = currentHPChange;
        }
    }
    return chosenCard;
}

size_t Deck::chooseMostDamagingCard() const {
    size_t chosenCard = 0;
    int highestDamage = INT32_MIN;
    size_t cardsCount = m_cards.size();
    for (size_t i = 0; i < cardsCount; i++) {
        int currentDamage = 0, dummy = 0;
        m_cards[i]->resourcesNeeded(dummy, currentDamage, dummy, dummy, dummy);
        if (currentDamage >= highestDamage) {
            chosenCard = i;
            highestDamage = currentDamage;
        }
    }
    return chosenCard;
}

void Deck::print() const {
    for (const auto &card: m_cards)
        card->print();
}

void Deck::toJSON(nlohmann::json &deckJSON) const {
    for (const auto &card: m_cards) {
        nlohmann::json cardJSON;
        card->toJSON(cardJSON);
        deckJSON.push_back(cardJSON);
    }
}
