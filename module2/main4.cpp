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

    int errorTolerance = 2;
    int stepsTaken = 0;
    int diamondSize;
    char directionChoice;

    while(true) {
        cout << "=== TASK 3: THE MAZE ===\n";
        cout << "Remaining error tolerance: " << errorTolerance << endl;
        cout << "Steps taken: " << stepsTaken << endl;
        cout << "Choose a direction (1: Left, 2: Right, 3: Straight): ";
        INPUT_CHAR(directionChoice);
        
        switch (directionChoice)
        {
        case '1':
            errorTolerance -= 1;
            cout << "Hit a Poisonous Root! Remaining error tolerance: " << errorTolerance << endl;
            if (errorTolerance <= 0) {
                PRESS_ANY_KEY();
                cout << "\n>> OUT OF CHANCES! The maze reshapes and kicks you back to the entrance.\n";
                cout << ">> RESTARTING TASK 3 FROM THE BEGINNING...\n";
                errorTolerance = 2;
                stepsTaken = 0;
                PRESS_ANY_KEY();
                CLEAR_TERMINAL();
                continue;
            }
            PRESS_ANY_KEY();
            cout << endl;
            continue;
        case '2':
            cout << "Safe path, you go deeper.\n";
            stepsTaken += 1;
            if (stepsTaken == 3) {
                cout << "You see a light... Oh wait, what is that..." << endl;
                PRESS_ANY_KEY();
                break;
            }
            PRESS_ANY_KEY();
            cout << endl;
            continue;
        case '3':
            cout << "You see a light... Oh wait, what is that..." << endl;
            PRESS_ANY_KEY();
            break;
        
        default:
            cout << "You are not on a valid path! Please try again!\n";
            PRESS_ANY_KEY();
            continue;
        }
        break;  

    }
    
    cout << "\n=== THE EXIT ===\n";
    cout << "You see something glowing in the middle of the arena...\n";
    cout << "Something is trapped inside it, and there is a machine asking you to enter a number...\n\n";
    cout << "Enter a number (minimum 5): ";
    cin >> diamondSize;
    cout << "A light shines and in your hands now lies a giant diamond!\n";

    for(int i = 1; i <= diamondSize; i++) { 
        for(int j = i; j < diamondSize; j++) {
            cout << ' ';
        }
        for(int j = 1; j < (2 * i); j++) {
            cout << '*';
        }
        cout << endl;
    }
    for(int i = diamondSize - 1; i >= 1; i--) { 
        for(int j = i; j < diamondSize; j++) {
            cout << ' ';
        }
        for(int j = 1; j < (2 * i); j++) {
            cout << '*';
        }
        cout << endl;
    }
    
    cout << "\n*** CONGRATULATIONS! YOU ARE THE WINNER OF THE TRIWIZARD TOURNAMENT! ***" << endl;

    return 0;
}