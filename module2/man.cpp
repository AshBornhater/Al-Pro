#include <iostream>

#define CLEAR_TERMINAL() std::cout << "\033[2J\033[1;1H";


#define PRESS_ANY_KEY() do { \
    std::cout << "Press Any Key to Continue . . . "; \
    std::cin.get(); \
    std::cin.ignore(1000, '\n'); \
} while(0)

using std::cout;
using std::cin;
using std::endl;


void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}   

int main() {
    cout << "Ini halaman 1" << endl;
    
    PRESS_ANY_KEY();
    clearScreen();
    
    cout << "Ini halaman 2, halaman 1 sudah terhapus!" << endl;
    
    return 0;
}