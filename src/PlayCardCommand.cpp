
#include "PlayCardCommand.h"

PlayCardCommand::PlayCardCommand(const size_t enemyIndex, const size_t cardIndex)
        : m_enemyIndex(enemyIndex), m_cardIndex(cardIndex) {}

bool PlayCardCommand::execute(GameInterface &game) const {
    return game.playCard(m_enemyIndex, m_cardIndex);
}