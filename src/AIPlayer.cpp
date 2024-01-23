
#include "AIPlayer.h"

AIPlayer::AIPlayer(const std::string &name, const int healthPoints, const int healthPointsMax, const int mana,
                   const int manaMax,
                   const int manaRefillSpeed, const int offense, const int offenseMax, const int offenseRefillSpeed,
                   const int defense, const int defenseMax, const Deck &cardsInHand)
        : Player(name, healthPoints, healthPointsMax, mana, manaMax, manaRefillSpeed, offense, offenseMax,
                 offenseRefillSpeed, defense, defenseMax, cardsInHand) {}

AIPlayer::AIPlayer(const std::string &name, const int healthPoints, const int healthPointsMax, const int mana,
                   const int manaMax,
                   const int manaRefillSpeed, const int offense, const int offenseMax, const int offenseRefillSpeed,
                   const int defense, const int defenseMax)
        : Player(name, healthPoints, healthPointsMax, mana, manaMax, manaRefillSpeed, offense, offenseMax,
                 offenseRefillSpeed, defense, defenseMax) {}

std::shared_ptr<Command> AIPlayer::play(size_t myPlayerIndex, GameInterface &game) const {
    std::srand(std::time(nullptr));
    const int healthPanicModeCoefficient = 2;
    size_t cardNumber;
    size_t enemyIndex;
    if (m_healthPoints < m_healthPointsMax / healthPanicModeCoefficient) {
        cardNumber = m_cardsInHand.chooseMostHealingCard();
        if (canPlayCard(cardNumber)) {
            do {
                enemyIndex = rand() % game.noOfActivePlayer();
            } while (enemyIndex == myPlayerIndex);
            PlayCardCommand playCardCommand(enemyIndex, cardNumber);
            std::cout << "p " << cardNumber << " " << enemyIndex << std::endl;
            return std::make_shared<PlayCardCommand>(playCardCommand);
        }
    }
    enemyIndex = game.findLeastHealthyEnemy();
    cardNumber = m_cardsInHand.chooseMostDamagingCard();
    if (canPlayCard(cardNumber)) {
        PlayCardCommand playCardCommand(enemyIndex, cardNumber);
        std::cout << "p " << cardNumber << " " << enemyIndex << std::endl;
        return std::make_shared<PlayCardCommand>(playCardCommand);
    }
    for (size_t i = 0; i < m_cardsInHand.noOfCards() * 10; i++) {
        cardNumber = rand() % m_cardsInHand.noOfCards();
        if (canPlayCard(cardNumber)) {
            do {
                enemyIndex = rand() % game.noOfActivePlayer();
            } while (enemyIndex == myPlayerIndex);
            PlayCardCommand playCardCommand(enemyIndex, cardNumber);
            std::cout << "p " << cardNumber << " " << enemyIndex << std::endl;
            return std::make_shared<PlayCardCommand>(playCardCommand);
        }
    }
    ThrowCommand throwCommand(cardNumber);
    std::cout << "t " << cardNumber << std::endl;
    return std::make_shared<ThrowCommand>(throwCommand);
}

void AIPlayer::toJSON(nlohmann::json &playerJSON) const {
    playerJSON = nlohmann::json{{"name",               m_name},
                                {"healthPoints",       m_healthPoints},
                                {"healthPointsMax",    m_healthPointsMax},
                                {"mana",               m_mana},
                                {"manaMax",            m_manaMax},
                                {"manaRefillSpeed",    m_manaRefillSpeed},
                                {"offense",            m_offense},
                                {"offenseMax",         m_offenseMax},
                                {"offenseRefillSpeed", m_offenseRefillSpeed},
                                {"defense",            m_defense},
                                {"defenseMax",         m_defenseMax},
                                {"isAI",               true},
    };
    nlohmann::json deckJSON;
    m_cardsInHand.toJSON(deckJSON);
    playerJSON["cardsInHand"] = deckJSON;
}

std::shared_ptr<Player> AIPlayer::clone() const {
    AIPlayer newPlayer = *this;
    return std::make_shared<AIPlayer>(newPlayer);
}
