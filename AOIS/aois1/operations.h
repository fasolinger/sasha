#ifndef AOIS1_OPERATIONS_H
#define AOIS1_OPERATIONS_H

#include <iostream>
#include <vector>
#include <sstream>
#include <math.h>
#include <algorithm>
#include "translations.h"


#define BASE_8 8
#define BASE_16 16
#define BASE_23 23

using namespace std;

struct Float
{
    vector<int> sign = { 0 };
    vector<int> index;
    vector<int> mantissa;
};

vector<int> addition(vector<int> numbers1, vector<int> numbers2)
{
    vector<int> numbers;
    bool flag = false;
    for (size_t i = numbers1.size(); i > 0; i--) {
        if (flag and ((numbers1[i - 1] == 0 and numbers2[i - 1] == 1) or (numbers1[i - 1] == 1 and numbers2[i - 1] == 0))) {
            numbers.push_back(0);
            flag = true;
        }
        else if (!flag and ((numbers1[i - 1] == 0 and numbers2[i - 1] == 1) or (numbers1[i - 1] == 1 and numbers2[i - 1] == 0))) {
            numbers.push_back(1);
            flag = false;
        }
        else if (numbers1[i - 1] == 0 and numbers2[i - 1] == 0 and !flag) {
            numbers.push_back(0);
            flag = false;
        }
        else if (numbers1[i - 1] == 0 and numbers2[i - 1] == 0 and flag) {
            numbers.push_back(1);
            flag = false;
        }
        else if (numbers1[i - 1] == 1 and numbers2[i - 1] == 1 and !flag) {
            numbers.push_back(0);
            flag = true;
        }
        else if (numbers1[i - 1] == 1 and numbers2[i - 1] == 1 and flag) {
            numbers.push_back(1);
            flag = true;
        }
    }
    reverse(numbers.begin(), numbers.end());
    if (numbers[0] == 1)
        additional_to_direct(numbers);
    return numbers;
}


vector<int> sum(vector<int> numbers1, vector<int> numbers2) {
    bool numbers1_needs_conversion = numbers1[0] == 1;
    bool numbers2_needs_conversion = numbers2[0] == 1;

    numbers1 = numbers1_needs_conversion ? direct_to_additional(numbers1) : numbers1;
    numbers2 = numbers2_needs_conversion ? direct_to_additional(numbers2) : numbers2;

    return addition(numbers1, numbers2);
}

vector<int> multiplication(vector<int> numbers1,vector<int> numbers2)
{
    vector<int> numbers;
    vector<int> buf_numbers_of_one;
    vector<int> buf_numbers_of_zero;
    bool sign = false;
    if (numbers1[0] == 1 and numbers2[0] == 1) {
        numbers1[0] = 0;
        numbers2[0] = 0;
    }
    else if (numbers1[0] == 1) {
        numbers1[0] = 0;
        sign = true;
    }
    else if (numbers2[0] == 1) {
        numbers2[0] = 0;
        sign = true;
    }
    for (size_t i = 0; i < numbers1.size(); i++) {
        buf_numbers_of_one.push_back(1);
        buf_numbers_of_zero.push_back(0);
    }
    numbers = buf_numbers_of_zero;
    while (numbers2 != buf_numbers_of_zero) {
        numbers = addition(numbers, numbers1);
        numbers2 = addition(numbers2, buf_numbers_of_one);
    }
    if (sign)
        numbers[0] = 1;
    else
        numbers[0] = 0;
    return numbers;
}

vector<int> division(vector<int> numbers1, vector<int> numbers2)
{
    vector<int> numbers;
    vector<int> buf_numbers;
    vector<int> numbers_of_null;
    bool sign = false;
    if (numbers1[0] == 1 and numbers2[0] == 1)
        numbers1[0] = 0;
    else if (numbers1[0] == 1) {
        sign = true;
        numbers1[0] = 0;
    }
    else if (numbers2[0] == 1)
        sign = true;
    for (size_t i = 0; i < BASE_16; i++) {
        numbers.push_back(0);
        buf_numbers.push_back(0);
        numbers_of_null.push_back(0);
    }
    buf_numbers[15] = 1;
    numbers[15] = 1;
    numbers[0] = 1;
    numbers2[0] = 1;
    while (numbers1[0] != 1 or numbers1 == numbers_of_null) {
        numbers1 = sum(numbers1, numbers2);
        numbers = sum(numbers, buf_numbers);
    }
    if (sign)
        numbers[0] = 1;
    return numbers;
}

void print_binary(vector<int>& numbers)
{
    for (int i = 0; i < numbers.size(); i++)
        cout << numbers[i];
    cout << "\n";
}

void print_float_binary(Float& numbers)
{
    cout << numbers.sign[0] << '|';
    for (size_t i = 0; i < numbers.index.size(); i++)
        cout << numbers.index[i];
    cout << "|";
    for (size_t i = 0; i < numbers.mantissa.size(); i++)
        cout << numbers.mantissa[i];
    cout << "\n";
}


void float_addition(Float& numbers1, Float& numbers2)
{
    Float numbers;
    if (numbers1.sign[0] == 1 and numbers2.sign[0] == 1) {
        numbers.sign[0] = 1;
        numbers1.mantissa[0] = 1;
        numbers2.mantissa[0] = 1;
    }
    else if (numbers1.sign[0] == 1)
        numbers1.mantissa[0] = 1;
    else if (numbers2.sign[0] == 1)
        numbers2.mantissa[0] = 1;
    numbers.index = sum(numbers1.index, numbers2.index);
    numbers.mantissa = sum(numbers1.mantissa, numbers2.mantissa);
    float rez = direct_to_int(numbers.mantissa) * pow(10, -direct_to_int(numbers.index) / 2);
    cout << rez << "\n";
    print_float_binary(numbers);
}

Float float_to_binary(float& num)
{
    Float numbers;
    ostringstream ss;
    ss << num;
    string s(ss.str());
    int ind = 0;
    if (num < 0) {
        numbers.sign[0] = 1;
        num = -num;
    }
    for (size_t i = s.size() - 1; i > 0; i--) {
        if (s[i] == '.')
            break;
        else
            ind++;
    }
    num *= pow(10, ind);
    num = int(num);
    numbers.index = int_to_direct(ind, BASE_8);
    numbers.mantissa = int_to_direct(num, BASE_23);

    return numbers;
}


#endif //AOIS1_OPERATIONS_H
