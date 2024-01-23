#include "SaveCommand.h"

SaveCommand::SaveCommand(const std::string &saveFileName)
        : m_saveFileName(saveFileName) {}

bool SaveCommand::execute(GameInterface &game) const {
    return game.saveGame(m_saveFileName);
}