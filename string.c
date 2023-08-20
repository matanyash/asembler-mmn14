#include <stdio.h>
#include <string.h>

void asciiToBinaryString(char inputChar, char *outputString) {
    int asciiValue = (int)inputChar;

    for (int i = 0; i < 12; i++) {
        outputString[i] = (asciiValue & (1 << (11 - i))) ? '1' : '0';
    }

    outputString[12] = '\0';
}
int isString(const char *str1) {
    char inputString[100];
    char str2[] = ".string";
    int length1 = strlen(str1);
    int length2 = strlen(str2);

    if (length1 != length2) {
        return 0; // Return false if lengths are different
    }

    for (int i = 0; i < length1; i++) {
        if (str1[i] != str2[i]) {
            return 0; // Return false if characters are different
        }
    }

    return 1; // Return true if both strings are equal
}

int main() {
    char inputChar;
    char binaryString[13]; // 12 bits + '\0' terminator

    printf("Enter a character: ");
    scanf("%c", &inputChar);

    asciiToBinaryString(inputChar, binaryString);

    printf("Binary representation of '%c' is: %s\n", inputChar, binaryString);

    return 0;
}
