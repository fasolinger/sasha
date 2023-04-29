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
    vector<int> numbers;
    int buf = 0;
    int num = abs(number);
    while (num) {
        buf = num % 2;
        numbers.push_back(buf);
        num /= 2;
    }
    int length = numbers.size();
    for (int i = 0; i < size - length; i++)
        numbers.push_back(0);
    reverse(numbers.begin(), numbers.end());
    if (number < 0)
        numbers[0] = 1;
    return numbers;
}

vector<int> direct_to_reverse(vector<int>& numbers)
{
    for (size_t i = 1; i < numbers.size(); i++) {
        if (numbers[i] == 1)
            numbers[i] = 0;
        else
            numbers[i] = 1;
    }
    return numbers;
}

vector<int> direct_to_additional(vector<int>& numbers)
{
    numbers = direct_to_reverse(numbers);
    if (numbers[numbers.size() - 1] == 0) {
        numbers[numbers.size() - 1] = 1;
        return numbers;
    }
    for (size_t i = numbers.size() - 1; i > 0; i--) {
        if (numbers[i - 1] == 0) {
            numbers[i] = 0;
            numbers[i - 1] = 1;
            break;
        }
        else
            numbers[i] = 0;
    }
    return numbers;
}

int direct_to_int(vector<int> numbers)
{
    int number = 0;
    reverse(numbers.begin(), numbers.end());
    for (size_t i = 0; i < numbers.size() - 1; i++)
        if (numbers[i] == 1)
            number += pow(2, i);
    if (numbers[numbers.size() - 1] == 1)
        return -number;
    else
        return number;
}

vector<int> reverse_to_direct(vector<int>& numbers)
{
    for (size_t i = 1; i < numbers.size(); i++) {
        if (numbers[i] == 1)
            numbers[i] = 0;
        else
            numbers[i] = 1;
    }
    return numbers;
}

vector<int> additional_to_direct(vector<int>& numbers)
{
    for (size_t i = numbers.size() - 1; i > 0; i--) {
        if (numbers[i] == 1 and (numbers[i - 1] == 1 or numbers[i - 1] == 0)) {
            numbers[i] = 0;
            break;
        }
        if (numbers[i] == 0)
            numbers[i] = 1;
        else
            numbers[i] = 0;
    }
    return reverse_to_direct(numbers);
}


#endif //AOIS1_TRANSLATIONS_H
