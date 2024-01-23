#include "Game.h"


Game::Game(const std::vector<std::shared_ptr<Player>> &players, const Deck &cardsInDeck,
           const CardsVisibility cardsVisibility, const int numberOfCardsInHand)
        : m_players(players), m_cardsInDeck(cardsInDeck),
          m_cardsVisibility(cardsVisibility), m_noOfCardsInHand(numberOfCardsInHand) {}

Game::Game(const std::vector<std::shared_ptr<Player>> &activePlayers,
           const std::vector<std::shared_ptr<Player>> &players,
           const size_t onTurn, const Deck &cardsInDeck, const Deck &usedCards,
           const CardsVisibility cardsVisibility, const int numberOfCardsInHand)
        : m_activePlayers(activePlayers), m_players(players), m_onTurn(onTurn), m_cardsInDeck(cardsInDeck),
          m_usedCards(usedCards), m_cardsVisibility(cardsVisibility), m_noOfCardsInHand(numberOfCardsInHand) {}

void Game::print() const {
    std::cout << "\n------------------------------------------------------------------------------\n" << std::endl;
    if (m_cardsVisibility == CardsVisibility::OPEN) {
        // Print information and cards for all active players
        for (const auto &player: m_activePlayers) {
            player->printInfo();
            player->printCards();
        }
    } else {
        std::cout << "\033[2J\033[1;1H" << std::endl;
        // Prompt the user to take over for the current player and print information of all active players
        std::cout << "Click enter to take over for player: " << m_activePlayers[m_onTurn]->name() << std::endl;
        std::string s;
        std::getline(std::cin, s);
        size_t playerCount = m_activePlayers.size();
        for (size_t i = 0; i < playerCount; i++) {
            m_activePlayers[i]->printInfo();
            if (i == m_onTurn) {
                m_activePlayers[i]->printCards();
            }
        }
    }
    std::cout << "Player: " << m_activePlayers[m_onTurn]->name() << " on turn!" << std::endl;
}

bool Game::canBeSetUp() const {
    if (m_cardsInDeck.noOfCards() + m_usedCards.noOfCards() <= m_players.size() * m_noOfCardsInHand) {
        std::cout << "Too few cards in deck for this many players." << std::endl;
        return false;
    }
    return true;
}

void Game::reconstructPlayers() {
    m_activePlayers.clear();
    for (const auto &player: m_players) {
        m_activePlayers.push_back(player->clone());
    }
}

void Game::setUpGame(bool &startWithSavedGame) {
    if (startWithSavedGame) {
        startWithSavedGame = false;
        return;
    }
    m_running = true;
    m_winner = "";
    reconstructPlayers();
    std::vector<std::shared_ptr<Card>> usedCards = m_usedCards.extractCards();
    m_cardsInDeck.addCards(usedCards);
    m_cardsInDeck.mixCards();
    for (auto &playerPt: m_activePlayers) {
        for (int i = 0; i < m_noOfCardsInHand; i++)
            playerPt->acceptCard(m_cardsInDeck.extractCard());
    }
}

void Game::nextTurn() {
    std::shared_ptr<Command> command;
    do {
        command = m_activePlayers[m_onTurn]->play(m_onTurn, *this);
    } while (!command->execute(*this));
}

size_t Game::findLeastHealthyEnemy() const {
    size_t playerCount = m_activePlayers.size();
    int leastHP = 0;
    // starting leastHealthyEnemy on 0 would cause all players to harm
    // player1 when all players have same HP
    std::srand(std::time(nullptr));
    size_t leastHealthyEnemy;
    do {
        leastHealthyEnemy = rand() % m_activePlayers.size();
    } while (leastHealthyEnemy == m_onTurn);
    for (size_t i = 0; i < playerCount; i++) {
        if (m_activePlayers[i]->healthPoints() < leastHP && i != m_onTurn) {
            leastHP = m_activePlayers[i]->healthPoints();
            leastHealthyEnemy = i;
        }
    }
    return leastHealthyEnemy;
}

bool Game::running() const {
    return m_running;
}

std::string Game::winner() const {
    return m_winner;
}

void Game::moveOnTurn() {
    if (m_onTurn + 1 >= m_activePlayers.size()) {
        m_onTurn = 0;
        for (std::shared_ptr<Player> &player: m_activePlayers) {
            player->refill();
        }
    } else {
        m_onTurn++;
    }
}

void Game::takeCard() {
    if (m_cardsInDeck.empty()) {
        m_cardsInDeck.addCards(m_usedCards.extractCards());
    }
    m_activePlayers[m_onTurn]->acceptCard(m_cardsInDeck.extractCard());
}

void Game::throwCard(const int cardNumber) {
    std::shared_ptr<Card> card = m_activePlayers[m_onTurn]->giveCard(cardNumber);
    takeCard();
    m_usedCards.addCard(card);
    moveOnTurn();
}

bool Game::playCard(const size_t enemyIndex, int const cardNumber) {
    if (enemyIndex >= m_activePlayers.size()) {
        std::cout << "Too high enemy number" << std::endl;
        return false;
    }
    std::shared_ptr<Card> card = m_activePlayers[m_onTurn]->giveCard(cardNumber);
    card->applyEffects(*this, m_onTurn, enemyIndex);
    m_usedCards.addCard(card);
    if (enemyIndex != m_onTurn && m_activePlayers[enemyIndex]->healthPoints() == 0) {
        if (enemyIndex > m_onTurn) {
            if (m_activePlayers[m_onTurn]->healthPoints() == 0) {
                killPlayer(enemyIndex);
                killPlayer(m_onTurn);
                if (m_onTurn >= m_activePlayers.size()) {
                    m_onTurn = 0;
                }
                return true;
            } else {
                takeCard();
                killPlayer(enemyIndex);
                moveOnTurn();
                return true;
            }
        } else {
            if (m_activePlayers[m_onTurn]->healthPoints() == 0) {
                killPlayer(enemyIndex);
                m_onTurn--;
                killPlayer(m_onTurn);
                if (m_onTurn >= m_activePlayers.size()) {
                    m_onTurn = 0;
                }
                return true;
            } else {
                takeCard();
                killPlayer(enemyIndex);
                if (m_onTurn >= m_activePlayers.size()) {
                    m_onTurn = 0;
                }
                return true;
            }
        }
    } else if (m_activePlayers[m_onTurn]->healthPoints() == 0) {
        takeCard();
        killPlayer(m_onTurn);
        if (m_onTurn >= m_activePlayers.size()) {
            m_onTurn = 0;
        }
        return true;
    } else {
        takeCard();
        moveOnTurn();
        return true;
    }
}

bool Game::saveGame(const std::string &filePath) const {
    std::ifstream file(filePath);
    if (file.good()) {
        std::cout << "File already exists" << std::endl;
        return false;
    }
    nlohmann::json gameJSON;
    nlohmann::json activePlayers;
    for (const auto &player: m_activePlayers) {
        nlohmann::json playerJSON;
        player->toJSON(playerJSON);
        activePlayers.push_back(playerJSON);
    }
    gameJSON["activePlayers"] = activePlayers;

    nlohmann::json playersJSON;
    for (const auto &player: m_players) {
        nlohmann::json playerJSON;
        player->toJSON(playerJSON);
        playersJSON.push_back(playerJSON);
    }
    gameJSON["players"] = playersJSON;
    gameJSON["onTurn"] = m_onTurn;

    nlohmann::json cardsInDeckJSON;
    m_cardsInDeck.toJSON(cardsInDeckJSON);
    gameJSON["cardsInDeck"] = cardsInDeckJSON;

    nlohmann::json usedCardsJSON;
    m_usedCards.toJSON(usedCardsJSON);
    gameJSON["usedCards"] = usedCardsJSON;

    gameJSON["cardsVisibility"] = m_cardsVisibility;
    gameJSON["noOfCardsInHand"] = m_noOfCardsInHand;

    std::ofstream of(filePath);
    of << std::setw(2) << gameJSON << std::endl;

    if (!of.good()) {
        std::cout << "Unable to create file, check if the target folder exists." << std::endl;
        return false;
    }
    std::cout << "Your game has been successfully saved to " + filePath + " !" << std::endl;
    return true;
}

void Game::endGame() {
    std::cout << "Closing the game..." << std::endl;
    m_running = false;
}

void Game::killPlayer(const size_t playerIndex) {
    for (int i = 0; i < m_noOfCardsInHand; i++) {
        m_usedCards.addCard(m_activePlayers[playerIndex]->giveCard(0));
    }
    m_activePlayers.erase(m_activePlayers.begin() + playerIndex);
    if (m_activePlayers.size() == 1) {
        m_winner = m_activePlayers[0]->name();
        m_running = false;
    }
}

void Game::attack(const int attackStrength, const size_t playerIndex) {
    std::shared_ptr<Player> player = m_activePlayers[playerIndex];
    if (player->defense() < attackStrength) {
        player->changeHP(-(attackStrength - player->defense()));
        player->changeDefense(-attackStrength);
    } else {
        player->changeDefense(-attackStrength);
    }
}

void Game::changeHP(const int HPChange, const size_t playerIndex) {
    m_activePlayers[playerIndex]->changeHP(HPChange);
}

void Game::changeOffense(const int offenseChange, const size_t playerIndex) {
    m_activePlayers[playerIndex]->changeOffense(offenseChange);
}

void Game::changeDefense(const int defenseChange, const size_t playerIndex) {
    m_activePlayers[playerIndex]->changeDefense(defenseChange);
}

void Game::changeMana(const int manaChange, const size_t playerIndex) {
    m_activePlayers[playerIndex]->changeMana(manaChange);
}

size_t Game::noOfActivePlayer() const {
    return m_activePlayers.size();
}