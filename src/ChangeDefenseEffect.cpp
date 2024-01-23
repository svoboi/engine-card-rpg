
#include "ChangeDefenseEffect.h"

ChangeDefenseEffect::ChangeDefenseEffect(const int change)
        : Effect(change) {}

void ChangeDefenseEffect::execute(GameInterface &game, const size_t playerIndex) {
    game.changeDefense(m_change, playerIndex);
}

void ChangeDefenseEffect::print() const {
    std::cout << "  Defense: " << m_change << std::endl;
}

void ChangeDefenseEffect::addResources(int &attack, int &HP, int &mana, int &offense, int &defense) const {
    defense -= m_change;
}

void ChangeDefenseEffect::toJSON(nlohmann::json &effectJSON) const {
    effectJSON["type"] = "defense";
    effectJSON["strength"] = m_change;
}