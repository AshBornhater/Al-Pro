#include <iostream>
#include "../include/func.hpp"

using std::cout;
using std::cin;
using std::endl;

int main(){

    // ==========================================
    // TASK 1: DECODE SIGNAL
    // ==========================================
    cout << "[TASK 1/3] DECODE SIGNAL - COMMUNICATION ROOM\n";
    cout << ">> Send Encrypt Signal and Decrypt Reply back to the Earth!.\n\n";
    cout << "[ ENCRYPT ]\n\n";

    char text[1000];
    char inputInstruct[] = "Input Text: ";
    inputStr(text, inputInstruct);
    
    int length = strLength(text);
    
    int column;
    inputColumn(column, length);
    
    int shift;
    char shiftInstruct[] = "Input Shift: ";
    inputNum(shift, shiftInstruct);

    int row = (length + column - 1) / column;
    char matrix[row][column];
    cout << "\nEncryption Matrix: \n\n";

    int textIndex = 0;
    for(int i = 0; i < row; i++) {
        cout << " ";
        for(int j = 0; j < column; j++) {  
            if(text[textIndex] != '\0') {  
                matrix[i][j] = text[textIndex];
                textIndex++;
                cout << " " << matrix[i][j];
            } else {
                matrix[i][j] = '_';
                cout << " " << matrix[i][j];
            }
        }
        cout << '\n';
    }

    cout << "\nText Length: " << length << endl;
    cout << "Matrix Row: " << row << "\tMatrix Column: " << column << endl << endl;

    char encryptNoKey[1000];
    char encryptPlusKey[1000];

    textIndex = 0;
    for(int i = 0; i < column; i++) {
        for(int j = 0; j < row; j++) {  
            encryptNoKey[textIndex] = matrix[j][i];
            encryptPlusKey[textIndex] = encryptChar((int)encryptNoKey[textIndex], shift);
            textIndex++;
        }
    }
    encryptNoKey[row * column] = '\0';
    encryptPlusKey[row * column] = '\0';

    cout << "\nEncryption Before Key is Added: " << encryptNoKey;
    cout << "\nEncryption After Key is Added: " << encryptPlusKey << endl;

    cin.ignore(1000, '\n');

    cout << "\n[ DECRYPT ]\n\n";
    char encryptedText[1000];
    char encryptedTextInstruct[] = "Input Encrypted Text: ";
    inputStr(encryptedText, encryptedTextInstruct);
    
    int encLen = strLength(encryptedText);

    char decryptedShift[1000];
    for(int i = 0; i < encLen; i++) {
        decryptedShift[i] = decryptChar((int)encryptedText[i], shift);
    }
    decryptedShift[encLen] = '\0';
 
    cout << "Decryption after shift key removed: " << decryptedShift << endl;

    int decRow = (encLen + column - 1) / column;
    char decMatrix[decRow][column];

    cout << "\nDecryption Matrix:\n\n";
    textIndex = 0;
    for(int i = 0; i < column; i++) {
        for(int j = 0; j < decRow; j++) {
            if(textIndex < encLen) {
                decMatrix[j][i] = decryptedShift[textIndex];
                textIndex++;
            } else {
                decMatrix[j][i] = '_';
            }
        }
    }

    for(int i = 0; i < decRow; i++) {
        cout << " ";
        for(int j = 0; j < column; j++) {
            cout << " " << decMatrix[i][j];
        }
        cout << '\n';
    }

    cout << endl;

    char decryptResult[1000];
    textIndex = 0;
    for(int i = 0; i < decRow; i++) {
        for(int j = 0; j < column; j++) {
            if(decMatrix[i][j] != '_') {
                decryptResult[textIndex++] = decMatrix[i][j];
            }
        }
    }
    decryptResult[textIndex] = '\0';
 
    cout << "\nDecryption Result : " << decryptResult << endl;
    cout << "\n>> [TASK 1/3] COMPLETE - Signal channel restored.\n";
    cout << ">> Press ENTER to continue to [ TASK 2 ]!.";
    cin.get();


    // ==========================================
    // TASK 2: REPAIR TEXT CONSOLE
    // ==========================================
    cout << "\n\n[TASK 2/3] REPAIR TEXT CONSOLE - CAPTAIN'S BRIDGE\n";
    cout << ">> Text console is malfunctioning again.\n";
    cout << ">> Rebuild deduplication and sorting features!\n\n";

    char continueTask2 = 'y';
    while (continueTask2 == 'y') {
        cout << "[ Text Verification ]\n";
        
        for (int sentence = 1; sentence <= 3; sentence++) {
            char textConsole[1000];
            
            char sentenceInstruct[] = "Input Sentence X           : ";
            sentenceInstruct[15] = '0' + sentence; 
            inputStr(textConsole, sentenceInstruct);

            cout << "--------------------------------------------------\n";

            char cleanText[1000];
            int cleanIndex = 0;
            for (int i = 0; textConsole[i] != '\0'; i++) {
                if (textConsole[i] != ' ') {
                    cleanText[cleanIndex] = textConsole[i];
                    cleanIndex++;
                }
            }
            cleanText[cleanIndex] = '\0';
            int lengthConsole = cleanIndex;

            cout << "Result for Sentence " << sentence << ":\n";
            cout << "Letter Count               : " << lengthConsole << "\n";
            
            cout << "1. Original                : ";
            for (int i = 0; i < lengthConsole; i++) {
                cout << cleanText[i];
                if (i < lengthConsole - 1) cout << ", ";
            }
            cout << "\n";

            cout << "2. Inverse                 : ";
            for (int i = lengthConsole - 1; i >= 0; i--) {
                cout << cleanText[i];
                if (i > 0) cout << ", ";
            }
            cout << "\n";

            cout << "3. Swap First-Last         : ";
            char swapText[1000];
            for(int i = 0; i <= lengthConsole; i++) swapText[i] = cleanText[i];
            
            if (lengthConsole > 1) {
                char tempFirst = swapText[0];
                swapText[0] = swapText[lengthConsole - 1];
                swapText[lengthConsole - 1] = tempFirst;
            }
            cout << swapText << "\n";

            cout << "4. Palindrome?             : ";
            bool isPalindrome = true;
            for (int i = 0; i < lengthConsole / 2; i++) {
                if (cleanText[i] != cleanText[lengthConsole - 1 - i]) {
                    isPalindrome = false;
                    break;
                }
            }
            if (isPalindrome) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }

            cout << "5. Sorted (Unique)         : ";
            char uniqueText[1000];
            int uniqueCount = 0;
            
            for (int i = 0; i < lengthConsole; i++) {
                bool isFound = false;
                for (int j = 0; j < uniqueCount; j++) {
                    if (cleanText[i] == uniqueText[j]) {
                        isFound = true;
                        break;
                    }
                }
                if (!isFound) {
                    uniqueText[uniqueCount] = cleanText[i];
                    uniqueCount++;
                }
            }
            uniqueText[uniqueCount] = '\0';
            
            insertionSort(uniqueText, uniqueCount);
            
            for (int i = 0; i < uniqueCount; i++) {
                cout << uniqueText[i];
                if (i < uniqueCount - 1) cout << ", ";
            }
            cout << "\n\n";
        }

        cout << "==================================================\n";
        
        char ynInput[1000];
        char ynInstruct[] = "Verify Other Text? (y/n): ";
        
        while(true) {
            inputStr(ynInput, ynInstruct);
            
            int charCount = 0;
            char firstChar = '\0';
            for (int i = 0; ynInput[i] != '\0'; i++) {
                if (ynInput[i] != ' ') {
                    if (charCount == 0) firstChar = ynInput[i];
                    charCount++;
                }
            }
            
            if (charCount == 1 && (firstChar == 'y' || firstChar == 'n')) {
                continueTask2 = firstChar;
                break;
            }
            cout << "   [!] Invalid input. Input y or n.\n";
        }
        cout << "\n";
    }

    cout << ">> [TASK 2/3] COMPLETE - Text console back online.\n";
    cout << ">> Press ENTER to continue to [ TASK 3 ]!.";
    cin.get();


    // ==========================================
    // TASK 3: ALIGN NAVIGATION MATRIX
    // ==========================================
    cout << "\n\n[TASK 3/3] ALIGN NAVIGATION MATRIX - ENGINE CORE\n";
    cout << ">> Navigation system total failure due to sabotage.\n";
    cout << ">> Reconstruct the coordinate matrix now!\n\n";
    cout << "[ MATRIX NAVIGATION ]\n\n";

    int matrixSize;
    char matrixInstruct[] = "Input Navigation Matrix size (min 3, max 5): ";
    
    while (true) {
        inputNum(matrixSize, matrixInstruct);
        if (matrixSize < 3 || matrixSize > 5) {
            cout << "   [!] Invalid input. Input size between 3 and 5.\n";
            continue;
        }
        break;
    }

    int primeMatrix[5][5];
    int compositeMatrix[5][5];
    
    int currentNumber = 2;
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            while (!isPrime(currentNumber)) {
                currentNumber++;
            }
            primeMatrix[i][j] = currentNumber;
            currentNumber++;
        }
    }

    currentNumber = 4;
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            while (!isComposite(currentNumber)) {
                currentNumber++;
            }
            compositeMatrix[i][j] = currentNumber;
            currentNumber++;
        }
    }

    cout << "\nPrime Coordinate Matrix:\n";
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            printFormatted(primeMatrix[i][j]);
            if (j < matrixSize - 1) cout << " ";
        }
        cout << '\n';
    }

    cout << "\nComposite Coordinate Matrix:\n";
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            printFormatted(compositeMatrix[i][j]);
            if (j < matrixSize - 1) cout << " ";
        }
        cout << '\n';
    }

    cout << "\nCoordinate Matrix has been restored.\n";
    cout << "Perform these processes to build a more accurate coordinate matrix:\n";
    cout << "1. Coordinate Matrix Integration\n";
    cout << "2. Matrix Transpose\n";
    cout << "3. Snake Traverse\n";
    cout << "4. C-Wise Traverse\n\n";
    
    cin.ignore(1000, '\n');
    cout << "Press ENTER to continue...\n";
    cin.get();

    cout << "COORDINATE MATRIX INTEGRATION:\n";
    cout << "--------------------------------------------------\n";
    int fusionMatrix[5][5];
    matrixAddition(fusionMatrix, primeMatrix, compositeMatrix, matrixSize);
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            printFormatted(fusionMatrix[i][j]);
            if (j < matrixSize - 1) cout << " ";
        }
        cout << '\n';
    }
    cout << '\n';

    cout << "MATRIX TRANSPOSE:\n";
    cout << "--------------------------------------------------\n";
    int transposeMatrix[5][5];
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            transposeMatrix[i][j] = fusionMatrix[j][i];
            printFormatted(transposeMatrix[i][j]);
            if (j < matrixSize - 1) cout << " ";
        }
        cout << '\n';
    }
    cout << '\n';

    cout << "SNAKE TRAVERSE:\n";
    cout << "--------------------------------------------------\n";
    int snakeMatrix[5][5];
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            if (i % 2 == 0) {
                snakeMatrix[i][j] = transposeMatrix[i][j];
            } else {
                snakeMatrix[i][j] = transposeMatrix[i][matrixSize - 1 - j];
            }
            printFormatted(snakeMatrix[i][j]);
            if (j < matrixSize - 1) cout << " ";
        }
        cout << '\n';
    }
    cout << '\n';

    cout << "C-WISE TRAVERSE:\n";
    cout << "--------------------------------------------------\n";
    int cwiseMatrix[5][5];
    for (int j = 0; j < matrixSize; j++) {
        for (int i = 0; i < matrixSize; i++) {
            if (j % 2 == 0) {
                cwiseMatrix[i][j] = snakeMatrix[i][j];
            } else {
                cwiseMatrix[i][j] = snakeMatrix[matrixSize - 1 - i][j];
            }
        }
    }

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            printFormatted(cwiseMatrix[i][j]);
            if (j < matrixSize - 1) cout << " ";
        }
        cout << '\n';
    }
    cout << '\n';

    cout << ">> [TASK 3/3] COMPLETE - Navigation matrix aligned.\n";
    cout << "======================================================\n";
    cout << "   ALL TASKS COMPLETE - SHIP SYSTEMS RESTORED\n";
    cout << "======================================================\n";

    return 0;
}