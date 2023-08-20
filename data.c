#include <stdio.h>

void intToBinaryString(int number, char *outputString) {
    for (int i = 0; i < 12; i++) {
        outputString[i] = (number & (1 << (11 - i))) ? '1' : '0';
    }

    outputString[12] = '\0';
}

int main() {
    int inputNumber;
    char binaryString[13]; // 12 bits + '\0' terminator

    printf("Enter an integer: ");
    scanf("%d", &inputNumber);

    intToBinaryString(inputNumber, binaryString);

    printf("Binary representation of %d is: %s\n", inputNumber, binaryString);

    return 0;
}
