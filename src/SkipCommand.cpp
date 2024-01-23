#include "SkipCommand.h"

bool SkipCommand::execute(GameInterface &game) const {
    game.moveOnTurn();
    return true;
}