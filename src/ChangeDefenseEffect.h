
#ifndef SEMESTRAL_WORK_CHANGEDEFENSEEFFECT_H
#define SEMESTRAL_WORK_CHANGEDEFENSEEFFECT_H


#include "Effect.h"

/**
 * @class ChangeDefenseEffect
 * @brief Represents a change defense effect in the game.
 *
 * The ChangeDefenseEffect class is derived from the Effect class and provides functionalities for executing
 * a change defense effect on a specified player in the game, printing the change defense value of the effect,
 * and modifying the defense value of the provided resources.
 */
class ChangeDefenseEffect : public Effect {
public:
    ChangeDefenseEffect(const int change);

    /**
     * @brief Executes the change defense effect on the specified player in the game.
     *
     * @param game The game interface on which the effect will be executed.
     * @param playerIndex The index of the player affected by the effect.
     */
    virtual void execute(GameInterface &game, const size_t playerIndex) override;

    /**
     * @brief Prints the change defense effect value of the effect.
     */
    virtual void print() const override;

    /**
     * @brief Adds the attack value of the effect to the provided resources.
     *
     * @param attack The attack value (not modified).
     * @param HP The health points value (not modified).
     * @param mana The mana value (not modified).
     * @param offense The offense value (not modified).
     * @param defense The defense value to be modified.
     */
    virtual void addResources(int &attack, int &HP, int &mana, int &offense, int &defense) const override;

    /**
     * @brief Transforms ChangeDefenseEffect into given json
     *
     * @param effectJSON result json
     */
    virtual void toJSON(nlohmann::json &effectJSON) const override;
};

#endif //SEMESTRAL_WORK_CHANGEDEFENSEEFFECT_H
