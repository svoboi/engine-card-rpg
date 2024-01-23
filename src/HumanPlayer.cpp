#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(const std::string &name, const int healthPoints, const int healthPointsMax, const int mana,
                         const int manaMax, const int manaRefillSpeed, const int offense, const int offenseMax,
                         const int offenseRefillSpeed, const int defense, const int defenseMax, const Deck &cardsInHand)
        : Player(name, healthPoints, healthPointsMax, mana, manaMax, manaRefillSpeed, offense, offenseMax,
                 offenseRefillSpeed, defense, defenseMax, cardsInHand) {}

HumanPlayer::HumanPlayer(const std::string &name, const int healthPoints, const int healthPointsMax, const int mana,
                         const int manaMax, const int manaRefillSpeed, const int offense, const int offenseMax,
                         const int offenseRefillSpeed, const int defense, const int defenseMax)
        : Player(name, healthPoints, healthPointsMax, mana, manaMax, manaRefillSpeed, offense, offenseMax,
                 offenseRefillSpeed, defense, defenseMax) {}

std::shared_ptr<Command> HumanPlayer::play(const size_t myPlayerIndex, GameInterface &game) const {
    std::shared_ptr<Command> command;
    while (true) {
        std::string input;
        std::getline(std::cin, input);
        std::stringstream inputStream;
        inputStream.str(input);
        std::string mode;
        if (!(inputStream >> mode) && !std::cin.eof()) {
            std::cout << "You didnt write anything, try again or type 'h' for help!" << std::endl;
            inputStream.clear();
            continue;
        }
        if (std::cin.eof()) {
            EndCommand endCommand;
            return std::make_shared<EndCommand>(endCommand);
        }
        if (mode == "p" && (command = readPlayCommand(inputStream, myPlayerIndex)) != nullptr) {
            return command;
        } else if (mode == "t" && (command = readThrowCommand(inputStream, myPlayerIndex)) != nullptr) {
            return command;
        } else if (mode == "s") {
            SkipCommand skipCommand;
            return std::make_shared<SkipCommand>(skipCommand);
        } else if (mode == "save" && (command = readSaveCommand(inputStream)) != nullptr) {
            return command;
        } else if (mode == "e") {
            EndCommand endCommand;
            return std::make_shared<EndCommand>(endCommand);
        } else if (mode == "h") {
            std::cout
                    << "Play card: type 'p', a card number and name of player you want to be considered 'enemy', e.g. 'p 5 Player2'\n"
                       "Cards that don't have any effect on enemy can be player as 'p 4'\n"
                       "If you play card that has an effect on enemy without naming enemy, effects will be applied to you.\n"
                       "Throw away card: type 't' and a card number, e.g. 't 3'\n"
                       "Skip round: 's'\n"
                       "Save: type 'save' and name for your save file, e.g. 'save savefile1'\n"
                       "End game: 'e'\n" << std::endl;
        } else if (mode != "p" && mode != "t" && mode != "s" && mode != "save" && mode != "e" && mode != "h") {
            std::cout << "Invalid input! for help type 'h'" << std::endl;
        }
    }
    return nullptr;
}

std::shared_ptr<Command> HumanPlayer::readSaveCommand(std::stringstream &inputStream) const {
    std::string saveFileName;
    if (!(inputStream >> saveFileName)) {
        inputStream.clear();
        std::cout << "Please include save file name!" << std::endl;
        return nullptr;
    }
    SaveCommand saveCommand(saveFileName);
    return std::make_shared<SaveCommand>(saveCommand);
}

std::shared_ptr<Command>
HumanPlayer::readPlayCommand(std::stringstream &inputStream, const size_t myPlayerIndex) const {
    size_t cardNumber;
    if (!(inputStream >> cardNumber)) {
        inputStream.clear();
        std::cout << "Please include card number!" << std::endl;
        return nullptr;
    }
    if (cardNumber > m_cardsInHand.noOfCards() - 1) {
        std::cout << "Card number too high, try again!" << std::endl;
        return nullptr;
    }
    if (!canPlayCard(cardNumber)) {
        std::cout << "You dont have enough resources to play this card, try again!" << std::endl;
        return nullptr;
    }
    size_t enemyNumber;

    if (!(inputStream >> enemyNumber)) {
        PlayCardCommand command(myPlayerIndex, cardNumber);
        std::cin.clear();
        return std::make_shared<PlayCardCommand>(command);
    } else {
        PlayCardCommand command(enemyNumber, cardNumber);
        return std::make_shared<PlayCardCommand>(command);
    }
}

std::shared_ptr<Command>
HumanPlayer::readThrowCommand(std::stringstream &inputStream, const size_t myPlayerIndex) const {
    size_t cardNumber;
    if (!(inputStream >> cardNumber)) {
        inputStream.clear();
        std::cout << "Please include card number!" << std::endl;
        return nullptr;
    }
    if (cardNumber > m_cardsInHand.noOfCards() - 1) {
        std::cout << "Card number too high, try again!" << std::endl;
        return nullptr;
    }
    ThrowCommand command(cardNumber);
    return std::make_shared<ThrowCommand>(command);
}

void HumanPlayer::toJSON(nlohmann::json &playerJSON) const {
    playerJSON = nlohmann::json{{"name",               m_name},
                                {"healthPoints",       m_healthPoints},
                                {"healthPointsMax",    m_healthPointsMax},
                                {"mana",               m_mana},
                                {"manaMax",            m_manaMax},
                                {"manaRefillSpeed",    m_manaRefillSpeed},
                                {"offense",            m_offense},
                                {"offenseMax",         m_offenseMax},
                                {"offenseRefillSpeed", m_offenseRefillSpeed},
                                {"defense",            m_defense},
                                {"defenseMax",         m_defenseMax},
                                {"isAI",               false},
    };
    nlohmann::json deckJSON;
    m_cardsInHand.toJSON(deckJSON);
    playerJSON["cardsInHand"] = deckJSON;
}

std::shared_ptr<Player> HumanPlayer::clone() const {
    HumanPlayer newPlayer = *this;
    return std::make_shared<HumanPlayer>(newPlayer);
}