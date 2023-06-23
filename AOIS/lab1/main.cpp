#include <iostream>
#include <vector>
#include "translations.h"
#include "operations.h"

using namespace std;

void perform_integer_operations(int num1, int num2)
{
vector<int> numbers1;
vector<int> numbers2;
vector<int> numbers;
cout << "First number = " << num1 << "\n"
<< "Second number = " << num2 << "\n";
numbers1 = convert_integer_to_base(num1, BASE_16);
numbers2 = convert_integer_to_base(num2, BASE_16);
numbers = sum_of_vectors(numbers1, numbers2);
cout << "Sum of numbers = " << convert_base_to_integer(numbers) << "\n";
print_binary_representation(numbers);
numbers = multiply_vectors(numbers1, numbers2);
cout << "Product of numbers = " << convert_base_to_integer(numbers) << "\n";
print_binary_representation(numbers);
numbers = divide_vectors(numbers1, numbers2);
cout << "num1 / num2 = " << convert_base_to_integer(numbers) << "\n";
print_binary_representation(numbers);
numbers = divide_vectors(numbers2, numbers1);
cout << "num2 / num1 = " << convert_base_to_integer(numbers) << "\n";
print_binary_representation(numbers);
cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << "\n";
}

void perform_arithmetic_on_floats(float number1, float number2)
{
Float numbers1, numbers2;
cout << "First number = " << number1 << "\n"
<< "Second number = " << number2 << "\n"
<< "Sum of numbers = ";
numbers1 = convert_float_to_binary(number1);
numbers2 = convert_float_to_binary(number2);
perform_float_addition(numbers1, numbers2);
}

int main()
{
int num1 = 9, num2 = 22;
perform_integer_operations(num1, num2);
perform_integer_operations(-num1, -num2);
perform_integer_operations(num1, -num2);
perform_integer_operations(-num1, num2);
