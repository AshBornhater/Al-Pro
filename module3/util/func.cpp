#include <iostream>
#include "../include/func.hpp"

using std::cout;
using std::cin;
using std::endl;

void inputStr(char text[], char instruction[]) {
     while(true) {
        cout << instruction;
        cin.getline(text, 1000);

        bool isEmpty = true;
        for(int i = 0; text[i] != '\0'; i++){
            if(text[i] != ' ') {
                isEmpty = false;
                break;
            }
        }

        if(isEmpty) {
            cout << "   [!] text must not be empty\n"; 
            continue;
        }      
        break;
    }
}

void inputColumn(int &column, int length) {
    while(true) {
        cout << "Input Column: ";
        cin >> column;
        if(cin.fail() || cin.peek() != '\n') {
            cout << "Input Must be Numeric!\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        if(column < 0 || column >= length) {
            cout << "Column must be > 0 and <= Text Length (?)\n";
            continue;
        }
        break;
    }
}

void inputNum(int &num, char instruction[]) {
    while(true) {
        cout << instruction;
        cin >> num;
        if(cin.fail() || cin.peek() != '\n') {
            cout << "Input Must be Numeric!\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        break;
    }
}

int strLength(char text[]) { 
    int length = 0;
    while (text[length] != '\0') {
        length++;
    }
    return length;
}

char encryptChar(int ch, int key) {
    return (char)((ch + key) % 128);
}

char decryptChar(int ch, int key) {
    return (char)((ch - (key % 128) + 128) % 128);
}

void insertionSort(char arr[], int length) {
    for (int i = 1; i < length; i++) {
        char key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) 
            return false;
    }
    return true;
}

bool isComposite(int num) {
    if (num <= 3) 
        return false;
    return !isPrime(num);
}

void matrixAddition(int result[5][5], int matrixA[5][5], int matrixB[5][5], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
}

void printFormatted(int num) {
    if(num < 10) {
        cout << "0" << "0" << num;
    } else if(num < 100) {
        cout << "0" << num;
    } else {
        cout << num;
    }
}

