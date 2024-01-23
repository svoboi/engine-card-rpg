
#include "ThrowCommand.h"

ThrowCommand::ThrowCommand(const size_t cardIndex)
        : m_cardIndex(cardIndex) {}

bool ThrowCommand::execute(GameInterface &game) const {
    game.throwCard(m_cardIndex);
    return true;
}