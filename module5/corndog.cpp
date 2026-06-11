#include <iostream>
#include <climits>

#define CLEAR_TERMINAL() std::cout << "\033[2J\033[1;1H"

#define PRESS_ANY_KEY()                              \
    do                                               \
    {                                                \
        std::cout << "\nPress Enter to continue..."; \
        std::cin.get();                              \
    } while (0)

#define RESET  "\033[0m"
#define RED    "\033[31m"
#define GREEN  "\033[32m"
#define BLUE   "\033[34m"
#define YELLOW "\033[33m"

using std::cin;
using std::cout;
using std::endl;
using std::string;

// Constants
const int PATTY_COUNT   = 3;
const int SAUCE_COUNT   = 6;
const int TOPPING_COUNT = 6;
const int BREAD_NEEDED  = 2;
const int MAX_HISTORY   = 200;

// Ingredient struct
struct Ingredient {
    string name;
    int    stock;
    int    buyPrice;

    bool isAvailable() {
        return stock > 0;
    }

    void restock(int amount) {
        stock += amount;
    }

    void deduct(int amount) {
        stock -= amount;
    }

    void displayStock() {
        cout << "  ~ " << name
             << " (Stock: " << stock << ")"
             << " | Rp." << buyPrice << endl;
    }

    void displayBuy(int number) {
        cout << "  " << number << ". "
             << name
             << " (Stock: " << stock
             << " | Price: Rp." << buyPrice << "/pcs)" << endl;
    }
};

// Customer random order struct
struct Order {
    int pattyIndex;
    int sauceIndex;
    int toppingIndex;

    void display(Ingredient pattyList[], Ingredient sauceList[], Ingredient toppingList[]) {
        cout << "=================================================" << endl;
        cout << "               CUSTOMER ORDER"                     << endl;
        cout << "  Patty : " << pattyList[pattyIndex].name         << endl;
        cout << "  Sauce : " << sauceList[sauceIndex].name         << endl;
        cout << "  Extra : " << toppingList[toppingIndex].name     << endl;
        cout << "=================================================" << endl;
    }
};

// Transaction history struct
struct Record {
    string pattyName;
    string sauceName;
    string toppingName;
    bool   correct;
    int    earned;

    void display(int number) {
        cout << "  Customer #" << number          << endl;
        cout << "    Patty   : " << pattyName     << endl;
        cout << "    Sauce   : " << sauceName     << endl;
        cout << "    Topping : " << toppingName   << endl;
        cout << "    Result  : ";
        if (correct) {
            cout << "Success";
        } else {
            cout << "Failed";
        }
        cout << " | Earned: Rp." << earned << endl;
        cout << "  -------------------------------------------------" << endl;
    }
};

// State management
struct Shop {
    int        money;
    int        startingCapital;
    int        totalSpent;
    int        totalEarned;
    int        totalCustomers;

    Ingredient pattyList[PATTY_COUNT];
    Ingredient sauceList[SAUCE_COUNT];
    Ingredient toppingList[TOPPING_COUNT];
    Ingredient bread;

    Record     history[MAX_HISTORY];
    int        historyCount;

    void setup() {
        money           = 200000;
        startingCapital = 200000;
        totalSpent      = 0;
        totalEarned     = 0;
        totalCustomers  = 0;
        historyCount    = 0;

        // Patty initialization
        pattyList[0] = {"Beef Sausage",    2, 10000};
        pattyList[1] = {"Mozarella",       2, 13000};
        pattyList[2] = {"Chicken Sausage", 2,  7000};

        // Sauce initialization
        sauceList[0] = {"Sweet",            2, 1000};
        sauceList[1] = {"Spicy",            2, 1000};
        sauceList[2] = {"Mayonnaise",       2, 1000};
        sauceList[3] = {"Sweet Spicy",      2, 1000};
        sauceList[4] = {"Spicy Mayonnaise", 2, 1000};
        sauceList[5] = {"All Sauce",        2, 1000};

        // Topping initialization
        toppingList[0] = {"Breadcrumbs",   2, 1000};
        toppingList[1] = {"Potato",        2, 3000};
        toppingList[2] = {"Matcha",         2, 1000};
        toppingList[3] = {"Chocolate",     2, 2000};
        toppingList[4] = {"Tiramisu",      2, 1000};
        toppingList[5] = {"Choco Crunchy", 2, 2000};

        // Bread initial stock is 2
        bread = {"Bread", 2, 1000};
    }
};

// Display helpers
void showHeader() {
    cout << BLUE;
    cout << "        /___)/__ \\( __ \\( \\( ) ( __ \\/ __ \\/___)" << endl;
    cout << "       ( (__ ( (_) ))   / )  (   )(_) )(_) ) (_" << endl;
    cout << "        \\___)\\___/ (_)\\_)(_)\\_) (____/ \\___/\\___)" << endl;
    cout << RED;
    cout << "               >> Corn Dog Simulator <<" << endl;
    cout << YELLOW;
    cout << "==========================================================" << endl;
    cout << RESET;
}

void showWelcomeScreen(Shop &shop) {
    CLEAR_TERMINAL();
    showHeader();
    cout << endl;
    cout << "    Welcome to CornDog - Corn Dog Shop!" << endl;
    cout << "    Player receives a starting capital of Rp." << shop.startingCapital << endl;
    cout << endl;
    cout << "==========================================================" << endl;
    cout << "Press Enter to start playing...";
    cin.get();
}

void showHappyLogo() {
    cout << RED;
    cout << "\t\t             .-----."                                             << endl;
    cout << "\t\t            ( o   o )   <- happy customer!"                       << endl;
    cout << "\t\t             \\  ~  /"                                            << endl;
    cout << "\t\t        " << GREEN << "_____" << RED << "/" << GREEN << "____" << RED << "\\" << GREEN << "_____" << endl;
    cout << GREEN;
    cout << "\t\t       |  CORN DOG SHOP  |"                                      << endl;
    cout << "\t\t       |_________________|"                                      << endl;
    cout << "\t\t            ||    ||"                                            << endl;
    cout << YELLOW;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"  << endl;
    cout << BLUE;
    cout << "   / __)/ _ \\(  _ \\( \\( )  (  _ \\/ _ \\/ __)"                       << endl;
    cout << "  ( (__(  (_) ))   / )  (    )(_) )(_) ) (_ "                       << endl;
    cout << "   \\___)\\___ /(_)\\_)(_)\\_)  (____/ \\___/\\___)"                      << endl;
    cout << RED;
    cout << "         >> The Best Corn Dog Selling Simulator! <<"                 << endl;
    cout << YELLOW;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"  << endl;
    cout << RESET;
}

void showSadLogo() {
    cout << RED;
    cout << "\t\t             .-----."                                             << endl;
    cout << "\t\t            ( >   < )   <- unhappy customer!"                    << endl;
    cout << "\t\t             \\  _  /"                                            << endl;
    cout << "\t\t        " << GREEN << "_____" << RED << "/" << GREEN << "____" << RED << "\\" << GREEN << "_____" << endl;
    cout << GREEN;
    cout << "\t\t       |  CORN DOG SHOP  |"                                      << endl;
    cout << "\t\t       |_________________|"                                      << endl;
    cout << "\t\t            ||    ||"                                            << endl;
    cout << YELLOW;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"  << endl;
    cout << BLUE;
    cout << "   / __)/ _ \\(  _ \\( \\( )  (  _ \\/ _ \\/ __)"                       << endl;
    cout << "  ( (__(  (_) ))   / )  (    )(_) )(_) ) (_ "                       << endl;
    cout << "   \\___)\\___ /(_)\\_)(_)\\_)  (____/ \\___/\\___)"                      << endl;
    cout << RED;
    cout << "              >> Corn Dog Simulator! <<"                             << endl;
    cout << YELLOW;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"  << endl;
    cout << RESET;
}

void showExitScreen() {
    CLEAR_TERMINAL();
    showHeader();
    cout << "\n          Thank You for Playing >_<\n\n";
    cout << "=================================================" << endl;
    cout << "Press Enter to Exit...";
}

// Input helper with error handling format validation
void readInt(int &num, int maxVal) {
    while (true) {
        cout << "Your choice: ";
        cin >> num;
        if (cin.fail() || cin.peek() != '\n' || num < 0 || num > maxVal) {
            cout << RED << "  [!] Enter a number between 0 and " << maxVal << ":" << RESET << endl;
            cin.clear();
            while (cin.get() != '\n');
            continue;
        }
        break;
    }
}

// Generate random order
Order randomOrder(Shop &shop) {
    Order order;

    int availablePatty[PATTY_COUNT], pattyCount = 0;
    for (int i = 0; i < PATTY_COUNT; i++) {
        if (shop.pattyList[i].isAvailable()) {
            availablePatty[pattyCount++] = i;
        }
    }

    int availableSauce[SAUCE_COUNT], sauceCount = 0;
    for (int i = 0; i < SAUCE_COUNT; i++) {
        if (shop.sauceList[i].isAvailable()) {
            availableSauce[sauceCount++] = i;
        }
    }

    int availableTopping[TOPPING_COUNT], toppingCount = 0;
    for (int i = 0; i < TOPPING_COUNT; i++) {
        if (shop.toppingList[i].isAvailable()) {
            availableTopping[toppingCount++] = i;
        }
    }

    order.pattyIndex   = availablePatty[rand() % pattyCount];
    order.sauceIndex   = availableSauce[rand() % sauceCount];
    order.toppingIndex = availableTopping[rand() % toppingCount];

    return order;
}

// Display step menus
void showPattyMenu(Shop &shop) {
    cout << "  [STEP 1/3] Choose Patty:" << endl;
    for (int i = 0; i < PATTY_COUNT; i++) {
        cout << "   " << (i + 1) << ". "
             << shop.pattyList[i].name
             << " (Stock: " << shop.pattyList[i].stock << ")" << endl;
    }
    cout << "   0. Cancel & return to main menu" << endl;
}

void showSauceMenu(Shop &shop) {
    cout << "  [STEP 2/3] Choose Sauce:" << endl;
    for (int i = 0; i < SAUCE_COUNT; i++) {
        cout << "   " << (i + 1) << ". "
             << shop.sauceList[i].name
             << " (Stock: " << shop.sauceList[i].stock << ")" << endl;
    }
    cout << "   0. Cancel & return to main menu" << endl;
}

void showToppingMenu(Shop &shop) {
    cout << "  [STEP 3/3] Choose Topping:" << endl;
    for (int i = 0; i < TOPPING_COUNT; i++) {
        cout << "   " << (i + 1) << ". "
             << shop.toppingList[i].name
             << " (Stock: " << shop.toppingList[i].stock << ")" << endl;
    }
    cout << "   0. Cancel & return to main menu" << endl;
}

// Count profit
int calcProfit(Order &order, int pickedPatty, int pickedSauce, int pickedTopping, Shop &shop) {
    int profit = 2000;

    if (pickedPatty == order.pattyIndex) {
        profit += shop.pattyList[pickedPatty].buyPrice + 4000;
    }
    if (pickedSauce == order.sauceIndex) {
        profit += 1200;
    }
    if (pickedTopping == order.toppingIndex) {
        profit += 1200;
    }

    return profit;
}

// Show receipt (Without ANSI Color on CORRECT / WRONG strings)
void showReceipt(Order &order, int pickedPatty, int pickedSauce, int pickedTopping,
                 Shop &shop, int totalEarned) {

    bool pattyOk   = (pickedPatty   == order.pattyIndex);
    bool sauceOk   = (pickedSauce   == order.sauceIndex);
    bool toppingOk = (pickedTopping == order.toppingIndex);
    bool anyOk     = pattyOk || sauceOk || toppingOk;

    CLEAR_TERMINAL();

    if (anyOk) {
        showHappyLogo();
        cout << "  Corn Dog successfully made! Thank you!" << endl;
        cout << "=================================================" << endl;
    } else {
        showSadLogo();
        cout << "  All ingredients wrong! Customer disappointed..." << endl;
        cout << "=================================================" << endl;
    }

    cout << "  Patty   [" << shop.pattyList[pickedPatty].name << "] -> ";
    if (pattyOk) {
        cout << "CORRECT +Rp." << (shop.pattyList[pickedPatty].buyPrice + 4000) << endl;
    } else {
        cout << "WRONG +Rp.0 (ingredient wasted)" << endl;
    }

    cout << "  Sauce   [" << shop.sauceList[pickedSauce].name << "] -> ";
    if (sauceOk) {
        cout << "CORRECT +Rp.1200" << endl;
    } else {
        cout << "WRONG +Rp.0 (ingredient wasted)" << endl;
    }

    cout << "  Extra   [" << shop.toppingList[pickedTopping].name << "] -> ";
    if (toppingOk) {
        cout << "CORRECT +Rp.1200" << endl;
    } else {
        cout << "WRONG +Rp.0 (ingredient wasted)" << endl;
    }

    cout << "  -------------------------------------------------" << endl;
    cout << "  Base payment    : Rp.2000"                          << endl;
    cout << "  Total Earned    : Rp." << totalEarned               << endl;
    cout << "  Current Balance : Rp." << shop.money                << endl;
    cout << "=================================================" << endl;
}

// Menu 1 — Sell
void startSelling(Shop &shop) {
    if (shop.bread.stock < BREAD_NEEDED) {
        CLEAR_TERMINAL();
        showHeader();
        cout << RED;
        cout << "  [!] Not enough bread stock (minimum 2 bread required).\n";
        cout << "      Please buy bread from the Ingredient Stock menu." << endl;
        cout << RESET;
        cout << "=================================================" << endl;
        cout << "Press Enter to go back... " << endl;
        cin.clear();
        while (cin.get() != '\n');
        return;
    }

    int pattyReady = 0, sauceReady = 0, toppingReady = 0;
    for (int i = 0; i < PATTY_COUNT;   i++) {
        if (shop.pattyList[i].isAvailable()) {
            pattyReady++;
        }
    }
    for (int i = 0; i < SAUCE_COUNT;   i++) {
        if (shop.sauceList[i].isAvailable()) {
            sauceReady++;
        }
    }
    for (int i = 0; i < TOPPING_COUNT; i++) {
        if (shop.toppingList[i].isAvailable()) {
            toppingReady++;
        }
    }

    if (pattyReady == 0 || sauceReady == 0 || toppingReady == 0) {
        CLEAR_TERMINAL();
        showHeader();
        cout << RED << "  [!] Not enough items in warehouse to complete any combination.\n Please restock." << RESET << endl;
        cin.clear();
        while (cin.get() != '\n');
        PRESS_ANY_KEY();
        return;
    }

    Order order    = randomOrder(shop);
    int pickedPatty   = -1;
    int pickedSauce   = -1;
    int pickedTopping = -1;
    bool cancelled    = false;

    // Step 1 — Patty
    while (true) {
        CLEAR_TERMINAL();
        showHeader();
        cout << "  Balance: Rp. " << shop.money << endl;
        order.display(shop.pattyList, shop.sauceList, shop.toppingList);
        showPattyMenu(shop);
        cout << "=================================================" << endl;

        int choice;
        readInt(choice, PATTY_COUNT);

        if (choice == 0) { 
            cancelled = true; 
            break; 
        }

        int idx = choice - 1;
        if (!shop.pattyList[idx].isAvailable()) {
            cin.clear();
            // Buang sisa buffer \n dari fungsi readInt agar PRESS_ANY_KEY() bekerja dengan benar
            while (cin.get() != '\n'); 
            cout << RED << "  [!] " << shop.pattyList[idx].name << " is out of stock!" << RESET << endl;
            PRESS_ANY_KEY();
            continue;
        }

        pickedPatty = idx;
        break;
    }

    if (cancelled) {
        return;
    }

    // Step 2 — Sauce
    while (true) {
        CLEAR_TERMINAL();
        showHeader();
        cout << "  Balance: Rp. " << shop.money << endl;
        order.display(shop.pattyList, shop.sauceList, shop.toppingList);
        showSauceMenu(shop);
        cout << "=================================================" << endl;

        int choice;
        readInt(choice, SAUCE_COUNT);

        if (choice == 0) { 
            cancelled = true; 
            break; 
        }

        int idx = choice - 1;
        if (!shop.sauceList[idx].isAvailable()) {
            cin.clear();
            // Buang sisa buffer \n dari fungsi readInt agar PRESS_ANY_KEY() bekerja dengan benar
            while (cin.get() != '\n'); 
            cout << RED << "  [!] " << shop.sauceList[idx].name << " is out of stock!" << RESET << endl;
            PRESS_ANY_KEY(); 
            continue;
        }

        pickedSauce = idx;
        break;
    }

    if (cancelled) {
        return;
    }

    // Step 3 — Topping
    while (true) {
        CLEAR_TERMINAL();
        showHeader();
        cout << "  Balance: Rp. " << shop.money << endl;
        order.display(shop.pattyList, shop.sauceList, shop.toppingList);
        showToppingMenu(shop);
        cout << "=================================================" << endl;

        int choice;
        readInt(choice, TOPPING_COUNT);

        if (choice == 0) { 
            cancelled = true; 
            break; 
        }

        int idx = choice - 1;
        if (!shop.toppingList[idx].isAvailable()) {
            cin.clear();
            // Buang sisa buffer \n dari fungsi readInt agar PRESS_ANY_KEY() bekerja dengan benar
            while (cin.get() != '\n'); 
            cout << RED << "  [!] " << shop.toppingList[idx].name << " is out of stock!" << RESET << endl;
            PRESS_ANY_KEY(); 
            continue;
        }

        pickedTopping = idx;
        break;
    }

    if (cancelled) {
        return;
    }

    shop.bread.deduct(BREAD_NEEDED);
    shop.pattyList[pickedPatty].deduct(1);
    shop.sauceList[pickedSauce].deduct(1);
    shop.toppingList[pickedTopping].deduct(1);

    int profit = calcProfit(order, pickedPatty, pickedSauce, pickedTopping, shop);
    shop.money          += profit;
    shop.totalEarned    += profit;
    shop.totalCustomers += 1;

    shop.history[shop.historyCount].pattyName   = shop.pattyList[pickedPatty].name;
    shop.history[shop.historyCount].sauceName   = shop.sauceList[pickedSauce].name;
    shop.history[shop.historyCount].toppingName = shop.toppingList[pickedTopping].name;
    shop.history[shop.historyCount].correct     = (pickedPatty   == order.pattyIndex &&
                                                    pickedSauce   == order.sauceIndex &&
                                                    pickedTopping == order.toppingIndex);
    shop.history[shop.historyCount].earned      = profit;
    shop.historyCount++;

    cin.clear();
    while (cin.get() != '\n');
    showReceipt(order, pickedPatty, pickedSauce, pickedTopping, shop, profit);
    PRESS_ANY_KEY();
}

// Menu 2 — Ingredient Stock (Buy Patty)
void buyPatty(Shop &shop) {
    while (true) {
        CLEAR_TERMINAL();
        showHeader();
        cout << "  Balance: Rp. " << shop.money << endl;
        cout << "=================================================" << endl;
        cout << "   BUY REQUIRED INGREDIENTS (PATTY)"              << endl;
        cout << "=================================================" << endl;
        for (int i = 0; i < PATTY_COUNT; i++) {
            shop.pattyList[i].displayBuy(i + 1);
        }
        cout << "  4. " << shop.bread.name << " (Stock: " << shop.bread.stock << " | Price: Rp." << shop.bread.buyPrice << "/pcs)" << endl;
        cout << "  0. Back" << endl;
        cout << "=================================================" << endl;

        int choice;
        readInt(choice, 4);

        if (choice == 0) {
            return;
        }

        cout << "  How many? (0 = cancel): ";
        int amount;
        cin >> amount;
        if (cin.fail() || cin.peek() != '\n' || amount < 0) {
            cout << RED << "[!] Enter a number between 0 and" << INT_MAX << ": " << RESET << endl;
            cin.clear(); 
            while (cin.get() != '\n'); 
            PRESS_ANY_KEY(); 
            continue;
        }
        if (amount == 0) {
            continue;
        }

        int totalCost = 0;
        if (choice == 4) {
            totalCost = amount * shop.bread.buyPrice;
            if (shop.money < totalCost) {
                cout << RED << "[!] Not enough money mate: " << RESET << endl;
                cin.clear();
                while (cin.get() != '\n'); 
                PRESS_ANY_KEY(); 
                continue;
            }
            shop.bread.restock(amount);
        } else {
            int idx = choice - 1;
            totalCost = amount * shop.pattyList[idx].buyPrice;
            if (shop.money < totalCost) {
                cout << RED << "[!] Not enough money mate: " << RESET << endl;
                cin.clear(); 
                while (cin.get() != '\n'); 
                PRESS_ANY_KEY(); 
                continue;
            }
            shop.pattyList[idx].restock(amount);
        }

        shop.money      -= totalCost;
        shop.totalSpent += totalCost;
        cout << GREEN << "  [+] Restock succeeded! Total payment spent: Rp." << totalCost << RESET << endl;
        cin.clear(); 
        while (cin.get() != '\n');
        PRESS_ANY_KEY();
    }
}

// Menu 2 — Ingredient Stock (Buy Sauce)
void buySauce(Shop &shop) {
    while (true) {
        CLEAR_TERMINAL();
        showHeader();
        cout << "  Balance: Rp. " << shop.money << endl;
        cout << "=================================================" << endl;
        cout << "                   BUY SAUCE"                      << endl;
        cout << "=================================================" << endl;
        for (int i = 0; i < SAUCE_COUNT; i++) {
            shop.sauceList[i].displayBuy(i + 1);
        }
        cout << "  0. Back" << endl;
        cout << "=================================================" << endl;

        int choice;
        readInt(choice, SAUCE_COUNT);

        if (choice == 0) {
            return;
        }

        int idx = choice - 1;
        cout << "  How many? (0 = cancel): ";
        int amount;
        cin >> amount;
        if (cin.fail() || cin.peek() != '\n' || amount < 0) {
            cout << RED << "[!] Enter a number between 0 and" << INT_MAX << ": " << RESET << endl;
            cin.clear(); 
            while (cin.get() != '\n'); 
            PRESS_ANY_KEY(); 
            continue;
        }
        if (amount == 0) {
            continue;
        }

        int totalCost = amount * shop.sauceList[idx].buyPrice;
        if (shop.money < totalCost) {
            cout << RED << "[!] Not enough money mate: " << RESET << endl;
            cin.clear(); 
            while (cin.get() != '\n'); 
            PRESS_ANY_KEY(); 
            continue;
        }

        shop.sauceList[idx].restock(amount);
        shop.money      -= totalCost;
        shop.totalSpent += totalCost;
        cout << GREEN << "  [+] Restock succeeded! Total payment spent: Rp." << totalCost << RESET << endl;
        cin.clear(); 
        while (cin.get() != '\n');
        PRESS_ANY_KEY();
    }
}

// Menu 2 — Ingredient Stock (Buy Topping)
void buyTopping(Shop &shop) {
    while (true) {
        CLEAR_TERMINAL();
        showHeader();
        cout << "  Balance: Rp. " << shop.money << endl;
        cout << "=================================================" << endl;
        cout << "                BUY EXTRA TOPPINGS"                << endl;
        cout << "=================================================" << endl;
        for (int i = 0; i < TOPPING_COUNT; i++) {
            shop.toppingList[i].displayBuy(i + 1);
        }
        cout << "  0. Back" << endl;
        cout << "=================================================" << endl;

        int choice;
        readInt(choice, TOPPING_COUNT);

        if (choice == 0) {
            return;
        }

        int idx = choice - 1;
        cout << "  How many? (0 = cancel): ";
        int amount;
        cin >> amount;
        if (cin.fail() || cin.peek() != '\n' || amount < 0) {
            cout << RED << "[!] Enter a number between 0 and" << INT_MAX << ": " << RESET << endl;
            cin.clear(); 
            while (cin.get() != '\n'); 
            PRESS_ANY_KEY(); 
            continue;
        }
        if (amount == 0) {
            continue;
        }

        int totalCost = amount * shop.toppingList[idx].buyPrice;
        if (shop.money < totalCost) {
            cout << RED << "[!] Not enough money mate: " << RESET << endl;
            cin.clear(); 
            while (cin.get() != '\n'); 
            PRESS_ANY_KEY(); 
            continue;
        }

        shop.toppingList[idx].restock(amount);
        shop.money      -= totalCost;
        shop.totalSpent += totalCost;
        cout << GREEN << "  [+] Restock succeeded! Total payment spent: Rp." << totalCost << RESET << endl;
        cin.clear();
        while (cin.get() != '\n');
        PRESS_ANY_KEY();
    }
}

// Menu 2 — Ingredient Stock Category Navigation
void ingredientStock(Shop &shop) {
    while (true) {
        CLEAR_TERMINAL();
        showHeader();
        cout << "  Balance: Rp. " << shop.money << endl;
        cout << "=================================================" << endl;

        cout << "           -- Required Ingredients --" << endl;
        for (int i = 0; i < PATTY_COUNT; i++) {
            shop.pattyList[i].displayStock();
        }
        shop.bread.displayStock();

        cout << endl;
        cout << "                  -- Sauce --" << endl;
        for (int i = 0; i < SAUCE_COUNT; i++) {
            shop.sauceList[i].displayStock();
        }

        cout << endl;
        cout << "                -- Extra Toppings --" << endl;
        for (int i = 0; i < TOPPING_COUNT; i++) {
            shop.toppingList[i].displayStock();
        }

        cout << "=================================================" << endl;
        cout << "  1. Buy Ingredients"     << endl;
        cout << "  0. Return to Main Menu" << endl;
        cout << "=================================================" << endl;

        int choice;
        readInt(choice, 1);

        if (choice == 0) {
            return;
        }

        while (true) {
            CLEAR_TERMINAL();
            showHeader();
            cout << "  Balance: Rp. " << shop.money << endl;
            cout << "=================================================" << endl;
            cout << "           SELECT INGREDIENT CATEGORY"             << endl;
            cout << "=================================================" << endl;
            cout << "  1. Required Ingredients (Patty)" << endl;
            cout << "  2. Sauce"                        << endl;
            cout << "  3. Extra Toppings"               << endl;
            cout << "  0. Back"                         << endl;
            cout << "=================================================" << endl;

            int cat;
            readInt(cat, 3);

            if (cat == 0) {
                break;
            } else if (cat == 1) {
                buyPatty(shop);
            } else if (cat == 2) {
                buySauce(shop);
            } else if (cat == 3) {
                buyTopping(shop);
            }
        }
    }
}

// Menu 3 — Total Selling Report
void totalSales(Shop &shop) {
    CLEAR_TERMINAL();
    showHeader();
    cout << "=================================================" << endl;
    cout << "         FINANCIAL & SALES REPORT"                 << endl;
    cout << "=================================================" << endl;
    cout << "  Starting Capital : Rp. " << shop.startingCapital << endl;
    cout << "  Total Expenses   : Rp. " << shop.totalSpent      << endl;
    cout << "  Total Revenue    : Rp. " << shop.totalEarned     << endl;
    cout << "  -------------------------------------------------" << endl;
    cout << "  Current Balance  : Rp. " << shop.money            << endl;
    int netProfit = shop.money - shop.startingCapital;
    cout << "  Net Profit       : Rp. " << (netProfit >= 0 ? "+" : "") << netProfit << endl;
    cout << "  Customers Served : "     << shop.totalCustomers   << endl;
    cout << "=================================================" << endl;
    cout << "Press Enter to return to menu... " << endl;
    cin.clear();
    while (cin.get() != '\n');
}

// Menu 4 — Sales History Log
void salesHistory(Shop &shop) {
    CLEAR_TERMINAL();
    showHeader();
    cout << "=================================================" << endl;
    cout << "              SALES HISTORY"                       << endl;
    cout << "=================================================" << endl;

    if (shop.historyCount == 0) {
        cout << "  No transaction logs found in system." << endl;
    } else {
        for (int i = 0; i < shop.historyCount; i++) {
            shop.history[i].display(i + 1);
        }
    }

    cout << "=================================================" << endl;
    cout << "Press Enter to go back... " << endl;
    cin.clear();
    while (cin.get() != '\n');
}

// Main operational routing structure
void mainMenu(Shop &shop) {
    while (true) {
        CLEAR_TERMINAL();
        showHeader();
        cout << "\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "\t |     1. START SELLING          |" << endl;
        cout << "\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "\t |     2. INGREDIENT STOCK       |" << endl;
        cout << "\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "\t |     3. TOTAL SALES            |" << endl;
        cout << "\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "\t |     4. SALES HISTORY          |" << endl;
        cout << "\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "\t |     0. EXIT                   |" << endl;
        cout << "\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;

        int choice;
        readInt(choice, 4);

        if (choice == 1) {
            startSelling(shop);
            cin.get();
        } else if (choice == 2) {
            ingredientStock(shop);
        } else if (choice == 3) {
            totalSales(shop);
            cin.get();
        } else if (choice == 4) {
            salesHistory(shop);
            cin.get();
        } else if (choice == 0) {
            cin.clear();
            while (cin.get() != '\n');
            showExitScreen();
            cin.get();
            return;
        }
    }
}

int main() {
    srand(time(0));

    Shop shop;
    shop.setup();
    
    showWelcomeScreen(shop);
    mainMenu(shop);
    return 0;
}