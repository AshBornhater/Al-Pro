#include <iostream>

#define CLEAR_TERMINAL() std::cout << "\033[2J\033[1;1H"

#define PRESS_ANY_KEY() do { \
    std::cout << "\nPress any key to continue . . . "; \
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

    char choice;
    int minute = 10;
    cout << "=== TASK 2: THE BLACK LAKE ===\n";

    while(minute < 60) {
        cout << "Minute " << minute << "... A Grindylow appears! (l: Fight, h: Dodge): ";
        
        INPUT_CHAR(choice);

        switch(choice) {
            case 'l':
                cout << "Your oxygen runs out from exhaustion fighting!\n";
                cout << ">> TIME/OXYGEN DEPLETED! A mermaid brings you back to the surface.\n";
                cout << ">> RESTARTING TASK 2 FROM THE BEGINNING...\n\n";
                minute = 10;
                PRESS_ANY_KEY();
                CLEAR_TERMINAL();
                cout << "\n=== TASK 2: THE BLACK LAKE ===\n";
                continue;
            case 'h':
                cout << "You escaped the Grindylow.\n";
                minute += 10;
                continue;
            default:
                cout << "Invalid choice! Please try again.\n";
                PRESS_ANY_KEY();
                continue;
        }
    }

    cout << "Exactly 60 minutes! You rescued the hostage." << endl;
    PRESS_ANY_KEY();
    CLEAR_TERMINAL();
    
    return 0;
}