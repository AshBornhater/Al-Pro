#include <iostream>

int main()
{
    int encryptionRange, reverseRange;
    char baseWord[5] = {'a', 'l', 'p', 'r', 'o'};

    std::cout << "|================ ENCRYPTION =================|" << std::endl;
    std::cout << "Enter range      : ";
    std::cin >> encryptionRange;

    std::cout << "Encrypt Result   : " 
              << (char)((baseWord[0] - 97 + (encryptionRange % 26) + 26) % 26 + 97)
              << (char)((baseWord[1] - 97 + (encryptionRange % 26) + 26) % 26 + 97)
              << (char)((baseWord[2] - 97 + (encryptionRange % 26) + 26) % 26 + 97)
              << (char)((baseWord[3] - 97 + (encryptionRange % 26) + 26) % 26 + 97)
              << (char)((baseWord[4] - 97 + (encryptionRange % 26) + 26) % 26 + 97)
              << std::endl << std::endl;

    std::cout << "|================ REVERSE ===================|" << std::endl;
    std::cout << "Enter range      : ";
    std::cin >> reverseRange;

    std::cout << "Reverse Result   : " 
              << (char)((baseWord[0] - 97 - (reverseRange % 26) + 26) % 26 + 97)
              << (char)((baseWord[1] - 97 - (reverseRange % 26) + 26) % 26 + 97)
              << (char)((baseWord[2] - 97 - (reverseRange % 26) + 26) % 26 + 97)
              << (char)((baseWord[3] - 97 - (reverseRange % 26) + 26) % 26 + 97)
              << (char)((baseWord[4] - 97 - (reverseRange % 26) + 26) % 26 + 97)
              << std::endl;

    return 0;
}