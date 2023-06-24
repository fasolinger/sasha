#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>

class MemoryTable {
    private:
        int table_size;
        std::vector<std::bitset<32>> memory_table;
    public:
        MemoryTable(int element_size) {
            table_size = element_size;
            memory_table.resize(table_size, std::bitset<32>(0));
        }
        std::vector<bool> get_comparing_flags(std::bitset<32> reference_element, std::bitset<32> inspected_element) {
            bool cur_g = false, cur_l = false;
            for (int i = 0; i < table_size; i++) {
                bool S_ji = inspected_element[i];
                bool a_i = reference_element[i];
                bool next_g = cur_g || (!a_i && S_ji && !cur_l);
                bool next_l = cur_l || (a_i && !S_ji && !cur_g);
                cur_g = next_g;
                cur_l = next_l;
            }
            return {cur_g, cur_l};
        }
        std::vector<std::bitset<32>> sort(std::vector<std::bitset<32>> list_of_elements, bool reverse=false) {
            int size = list_of_elements.size();
            for (int i = 0; i < size - 1; i++) {
                int min_index = i;
                for (int j = i + 1; j < size; j++) {
                    int flag = -1;
                    if (reverse == false) {
                        flag = 1;
                    }
                    if (compare_2_elements(list_of_elements[j], list_of_elements[min_index]) == flag) {
                        min_index = j;
                    }
                }
                std::swap(list_of_elements[i], list_of_elements[min_index]);
            }
            return list_of_elements;
        }
        int compare_2_elements(std::bitset<32> element1, std::bitset<32> element2) {
            std::vector<bool> flags = get_comparing_flags(element1, element2);
            if (flags[0] == true) {
                return 1;
            }
            else if (flags[1] == true) {
                return -1;
            }
            else {
                return 0;
            }
        }
};
            
            
    vector<int> f_closest(int value, bool below=true) {
    vector<vector<int>> suitable_elements;
    for (auto x : memory_table) {
        if (compare_elements(x, value) == 0) {
            suitable_elements.push_back(x);
        }
    }
    if (!below) {
        for (auto x : memory_table) {
            if (compare_elements(x, value) == 1) {
                suitable_elements.push_back(x);
            }
        }
    } else {
        for (auto x : memory_table) {
            if (compare_elements(x, value) == -1) {
                suitable_elements.push_back(x);
            }
        }
    }
    sort(suitable_elements.begin(), suitable_elements.end(), below ? greater<vector<int>>() : less<vector<int>>());
    suitable_elements.erase(unique(suitable_elements.begin(), suitable_elements.end()), suitable_elements.end());
    return suitable_elements.back();
}

int compare(vector<int> comparable_object, int reference) {
    auto result_of_compare_elements = get_comparing_flags(reference, comparable_object);
    if (result_of_compare_elements['g_flag'] && !result_of_compare_elements['l_flag']) {
        return 1;
    } else if (!result_of_compare_elements['g_flag'] && result_of_compare_elements['l_flag']) {
        return -1;
    } else if (!result_of_compare_elements['g_flag'] && !result_of_compare_elements['l_flag']) {
        return 0;
    }
}
    
std::unordered_map<std::string, bool> getCompareFlags(std::string reference_element, std::string inspected_element) {
    bool cur_g = false, cur_l = false;
    int table_size = reference_element.size();
    for (int i = 0; i < table_size; i++) {
        bool S_ji = bool(inspected_element[i] - '0');
        bool a_i = bool(reference_element[i] - '0');
        bool next_g = cur_g || (!a_i && S_ji && !cur_l);
        bool next_l = cur_l || (a_i && !S_ji && !cur_g);
        cur_g = next_g;
        cur_l = next_l;
    }
    return {{"g_flag", cur_g}, {"l_flag", cur_l}};
}

std::string getShifWord(int index, std::string word) {
    int shear = word.size() - index;
    std::string a = word.substr(0, shear);
    std::string b = word.substr(shear);
    std::string sheared_word = b + a;
    return sheared_word;
}

void createNewEntry(std::vector<std::string>& memory_table, std::string word, int index) {
    std::string sheared_word = get_sheared_word(index, word);
    int table_size = memory_table.size();
    for (int i = 0; i < table_size; i++) {
        memory_table[i][index] = sheared_word[i];
    }
}

std::string to_string(std::vector<std::string>& memory_table) {
    std::string table_print = "";
    for (auto i : memory_table) {
        table_print += i + "\n";
    }
    return table_print;
}
    

    class MyClass {
public:
    static std::vector<std::vector<int>> get_random_words(int size) {
        std::vector<std::vector<int>> list_of_words(size, std::vector<int>(size));
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                list_of_words[i][j] = rand() % 2;
            }
        }
        return list_of_words;
    }
    std::vector<int> get_choosen_word(int number) {
        std::vector<int> sheared_word;
        for (int i = 0; i < memory_table.size(); i++) {
            sheared_word.push_back(memory_table[i][number]);
        }
        std::vector<int> word;
        for (int i = number; i < sheared_word.size(); i++) {
            word.push_back(sheared_word[i]);
        }
        for (int i = 0; i < number; i++) {
            word.push_back(sheared_word[i]);
        }
        return word;
    }
    std::vector<std::vector<int>> get_full_list_of_words() {
        std::vector<std::vector<int>> list_of_words(table_size, std::vector<int>(table_size));
        for (int i = 0; i < table_size; i++) {
            list_of_words[i] = get_choosen_word(i);
        }
        normal_table = list_of_words;
        return list_of_words;
    }
    std::vector<int> f1(std::vector<std::vector<int>> elements) {
        std::vector<int> result;
        for (int i = 0; i < elements[0].size(); i++) {
            result.push_back(elements[0][i] && elements[1][i]);
        }
        return result;
    }
private:
    std::vector<std::vector<int>> memory_table;
    std::vector<std::vector<int>> normal_table;
    int table_size;
};

    class Solution {
public:
    std::vector<int> f14(std::vector<std::vector<int>>& elements) {
        auto result = f1(elements);
        std::transform(result.begin(), result.end(), result.begin(), [](int x){return !x;});
        return result;
    }
    
    std::vector<int> f3(std::vector<std::vector<int>>& elements) {
        return elements[0];
    }
    
    std::vector<int> f12(std::vector<std::vector<int>>& elements) {
        std::vector<int> res(elements[0].size());
        std::transform(elements[0].begin(), elements[0].end(), res.begin(), [](int x){return !x;});
        return res;
    }
    
    std::vector<int> logical_func(std::string func, std::vector<std::vector<int>>& elements) {
        std::unordered_map<std::string, std::func<std::vector<int>(std::vector<std::vector<int>>&)>> operations = {
            {"f1", std::bind(&Solution::f1, this, std::placeholders::_1)},
            {"f14", std::bind(&Solution::f14, this, std::placeholders::_1)},
            {"f3", std::bind(&Solution::f3, this, std::placeholders::_1)},
            {"f12", std::bind(&Solution::f12, this, std::placeholders::_1)}
        };
        return operations[func](elements);
    }
    
    std::unordered_map<int, std::string> arithmetics(std::vector<int>& V) {
        std::vector<std::string> list_of_all_words = get_full_list_of_words();
        std::vector<std::string> suitable_words;
        std::copy_if(list_of_all_words.begin(), list_of_all_words.end(), std::back_inserter(suitable_words), [V](std::string x){return x.substr(0, 3) == std::to_string(V[0]);});
        std::unordered_map<int, std::string> results;
        for (auto word : suitable_words) {
            auto A = word.substr(3, 4);
            auto B = word.substr(7, 4);
            auto sum = std::to_string(std::stoi(A) + std::stoi(B));
            results.emplace(results.size(), word.substr(0, 11) + sum);
        }
        return results;
    }
    
private:
    std::vector<int> f1(std::vector<std::vector<int>>& elements) {
        std::vector<int> result(elements[0].size());
        for (int i = 0; i < elements[0].size(); i++) {
            result[i] = elements[0][i] and elements[1][i];
        }
        return result;
    }
    
    std::vector<std::string> get_full_list_of_words() {
        std::vector<std::string> words;
        for (int i = 0; i < 10000; i++) {
            words.emplace_back(std::to_string(i));
        }
        return words;
    }
};

    vector<int> sum_of_parts_of_words(string word1, string word2) {
        vector<int> el1, el2, res;
        for (char c : word1) {
                el1.push_back(c - '0');
        }
        for (char c : word2) {
                el2.push_back(c - '0');
        }
        string result = "";
        int carry = 0;
        while (!el1.empty() && !el2.empty()) {
                int digital1 = el1.back();
                el1.pop_back();
                int digital2 = el2.back();
                el2.pop_back();
                int temp = digital1 ^ digital2 ^ carry;
                result = to_string(temp) + result;
                carry = (digital1 && digital2) || ((digital1 ^ digital2) && carry);
        }
        result = to_string(carry) + result;
        for (char c : result) {
                res.push_back(c - '0');
        }
        return res;
        };


using namespace std;

int main() {
AccosiativeMemoryTable a(16);
vector<string> list_of_words = AccosiativeMemoryTable::get_random_words(16);
cout << "<Список слов: ";
for (string word : list_of_words) {
cout << word << " ";
}
cout << ">" << endl;
for (int i = 0; i < 16; i++) {
a.create_new_entry(list_of_words[i], i);
}
cout << a << endl;
cout << "________________________________________________________________" << endl;
cout << "Выбранный элемент: " << a.get_choosen_word(5) << endl;
cout << "Целый элемент: ";
vector<string> full_list = a.get_full_list_of_words();
for (string word : full_list) {
    cout << word << " ";
}
cout << endl;
cout << "Наиближайший: " << a.find_the_closest_value({0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0}, false) << endl;

cout << "logical func" << endl;
vector<string> func = {"f1", "f14", "f3", "f12"};
cout << "f1: " << a.logical_func(func[0], {full_list[0], full_list[1]}) << endl;
cout << "f14: " << a.logical_func(func[1], {full_list[0], full_list[1]}) << endl;
cout << "f3: " << a.logical_func(func[2], {full_list[0]}) << endl;
cout << "f12: " << a.logical_func(func[3], {full_list[0]}) << endl;

cout << "sum" << endl;
vector<int> sum_values = {1, 0, 1};
vector<int> result = a.arithmetics(sum_values);
cout << result[0];
for (int i = 1; i < result.size(); i++) {
    cout << ", " << result[i];
}
cout << endl;

return 0;
