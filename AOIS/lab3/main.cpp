#include <iostream>
#include "lib.h"

int main() {
    std::string input_formula, sdnf, sknf;
    TrueTable true_table_sdnf, true_table_sknf;
    std::cout << "Enter formula: ";
    std::getline(std::cin, input_formula);
    true_table_sknf.run_true_table(input_formula);
    true_table_sdnf.run_true_table(input_formula);
    true_table_sknf.print_table();
    sdnf = true_table_sdnf.create_normal_form(1);
    sknf = true_table_sknf.create_normal_form(0);
    std::cout << "SDNF: " << sdnf << "\n";
    std::cout << "SKNF: " << sknf << "\n";
    sdnf = true_table_sdnf.calculation_method(1);
    sknf = true_table_sknf.calculation_method(0);
    std::cout << "Calculation method:\n";
    std::cout << "TDNF: " << sdnf << "\n";
    std::cout << "TKNF: " << sknf << "\n";
    sknf = true_table_sknf.tabular_method(0);
    sdnf = true_table_sdnf.tabular_method(1);
    std::cout << "Tabular method:\n";
    std::cout << "TDNF: " << sdnf << "\n";
    std::cout << "TKNF: " << sknf << "\n";
    sdnf = true_table_sdnf.tabular_calculation_method(1);
    sknf = true_table_sknf.tabular_calculation_method(0);
    std::cout << "Tabular-calculation method:\n";
    std::cout << "TDNF: " << sdnf << "\n";
    std::cout << "TKNF: " << sknf << "\n";
}
