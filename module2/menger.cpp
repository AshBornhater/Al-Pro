#include <iostream>
using namespace std;

bool isMenger(int x, int y, int level) {
    if (level == 0) return true;
    if ((x % 3 == 1) && (y % 3 == 1)) return false;
    return isMenger(x / 3, y / 3, level - 1);
}

int main() {
    int size = 27; // 3^3
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            cout << (isMenger(x, y, 3) ? "█" : " ");
        }
        cout << "\n";
    }
}