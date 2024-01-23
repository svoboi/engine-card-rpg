//
// Created by svobi on 06.06.2023.
//

#ifndef SEMESTRAL_WORK_ATTACKEFFECT_H
#define SEMESTRAL_WORK_ATTACKEFFECT_H


#include "Effect.h"

/**
 * @class AttackEffect
 * @brief Represents an attack effect in the game.
 *
 * The AttackEffect class is derived from the Effect class and provides functionalities for executing an attack effect
 * on a specified player in the game, printing the attack value of the effect, and modifying the attack value of the
 * provided resources.
 */
class AttackEffect : public Effect {
public:

    AttackEffect(const int change);

    /**
     * @brief Executes the attack effect on the specified player in the game.
     *
     * @param game The game interface on which the effect will be executed.
     * @param playerIndex The index of the player affected by the effect.
     */
    virtual void execute(GameInterface &game, const size_t playerIndex) override;

    /**
     * @brief Prints the attack value of the effect.
     */
    virtual void print() const override;

    /**
     * @brief Adds the attack value of the effect to the provided resources.
     *
     * @param attack The attack value to be modified.
     * @param HP The health points value (not modified).
     * @param mana The mana value (not modified).
     * @param offense The offense value (not modified).
     * @param defense The defense value (not modified).
     */
    virtual void addResources(int &attack, int &HP, int &mana, int &offense, int &defense) const override;

    /**
     * @brief Transforms AttackEffect into given json
     *
     * @param effectJSON result json
     */
    virtual void toJSON(nlohmann::json &effectJSON) const override;
};


#endif //SEMESTRAL_WORK_ATTACKEFFECT_H
