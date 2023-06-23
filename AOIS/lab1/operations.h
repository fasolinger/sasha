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

vector<int> add_binary_vectors(const vector<int>& v1, const vector<int>& v2)
{
    vector<int> res;
    int carry = 0;
    for (int i = v1.size() - 1; i >= 0; i--) {
        int sum = v1[i] + v2[i] + carry;
        res.push_back(sum % 2);
        carry = sum / 2;
    }
    if (carry > 0) {
        res.push_back(carry);
    }
    reverse(res.begin(), res.end());
    return res;
}

vector<int> addition(const vector<int>& numbers1, const vector<int>& numbers2)
{
    vector<int> res = add_binary_vectors(numbers1, numbers2);
    if (res[0] == 1) {
        res = additional_to_direct(res);
    }
    return res;
}



vector<int> to_direct_notation(const vector<int>& numbers)
{
    vector<int> res = numbers;
    if (res[0] == 1) {
        res = direct_to_additional(res);
    }
    return res;
}

vector<int> sum(const vector<int>& numbers1, const vector<int>& numbers2)
{
    vector<int> numbers1_direct = to_direct_notation(numbers1);
    vector<int> numbers2_direct = to_direct_notation(numbers2);
    vector<int> res = add_binary_vectors(numbers1_direct, numbers2_direct);
    return to_additional_notation(res);
}

vector<int> multiply(const vector<int>& numbers1, const vector<int>& numbers2)
{
    bool sign = (numbers1[0] == 1) ^ (numbers2[0] == 1);
    vector<int> numbers1_abs = to_direct_notation(abs(numbers1));
    vector<int> numbers2_abs = to_direct_notation(abs(numbers2));
    vector<int> res(numbers1_abs.size() + numbers2_abs.size(), 0);
    for (int i = numbers1_abs.size() - 1; i >= 0; i--) {
        int carry = 0;
        for (int j = numbers2_abs.size() - 1; j >= 0; j--) {
            int prod = numbers1_abs[i] * numbers2_abs[j] + res[i + j + 1] + carry;
            res[i + j + 1] = prod % 2;
            carry = prod / 2;
        }
        res[i] += carry;
    }
    res = to_additional_notation(res);
    res[0] = sign ? 1 : 0;
    return res;
}


void print_float_binary(const Float& numbers)
{
    cout << numbers.sign[0] << '|';
    print_binary(numbers.index);
    cout << '|';
    print_binary(numbers.mantissa);
    cout << "\n";
}

Float add_floats(const Float& numbers1, const Float& numbers2)
{
    Float numbers;
    bool both_negative = (numbers1.sign[0] == 1) && (numbers2.sign[0] == 1);
    bool first_negative = (numbers1.sign[0] == 1) && (numbers2.sign[0] == 0);
    bool second_negative = (numbers1.sign[0] == 0) && (numbers2.sign[0] == 1);
    
    if (both_negative) {
        numbers.sign[0] = 1;
        numbers1.mantissa[0] = 1;
        numbers2.mantissa[0] = 1;
    }
    else if (first_negative) {
        numbers1.mantissa[0] = 1;
        numbers = subtract_floats(numbers1, numbers2);
        return numbers;
    }
    else if (second_negative) {
        numbers2.mantissa[0] = 1;
        numbers = subtract_floats(numbers1, numbers2);
        return numbers;
    }

    numbers.index = sum(numbers1.index, numbers2.index);
    numbers.mantissa = sum(numbers1.mantissa, numbers2.mantissa);

    int mantissa_int = direct_to_int(numbers.mantissa);
    int index_int = direct_to_int(numbers.index);
    float rez = mantissa_int * pow(10, -index_int / 2.0);

    cout << rez << "\n";
    return numbers;
}

Float float_to_binary(float num)
{
    Float numbers;
    int ind = 0;
    if (num < 0) {
        numbers.sign[0] = 1;
        num = -num;
    }
    while (num >= 2) {
        num /= 2;
        ind++;
    }
    while (num < 1 && num != 0) {
        num *= 2;
        ind--;
    }
    vector<int> index_bits = int_to_binary(abs(ind));
    vector<int> mantissa_bits;
    for (int i = 0; i < 23; i++) {
        num *= 2;
        if (num >= 1) {
            mantissa_bits.push_back(1);
            num -= 1;
        } else {
            mantissa_bits.push_back(0);
        }
    }
    numbers.index = index_bits;
    numbers.mantissa = mantissa_bits;
    return numbers;
}


#endif //AOIS1_OPERATIONS_H
