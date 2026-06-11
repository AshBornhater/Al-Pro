#include <iostream>

#define CLEAR_TERMINAL() std::cout << "\033[2J\033[1;1H"

#define PRESS_ANY_KEY()                                    \
    do                                                     \
    {                                                      \
        std::cout << "\nPress any key to continue . . . "; \
        std::cin.get();                                    \
        std::cin.ignore(1000, '\n');                       \
    } while (0)

#define INPUT_CHAR(var)              \
    do                               \
    {                                \
        std::cin.get(var);           \
        std::cin.ignore(1000, '\n'); \
    } while (0)

using std::cin;
using std::cout;
using std::endl;

int main()
{
    // Age Qualification
    int championAge;
    cout << "\n=== GOBLET OF FIRE: TRIWIZARD TOURNAMENT ===\n";
    cout << "Enter your age: ";
    cin >> championAge;
    cin.ignore(1000, '\n');

    if (championAge <= 0)
    {
        cout << "Your Age is not Valid!" << endl;
    }
    else if (championAge < 17)
    {
        cout << "The Goblet of Fire rejects you! You are too young!" << endl;
    }
    else
    {
        cout << "The Goblet of Fire ignites! You have been chosen as a Triwizard Champion.\n"
             << endl;
        PRESS_ANY_KEY();

        // Dragon Arena
        int magicalProtection = 3;
        char strategyChoice;

        while (true)
        {
            cout << "=== TASK 1: HUNGARIAN HORNTAIL DRAGON ===\n";
            cout << "Remaining magical protection: " << magicalProtection << " time(s)." << endl;
            cout << "Choose a strategy (a: Hide, b: Summon Broom): ";

            INPUT_CHAR(strategyChoice);

            switch (strategyChoice)
            {
            case 'a':
                cout << "The dragon breathes fire! You are injured.\n";
                magicalProtection -= 1;
                if (magicalProtection <= 0)
                {
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
                CLEAR_TERMINAL();
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
                PRESS_ANY_KEY();
                continue;
            }
            break;
        }

        // The Black Lake
        char choice;
        int minute = 10;
        cout << "=== TASK 2: THE BLACK LAKE ===\n";

        while (minute < 60)
        {
            cout << "Minute " << minute << "... A Grindylow appears! (l: Fight, h: Dodge): ";

            INPUT_CHAR(choice);

            switch (choice)
            {
            case 'l':
                cout << "Your oxygen runs out from exhaustion fighting!\n";
                cout << ">> TIME/OXYGEN DEPLETED! A mermaid brings you back to the surface.\n";
                cout << ">> RESTARTING TASK 2 FROM THE BEGINNING...\n\n";
                minute = 10;
                PRESS_ANY_KEY();
                CLEAR_TERMINAL();
                cout << "=== TASK 2: THE BLACK LAKE ===\n";
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

        // The Living Maze
        int errorTolerance = 2;
        int stepsTaken = 0;
        int diamondSize;
        char directionChoice;

        while (true)
        {
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
                if (errorTolerance <= 0)
                {
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
                if (stepsTaken == 3)
                {
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
        while (diamondSize < 5)
        {
            cout << "Enter a number (minimum 5): ";
            cin >> diamondSize;
        }

        cout << "A light shines and in your hands now lies a giant diamond!\n\n";

        // Diamond Shape
        for (int i = 1; i <= diamondSize; i++)
        {
            for (int j = i; j < diamondSize; j++)
                cout << ' ';
            for (int j = 1; j < (2 * i); j++)
                cout << '*';
            cout << endl;
        }
        for (int i = diamondSize - 1; i >= 1; i--)
        {
            for (int j = i; j < diamondSize; j++)
                cout << ' ';
            for (int j = 1; j < (2 * i); j++)
                cout << '*';
            cout << endl;
        }

        cout << "\n*** CONGRATULATIONS! YOU ARE THE WINNER OF THE TRIWIZARD TOURNAMENT! ***" << endl;
    }

    return 0;
}