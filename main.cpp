#include <iostream>
#include <fstream>
#include <vector>

std::string decrypt(const std::string& encrypted) {
    std::string decrypted = encrypted;
    for (char& c : decrypted) {
        c = c - 3; // простой шифр цезаря (сдвиг на -3)
    }
    return decrypted;
}

std::string getWordFromFile() {
    std::ifstream file("words.txt");
    std::vector<std::string> words;
    std::string word;
    static int index = 0; // используем статическую переменную вместо рандома

    if (file.is_open()) {
        while (file >> word) {
            words.push_back(decrypt(word));
        }
        file.close();
    }

    if (words.empty()) return "default";

    index = (index + 1) % words.size(); // переход к следующему слову при каждом запуске
    return words[index];
}

void displayWord(const std::string& word, const std::vector<char>& guessed) {
    for (char c : word) {
        if (std::find(guessed.begin(), guessed.end(), c) != guessed.end()) {
            std::cout << c << " ";
        } else {
            std::cout << "_ ";
        }
    }
    std::cout << std::endl;
}

void playGame() {
    std::string word = getWordFromFile();
    std::vector<char> guessed;
    int attempts = 6;
    bool wordGuessed = false;

    while (attempts > 0 && !wordGuessed) {
        std::cout << "\nword: ";
        displayWord(word, guessed);

        std::cout << "enter a letter: ";
        char guess;
        std::cin >> guess;

        if (std::find(guessed.begin(), guessed.end(), guess) != guessed.end()) {
            std::cout << "you have already entered this letter!\n";
            continue;
        }

        guessed.push_back(guess);
        if (word.find(guess) == std::string::npos) {
            attempts--;
            std::cout << "no such letter! attempts left: " << attempts << "\n";
        }

        wordGuessed = true;
        for (char c : word) {
            if (std::find(guessed.begin(), guessed.end(), c) == guessed.end()) {
                wordGuessed = false;
                break;
            }
        }
    }

    std::cout << "\ngame over!\n";
    if (wordGuessed) {
        std::cout << "you guessed the word: " << word << "\n";
    } else {
        std::cout << "you lost. the word was: " << word << "\n";
    }

    std::cout << "used letters: ";
    for (char c : guessed) {
        std::cout << c << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "hangman game!\n";
    playGame();
    return 0;
}
