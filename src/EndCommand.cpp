#include "EndCommand.h"

bool EndCommand::execute(GameInterface &game) const {
    game.endGame();
    return true;
}