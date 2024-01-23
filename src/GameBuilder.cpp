#include "GameBuilder.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"

std::unique_ptr<Game> GameBuilder::buildFromFile(const std::string &fileName, const bool fromConfigFile) const {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        return nullptr;
    }
    nlohmann::json gameJSON;
    try {
        gameJSON = nlohmann::json::parse(file);

    } catch (const nlohmann::json::parse_error &e) {
        std::cout << "This json can't be parsed!" << std::endl;
        return nullptr;
    }
    if (!gameJSON.contains("players") || !gameJSON.contains("cardsVisibility")
        || !gameJSON.contains("noOfCardsInHand")) {
        std::cout << "players, cardsVisibility or noOfCardsInHand is missing!" << std::endl;
        return nullptr;
    }
    int noOfCardsInHand = gameJSON["noOfCardsInHand"];

    const nlohmann::json &playersJSON = gameJSON["players"];
    std::vector<std::shared_ptr<Player>> players;
    if (!buildPlayers(playersJSON, noOfCardsInHand, players, false)) {
        return nullptr;
    }

    nlohmann::json cardsInDeckJSON = gameJSON["cardsInDeck"];
    std::vector<std::shared_ptr<Card>> cardsInDeckVector;
    if (!buildDeck(cardsInDeckJSON, cardsInDeckVector)) {
        return nullptr;
    }
    CardsVisibility cardsVisibility;
    int cardsVisibilityInt = gameJSON["cardsVisibility"];
    if (cardsVisibilityInt == 0) {
        cardsVisibility = CardsVisibility::OPEN;
    } else if (cardsVisibilityInt == 1) {
        cardsVisibility = CardsVisibility::CLOSED;
    } else {
        std::cout << "Unknown visibility of cards!" << std::endl;
        return nullptr;
    }

    if (fromConfigFile) {
        if (!gameJSON.contains("cardsQuantities")) {
            std::cout << "cardsQuantities are missing!" << std::endl;
            return nullptr;
        }
        std::vector<std::shared_ptr<Card>> cardsWithCorrectQuantities;
        std::vector<int> quantities = gameJSON["cardsQuantities"];
        if (quantities.size() != cardsInDeckVector.size()) {
            std::cout << "Number of cards and their quantities is different!" << std::endl;
            return nullptr;
        }
        size_t quantityCount = quantities.size();
        for (size_t i = 0; i < quantityCount; i++) {
            int quantityOfCardOnIndexI = quantities[i];
            for (int j = 0; j < quantityOfCardOnIndexI; j++) {
                cardsWithCorrectQuantities.emplace_back(cardsInDeckVector[i]);
            }
        }
        Deck cardsInDeck(cardsWithCorrectQuantities);
        std::unique_ptr<Game> game = std::make_unique<Game>(players, cardsInDeck, cardsVisibility, noOfCardsInHand);
        return game;
    } else {
        Deck cardsInDeck(cardsInDeckVector);
        if (!gameJSON.contains("activePlayers") || !gameJSON.contains("onTurn") || !gameJSON.contains("usedCards")) {
            std::cout << "activePlayers, onTurn or usedCards is missing!" << std::endl;
            return nullptr;
        }

        const nlohmann::json &activePlayersJSON = gameJSON["activePlayers"];
        std::vector<std::shared_ptr<Player>> activePlayers;
        if (!buildPlayers(activePlayersJSON, noOfCardsInHand, activePlayers, true)) {
            return nullptr;
        }

        size_t onTurn = gameJSON["onTurn"];
        if (onTurn >= activePlayers.size()) {
            std::cout << "onTurn is too high." << std::endl;
            return nullptr;
        }
        nlohmann::json usedCardsJSON = gameJSON["usedCards"];
        std::vector<std::shared_ptr<Card>> usedCardsVector;
        if (!buildDeck(usedCardsJSON, usedCardsVector)) {
            return nullptr;
        }
        Deck usedCards(cardsInDeckVector);
        std::unique_ptr<Game> game = std::make_unique<Game>(activePlayers, players, onTurn, cardsInDeck,
                                                            usedCards, cardsVisibility, noOfCardsInHand);
        return game;
    }
}


bool GameBuilder::buildEffects(const nlohmann::json &effectsJSON, std::vector<std::shared_ptr<Effect>> &effects) const {
    for (const auto &effectJSON: effectsJSON) {
        if (!effectJSON.contains("type")
            || !effectJSON.contains("strength")) {
            std::cout << "At least one of the effects doesn't contain type or strength!" << std::endl;
            return false;
        }
        std::string type = effectJSON["type"];
        int strength = effectJSON["strength"];

        if (type == "attack") {
            AttackEffect effect(strength);
            std::shared_ptr<AttackEffect> effectPt = std::make_shared<AttackEffect>(effect);
            effects.emplace_back(effectPt);
        } else if (type == "HP") {
            ChangeHPEffect effect(strength);
            std::shared_ptr<ChangeHPEffect> effectPt = std::make_shared<ChangeHPEffect>(effect);
            effects.push_back(effectPt);
        } else if (type == "offense") {
            ChangeOffenseEffect effect(strength);
            std::shared_ptr<ChangeOffenseEffect> effectPt = std::make_shared<ChangeOffenseEffect>(effect);
            effects.push_back(effectPt);
        } else if (type == "defense") {
            ChangeDefenseEffect effect(strength);
            std::shared_ptr<ChangeDefenseEffect> effectPt = std::make_shared<ChangeDefenseEffect>(effect);
            effects.push_back(effectPt);
        } else if (type == "mana") {
            ChangeManaEffect effect(strength);
            std::shared_ptr<ChangeManaEffect> effectPt = std::make_shared<ChangeManaEffect>(effect);
            effects.push_back(effectPt);
        } else {
            std::cout << "Unknown effect type!" << std::endl;
            return false;
        }
    }
    return true;
}

bool GameBuilder::buildDeck(const nlohmann::json &deckJSON, std::vector<std::shared_ptr<Card>> &cards) const {
    for (const auto &cardJSON: deckJSON) {
        if (!cardJSON.contains("effectsOnEnemy")
            || !cardJSON.contains("effectsOnMe")
            || !cardJSON.contains("name")
            || !cardJSON.contains("description")) {
            return false;
        }
        std::string name = cardJSON["name"];
        std::string description = cardJSON["description"];


        std::vector<std::shared_ptr<Effect>> effectsOnMe;

        const nlohmann::json &effectsOnMeJSON = cardJSON["effectsOnMe"];
        std::vector<Card> cardsVector;
        if (!buildEffects(effectsOnMeJSON, effectsOnMe)) {
            return false;
        }

        const nlohmann::json &effectsOnEnemyJSON = cardJSON["effectsOnEnemy"];
        std::vector<std::shared_ptr<Effect>> effectsOnEnemy;
        if (!buildEffects(effectsOnEnemyJSON, effectsOnEnemy)) {
            return false;
        }
        Card card(name, description, effectsOnMe, effectsOnEnemy);
        cards.emplace_back(std::make_shared<Card>(card));
    }
    return true;
}

bool GameBuilder::buildPlayers(const nlohmann::json &playersJSON, const size_t noOfCardsInHand,
                               std::vector<std::shared_ptr<Player>> &players, const bool withCards) const {
    for (const auto &playerJSON: playersJSON) {
        if (!playerJSON.contains("name")
            || !playerJSON.contains("healthPoints") || !playerJSON.contains("healthPointsMax")
            || !playerJSON.contains("mana") || !playerJSON.contains("manaMax")
            || !playerJSON.contains("manaRefillSpeed")
            || !playerJSON.contains("offense") || !playerJSON.contains("offenseMax")
            || !playerJSON.contains("offenseRefillSpeed")
            || !playerJSON.contains("defense") || !playerJSON.contains("defenseMax")
            || !playerJSON.contains("isAI")) {
            std::cout << "Unable to read players." << std::endl;
            return false;
        }
        std::string name = playerJSON["name"];
        int healthPoints = playerJSON["healthPoints"];
        int healthPointsMax = playerJSON["healthPointsMax"];
        int mana = playerJSON["mana"];
        int manaMax = playerJSON["manaMax"];
        int manaRefillSpeed = playerJSON["manaRefillSpeed"];
        int offense = playerJSON["offense"];
        int offenseMax = playerJSON["offenseMax"];
        int offenseRefillSpeed = playerJSON["offenseRefillSpeed"];
        int defense = playerJSON["defense"];
        int defenseMax = playerJSON["defenseMax"];
        bool isAI = playerJSON["isAI"];

        if (!withCards) {
            if (isAI) {
                AIPlayer humanPlayer(name, healthPoints, healthPointsMax, mana, manaMax, manaRefillSpeed, offense,
                                     offenseMax, offenseRefillSpeed, defense, defenseMax);
                players.emplace_back(std::make_shared<AIPlayer>(humanPlayer));
            } else {
                HumanPlayer humanPlayer(name, healthPoints, healthPointsMax, mana, manaMax, manaRefillSpeed, offense,
                                        offenseMax, offenseRefillSpeed, defense, defenseMax);
                players.emplace_back(std::make_shared<HumanPlayer>(humanPlayer));
            }
        } else {
            if (!playerJSON.contains("cardsInHand")) {
                std::cout << "At least one player doesn't contain cardsInHand" << std::endl;
                return false;
            }
            const nlohmann::json &deckJSON = playerJSON["cardsInHand"];
            std::vector<std::shared_ptr<Card>> cardsVector;
            if (!buildDeck(deckJSON, cardsVector)) {
                return false;
            }
            Deck cardsInHand(cardsVector);
            if (cardsInHand.noOfCards() != noOfCardsInHand) {
                std::cout << "At least one of the players has wrong number of cards." << std::endl;
                return false;
            }
            if (isAI) {
                AIPlayer humanPlayer(name, healthPoints, healthPointsMax, mana, manaMax, manaRefillSpeed, offense,
                                     offenseMax, offenseRefillSpeed, defense, defenseMax, cardsInHand);
                players.emplace_back(std::make_shared<AIPlayer>(humanPlayer));
            } else {
                HumanPlayer humanPlayer(name, healthPoints, healthPointsMax, mana, manaMax, manaRefillSpeed, offense,
                                        offenseMax, offenseRefillSpeed, defense, defenseMax, cardsInHand);
                players.emplace_back(std::make_shared<HumanPlayer>(humanPlayer));
            }
        }
    }
    return true;
}