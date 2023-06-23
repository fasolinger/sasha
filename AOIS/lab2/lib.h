#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#define SIZE 8

class Stack {
public:
    void push(char info);
    void push(bool info);
    void pop(char* info);
    void pop(bool* info);
private:
    struct Node {
        Node* next;
        union {
            char char_info;
            bool bool_info;
        };
        bool is_bool;
        Node(Node* next, char info) : next(next), char_info(info), is_bool(false) {}
        Node(Node* next, bool info) : next(next), bool_info(info), is_bool(true) {}
    };
    Node* top = nullptr;
};

void Stack::push(char info) {
    top = new Node(top, info);
}

void Stack::push(bool info) {
    top = new Node(top, info);
}

void Stack::pop(char* info) {
    *info = top->char_info;
    Node* temp = top;
    top = top->next;
    delete temp;
}

void Stack::pop(bool* info) {
    *info = top->bool_info;
    Node* temp = top;
    top = top->next;
    delete temp;
}

class TrueTable {
public:
    TrueTable() {}
    void generate_table(const std::string& expression);
    void print_table() const;
    std::vector<int> get_sknf() const;
    std::vector<int> get_sdnf() const;
    std::vector<int> get_binary_sknf() const;
    std::vector<int> get_binary_sdnf() const;
    std::vector<int> get_decimal_sknf() const;
    std::vector<int> get_decimal_sdnf() const;
    std::vector<int> get_index() const;
private:
    bool evaluate_expression(const std::string& expression, bool a, bool b, bool c) const;
    std::string translate_to_rpn(const std::string& expression) const;
    std::vector<int> minterms_from_true_table(bool TrueTable::* member) const;
    Set table[8];
};

class Formula {
public:
    virtual std::string create_formula(const std::vector<int>& minterms) const = 0;
    virtual void print_binary_formula(const std::vector<int>& minterms) const;
    virtual void print_decimal_formula(const std::vector<int>& minterms) const;
};

class SKNF : public Formula {
public:
    std::string create_formula(const std::vector<int>& minterms) const override;
};

class SDNF : public Formula {
public:
    std::string create_formula(const std::vector<int>& minterms) const override;
    std::vector<int> get_index(const std::vector<int>& minterms) const;
};

void Formula::print_binary_formula(const std::vector<int>& minterms) const {
    for (int minterm : minterms) {
        std::vector<int> binary = int_to_direct_code(minterm, 3);
        for (int bit : binary) {
            std::cout << bit;
        }
        std::cout << ' ';
    }
    std::cout << '\n';
}

void Formula::print_decimal_formula(const std::vector<int>& minterms) const {
    for (int minterm : minterms) {
        std::cout << minterm << ' ';
    }
    std::cout << '\n';
}

void SKNF::print_binary_formula(const std::vector<int>& minterms) const {
    std::cout << "Binary SKNF: ";
    Formula::print_binary_formula(minterms);
}

void SKNF::print_decimal_formula(const std::vector<int>& minterms) const {
    std::cout << "Decimal SKNF: ";
    Formula::print_decimal_formula(minterms);
}

void SDNF::print_binary_formula(const std::vector<int>& minterms) const {
    std::cout << "Binary SDNF: ";
    Formula::print_binary_formula(minterms);
}

void SDNF::print_decimal_formula(const std::vector<int>& minterms) const {
    std::cout << "Decimal SDNF: ";
    Formula::print_decimal_formula(minterms);
}

void SDNF::print_index(const std::vector<int>& index) const {
    std::cout << "Index: ";
    Formula::print_decimal_formula(index);
}

#include "math.h"
#include "algorithm"


TrueTable::TrueTable() {
    int values[3] = {0, 1};
    int num_values = sizeof(values) / sizeof(values[0]);
    int num_rows = pow(num_values, 3);
    for (int i = 0; i < num_rows; i++) {
        int a_val = values[(i / (num_values * num_values)) % num_values];
        int b_val = values[(i / num_values) % num_values];
        int c_val = values[i % num_values];
        table[i].a = a_val;
        table[i].b = b_val;
        table[i].c = c_val;
    }
}

void TrueTable::push_char(char info) {
    char_stack.push(info);
}

void TrueTable::push_bool(bool info) {
    bool_stack.push(info);
}

void TrueTable::pop_char(char* info) {
    char_stack.pop(info);
}

void TrueTable::pop_bool(bool* info) {
    *info = bool_stack.top();
    bool_stack.pop();
}

int TrueTable::prior(char oper) {
    if (oper == '(') return 1;
    if (oper == '+' || oper == '-') return 2;
    if (oper == '*' || oper == '/') return 3;
    if (oper == '!') return 4;
    return 0;
}

std::string TrueTable::translate(std::string expression) {
    std::string result;
    std::stack<char> op_stack;
    for (size_t i = 0; i < expression.size(); i++) {
        if (expression[i] == '(') {
            op_stack.push(expression[i]);
        } else if (expression[i] == ')') {
            while (!op_stack.empty() && op_stack.top() != '(') {
                result += op_stack.top();
                op_stack.pop();
            }
            if (!op_stack.empty() && op_stack.top() == '(') {
                op_stack.pop();
            }
        } else if (expression[i] >= 'a' && expression[i] <= 'c') {
            result += expression[i];
        } else if (expression[i] == '+' || expression[i] == '*' || expression[i] == '!') {
            while (!op_stack.empty() && prior(op_stack.top()) >= prior(expression[i])) {
                result += op_stack.top();
                op_stack.pop();
            }
            op_stack.push(expression[i]);
        }
    }
    while (!op_stack.empty()) {
        result += op_stack.top();
        op_stack.pop();
    }
    return result;
}

bool TrueTable::evaluate_expression(const std::string& expression, const std::vector<bool>& values) {
    std::stack<bool> value_stack;
    for (size_t i = 0; i < expression.size(); i++) {
        if (expression[i] == ' ') continue;
        if (expression[i] == 'a') {
            value_stack.push(values[0]);
        } else if (expression[i] == 'b') {
            value_stack.push(values[1]);
        } else if (expression[i] == 'c') {
            value_stack.push(values[2]);
        } else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
            bool operand2 = value_stack.top(); value_stack.pop();
            bool operand1 = value_stack.top(); value_stack.pop();
            bool result;
            if (expression[i] == '+') {
                result = operand1 || operand2;
            } else if (expression[i] == '-') {
                result = operand1 && !operand2;
            } else if (expression[i] == '*') {
                result = operand1 && operand2;
            } else if (expression[i] == '/') {
                result = operand1 || !operand2;
            }
            value_stack.push(result);
        } else if (expression[i] == '!') {
            bool operand = value_stack.top(); value_stack.pop();
            bool result = !operand;
            value_stack.push(result);
        }
    }
    return value_stack.top();
}

void TrueTable::generate_true_table(const std::string& expression) {
    std::vector<bool> values(3);
    for (int i = 0; i < SIZE; i++) {
        values[0] = table[i].a;
        values[1] = table[i].b;
        values[2] = table[i].c;
        table[i].result = evaluate_expression(expression, values);
    }
}

std::string SKNF::generate_sknf() const {
    std::string sknf;
    for (int i = 0; i < SIZE; i++) {
        if (table[i].result == 0) {
            sknf += "(";
            if (table[i].a == 0) {
                sknf += "a'";
            } else {
                sknf += "a";
            }
            if (table[i].b == 0) {
                sknf += "+b'";
            } else {
                sknf += "+b";
            }
            if (table[i].c == 0) {
                sknf += "+c";
            } else {
                sknf += "+c'";
            }
            sknf += ")";
            sknf += "*";
        }
    }
    if (sknf.size() > 0) {
        sknf.erase(sknf.size() - 1);
        return sknf;
    } else {
        return "Doesn't exist";
    }
}

std::string SDNF::generate_sdnf() const {
    std::string sdnf;
    for (int i = 0; i < SIZE; i++) {
        if (table[i].result == 1) {
            sdnf += "(";
            if (table[i].a == 0) {
                sdnf += "a'";
            } else {
                sdnf += "a";
            }
            if (table[i].b == 0) {
                sdnf += "*b'";
            } else {
                sdnf += "*b";
            }
            if (table[i].c == 0) {
                sdnf += "*c";
            } else {
                sdnf += "*c'";
            }
            sdnf += ")";
            sdnf += "+";
        }
    }
    if (sdnf.size() > 0) {
        sdnf.erase(sdnf.size() - 1);
        return sdnf;
    } else {
        return "Doesn't exist";
    }
}

void SDNF::print_sdnf_expression(const std::string& sdnf_expression) const {
    std::cout << "SDNF: " << sdnf_expression << "\n";
}

void SKNF::print_sknf_expression(const std::string& sknf_expression) const {
    std::cout << "SKNF: " << sknf_expression << "\n";
}

void TrueTable::print_true_table() const {
    std::cout << "\n                       True table";
    std::cout << "\n" << "---------------------------------------------------------\n";
    std::cout << "\t" << "|  1  " << "|  2  "
              << "|  3  " << "|  4  "
              << "|  5  " << "|  6  "
              << "|  7  " << "|  8  |\n";
    std::cout << "---------------------------------------------------------\n" << "  a\t";
    for (int i = 0; i < SIZE; i++) {
        std::cout << "|  " << table[i].a << "  ";
    }
    std::cout << "|\n" << "---------------------------------------------------------\n" << "  b\t";
    for (int i = 0; i < SIZE; i++) {
        std::cout << "|  " << table[i].b << "  ";
    }
    std::cout << "|\n" << "---------------------------------------------------------\n" << "  c\t";
    for (int i = 0; i < SIZE; i++) {
        std::cout << "|  " << table[i].c << "  ";
    }
    std::cout << "|\n" << "---------------------------------------------------------\n" << "  res\t";
    for (int i = 0; i < SIZE; i++) {
        std::cout << "|  " << table[i].result << "  ";
    }
    std::cout << "|\n" << "---------------------------------------------------------\n\n";
}

void TrueTable::print_index()
{
    std::vector<int> nums;
    int num;
    for (size_t i = 0; i < SIZE; i++)
        nums.push_back(this->table[i].result);
    num = direct_code_to_int(nums);
    std::cout << "Index: " << num << "\n";
}

int TrueTable::direct_code_to_int(std::vector<int> nums)
{
    int number = 0;
    std::reverse(nums.begin(), nums.end());
    for (size_t i = 0; i < nums.size(); i++)
        if (nums[i] == 1)
            number += pow(2, i);
    return number;
}

void TrueTable::print_binary_index() const {
    std::vector<int> binary_digits;
    for (int i = 0; i < SIZE; i++) {
        binary_digits.push_back(table[i].result);
    }
    int binary_index = binary_to_decimal(binary_digits);
    std::cout << "Binary index: " << binary_index << "\n";
}

int TrueTable::binary_to_decimal(const std::vector<int>& binary_digits) const {
    int decimal_number = 0;
    int base = 1;
    for (int i = binary_digits.size() - 1; i >= 0; i--) {
        decimal_number += binary_digits[i] * base;
        base *= 2;
    }
    return decimal_number;
}

std::vector<int> TrueTable::decimal_to_binary(int decimal_number, int size) const {
    std::vector<int> binary_digits(size, 0);
    int index = binary_digits.size() - 1;
    while (decimal_number > 0 && index >= 0) {
        binary_digits[index] = decimal_number % 2;
        decimal_number /= 2;
        index--;
    }
    if (decimal_number < 0) {
        binary_digits[0] = 1;
    }
    return binary_digits;
}

void SKNF::print_binary_expression() const {
    std::string binary_expression = "*(";
    for (const auto& row : table) {
        if (row.result == 0) {
            binary_expression += std::to_string(row.a);
            binary_expression += std::to_string(row.b);
            binary_expression += std::to_string(row.c);
            binary_expression += ",";
        }
    }
    if (binary_expression.size() > 3) {
        binary_expression.pop_back();
        binary_expression += ")";
        std::cout << "Binary SKNF: " << binary_expression << "\n";
    } else {
        std::cout << "Binary SKNF: does not exist\n";
    }
}

void SKNF::print_decimal_expression() const {
    std::string decimal_expression = "*(";
    for (const auto& row : table) {
        if (row.result == 0) {
            std::vector<int> binary_digits = {row.a, row.b, row.c};
            int decimal_number = SKNF::binary_to_decimal(binary_digits);
            decimal_expression += std::to_string(decimal_number);
            decimal_expression += ",";
        }
    }
    if (decimal_expression.size() > 3) {
        decimal_expression.pop_back();
        decimal_expression += ")";
        std::cout << "Decimal SKNF: " << decimal_expression << "\n";
    } else {
        std::cout << "Decimal SKNF: does not exist\n";
    }
}

void SDNF::print_decimal_expression() const {
    std::string decimal_expression = "+(";
    for (const auto& row : table) {
        if (row.result == 1) {
            std::vector<int> binary_digits = {row.a, row.b, row.c};
            int decimal_number = SDNF::binary_to_decimal(binary_digits);
            decimal_expression += std::to_string(decimal_number);
            decimal_expression += ",";
        }
    }
    if (decimal_expression.size() > 3) {
        decimal_expression.pop_back();
        decimal_expression += ")";
        std::cout << "Decimal SDNF: " << decimal_expression << "\n";
    } else {
        std::cout << "Decimal SDNF: does not exist\n";
    }
}
