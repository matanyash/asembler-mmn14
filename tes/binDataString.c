#include "lib.h"
#include "binDataString.h"


char *registerToBinaryString2(const char *reg) {
    char *binaryString;
    switch (reg[2]) {
        case '0':
            binaryString = "00000";
            break;
        case '1':
            binaryString = "00001";
            break;
        case '2':
            binaryString = "00010";
            break;
        case '3':
            binaryString = "00011";
            break;
        case '4':
            binaryString = "00100";
            break;
        case '5':
            binaryString = "00101";
            break;
        case '6':
            binaryString = "00110";
            break;
        case '7':
            binaryString = "00111";
            break;

    }
    return binaryString;
}


char *registerToBinaryString10(const char *reg) {
    char *binaryString;
    switch (reg[2]) {
        case '0':
            binaryString = "000000000000";
            break;
        case '1':
            binaryString = "000000000100";
            break;
        case '2':
            binaryString = "000000001000";
            break;
        case '3':
            binaryString = "000000001100";
            break;
        case '4':
            binaryString = "000000010000";
            break;
        case '5':
            binaryString = "000000010100";
            break;
        case '6':
            binaryString = "000000011000";
            break;
        case '7':
            binaryString = "000000011100";
            break;
    }
    return binaryString;
}


void intToBinaryString10(int num, char *binaryStr) {
    int i;
    if (num < 0) {
        sprintf(binaryStr, "Negative numbers are not supported.");
        return;
    }

    if (num == 0) {
        sprintf(binaryStr, "0000000000");
        return;
    }
    i = 9;
    while (num > 0 && i >= 0) {
        binaryStr[i] = (num % 2) + '0';
        num /= 2;
        i--;
    }

    while (i >= 0) {
        binaryStr[i] = '0';
        i--;
    }

    binaryStr[10] = '\0';
}


char *numberToBinaryString(const char *numberStr) {
    int num = atoi(numberStr);
    int i;
    int index;
    char *binaryString = (char *) malloc(11 * sizeof(char));
    if (binaryString == NULL) {
        return NULL;
    }

    index = 0;

    if (num < 0) {
        binaryString[index++] = '1';
        num = -num;
        num = 1024 - num;
    } else {
        binaryString[index++] = '0';
    }


    for (i = 8; i >= 0; i--) {
        binaryString[index++] = ((num >> i) & 1) + '0';
    }

    binaryString[10] = '\0';
    return binaryString;
}


char *registerToBinaryString(const char *reg) {
    char *binaryString = NULL;
    switch (reg[2]) {
        case '0':
            binaryString = "000";
            break;
        case '1':
            binaryString = "001";
            break;
        case '2':
            binaryString = "010";
            break;
        case '3':
            binaryString = "011";
            break;
        case '4':
            binaryString = "100";
            break;
        case '5':
            binaryString = "101";
            break;
        case '6':
            binaryString = "110";
            break;
        case '7':
            binaryString = "111";
            break;
        default:

            break;
    }

    return binaryString;
}


void convertToBinaryString(int num, char *binaryStr) {
    int i;
    if (num < 0 || num > 15) {
        binaryStr[0] = '\0';
        return;
    }

    for (i = 3; i >= 0; i--) {
        binaryStr[3 - i] = ((num >> i) & 1) + '0';
    }
    binaryStr[4] = '\0';
}


void intToBinaryString(int number, char *outputString) {
    int i;
    for (i = 0; i < 12; i++) {
        outputString[i] = (number & (1 << (11 - i))) ? '1' : '0';
    }

    outputString[12] = '\0';
}


void asciiToBinaryString(char inputChar, char *outputString) {
    int asciiValue = (int) inputChar;
    int i;
    for (i = 0; i < 12; i++) {
        outputString[i] = (asciiValue & (1 << (11 - i))) ? '1' : '0';
    }

    outputString[12] = '\0';
}



