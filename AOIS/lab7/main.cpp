#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

vector<vector<bool>> generate_random_table() {
    vector<bool> row;
    vector<vector<bool>> table;
    for (int j = 0; j < 20; j++) {
        for (int i = 0; i < 10; i++) {
            if (rand() % 2 == 1) 
                row.push_back(1);
            else 
                row.push_back(0);
        }
        table.push_back(row);
        row.clear();
    }
    return table;
}

struct Trigger {
    bool g;
    bool l;
};

Trigger recursive_function(string argument, vector<bool> word, int i) {
    Trigger final_state;
    Trigger initial_state;
    if (i + 1 == word.size()) {
        initial_state.g = false;
        initial_state.l = false;
    }
    else {
        initial_state = recursive_function(argument, word, i + 1);
    }
    if (initial_state.g || (argument[i] == '0' && word[i] == 1 && !initial_state.l)) {
        final_state.g = true;
    }
    else {
        final_state.g = false;
    }
    if (initial_state.l || (argument[i] == '1' && word[i] == 0 && !initial_state.g)) {
        final_state.l = true;
    }
    else {
        final_state.l = false;
    }
    return final_state;
};


void print_word(const vector<bool>& word_to_print) {
    for (size_t i = 0; i < word_to_print.size(); i++) {
        cout << word_to_print[i];
    }
}

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
}


void print_matches(const vector<vector<bool>>& matches, const vector<vector<bool>>& dictionary, size_t best_match_discharge) {
    int index = 0;
    for (size_t i = 0; i < matches.size(); i++) {
        for (int j = 0; j < dictionary.size(); j++) {
            if (dictionary[j] == matches[i]) {
                index = j;
                break;
            }
        }
        cout << "[" << index << "] ";
        for (size_t j = 0; j < matches[i].size(); j++) {
            cout << matches[i][j];
        }
        cout << endl;
    }

    cout << "Max matches discharge: " << best_match_discharge << endl;
}

bool boolean_search(const vector<vector<bool>>& book, const string& argument, bool (BooleanFunctions::*bool_function)(const vector<bool>&)) {
    for (size_t i = 0; i < book.size(); i++) {
        const vector<bool>& word = book[i];
        if ((boolean_functions.*bool_function)(word)) {
            cout << "[" << i << "] ";
            for (bool bit : word) {
                cout << bit;
            }
            cout << endl;
        }
    }

    return true;
}


class BooleanFunctions {
public:
    bool and_function(const vector<bool>& word) {
        return word[0] && word[1] && word[2];
    }

    bool or_function(const vector<bool>& word) {
        return word[0] || word[1] || word[2];
    }

    bool xor_function(const vector<bool>& word) {
        return (word[0] && !word[1] && !word[2]) || (!word[0] && word[1] && !word[2]) || (!word[0] && !word[1] && word[2]);
    }
};

BooleanFunctions boolean_functions;




class Dictionary {
public:
    Dictionary() {
        setlocale(LC_ALL, "Russian");
        words = get_random();
    }

    void print() const {
        for (size_t i = 0; i < words.size(); i++) {
            cout << "[" << i << "] ";
            print_word(words[i]);
            cout << endl;
        }
    }

    void search_by_match() const {
        cout << endl << "Enter the number of the word to search for matches: ";
        size_t matching;
        cin >> matching;
        int best_match_discharge;
        vector<vector<bool>> matches = find_best_matches(words, words[matching], &best_match_discharge);
        cout << "Selected word - [" << matching << "] ";
        print_word(words[matching]);
        cout << endl;
        cout << "Max similar words: " << endl;
        print_matches(matches, words, best_match_discharge);
        cout << endl << "Enter the word to search: ";
        string word;
        cin >> word;
        for (size_t i = 0; i < words.size(); i++) {
            cout << "[" << i << "]";
            Trigger compare = recursive_function(word, words[i], 0);
            cout << compare.g << " " << compare.l << endl;
        }
    }

    void search_by_boolean_function() const {
        cout << endl << "Enter the word to search: ";
        string word;
        cin >> word;
        int operation;
        cout << "Select a Boolean operation to search:" << endl;
        cout << "1. AND" << endl;
        cout << "2. OR" << endl;
        cout << "3. XOR" << endl;
        cin >> operation;
        bool (BooleanFunctions::*bool_function)(const vector<bool>&) = nullptr;
        switch (operation) {
            case 1:
                bool_function = &BooleanFunctions::and_function;
                break;
            case 2:
                bool_function = &BooleanFunctions::or_function;
                break;
            case 3:
                bool_function = &BooleanFunctions::xor_function;
                break;
            default:
                cout << "Invalid operation" << endl;
                return;
        }

        boolean_search(words, word, bool_function);
    }

private:
    vector<vector<bool>> words;
};

Dictionary dictionary;

int main() {
    int choice;
    cout << "Choose an operation:" << "\n" << "1 - Search by match " << "\n" << "2 - Search based on Boolean function" << endl;
    cin >> choice;
    if (choice == 1) {
        dictionary.search_by_match();
    }
    else if (choice == 2) {
        dictionary.search_by_boolean_function();
    }
    else {
        cout << "Invalid choice" << endl;
    }

    return 0;
}
