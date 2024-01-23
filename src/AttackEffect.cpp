#include "AttackEffect.h"

AttackEffect::AttackEffect(const int change)
        : Effect(change) {}


void AttackEffect::execute(GameInterface &game, const size_t playerIndex) {
    game.attack(m_change, playerIndex);
}

void AttackEffect::print() const {
    std::cout << "  Attack: " << m_change << std::endl;
}

void AttackEffect::addResources(int &attack, int &HP, int &mana, int &offense, int &defense) const {
    attack += m_change;
}

void AttackEffect::toJSON(nlohmann::json &effectJSON) const {
    effectJSON["type"] = "attack";
    effectJSON["strength"] = m_change;
}