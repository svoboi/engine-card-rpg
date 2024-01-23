#include "ChangeHPEffect.h"

ChangeHPEffect::ChangeHPEffect(const int change)
        : Effect(change) {}

void ChangeHPEffect::execute(GameInterface &game, const size_t playerIndex) {
    game.changeHP(m_change, playerIndex);
}

void ChangeHPEffect::print() const {
    std::cout << "  HP: " << m_change << std::endl;
}

void ChangeHPEffect::addResources(int &attack, int &HP, int &mana, int &offense, int &defense) const {
    HP -= m_change;
}

void ChangeHPEffect::toJSON(nlohmann::json &effectJSON) const {
    effectJSON["type"] = "HP";
    effectJSON["strength"] = m_change;
}