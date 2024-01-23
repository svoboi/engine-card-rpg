//
// Created by svobi on 06.06.2023.
//

#ifndef SEMESTRAL_WORK_CHANGEHPEFFECT_H
#define SEMESTRAL_WORK_CHANGEHPEFFECT_H

#include "Effect.h"

/**
 * @class ChangeHPEffect
 * @brief Represents a change HP effect in the game.
 *
 * The ChangeHPEffect class is derived from the Effect class and provides functionalities for executing
 * a change HP effect on a specified player in the game, printing the change HP value of the effect,
 * and modifying the HP value of the provided resources.
 */
class ChangeHPEffect : public Effect {
public:
    ChangeHPEffect(const int change);

    /**
     * @brief Executes the change HP effect on the specified player in the game.
     *
     * @param game The game interface on which the effect will be executed.
     * @param playerIndex The index of the player affected by the effect.
     */
    virtual void execute(GameInterface &game, const size_t playerIndex) override;

    /**
     * @brief Prints the change HP effect value of the effect.
     */
    virtual void print() const override;

    /**
     * @brief Adds the attack value of the effect to the provided resources.
     *
     * @param attack The attack value (not modified).
     * @param HP The health points value to be modified.
     * @param mana The mana value (not modified).
     * @param offense The offense value (not modified).
     * @param defense The defense value (not modified).
     */
    virtual void addResources(int &attack, int &HP, int &mana, int &offense, int &defense) const override;

    /**
     * @brief Transforms ChangeHPEffect into given json
     *
     * @param effectJSON result json
     */
    virtual void toJSON(nlohmann::json &effectJSON) const override;
};


#endif //SEMESTRAL_WORK_CHANGEHPEFFECT_H
