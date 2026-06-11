#pragma once

void inputStr(char text[], char instruction[]);
void inputColumn(int &column, int length);
void inputNum(int &num, char instruction[]);
int strLength(char text[]);
char encryptChar(int ch, int key);
char decryptChar(int ch, int key);
void insertionSort(char arr[], int length);
bool isPrime(int num);
bool isComposite(int num);
void matrixAddition(int result[5][5], int matrixA[5][5], int matrixB[5][5], int size);
void printFormatted(int num);
