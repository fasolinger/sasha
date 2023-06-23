#include "lib.h"


int main()
{
   TrueTable true_table;
std::string formula;
std::cout << "Enter formula: ";
std::getline(std::cin, formula);

true_table.generate_table(formula);
true_table.print_table();

std::vector<int> sknf = true_table.get_sknf();
std::vector<int> sdnf = true_table.get_sdnf();

std::cout << "SKNF: ";
print_formula(sknf);
std::cout << "SDNF: ";
print_formula(sdnf);

std::vector<int> binary_sknf = true_table.get_binary_sknf();
std::vector<int> binary_sdnf = true_table.get_binary_sdnf();

std::cout << "Binary SKNF: ";
print_formula(binary_sknf);
std::cout << "Binary SDNF: ";
print_formula(binary_sdnf);

std::vector<int> decimal_sknf = true_table.get_decimal_sknf();
std::vector<int> decimal_sdnf = true_table.get_decimal_sdnf();

std::cout << "Decimal SKNF: ";
print_formula(decimal_sknf);
std::cout << "Decimal SDNF: ";
print_formula(decimal_sdnf);

std::vector<int> index = true_table.get_index();

std::cout << "Index: ";
print_formula(index);
}
