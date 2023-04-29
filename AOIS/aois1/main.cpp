#include <iostream>
#include <vector>
#include "translations.h"
#include "operations.h"

using namespace std;

void run_int(int num1, int num2)
{
    vector<int> numbers1;
    vector<int> numbers2;
    vector<int> numbers;
    cout << "num1 = " << num1 << "\n"
              << "num2 = " << num2 << "\n";
    numbers1 = int_to_direct(num1, BASE_16);
    numbers2 = int_to_direct(num2, BASE_16);
    numbers = sum(numbers1, numbers2);
    cout << "num1 + num2 = " << direct_to_int(numbers) << "\n";
    print_binary(numbers);
    numbers = multiplication(numbers1, numbers2);
    cout << "num1 * num2 = " << direct_to_int(numbers) << "\n";
    print_binary(numbers);
    numbers = division(numbers1, numbers2);
    cout << "num1 / num2 = " << direct_to_int(numbers) << "\n";
    print_binary(numbers);
    numbers = division(numbers2, numbers1);
    cout << "num2 / num1 = " << direct_to_int(numbers) << "\n";
    print_binary(numbers);
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << "\n";
}

int main()
{
    //9 22
    int num1 = 9, num2 = 22;
    run_int(num1, num2);
    run_int(-num1, -num2);
    run_int(num1, -num2);
    run_int(-num1, num2);

    float number1 = 2.725, number2 = 5.175;
    Float numbers1, numbers2;
    cout << "num1 = " << number1 << "\n"
         << "num2 = " << number2 << "\n"
         << "num1 + num2 = ";
    numbers1 = float_to_binary(number1);
    numbers2 = float_to_binary(number2);
    float_addition(numbers1, numbers2);
}