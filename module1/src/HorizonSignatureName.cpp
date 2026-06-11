#include <iostream>

int main()
{
    char lowercaseWord[5];
    std::cout << "|============== HORIZON SIGNATURE NAME ==============|" << std::endl;
    std::cout << "Input 5 Word (Lowercase)  : ";
    std::cin >> lowercaseWord;

    std::cout << "INPUT        : " << lowercaseWord << std::endl;
    std::cout << "UPPERCASE    : " 
              << (char)(lowercaseWord[0] - 32)
              << (char)(lowercaseWord[1] - 32)
              << (char)(lowercaseWord[2] - 32)
              << (char)(lowercaseWord[3] - 32)
              << (char)(lowercaseWord[4] - 32)
              << std::endl;
    std::cout << "ASCII        : " 
              << (int)(lowercaseWord[0]) << " "
              << (int)(lowercaseWord[1]) << " "
              << (int)(lowercaseWord[2]) << " "
              << (int)(lowercaseWord[3]) << " "
              << (int)(lowercaseWord[4]) << " "
              << std::endl;
    std::cout << "TOTAL ASCII  : " 
              << (int)(lowercaseWord[0]) + 
                 (int)(lowercaseWord[1]) + 
                 (int)(lowercaseWord[2]) + 
                 (int)(lowercaseWord[3]) + 
                 (int)(lowercaseWord[4]) 
              << std::endl;
    std::cout << "MEAN : "
              << (lowercaseWord[0] +
                  lowercaseWord[1] +
                  lowercaseWord[2] +
                  lowercaseWord[3] +
                  lowercaseWord[4]) / 5.0
              << std::endl;
              
}