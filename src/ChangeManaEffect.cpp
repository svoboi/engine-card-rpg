#include "ChangeManaEffect.h"

ChangeManaEffect::ChangeManaEffect(const int change)
        : Effect(change) {}

void ChangeManaEffect::execute(GameInterface &game, const size_t playerIndex) {
    game.changeMana(m_change, playerIndex);
}

void ChangeManaEffect::print() const {
    std::cout << "  Mana: " << m_change << std::endl;
}

void ChangeManaEffect::addResources(int &attack, int &HP, int &mana, int &offense, int &defense) const {
    mana -= m_change;
}

void ChangeManaEffect::toJSON(nlohmann::json &effectJSON) const {
    effectJSON["type"] = "mana";
    effectJSON["strength"] = m_change;
}