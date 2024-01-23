#ifndef SEMESTRALKA_EFFECT_H
#define SEMESTRALKA_EFFECT_H

#include <string>
#include <memory>
#include <iostream>
#include "GameInterface.h"
#include "../libs/json.hpp"

/**
 * @class Effect
 * @brief Represents an effect that can be applied in a game.
 *
 * The Effect class is an abstract base class that defines the common interface for all effects.
 * It provides methods for executing the effect, printing its value, adding the effect's value to resources,
 * and accessing the value of the change.
 */
class Effect {
public:
    Effect(const int change);

    virtual ~Effect() = default;

    /**
     * @brief Applies the effect on player in given game.
     *
     * @param game The game instance.
     * @param playerIndex The index of the player affected by the effect.
     */
    virtual void execute(GameInterface &game, const size_t playerIndex) = 0;

    /**
     * @brief Prints the effect value of the effect.
     */
    virtual void print() const = 0;

    /**
     * @brief Adds the effect value of the effect to the provided resources.
     *
     * @param attack The attack value to be modified.
     * @param HP The health points value to be modified.
     * @param mana The mana value to be modified.
     * @param offense The offense value to be modified.
     * @param defense The defense value to be modified.
     */
    virtual void addResources(int &attack, int &HP, int &mana, int &offense, int &defense) const = 0;

    /**
     * @brief Returns the value of the change.
     *
     * @return The value of the change.
     */
    int change() const;

    /**
     * @brief Transforms Effect into given json
     *
     * @param effectJSON result json
     */
    virtual void toJSON(nlohmann::json &effectJSON) const = 0;

protected:
    int m_change;
};


#endif //SEMESTRALKA_EFFECT_H
