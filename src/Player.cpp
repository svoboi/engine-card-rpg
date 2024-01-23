#include "Player.h"

Player::Player(const std::string &name, const int healthPoints, const int healthPointsMax, const int mana,
               const int manaMax,
               const int manaRefillSpeed, const int offense, const int offenseMax, const int offenseRefillSpeed,
               const int defense, const int defenseMax, const Deck &cardsInHand)
        : m_name(name), m_healthPoints(healthPoints), m_healthPointsMax(healthPointsMax),
          m_mana(mana), m_manaMax(manaMax), m_manaRefillSpeed(manaRefillSpeed), m_offense(offense),
          m_offenseMax(offenseMax), m_offenseRefillSpeed(offenseRefillSpeed), m_defense(defense),
          m_defenseMax(defenseMax), m_cardsInHand(cardsInHand) {}

Player::Player(const std::string &name, const int healthPoints, const int healthPointsMax, const int mana,
               const int manaMax,
               const int manaRefillSpeed, const int offense, const int offenseMax, const int offenseRefillSpeed,
               const int defense, const int defenseMax)
        : m_name(name), m_healthPoints(healthPoints), m_healthPointsMax(healthPointsMax),
          m_mana(mana), m_manaMax(manaMax), m_manaRefillSpeed(manaRefillSpeed), m_offense(offense),
          m_offenseMax(offenseMax), m_offenseRefillSpeed(offenseRefillSpeed), m_defense(defense),
          m_defenseMax(defenseMax) {}

bool Player::canPlayCard(const size_t cardNumber) const {
    int attack = 0, HPNeeded = 0, manaNeeded = 0, offenseNeeded = 0, defenseNeeded = 0;
    m_cardsInHand.cardOnIndex(cardNumber)->resourcesNeeded(attack, HPNeeded, manaNeeded, offenseNeeded, defenseNeeded);
    if (attack >= m_defense - defenseNeeded) {
        HPNeeded += attack - m_defense + defenseNeeded;
        defenseNeeded += (defenseNeeded <= m_defense) ? m_defense : defenseNeeded;
    } else {
        defenseNeeded += attack;
    }
    if (m_mana < manaNeeded
        || m_healthPoints < HPNeeded
        || m_defense < defenseNeeded
        || m_offense < offenseNeeded)
        return false;
    return true;
}

std::shared_ptr<Card> Player::giveCard(const int cardNumber) {
    return m_cardsInHand.extractCardOnIndex(cardNumber);
}

void Player::acceptCard(const std::shared_ptr<Card> &card) {
    m_cardsInHand.addCard(card);
}

void Player::changeHP(int diff) {
    m_healthPoints = (m_healthPoints + diff > 0) ? (m_healthPoints + diff) : 0;
    if (m_healthPoints > m_healthPointsMax) {
        m_healthPoints = m_healthPointsMax;
    }
}

void Player::changeMana(int diff) {
    m_mana = (m_mana + diff > 0) ? (m_mana + diff) : 0;
    if (m_mana > m_manaMax) {
        m_mana = m_manaMax;
    }
}

void Player::changeOffense(int diff) {
    m_offense = (m_offense + diff > 0) ? (m_offense + diff) : 0;
    if (m_offense > m_offenseMax) {
        m_offense = m_offenseMax;
    }
}

void Player::changeDefense(int diff) {
    m_defense = (m_defense + diff > 0) ? (m_defense + diff) : 0;
    if (m_defense > m_defenseMax) {
        m_defense = m_defenseMax;
    }
}

void Player::refill() {
    changeMana(m_manaRefillSpeed);
    changeOffense(m_offenseRefillSpeed);
}

std::string Player::name() const {
    return m_name;
}

int Player::healthPoints() const {
    return m_healthPoints;
}

int Player::defense() const {
    return m_defense;
}

void Player::printInfo() const {
    std::cout << "Player: " << m_name << "\n";
    std::cout << " Health points: " << m_healthPoints << "/" << m_healthPointsMax << "\n";
    std::cout << " Mana: " << m_mana << "/" << m_manaMax << " (" << m_manaRefillSpeed << ")" << "\n";
    std::cout << " Offense: " << m_offense << "/" << m_offenseMax << " (" << m_offenseRefillSpeed << ")" << "\n";
    std::cout << " Defense: " << m_defense << "/" << m_defenseMax << "\n" << std::endl;
}

void Player::printCards() const {
    m_cardsInHand.print();
}
