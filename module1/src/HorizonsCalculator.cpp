#include <iostream>


int main() {
    double firstNumber;
    double secondNumber;
    
    std::cout << "|============== HORIZON CALCULATOR ==============|" << std::endl;
    std::cout << "Input First Number   : ";
    std::cin >> firstNumber;
    std::cout << "Input Second Number  : ";
    std::cin >> secondNumber;
    
    std::cout << "|============== HORIZON CALCULATOR ==============|" << std::endl;
    std::cout << "Addition             : " << firstNumber + secondNumber << std::endl;
    std::cout << "Subtraction          : " << firstNumber - secondNumber << std::endl;
    std::cout << "Multiplication       : " << firstNumber * secondNumber << std::endl;
    std::cout << "Division             : " << firstNumber / secondNumber << std::endl;
    
    
}

