#ifndef SEMESTRAL_WORK_CHANGEOFFENSEEFFECT_H
#define SEMESTRAL_WORK_CHANGEOFFENSEEFFECT_H


#include "Effect.h"

/**
 * @class ChangeOffenseEffect
 * @brief Represents a change offense effect in the game.
 *
 * The ChangeOffenseEffect class is derived from the Effect class and provides functionalities for executing
 * a change offense effect on a specified player in the game, printing the change offense value of the effect,
 * and modifying the offense value of the provided resources.
 */
class ChangeOffenseEffect : public Effect {
public:
    ChangeOffenseEffect(const int change);

    /**
     * @brief Executes the change offense effect on the specified player in the game.
     *
     * @param game The game interface on which the effect will be executed.
     * @param playerIndex The index of the player affected by the effect.
     */
    virtual void execute(GameInterface &game, const size_t playerIndex) override;

    /**
     * @brief Prints the offense HP effect value of the effect.
     */
    virtual void print() const override;

    /**
     * @brief Adds the offense value of the effect to the provided resources.
     *
     * @param attack The attack value (not modified).
     * @param HP The health points value (not modified).
     * @param mana The mana value (not modified).
     * @param offense The offense value to be modified.
     * @param defense The defense value (not modified).
     */
    virtual void addResources(int &attack, int &HP, int &mana, int &offense, int &defense) const override;

    /**
     * @brief Transforms ChangeOffenseEffect into given json
     *
     * @param effectJSON result json
     */
    virtual void toJSON(nlohmann::json &effectJSON) const override;

};

#endif //SEMESTRAL_WORK_CHANGEOFFENSEEFFECT_H
