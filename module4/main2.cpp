#include <iostream>

using std::cout;
using std::cin;
using std::endl;

const int MAX_ITEMS = 100;

#define CLEAR_TERMINAL() std::cout << "\033[2J\033[1;1H"

#define PRESS_ANY_KEY()                                    \
    do                                                     \
    {                                                      \
        std::cout << "\nPress any key to continue . . . "; \
        std::cin.get();                                    \
        std::cin.ignore(1000, '\n');                       \
    } while (0)



bool isInputInvalid() {
    if (cin.fail() || cin.peek() != '\n') {
        clearInputBuffer();
        cout << "[Failed] Input must be a number!" << endl;
        PRESS_ANY_KEY();
        return true;
    }
    return false;
}

void printMainHeader() {
    cout << "======================================" << endl;
    cout << "[                                     ]" << endl;
    cout << "|          MODULE 4 - FUNCTION        |" << endl;
    cout << "[                                     ]" << endl;
    cout << "======================================" << endl;
}

void printStoreHeader() {
    cout << "#=================================#" << endl;
    cout << "|          TIVAIZ STORE           |" << endl;
    cout << "#=================================#" << endl;
}

void printCalcHeader() {
    cout << "+=================================-" << endl;
    cout << "|          K4LKUL4T0R             |" << endl;
    cout << "x=================================/" << endl;
}

void copyString(char dest[], const char src[]) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

long long factorial(int n) {
    if (n == 0) return 1;
    return n * factorial(n - 1);
}

float basicOperation(float numA, float numB, char op) {
    if (op == '+') return numA + numB;
    if (op == '-') return numA - numB;
    if (op == '*') return numA * numB;
    if (op == '/') return numA / numB;
    return 0;
}

bool addItem(char itemNames[][100], int itemStocks[], int itemPrices[], int &totalItems) {
    CLEAR_TERMINAL();
    printStoreHeader();
    cout << "--------------------------------" << endl;
    cout << "           ADD ITEM" << endl;
    cout << "--------------------------------" << endl;

    char itemName[100];
    int stockVal, priceVal;

    cout << "--------------------------------" << endl;
    cout << "Item Name    : ";
    cin.ignore();
    cin.getline(itemName, 100);

    cout << "--------------------------------" << endl;
    cout << "Stock (unit) : ";
    cin >> stockVal;
    if (isInputInvalid()) {
        return true;
    }

    cout << "--------------------------------" << endl;
    cout << "Price        : ";
    cin >> priceVal;
    if (isInputInvalid()) {
        return true;
    }

    copyString(itemNames[totalItems], itemName);
    itemStocks[totalItems] = stockVal;
    itemPrices[totalItems] = priceVal;
    totalItems++;

    cout << "[Success] " << itemName << " added! (Total items: " << totalItems << ")" << endl;
    PRESS_ANY_KEY();
    return false;
}

bool removeItem(char itemNames[][100], int itemStocks[], int itemPrices[], int &totalItems) {
    CLEAR_TERMINAL();
    printStoreHeader();
    cout << "--------------------------------" << endl;
    cout << "           REMOVE ITEM" << endl;

    for (int i = 0; i < totalItems; i++) {
        cout << "--------------------------------" << endl;
        cout << "No           : " << i + 1 << endl;
        cout << "Item Name    : " << itemNames[i] << endl;
        cout << "Stock        : " << itemStocks[i] << endl;
        cout << "Price/Unit   : " << itemPrices[i] << endl;
    }

    cout << "------------------------------------------------" << endl;
    cout << "Choose item number to remove (1-" << totalItems << "): ";

    int choice;
    cin >> choice;
    if (isInputInvalid()) {
        return true;
    }

    if (choice < 1 || choice > totalItems) {
        cout << "[Failed] Number " << choice << " is invalid! Choose between 1 and " << totalItems << "." << endl;
        PRESS_ANY_KEY();
        return true;
    }

    char removedName[100];
    copyString(removedName, itemNames[choice - 1]);

    for (int i = choice - 1; i < totalItems - 1; i++) {
        copyString(itemNames[i], itemNames[i + 1]);
        itemStocks[i] = itemStocks[i + 1];
        itemPrices[i] = itemPrices[i + 1];
    }
    totalItems--;

    cout << "[Success] " << removedName << " removed! (Total items: " << totalItems << ")" << endl;
    PRESS_ANY_KEY();
    return false;
}

bool editItem(char itemNames[][100], int itemStocks[], int itemPrices[], int totalItems) {
    while (true) {
        CLEAR_TERMINAL();
        printStoreHeader();
        cout << "--------------------------------" << endl;
        cout << "           EDIT ITEM" << endl;

        for (int i = 0; i < totalItems; i++) {
            cout << "--------------------------------" << endl;
            cout << "No           : " << i + 1 << endl;
            cout << "Item Name    : " << itemNames[i] << endl;
            cout << "Stock        : " << itemStocks[i] << endl;
            cout << "Price/Unit   : " << itemPrices[i] << endl;
        }

        cout << "------------------------------------------------" << endl;
        cout << "Choose item number to edit (1-" << totalItems << "): ";

        int choice;
        cin >> choice;
        if (isInputInvalid()) {
            return true;
        }

        if (choice < 1 || choice > totalItems) {
            cout << "[Failed] Number " << choice << " is invalid! Choose between 1 and " << totalItems << "." << endl;
            PRESS_ANY_KEY();
            return true;
        }

        int idx = choice - 1;

        while (true) {
            CLEAR_TERMINAL();
            printStoreHeader();
            cout << "--------------------------------" << endl;
            cout << "           EDIT ITEM" << endl;
            cout << "--------------------------------" << endl;
            cout << "Item  : " << itemNames[idx] << endl;
            cout << "--------------------------------" << endl;
            cout << "1. Edit Price" << endl;
            cout << "2. Add Stock" << endl;
            cout << "3. Reduce Stock" << endl;
            cout << "0. Back" << endl;
            cout << "--------------------------------" << endl;
            cout << "Choose option: ";

            int option;
            cin >> option;
            if (isInputInvalid()) {
                return true;
            }

            if (option == 0) {
                return false;
            } else if (option == 1) {
                int oldPrice = itemPrices[idx];
                cout << "--------------------------------" << endl;
                cout << "New Price : ";
                int newPrice;
                cin >> newPrice;
                if (isInputInvalid()) {
                    return true;
                }

                itemPrices[idx] = newPrice;
                cout << "[Success] Price of " << itemNames[idx] << ": " << oldPrice << " -> " << newPrice << endl;
                PRESS_ANY_KEY();
            } else if (option == 2) {
                int oldStock = itemStocks[idx];
                cout << "--------------------------------" << endl;
                cout << "Amount to add: ";
                int amount;
                cin >> amount;
                if (isInputInvalid()) {
                    return true;
                }

                itemStocks[idx] += amount;
                cout << "[Success] Stock of " << itemNames[idx] << ": " << oldStock << " -> " << itemStocks[idx] << endl;
                PRESS_ANY_KEY();
            } else if (option == 3) {
                cout << "--------------------------------" << endl;
                cout << "Amount to reduce: ";
                int amount;
                cin >> amount;
                if (isInputInvalid()) {
                    return true;
                }

                if (itemStocks[idx] - amount < 1) {
                    cout << "[Failed] Minimum stock is 1!" << endl;
                    PRESS_ANY_KEY();
                    return true;
                }
                int oldStock = itemStocks[idx];
                itemStocks[idx] -= amount;
                cout << "[Success] Stock of " << itemNames[idx] << ": " << oldStock << " -> " << itemStocks[idx] << endl;
                PRESS_ANY_KEY();
            } else {
                cout << "[Failed] Invalid menu! Choose between 0 and 3." << endl;
                PRESS_ANY_KEY();
                return true;
            }
        }
    }
}

bool viewItems(char itemNames[][100], int itemStocks[], int itemPrices[], int totalItems) {
    CLEAR_TERMINAL();
    printStoreHeader();
    cout << "--------------------------------" << endl;
    cout << "           VIEW ITEMS" << endl;

    for (int i = 0; i < totalItems; i++) {
        cout << "--------------------------------" << endl;
        cout << "No           : " << i + 1 << endl;
        cout << "Item Name    : " << itemNames[i] << endl;
        cout << "Stock        : " << itemStocks[i] << endl;
        cout << "Price/Unit   : " << itemPrices[i] << endl;
        cout << "Total Price  : " << itemStocks[i] * itemPrices[i] << endl;
    }

    cout << "------------------------------------------------" << endl;
    cout << "Total items  : " << totalItems << " types" << endl;
    cout << "------------------------------------------------" << endl;
    PRESS_ANY_KEY();
    return false;
}

bool menuStore(char itemNames[][100], int itemStocks[], int itemPrices[], int &totalItems) {
    while (true) {
        CLEAR_TERMINAL();
        printStoreHeader();
        cout << "1. Add Item" << endl;
        cout << "2. Remove Item" << endl;
        cout << "3. Edit Item" << endl;
        cout << "4. View Items" << endl;
        cout << "0. Back" << endl;
        cout << "================================" << endl;
        cout << "Choose menu: ";

        int choice;
        cin >> choice;
        if (isInputInvalid()) {
            return true;
        }

        if (choice == 0) {
            return false;
        } else if (choice == 1) {
            if (addItem(itemNames, itemStocks, itemPrices, totalItems)) {
                return true;
            }
        } else if (choice == 2) {
            if (removeItem(itemNames, itemStocks, itemPrices, totalItems)) {
                return true;
            }
        } else if (choice == 3) {
            if (editItem(itemNames, itemStocks, itemPrices, totalItems)) {
                return true;
            }
        } else if (choice == 4) {
            if (viewItems(itemNames, itemStocks, itemPrices, totalItems)) {
                return true;
            }
        } else {
            cout << "[Failed] Invalid menu! Choose between 0 and 4." << endl;
            PRESS_ANY_KEY();
            return true;
        }
    }
}

bool menuBasicOp() {
    CLEAR_TERMINAL();
    printCalcHeader();
    cout << "--------------------------------" << endl;
    cout << "Operator (+, -, *, /) : ";
    char op;
    cin.get(op);
    clearInputBuffer();

    if (op != '+' && op != '-' && op != '*' && op != '/') {
        cout << "[Failed] Invalid operator!" << endl;
        PRESS_ANY_KEY();
        return true;
    }

    cout << "--------------------------------" << endl;
    cout << "First number  : ";
    float numA;
    cin >> numA;
    if (isInputInvalid()) {
        return true;
    }

    cout << "--------------------------------" << endl;
    cout << "Second number : ";
    float numB;
    cin >> numB;
    if (isInputInvalid()) {
        return true;
    }

    cout << "--------------------------------" << endl;
    if (op == '/' && numB == 0) {
        cout << "[Failed] Cannot divide by zero!" << endl;
        PRESS_ANY_KEY();
        return true;
    }

    float result = basicOperation(numA, numB, op);
    cout << numA << " " << op << " " << numB << " = " << result << endl;
    PRESS_ANY_KEY();
    return false;
}

bool menuFactorial() {
    CLEAR_TERMINAL();
    printCalcHeader();
    cout << "--------------------------------" << endl;
    cout << "N : ";
    int n;
    cin >> n;
    if (isInputInvalid()) {
        return true;
    }

    cout << "--------------------------------" << endl;
    if (n < 0) {
        cout << "[Failed] Factorial is not defined for negative numbers!" << endl;
        PRESS_ANY_KEY();
        return true;
    }

    long long result = factorial(n);
    cout << n << "! = " << result << endl;
    PRESS_ANY_KEY();
    return false;
}

bool menuCalc() {
    while (true) {
        CLEAR_TERMINAL();
        printCalcHeader();
        cout << "1. Basic Operation (+, -, *, /)" << endl;
        cout << "2. Factorial" << endl;
        cout << "0. Back" << endl;
        cout << "===============================" << endl;
        cout << "Choose menu: ";

        int choice;
        cin >> choice;
        if (isInputInvalid()) {
            return true;
        }

        if (choice == 0) {
            return false;
        } else if (choice == 1) {
            if (menuBasicOp()) {
                return true;
            }
        } else if (choice == 2) {
            if (menuFactorial()) {
                return true;
            }
        } else {
            cout << "[Failed] Invalid menu! Choose between 0 and 2." << endl;
            PRESS_ANY_KEY();
            return true;
        }
    }
}

int main() {
    char itemNames[MAX_ITEMS][100];
    int itemStocks[MAX_ITEMS];
    int itemPrices[MAX_ITEMS];
    int totalItems = 0;

    while (true) {
        CLEAR_TERMINAL();
        printMainHeader();
        cout << "1. TIVAIZ Store" << endl;
        cout << "2. TIVAIZ Calculator" << endl;
        cout << "0. Exit" << endl;
        cout << "================================" << endl;
        cout << "Choose menu: ";

        int choice;
        cin >> choice;
        if (isInputInvalid()) {
            continue;
        }

        if (choice == 0) {
            break;
        } else if (choice == 1) {
            menuStore(itemNames, itemStocks, itemPrices, totalItems);
        } else if (choice == 2) {
            menuCalc();
        } else {
            cout << "[Failed] Invalid menu! Choose between 0 and 2." << endl;
            PRESS_ANY_KEY();
        }
    }

    return 0;
}