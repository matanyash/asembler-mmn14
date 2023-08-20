#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "LabelTabel.c"
#include "binaryAction.c"

#define DATA ".data"
#define STRING ".string"
#define ENTRY ".entry"
#define EXTERNAL ".extern"
#define memoryData 1024
#define MAX_STRING_LENGTH 100
#define MAX_TABLE_SIZE 1024
#define REGISTER_SIZE 8

const char *regs[REGISTER_SIZE] = {"@r0", "@r1", "@r2", "@r3", "@r4", "@r5", "@r6" , "@r7"};
const char *wordArray[] = { "mov", "cmp", "add", "sub", "not" ,"clr", "lea", "inc", "dec", "jmp","bne" , "red","prn","jsr","rts", "stop" };
const int numWords = sizeof(wordArray) / sizeof(wordArray[0]);

//משתנים סטטים
static int flagEror;
static int flagSimble;
static int L = 0;
static int DC = 0;
static int IC = 100;

//////////////////טבלת קידוד
typedef struct {
    char strings[MAX_TABLE_SIZE][MAX_STRING_LENGTH];
    int nextIndex;
} StringTableBIN;


void initStringTable(StringTableBIN *table) {
    table->nextIndex = 0;
}

int addStringToStringTable(StringTableBIN *table, const char *str) {
    if (table->nextIndex >= MAX_TABLE_SIZE) {
        return -1; // Table is full
    }

    strncpy(table->strings[table->nextIndex], str, MAX_STRING_LENGTH - 1);
    table->strings[table->nextIndex][MAX_STRING_LENGTH - 1] = '\0'; // Ensure null-terminated

    table->nextIndex++;
    return table->nextIndex - 1; // Index of the added string
}

void updateStringInTable(StringTableBIN *table, int index, const char *newStr) {
    if (index >= 0 && index < table->nextIndex) {
        strncpy(table->strings[index], newStr, MAX_STRING_LENGTH - 1);
        table->strings[index][MAX_STRING_LENGTH - 1] = '\0'; // Ensure null-terminated
    }
}

void printStringTable(const StringTableBIN *table) {
    for (int i = 0; i < table->nextIndex; i++) {
        printf("\nString %d: %s\n", i, table->strings[i]);
    }
}

/////////////////
//בדיקה האם הפעולה קיימת
int isWordInArray(const char *line ){
    char lineCopy[100]; // Make a copy of the input line to avoid modifying the original
    strcpy(lineCopy, line);

    char *token = strtok(lineCopy, " ");
    while (token != NULL) {
        for (int i = 0; i < numWords; i++) {
            if (strcmp(token, wordArray[i]) == 0) {
                printf("\nFound word: %s\n", wordArray[i]);
                return 1;
            }
        }
        token = strtok(NULL, " ");
    }
    return 0;
}


//בדיקת סמל
int isSimbele(const char *word) {
    int length = strlen(word);

    if (length > 0 && word[length - 1] == ':') {
        return 1;
    } else {
        return 0;
    }
}

//פונקציות בדיקת מילים
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


// בודק אם המחרוזת מכילה את המילה ".string"
int containsStringKeyword(const char *line) {
    return strstr(line, ".string") != NULL;
}

// בודק אם המחרוזת מכילה את המילה ".data"
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

//פונקצית עדכון טבלת סמלים
void upTabelLabel(char * label, int counter, char * type){
    printf(" this up the table with labal = %s, DC/IC = %d, and - %s", label, counter, type);
    addParamToTable(counter, label, type);
}



void upDataTable(){
    printf("\nup data label in table");
}




//פונקציה קידוד בינארי סטרינג
void asciiToBinaryString(char inputChar, char *outputString) {
    int asciiValue = (int)inputChar;

    for (int i = 0; i < 12; i++) {
        outputString[i] = (asciiValue & (1 << (11 - i))) ? '1' : '0';
    }

    outputString[12] = '\0';
}

//קידוד בינארי סטרינג
void binaryString(const char *line,StringTableBIN *table){
    const char *startQuote = strchr(line, '"');
    char binaryString[13];
    char andString[13] = "000000000000";
    if (startQuote == NULL) {
        printf("No quoted word found.\n");
        return;
    }

    const char *endQuote = strchr(startQuote + 1, '"');
    if (endQuote == NULL) {
        printf("Invalid quoted word format.\n");
        return;
    }

    printf("Quoted word: ");
    for (const char *p = startQuote + 1; p < endQuote; p++) {
        printf("\n%c ", *p);
        asciiToBinaryString(*p, binaryString);
        printf(" binary is - %s", binaryString);
        addStringToStringTable(table,binaryString);
        DC = DC +1;
    }
    printf("\nand strtig - %s",andString);
    addStringToStringTable(table,andString);
    DC = DC +1;
    printf("\n");
}
//קידוד בינארי של מספרים
void intToBinaryString(int number, char *outputString) {
    for (int i = 0; i < 12; i++) {
        outputString[i] = (number & (1 << (11 - i))) ? '1' : '0';
    }

    outputString[12] = '\0';
}
//initStringTable(&table);
//פונקציה קידוד בינארי מספרים
void binaryData(const char *line ,StringTableBIN *table) {
    const char *delimiters = " ,";
    char *line_copy = strdup(line);
    char *token = strtok(line_copy, delimiters);
    char binaryString[13]; // 12 bits + '\0' terminator

    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            long int num = strtol(token, NULL, 10);
            printf("\nNumber: %ld", num);
            intToBinaryString(num,binaryString);
            printf(" binary is - %s", binaryString);
            addStringToStringTable(table, binaryString);
            DC = DC +1;
        }

        token = strtok(NULL, delimiters);
    }
    free(line_copy);
}


/////////////////////


