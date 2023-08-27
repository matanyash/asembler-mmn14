#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "LabelTabel.c"

#define memoryData 1024
#define MAX_STRING_LENGTH 100
#define MAX_TABLE_SIZE 1024
#define MAX_WORDS 100
#define MAX_WORD_LENGTH 50
#define A "00"
#define R "01"
#define E "10"


static int flagEror;
static int flagSimble;
static int L = 0;
static int DC = 0;
static int IC = 100;

const char *wordArray[16] = {"mov", "cmp", "add", "sub", "not", "clr", "lea", "inc", "dec", "jmp", "bne", "red", "prn",
                             "jsr", "rts", "stop"};
const int numWords = sizeof(wordArray) / sizeof(wordArray[0]);

void intToBinaryString10(int num, char *binaryStr);
int isWordInArray1(const char *word);


typedef struct {
    char strings[MAX_TABLE_SIZE][MAX_STRING_LENGTH];
    char ent[10][10];
    int nextIndex;
} StringTableBIN;


void initStringTable(StringTableBIN *table) {
    table->nextIndex = 0;
}

int addStringToStringTable(StringTableBIN *table, const char *str) {
    if (table->nextIndex >= MAX_TABLE_SIZE) {
        return -1;
    }

    strncpy(table->strings[table->nextIndex], str, MAX_STRING_LENGTH - 1);
    table->strings[table->nextIndex][MAX_STRING_LENGTH - 1] = '\0';

    table->nextIndex++;
    return table->nextIndex - 1;
}

void updateTables(StringTableBIN *table1) {
    int size1 = table1->nextIndex;
    int type;
    char newBin[13];
    int i, j;

    for (i = 0; i < size1; i++) {
        for (j = 0; j < 10; j++) {
            if (tableLabel[j].nextIndex == -1) continue;
            if (strcmp(table1->strings[i], tableLabel[j].Label) == 0)
            {
                if (strcmp(tableLabel[j].Type, "entry") == 0){
                    type = tableLabel[j].ID;
                    intToBinaryString10(type, newBin);
                    strcat(newBin,E);
                    printf(" \n   is entry \n");
                    strcpy( table1->strings[i], newBin);
                    continue;
            }
                else if (strcmp(tableLabel[j].Type, "extrnal") == 0) {
                    type = tableLabel[j].ID;
                    strcpy(newBin , "000000000001");
                    strcpy(table1->strings[i], newBin);
                    strcpy(table1->ent[i], tableLabel[j].Label);
                    continue;
                }
                type = tableLabel[j].ID;
                intToBinaryString10(type, newBin);
                strcat(newBin,E);
                printf(" \n   is entry \n");
                strcpy( table1->strings[i], newBin);
                continue;
            }
        }
    }
}
void printStringTable(const StringTableBIN *table) {
    for (int i = 0; i < table->nextIndex; i++) {
        printf("\nString %d: %s\n", i, table->strings[i]);
    }
}

/*A function to check if an action exists*/
int isWordInArray(const char *line) {
    int i;
    char lineCopy[1000];
    char *token;
    unsigned long long len = strlen(line);
    strcpy(lineCopy, line);
    if (len > 0 && lineCopy[len - 1] == '\n') {
        lineCopy[len - 1] = '\0';
    }

    if (lineCopy[len - 1] != ' ') {
        strcat(lineCopy, " ");
    }
    token = strtok(lineCopy, " ");
    while (token != NULL) {
        for (i = 0; i < numWords; i++) {
            if (strcmp(token, wordArray[i]) == 0) {
                return i;
            }
        }
        token = strtok(NULL, " ");
    }
    return -1;
}


int isSymbol(const char *word) {
    unsigned long long length = strlen(word);

    if (length > 0 && word[length - 1] == ':') {
        return 1;
    } else {
        return 0;
    }
}


int isStringKeyword(const char *word) {
    return strcmp(word, ".string") == 0;
}


int isDataKeyword(const char *word) {
    return strcmp(word, ".data") == 0;
}

int isExternKeyword(const char *word) {
    return strcmp(word, ".extern") == 0;
}

int isEntryKeyword(const char *word) {
    return strcmp(word, ".entry") == 0;
}


/*Checks if the string contains the word ".string"*/
int containsStringKeyword(const char *line) {
    return strstr(line, ".string") != NULL;
}

/*Checks if the string contains the word ".entry"*/
int containsDataKeyword(const char *line) {
    return strstr(line, ".data") != NULL;
}

// בודק אם המחרוזת מכילה את המילה "extern."
int containsExternKeyword(const char *line) {
    return strstr(line, ".extern") != NULL;
}

// בודק אם המחרוזת מכילה את המילה ".entry"
int containsEntryKeyword(const char *line) {
    return strstr(line, ".entry") != NULL;
}

/*Symbol table update function*/
void upTabelLabel(char *label, int counter, char *type) {
    addParamToTable(counter, label, type);
}

/*String binary encoding function*/
void asciiToBinaryString(char inputChar, char *outputString) {
    int asciiValue = (int) inputChar;
    int i;
    for (i = 0; i < 12; i++) {
        outputString[i] = (asciiValue & (1 << (11 - i))) ? '1' : '0';
    }

    outputString[12] = '\0';
}

/*String binary encoding*/
void binaryString(const char *line, StringTableBIN *table) {
    const char *startQuote = strchr(line, '"');
    char binaryString[13];
    char andString[13] = "000000000000";
    const char *p;
    const char *endQuote;
    if (startQuote == NULL) {
        printf("No quoted word found.\n");
        return;
    }

    endQuote = strchr(startQuote + 1, '"');
    if (endQuote == NULL) {
        printf("Invalid quoted word format.\n");
        return;
    }

    printf("Quoted word: ");
    for (p = startQuote + 1; p < endQuote; p++) {
        asciiToBinaryString(*p, binaryString);
        addStringToStringTable(table, binaryString);
        DC = DC + 1;
    }
    addStringToStringTable(table, andString);
    DC = DC + 1;

}

/*Binary coding of numbers*/
void intToBinaryString(int number, char *outputString) {
    int i;
    for (i = 0; i < 12; i++) {
        outputString[i] = (number & (1 << (11 - i))) ? '1' : '0';
    }

    outputString[12] = '\0';
}

/*Binary encoding function numbers*/
void binaryData(const char *line, StringTableBIN *table) {
    const char *delimiters = " ,";
    char *line_copy = strdup(line);
    char *token = strtok(line_copy, delimiters);
    char binaryString[13];
    long int num;

    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            num = strtol(token, NULL, 10);
            intToBinaryString(num, binaryString);
            addStringToStringTable(table, binaryString);
            DC = DC + 1;
        }

        token = strtok(NULL, delimiters);
    }
    free(line_copy);
}


int isNum(const char *str) {
    char firstChar = str[0];
    return ((firstChar >= '0' && firstChar <= '9') || firstChar == '-' || firstChar == '+');
}

int isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == ' ');
}


char *numberToBinaryString(const char *numberStr) {
    int num = atoi(numberStr);
    int i;
    char *binaryString = (char *) malloc(11 * sizeof(char));
    if (binaryString == NULL) {
        return NULL;
    }

    int index = 0;

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
    printf("\n binary is %s", binaryString);
    return binaryString;
}

char *registerToBinaryString(const char *reg) {
    char *binaryString = NULL;
    //printf("----------- reg is  %s-----",reg);
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
            // Handle invalid register
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


void concatenateWords(const char *word1, const char *word2, const char *word3, const char *word4, char *result) {
    strcpy(result, word1); 

    strcat(result, word2);

    strcat(result, word3); 

    strcat(result, word4); 
}


void binaryFirstLine(char *word1, char *word2, int act, StringTableBIN *table) {
    int action = act;
    char firstLine[13];
    char directive[5];
    char target[4];
    char source[4];
    if (isWordInArray1(word1) == 1) {
        strcpy(source, "101");
    } else if ((isNum(word1) == 1))strcpy(source, "001");
    else strcpy(source, "011");

    if ((isWordInArray1(word2) == 1)) {
        strcpy(target, "101");
    } else if ((isNum(word2) == 1))strcpy(target, "001");
    else strcpy(target, "011");

    if (strcmp(word1, "!") == 0)strcpy(source, "000");
    if (strcmp(word2, "!") == 0)strcpy(target, "000");

    convertToBinaryString(action, directive);
    concatenateWords(source, directive, target, A, firstLine);
    addStringToStringTable(table, firstLine);
    L++;
}

int isWordInArray1(const char *word) {
    if (word[0] == '@' && word[1] == 'r') {
        if (word[2] >= '0' && word[2] <= '7')return 1;
        else printf("\nthe reg not exits\n");
        flagEror = 1;
    }
    return 0;
}

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


void base64_encode(const char* input, char* output) {
    const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    unsigned long long input_length = strlen(input);
    unsigned int value;
    int i,j;
    int output_length = 0;

    for (i = 0; i < input_length; i += 6) {
        value = 0;
        for (j = 0; j < 6 && i + j < input_length; j++) {
            value = (value << 1) | (input[i + j] - '0');
        }
        output[output_length++] = base64_table[value];
    }

    output[output_length] = '\0';
}

void process_input_file(StringTableBIN *table, const char* output_filename) {
    char input_string[13];
    char output_string[9];
    int i=0;
    FILE* output_file = fopen(output_filename, "w");

    if (output_file == NULL) {
        printf("error not can open the file\n");
        return;
    }

    while (i < table->nextIndex) {
        strcpy(input_string,table->strings[i]);

        base64_encode(input_string, output_string);
        fprintf(output_file, "%s\n", output_string);
        i++;
    }

    fclose(output_file);
}

void process_input_file_ent(const char* output_filename) {
    int i = 0;
    FILE *output_file = fopen(output_filename, "w");

    if (output_file == NULL) {
        printf("eror not can open the file\n");
        return;
    }
    while (i < MAX_TABLE_SIZE) {
        if (strcmp(tableLabel[i].Type, "entry") == 0) {
            fprintf(output_file, "%s %d\n",tableLabel[i].Label, tableLabel[i].ID);
        }
        i++;
    }
    fclose(output_file);
}

void process_input_file_ext(const char* output_filename, StringTableBIN *table) {
    int i = 0;
    FILE *output_file = fopen(output_filename, "w");

    if (output_file == NULL) {
        printf("eror not can open the file\n");
        return;
    }
    while (i < table->nextIndex) {
        if (strcmp(table->strings[i], "000000000001") == 0) {
            fprintf(output_file, "%s %d\n",table->ent[i],i+100);
        }
        i++;
    }
    fclose(output_file);
}

void tokenizeString(const char *input, char tokens[][MAX_WORD_LENGTH], int *numTokens) {
    *numTokens = 0;
    int i;
    char inputCopy[MAX_WORD_LENGTH];
    char *wordStart = inputCopy;

    strcpy(inputCopy, input);
    for (i = 0; inputCopy[i] != '\0'; i++) {
        if (inputCopy[i] == ',' || isspace(inputCopy[i])) {
            inputCopy[i] = '\0';

            if (wordStart != &inputCopy[i]) {
                strncpy(tokens[*numTokens], wordStart, MAX_WORD_LENGTH);
                tokens[*numTokens][MAX_WORD_LENGTH - 1] = '\0';
                (*numTokens)++;
            }

            wordStart = &inputCopy[i + 1];
        }
    }

    if (wordStart != &inputCopy[strlen(inputCopy)]&&wordStart[0] != '\0') {
        strncpy(tokens[*numTokens], wordStart, MAX_WORD_LENGTH);
        tokens[*numTokens][MAX_WORD_LENGTH - 1] = '\0';
        (*numTokens)++;
    }
}

void binaryActioen(char *line , StringTableBIN *table) {
    char extractedWords[2][50];
    char lineCopy[100];
    int action = isWordInArray(line);
    char twoLine[13];
    char regBinString[13];
    char *numBinaryString;
    char tokens[MAX_WORDS][MAX_WORD_LENGTH];
    int numTokens;
    int count;
    int i;
    strcpy(lineCopy, line);
    tokenizeString(line, tokens, &numTokens);

    count = numTokens -1;
    if ((strcmp(tokens[numTokens-1], "rts") == 0)){
        addStringToStringTable(table,"000111000000");
        L++;
    }

    if(strcmp(tokens[numTokens-1], "stop") == 0){
        addStringToStringTable(table, "000111100000");
        L++;
        return;
    }
    if (isSymbol(tokens[0]) == 1) {
        count--;

    }
    if (count == 1) {
        strcpy(extractedWords[0], "!");
        strcpy(extractedWords[1], tokens[numTokens - 1]);
    }
    if (count == 2) {
        strcpy(extractedWords[0], tokens[numTokens - 2]);
        strcpy(extractedWords[1], tokens[numTokens - 1]);
    }

    if ((isWordInArray1(extractedWords[0]))==1)strcpy(regBinString, registerToBinaryString10(extractedWords[0]));
    if ((isWordInArray1(extractedWords[1]))==1)strcpy(regBinString, registerToBinaryString10(extractedWords[1]));

    binaryFirstLine(extractedWords[0], extractedWords[1], action, table);
    numBinaryString = numberToBinaryString(extractedWords[0]);

    switch (action) {
        case 0:
            if (isWordInArray1(extractedWords[0]) && isWordInArray1(extractedWords[1])){
                strcpy(twoLine, registerToBinaryString2(extractedWords[0]));
                strcat(twoLine, registerToBinaryString2(extractedWords[1]));
                strcat(twoLine, A);
                addStringToStringTable(table, twoLine);
                L++;
                break;
            }
            if(isWordInArray1(extractedWords[0])){
                strcpy(regBinString, registerToBinaryString2(extractedWords[0]));
                strcat(regBinString, "0000000");
                addStringToStringTable(table, regBinString);
                L++;
            }

            else if(isNum(extractedWords[0])){
                strcpy(twoLine, numberToBinaryString(extractedWords[0]));
                strcat(twoLine, A);
                addStringToStringTable(table, twoLine);
                L++;

            } else addStringToStringTable(table, extractedWords[0]);

            if (isWordInArray1(extractedWords[1])){
                addStringToStringTable(table, regBinString);
                L++;
                break;
            }
            else if(isNum(extractedWords[1])){
                strcpy(twoLine, numberToBinaryString(extractedWords[1]));
                strcat(twoLine, A);
                addStringToStringTable(table, twoLine);
                L++;
                break;
            } else
                addStringToStringTable(table, extractedWords[1]);
            L++;
            break;
        case 1:

            break;
        case 2:

            break;
        case 3:
            if (isWordInArray1(extractedWords[0]) && isWordInArray1(extractedWords[1])){
                strcpy(twoLine, registerToBinaryString2(extractedWords[0]));
                strcat(twoLine, registerToBinaryString2(extractedWords[1]));
                strcat(twoLine, A);
                addStringToStringTable(table, twoLine);
                L++;
                break;
            }
            break;
        case 4:
            if (isWordInArray1(extractedWords[1])) {
                strcpy(twoLine, regBinString);
                strcat(twoLine, A);
                addStringToStringTable(table, twoLine);
            } else
                addStringToStringTable(table, extractedWords[1]);
            L++;
            break;
        case 5:
            if (isWordInArray1(extractedWords[1])) {
                strcpy(twoLine, regBinString);
                strcat(twoLine, A);
                addStringToStringTable(table, twoLine);
            } else
                addStringToStringTable(table, extractedWords[1]);
            L++;
            break;
        case 6:
            if (isWordInArray1(extractedWords[1])) {
                addStringToStringTable(table, "000110001100");
            } else
                addStringToStringTable(table, "000110010100");
            L++;
            break;
        case 7:
            if (isWordInArray1(extractedWords[1])) {
                strcpy(twoLine, regBinString);
                strcat(twoLine, A);
                addStringToStringTable(table, twoLine);
            } else
                addStringToStringTable(table, extractedWords[1]);
            L++;
            break;
        case 8:
            if (isWordInArray1(extractedWords[1])) {
                strcpy(twoLine, regBinString);
                strcat(twoLine, A);
                addStringToStringTable(table, twoLine);
            } else
                addStringToStringTable(table, extractedWords[1]);
            L++;
            break;
        case 9:
            if (isWordInArray1(extractedWords[1])) {
                strcpy(twoLine, regBinString);
                strcat(twoLine, A);
                addStringToStringTable(table, twoLine);
            } else
                addStringToStringTable(table, extractedWords[1]);
            L++;
            break;
        case 10:
            if (isWordInArray1(extractedWords[1])) {
                strcpy(twoLine, regBinString);
                strcat(twoLine, A);
                addStringToStringTable(table, twoLine);
            } else
                addStringToStringTable(table, extractedWords[1]);
            L++;
            break;
        case 11:
            if (isWordInArray1(extractedWords[1])) {
                strcpy(twoLine, regBinString);
                strcat(twoLine, A);
                addStringToStringTable(table, twoLine);
            } else
                addStringToStringTable(table, extractedWords[1]);
            L++;
            break;
        case 12:
            if (isWordInArray1(extractedWords[1])) {
                strcpy(twoLine, regBinString);
                strcat(twoLine, A);
                addStringToStringTable(table, twoLine);
            } else if (isNum(extractedWords[1]) == 1) {
                strcpy(twoLine, numberToBinaryString(extractedWords[1]));
                strcat(twoLine, A);
                addStringToStringTable(table, twoLine);

            } else addStringToStringTable(table, extractedWords[1]);
            L++;
            break;
        case 13:
            if (isWordInArray1(extractedWords[1])) {
                strcpy(twoLine, regBinString);
                strcat(twoLine, A);
                addStringToStringTable(table, twoLine);
            } else
                addStringToStringTable(table, extractedWords[1]);
            L ++;
            break;
        default:
            break;
    }
}

int chekLineEror(char * line_copy){
    //printf("\nhere chek eror\n");
    //flagEror++;
    return 0;
}