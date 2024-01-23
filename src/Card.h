#ifndef SEMESTRALKA_CARD_H
#define SEMESTRALKA_CARD_H

#include <string>
#include <vector>
#include <memory>
#include "Effect.h"
#include "GameInterface.h"
#include "../libs/json.hpp"

/**
 * @class Card
 * @brief Represents a card with it's effects in the game.
 *
 * The Card class is responsible for constructing a card with a name, description, and lists of effects.
 * It also provides functionalities for applying the effects on the game, printing the card's information,
 * and retrieving the effects on the card itself and on the enemy.
 */
class Card {
public:
    /**
     * construct new Card and counts needed resources
     */
    explicit Card(const std::string &name, const std::string &description,
                  const std::vector<std::shared_ptr<Effect>> &effectsOnMe,
                  const std::vector<std::shared_ptr<Effect>> &effectsOnEnemy);

    /**
     * goes through effects and calls execute on them with game and playerIndex as parameters
     */
    void applyEffects(GameInterface &game, int playerIndex, int enemyIndex);

    /**
     * @brief Applies the effects of the card on the game.
     *
     * @param game The game interface on which to apply the effects.
     * @param playerIndex The index of the player on whom to apply the effects.
     * @param enemyIndex The index of the enemy on whom to apply the effects.
     */
    void resourcesNeeded(int &attack, int &HP, int &mana, int &offense, int &defense) const;

    /**
     * @brief Prints the details of the card.
     */
    void print() const;

    /**
     * @brief Transforms Card into given json
     *
     * @param cardJSON result json
     */
    void toJSON(nlohmann::json &cardJSON) const;

protected:
    std::string m_name;
    std::string m_description;
    std::vector<std::shared_ptr<Effect>> m_effectsOnMe;
    std::vector<std::shared_ptr<Effect>> m_effectsOnEnemy;
};


#endif //SEMESTRALKA_CARD_H
