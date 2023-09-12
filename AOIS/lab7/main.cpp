#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <functional>
#include <locale>

std::vector<std::vector<bool>> generate_random_table() {
    std::vector<std::vector<bool>> table;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 1);

    for (int j = 0; j < 20; j++) {
        std::vector<bool> row;
        for (int i = 0; i < 10; i++) {
            bool value = dist(gen);
            row.push_back(value);
        }
        table.push_back(row);
    }

        return table;
};

struct Trig {
    bool L;
    bool G;
};

std::vector<bool> rec_func(const std::string& argument, const std::vector<bool>& word, int i) {
    std::vector<bool> final_state(2, false);
    std::vector<bool> initial_state(2, false);

    if (i + 1 == word.size()) {
        initial_state[0] = false;
        initial_state[1] = false;
    }
    else {
        initial_state = rec_func(argument, word, i + 1);
    }

    if (initial_state[0] || (argument[i] == '0' && word[i] && !initial_state[1])) {
        final_state[0] = true;
    }

    if (initial_state[1] || (argument[i] == '1' && !word[i] && !initial_state[0])) {
        final_state[1] = true;
    }

    return final_state;
};


void print_word(vector<bool>& word) {
    for (size_t i = 0; i < word.size(); i++) {
        std::cout << word[i];
    }
};

vector<vector<bool>> find_best_matches(const vector<vector<bool>>& book, const vector<bool>& word, int* best_match_discharge) {
    vector<vector<bool>> best_matches;
    *best_match_discharge = 0;
    int current_best_match_discharge;

    for (size_t i = 0; i < book.size(); i++) {
        cout << "Word to compare: ";
        print_word(book[i]);
        cout << endl;

        if (word != book[i]) {
            current_best_match_discharge = 0;
            for (size_t j = 0; j < word.size(); j++) {
                if (word[j] == book[i][j]) {
                    current_best_match_discharge++;
                }
                else {
                    break;
                }
            }
            cout << "current_best_match_discharge = " << current_best_match_discharge << "  ";
            if (current_best_match_discharge > *best_match_discharge) {
                *best_match_discharge = current_best_match_discharge;
                best_matches.clear();
                best_matches.push_back(book[i]);
            }
            else if (current_best_match_discharge == *best_match_discharge) {
                best_matches.push_back(book[i]);
            }
            cout << "best_match_discharge = " << *best_match_discharge << "  ";
            cout << endl;
        }
    }

    return best_matches;
};

std::vector<std::vector<bool>> find_best_matches(const std::vector<std::vector<bool>>& book, const std::vector<bool>& word, int* best_match_discharge) {
    std::vector<std::vector<bool>> best_matches;
    *best_match_discharge = 0;

    for (const std::vector<bool>& bookWord : book) {
        std::cout << "Word to compare: ";
        print_word(bookWord);
        std::cout << std::endl;

        if (word != bookWord) {
            int current_best_match_discharge = 0;
            auto mismatch = std::mismatch(word.begin(), word.end(), bookWord.begin());
            current_best_match_discharge = std::distance(word.begin(), mismatch.first);

            std::cout << "current_best_match_discharge = " << current_best_match_discharge << "  ";
            if (current_best_match_discharge > *best_match_discharge) {
                *best_match_discharge = current_best_match_discharge;
                best_matches.clear();
                best_matches.push_back(bookWord);
            }
            else if (current_best_match_discharge == *best_match_discharge) {
                best_matches.push_back(bookWord);
            }
            std::cout << "best_match_discharge = " << *best_match_discharge << "  ";
            std::cout << std::endl;
        }
    }

    return best_match;
};

class Functions {
public:
    std::function<bool(const std::vector<bool>&)> and = [](const std::vector<bool>& word) {
        return word[0] && word[1] && word[2];
    };

    std::function<bool(const std::vector<bool>&)> or = [](const std::vector<bool>& word) {
        return word[0] || word[1] || word[2];
    };

    std::function<bool(const std::vector<bool>&)> xor = [](const std::vector<bool>& word) {
        return (word[0] && !word[1] && !word[2]) || (!word[0] && word[1] && !word[2]) || (!word[0] && !word[1] && word[2]);
    };
};


class Dict {
public:
    Dict() {
        setlocale(LC_ALL, "Russian");
        words = get_random();
    }

    void print() const {
        size_t i = 0;
        for (const auto& word : words) {
            std::cout << "[" << std::to_string(i) << "] ";
            print_word(word);
            std::cout << std::endl;
            i++;
        }
    }
};

    void match_search() const {
    std::cout << std::endl << "Enter the number of the word to search for matches: ";
    size_t matching;
    std::cin >> matching;
    int best_match_discharge;
    std::vector<std::vector<bool>> matches = find_match(words, words[matching], &best_match_discharge);
    std::cout << "Selected word - [" << matching << "] ";
    print_word(words[matching]);
    std::cout << std::endl;
    std::cout << "Max similar words: " << std::endl;
    print_match(matches, words, best_match_discharge);
    std::cout << std::endl << "Enter the word to search: ";
    std::string word;
    std::cin >> word;
    for (size_t i = 0; i < words.size(); i++) {
        std::cout << "[" << i << "]";
        Trigger compare = recursive_function(word, words[i], 0);
        std::cout << compare.g << " " << compare.l << std::endl;
    }
};

    void boolean_search() const {
    std::cout << std::endl << "Enter the word to search: ";
    std::string word;
    std::cin >> word;
    int operation;
    std::cout << "Select a Boolean operation to search:" << std::endl;
    std::cout << "1. AND" << std::endl;
    std::cout << "2. OR" << std::endl;
    std::cout << "3. XOR" << std::endl;
    std::cin >> operation;

    std::function<bool(const std::vector<bool>&)> bool_function = nullptr;
    switch (operation) {
        case 1:
            bool_function = [this](const std::vector<bool>& word) { return booleanFunctions.and_function(word); };
            break;
        case 2:
            bool_function = [this](const std::vector<bool>& word) { return booleanFunctions.or_function(word); };
            break;
        case 3:
            bool_function = [this](const std::vector<bool>& word) { return booleanFunctions.xor_function(word); };
            break;
        default:
            std::cout << "Invalid operation" << std::endl;
            return;
    }

    boolean_search(words, word, bool_function);
};

Dict dict;

int main() {
    Dictionary dictionary;

    std::cout << "Choose an operation:" << std::endl;
    std::cout << "1 - Match search" << std::endl;
    std::cout << "2 - Boolean search" << std::endl;

    int choice;
    std::cin >> choice;

    std::function<void()> operation = nullptr;
    if (choice == 1) {
        operation = [&dictionary]() { dictionary.match_search(); };
    } else if (choice == 2) {
        operation = [&dictionary]() { dictionary.boolean_search(); };
    } else {
        std::cout << "Invalid choice" << std::endl;
        return 0;
    }

    operation();

    return 0;
}
