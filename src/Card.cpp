#include "Card.h"

Card::Card(const std::string &name, const std::string &description,
           const std::vector<std::shared_ptr<Effect>> &effectsOnMe,
           const std::vector<std::shared_ptr<Effect>> &effectsOnEnemy)
        : m_name(name), m_description(description), m_effectsOnMe(effectsOnMe), m_effectsOnEnemy(effectsOnEnemy) {}

void Card::applyEffects(GameInterface &game, int playerIndex, int enemyIndex) {
    for (const auto &effect: m_effectsOnMe)
        effect->execute(game, playerIndex);
    for (const auto &effect: m_effectsOnEnemy)
        effect->execute(game, enemyIndex);
}

void Card::resourcesNeeded(int &attack, int &HP, int &mana, int &offense, int &defense) const {
    for (const auto &effect: m_effectsOnMe) {
        effect->addResources(attack, HP, mana, offense, defense);
    }
}

void Card::print() const {
    std::cout << "Name: " << m_name << "\n";
    std::cout << " " << m_description << "\n";
    std::cout << "Effects on Me:" << std::endl;
    for (const auto &effect: m_effectsOnMe) {
        effect->print();
    }
    std::cout << "Effects on Enemy:" << std::endl;
    for (const auto &effect: m_effectsOnEnemy) {
        effect->print();
    }
    std::cout << std::endl;
}

void Card::toJSON(nlohmann::json &cardJSON) const {
    nlohmann::json effectsOnMe;
    for (const auto &effect: m_effectsOnMe) {
        nlohmann::json effectJSON;
        effect->toJSON(effectJSON);
        effectsOnMe.push_back(effectJSON);
    }
    cardJSON["effectsOnMe"] = effectsOnMe;
    nlohmann::json effectsOnEnemy;
    for (const auto &effect: m_effectsOnEnemy) {
        nlohmann::json effectJSON;
        effect->toJSON(effectJSON);
        effectsOnEnemy.push_back(effectJSON);
    }
    cardJSON["effectsOnEnemy"] = effectsOnEnemy;
    cardJSON["name"] = m_name;
    cardJSON["description"] = m_description;
}
