#ifndef SEMESTRALKA_SAVECOMMAND_H
#define SEMESTRALKA_SAVECOMMAND_H


#include "Command.h"

/**
 * @class SaveCommand
 * @brief The SaveCommand class represents a command to save the game.
 *
 * The SaveCommand class is a concrete implementation of the Command interface.
 * It is responsible for executing the save command in the game, which saves the current state of the game to a file.
 * The save file name is provided during the construction of the SaveCommand object.
 */
class SaveCommand : public Command {
public:
    SaveCommand(const std::string &saveFileName);

    /**
     * @brief Executes the save command in the game.
     *
     * @param game The game interface.
     * @return True if the command was successfully executed, false otherwise.
     */
    virtual bool execute(GameInterface &game) const override;

private:
    std::string m_saveFileName;
};


#endif //SEMESTRALKA_SAVECOMMAND_H
