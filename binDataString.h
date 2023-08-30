#ifndef BIN
#define BIN

/*A function that converts a number to 10-bit encoding*/
void intToBinaryString10(int num, char *binaryStr);

/*A function that converts a register into 4-bit encoding*/
char *registerToBinaryString2(const char *reg);

/*A function that converts a register into 10-bit encoding*/
char *registerToBinaryString10(const char *reg);

/*A function that accepts a number and returns a 10-digit binary code*/
char *numberToBinaryString(const char *numberStr);

char *registerToBinaryString(const char *reg);

void convertToBinaryString(int num, char *binaryStr);

/*Binary coding of numbers*/
void intToBinaryString(int number, char *outputString);


/*String binary encoding function*/
void asciiToBinaryString(char inputChar, char *outputString);



#endif
