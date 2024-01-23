
#include "ChangeOffenseEffect.h"

ChangeOffenseEffect::ChangeOffenseEffect(const int change)
        : Effect(change) {}

void ChangeOffenseEffect::execute(GameInterface &game, const size_t playerIndex) {
    game.changeOffense(m_change, playerIndex);
}

void ChangeOffenseEffect::print() const {
    std::cout << "  Offense: " << m_change << std::endl;
}

void ChangeOffenseEffect::addResources(int &attack, int &HP, int &mana, int &offense, int &defense) const {
    offense -= m_change;
}

void ChangeOffenseEffect::toJSON(nlohmann::json &effectJSON) const {
    effectJSON["type"] = "offense";
    effectJSON["strength"] = m_change;
}