#include <iostream>
#include <thread>
#include <chrono>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main() {
    int length;

    cout << "=======================================================================\n";
    cout << "|                             Heil Hitler                             |\n";
    cout << "=======================================================================\n";

    while (true) {
        cout << "Enter length (odd number): ";
        cin >> length;
        if (cin.fail() || length % 2 == 0 || length < 3) {
            cout << "Invalid input! Please enter an odd number >= 3." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        break;
    }

    int mid = length / 2;

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            if (i == mid || j == mid ||
                (j == 0 && i < mid) || (i == 0 && j > mid) ||
                (j == length - 1 && i > mid) || (i == length - 1 && j < mid))
                cout << "* ";
            else
                cout << "  ";
        }
        cout << "\n";
    }

    string command;
    while (true) {
        cout << "\nType 'HeilHitler' for better experience: ";
        cin >> command;
        if (command != "HeilHitler") {
            cin.ignore(1000, '\n');
            continue;
        } else
            break;
    }

    int step = 0;
    while (true) {
        cout << "\033[2J\033[1;1H";
        cout << "=======================================================================\n";
        cout << "|                             Heil Hitler                             |\n";
        cout << "=======================================================================\n\n";

        for (int i = 0; i < length; i++) {
            for (int j = 0; j < length; j++) {
                bool draw = false;

                if (step == 0) {
                    if (i == mid || j == mid ||
                        (j == 0 && i < mid) || (i == 0 && j > mid) ||
                        (j == length - 1 && i > mid) || (i == length - 1 && j < mid))
                        draw = true;
                }
                else if (step == 1 || step == 3) {
                    if (i == j || i + j == length - 1)
                        draw = true;
                }
                else if (step == 2) {
                    if (i == mid || j == mid ||
                        (i == 0 && j < mid) || (j == length - 1 && i < mid) ||
                        (i == length - 1 && j > mid) || (j == 0 && i > mid))
                        draw = true;
                }

                if (draw) 
                    cout << "* ";
                else 
                    cout << "  ";
            }
            cout << "\n";
        }

        cout << "\nCongratulations, you are part of the Nazi now.\n";
        step = (step + 1) % 4;

        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }

    return 0;
}