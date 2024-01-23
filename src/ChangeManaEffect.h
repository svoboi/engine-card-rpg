//
// Created by svobi on 06.06.2023.
//

#ifndef SEMESTRAL_WORK_CHANGEMANAEFFECT_H
#define SEMESTRAL_WORK_CHANGEMANAEFFECT_H

#include "Effect.h"

/**
 * @class ChangeManaEffect
 * @brief Represents a change mana effect in the game.
 *
 * The ChangeManaEffect class is derived from the Effect class and provides functionalities for executing
 * a change mana effect on a specified player in the game, printing the change mana value of the effect,
 * and modifying the mana value of the provided resources.
 */
class ChangeManaEffect : public Effect {
public:
    ChangeManaEffect(const int change);

    /**
    * @brief Executes the change mana effect on the specified player in the game.
     *
     * @param game The game interface on which the effect will be executed.
     * @param playerIndex The index of the player affected by the effect.
     */
    virtual void execute(GameInterface &game, const size_t playerIndex) override;

    /**
     * @brief Prints the change mana effect value of the effect.
     */
    virtual void print() const override;

    /**
     * @brief Adds the mana value of the effect to the provided resources.
     *
     * @param attack The attack value (not modified).
     * @param HP The health points value (not modified).
     * @param mana The mana value to be modified.
     * @param offense The offense value (not modified).
     * @param defense The defense value (not modified).
     */
    virtual void addResources(int &attack, int &HP, int &mana, int &offense, int &defense) const override;

    /**
     * @brief Transforms ChangeManaEffect into given json
     *
     * @param effectJSON result json
     */
    virtual void toJSON(nlohmann::json &effectJSON) const override;

};


#endif //SEMESTRAL_WORK_CHANGEMANAEFFECT_H
