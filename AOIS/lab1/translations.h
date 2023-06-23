#ifndef AOIS1_TRANSLATIONS_H
#define AOIS1_TRANSLATIONS_H

#include <iostream>
#include <vector>
#include <sstream>
#include <math.h>
#include <algorithm>

using namespace std;

vector<int> int_to_direct(int number, int size)
{
    vector<int> bits(size, 0);
    int index = size - 1;
    bool is_negative = (number < 0);
    number = abs(number);
    while (number > 0 && index >= 0) {
        bits[index] = number % 2;
        number /= 2;
        index--;
    }
    if (is_negative) {
        bits[0] = 1;
        bits = direct_to_additional(bits);
    }
    return bits;
}

vector<int> reverse_bits(const vector<int>& bits)
{
    vector<int> reversed(bits.size());
    for (size_t i = 0; i < bits.size(); i++) {
        reversed[i] = (bits[i] == 0) ? 1 : 0;
    }
    return reversed;
}

vector<int> direct_to_additional(vector<int>& bits)
{
    vector<int> reversed = reverse_bits(bits);
    vector<int> sum(reversed.size(), 1);
    for (size_t i = 0; i < reversed.size(); i++) {
        if (reversed[i] == 1 && sum[i] == 1) {
            reversed[i] = 0;
        } else if (reversed[i] == 0 && sum[i] == 1) {
            reversed[i] = 1;
            break;
        }
    }
    return reverse_bits(reversed);
}

int direct_to_int(const vector<int>& bits)
{
    int value = 0;
    bool is_negative = (bits[0] == 1);
    vector<int> number = (is_negative) ? direct_to_additional(bits) : bits;
    for (size_t i = 0; i < number.size(); i++) {
        value = (value << 1) | number[i];
    }
    return (is_negative) ? -value : value;
}

vector<int> reverse_to_direct(vector<int>& bits)
{
    return reverse_bits(bits);
}

vector<int> additional_to_direct(vector<int>& bits)
{
    vector<int> reversed = reverse_bits(bits);
    vector<int> sum(reversed.size(), 1);
    for (size_t i = 0; i < reversed.size(); i++) {
        if (reversed[i] == 0 && sum[i] == 1) {
            reversed[i] = 1;
            break;
        } else if (reversed[i] == 1 && sum[i] == 1) {
            reversed[i] = 0;
        }
    }
    return reverse_bits(reversed);
}
