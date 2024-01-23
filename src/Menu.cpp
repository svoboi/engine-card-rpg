#include "Menu.h"

Menu::Menu(std::istream &in, std::ostream &out)
        : m_in(in), m_out(out) {}

bool Menu::winnerAndAskIfNewGame(const std::string &name) const {
    std::cout << "\033[2J\033[1;1H" << std::endl;
    m_out << "Player: " << name << " won!" << std::endl;
    m_out << "New game [y] or not [n]?" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    while (!m_in.eof() && input != "y" && input != "n") {
        std::cout << "Please put in your answer: [y] to play new game or [n] to close this app." << std::endl;
        std::getline(std::cin, input);
    }
    if (input == "y") {
        return true;
    } else {
        return false;
    }
}

bool Menu::shouldStartWithSavedGame() const {
    m_out << "New game from configuration file [c] or load game from save file [s]?" << std::endl;
    std::string input;
    std::getline(m_in, input);
    while (!m_in.eof() && input != "c" && input != "s") {
        m_out << "Please put in your answer: [c] to play new game or [s] to load save file." << std::endl;
        std::getline(std::cin, input);
    }
    if (input == "c") {
        return false;
    } else {
        return true;
    }
}

std::string Menu::getfileName() const {
    m_out << "Write the path to your file please or [e] to exit." << std::endl;
    std::string fileName;

    while (true) {
        fileName = "";
        std::getline(m_in, fileName);
        if (m_in.eof() || fileName == "e") {
            m_out << "Closing the app..." << std::endl;
            return "";
        }
        std::ifstream file(fileName);
        if (file.is_open()) {
            break;
        }
        m_out << "This file is not available. Try again or enter [e] to exit." << std::endl;
    }
    return fileName;
}
