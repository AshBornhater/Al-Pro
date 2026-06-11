#include <iostream>

#define CLEAR_TERMINAL() std::cout << "\033[2J\033[1;1H"

#define PRESS_ANY_KEY() do { \
    std::cout << "Press any key to continue . . . "; \
    std::cin.get(); \
    std::cin.ignore(1000, '\n'); \
} while(0)

#define INPUT_CHAR(var) do { \
    std::cin.get(var); \
    std::cin.ignore(1000, '\n'); \
} while(0)

using std::cout;
using std::cin;
using std::endl;

int main() {

    int magicalProtection = 3;
    char strategyChoice;

    while(true) {
        cout << "=== TASK 1: HUNGARIAN HORNTAIL DRAGON ===\n";
        cout << "Remaining magical protection: " << magicalProtection << " time(s)." << endl;
        cout << "Choose a strategy (a: Hide, b: Summon Broom): ";
        
        INPUT_CHAR(strategyChoice);

        switch(strategyChoice) {
               case 'a':
                   cout << "The dragon breathes fire! You are injured.\n";
                   magicalProtection -= 1;
                   if(magicalProtection <= 0) {
                       PRESS_ANY_KEY();
                       cout << "\n>> OUT OF CHANCES! You are pulled out of the arena by the dragon handler.\n";
                       cout << ">> RESTARTING TASK 1 FROM THE BEGINNING...\n";
                       magicalProtection = 3;
                       PRESS_ANY_KEY();
                       CLEAR_TERMINAL();
                       continue;
                   }
                   PRESS_ANY_KEY();
                   continue;
   
               case 'b':
                   cout << "Success! You grabbed the Golden Egg!\n"; 
                   PRESS_ANY_KEY();
                   break;
               default:
                   cout << "Invalid choice! Please try again.\n";
                   PRESS_ANY_KEY();
                   continue;
        }
        break;

    }

    return 0;
}