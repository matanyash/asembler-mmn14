#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "LabelTabel.c"

#define memoryData 1024
#define MAX_STRING_LENGTH 100
#define MAX_TABLE_SIZE 1024
#define REGISTER_SIZE 8

//משתנים סטטים
static int flagEror;
static int flagSimble;
static int L = 0;
static int DC = 0;
static int IC = 100;

const char *regs[REGISTER_SIZE] = {"@r0", "@r1", "@r2", "@r3", "@r4", "@r5", "@r6", "@r7"};
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
        return -1; // Table is full
    }

    strncpy(table->strings[table->nextIndex], str, MAX_STRING_LENGTH - 1);
    table->strings[table->nextIndex][MAX_STRING_LENGTH - 1] = '\0'; // Ensure null-terminated

    table->nextIndex++;
    return table->nextIndex - 1; // Index of the added string
}
int addEntToStringTable(StringTableBIN *table, const char *str) {
    if (table->nextIndex >= MAX_TABLE_SIZE) {
        return -1; // Table is full
    }

    strncpy(table->ent[table->nextIndex], str, MAX_STRING_LENGTH - 1);
    table->ent[table->nextIndex][MAX_STRING_LENGTH - 1] = '\0'; // Ensure null-terminated

    table->nextIndex++;
    return table->nextIndex - 1; // Index of the added string
}


void updateTables(StringTableBIN *table1) {
    int size1 = table1->nextIndex;
    printf("\nsize1 =  %d \n",size1);
    int type;
    char newBin[13];
    char R[3] = "01";
    char E[3] = "10";
    int i, j;

    for (i = 0; i < size1; i++) {
        for (j = 0; j < 10; j++) {
            //printf("\n i is = %d , j is %d \n",i,j);
            //printf("\n table1 is %s \n",table1->strings[i]);
            if (tableLabel[j].nextIndex == -1) continue;
            //printf("\nlabal = %s    \n", (tableLabel[j].Type));
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
                //Update string value with the ID from table2
                    type = tableLabel[j].ID;
                    strcpy(newBin , "000000000001");
                    strcpy(table1->strings[i], newBin);
                    strcpy(table1->ent[i], tableLabel[j].Label);
                    //printf("\na   %s    \n",table1->strings[i]);
                    continue;
                }
                type = tableLabel[j].ID;
                intToBinaryString10(type, newBin);
                strcat(newBin,E);
                printf(" \n   is entry \n");
                strcpy( table1->strings[i], newBin);
                continue;
            //else strcpy((char *) table1[i].strings, "2222222222");
            }
            //if (tableLabel[j].nextIndex == -1) break;
        }
        //printf("\n --  i is %d ----\n",i);
    }
    printf("\n --   good ----\n");
}
void printStringTable(const StringTableBIN *table) {
    for (int i = 0; i < table->nextIndex; i++) {
        printf("\nString %d: %s\n", i, table->strings[i]);
    }
}

/////////////////
//בדיקה האם הפעולה קיימת
int isWordInArray(const char *line) {
    int i;
    char lineCopy[1000];
    char *token;
    strcpy(lineCopy, line);
    int len = strlen(lineCopy);
    if (len > 0 && lineCopy[len - 1] == '\n') {
        lineCopy[len - 1] = '\0';
    }

    if (lineCopy[len - 1] != ' ') {
        strcat(lineCopy, " ");
    }
    //printf("--------------%s-----", lineCopy);
    token = strtok(lineCopy, " ");
    //printf("\n-------------%s-----------",token);
    while (token != NULL) {
        for (i = 0; i < numWords; i++) {
            if (strcmp(token, wordArray[i]) == 0) {
                printf("\nFound word: %s\n", wordArray[i]);
                return i;
            }
        }
        token = strtok(NULL, " ");
        //printf("\n-------------%s-----------",token);
    }
    return -1;
}

/*
//////////////בדיקה חדשה
int isWordInArray(const char *line) {
        int i;
        char currentWord[100];  // Assuming max word length is 100 characters

        for (i = 0; line[i] != '\0'; i++) {
            if (line[i] != ' ') {
                currentWord[i] = line[i];
            } else {
                currentWord[i] = '\0';  // Add a null-terminator to complete the current word

                for (int k = 0; k < numWords; k++) {
                    if (strcmp(currentWord, wordArray[k]) == 0) {
                        printf("\nFound word: %s\n", wordArray[k]);
                        return 1;
                    }
                }
                i = -1;  // Reset the index for the next word
            }
        }

        // Check the last word (no trailing space)
        currentWord[i] = '\0';
        for (int k = 0; k < numWords; k++) {
            if (strcmp(currentWord, wordArray[k]) == 0) {
                printf("\nFound word: %s\n", wordArray[k]);
                return 1;
            }
        }

        if (i > 0) {  // Check if there's a non-empty last word
            for (int k = 0; k < numWords; k++) {
                if (strcmp(currentWord, wordArray[k]) == 0) {
                    printf("\nFound word: %s\n", wordArray[k]);
                    return 1;
                }
            }

        }
    return -1;
    }
    */
///////////////////////
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
void upTabelLabel(char *label, int counter, char *type) {
//    printf(" this up the table with labal = %s, DC/IC = %d, and - %s", label, counter, type);
    addParamToTable(counter, label, type);
}


void upDataTable() {
    printf("\nup data label in table");
}


//פונקציה קידוד בינארי סטרינג
void asciiToBinaryString(char inputChar, char *outputString) {
    int asciiValue = (int) inputChar;

    for (int i = 0; i < 12; i++) {
        outputString[i] = (asciiValue & (1 << (11 - i))) ? '1' : '0';
    }

    outputString[12] = '\0';
}

//קידוד בינארי סטרינג
void binaryString(const char *line, StringTableBIN *table) {
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
        addStringToStringTable(table, binaryString);
        DC = DC + 1;
    }
    printf("\nand strtig - %s", andString);
    addStringToStringTable(table, andString);
    DC = DC + 1;
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
void binaryData(const char *line, StringTableBIN *table) {
    const char *delimiters = " ,";
    char *line_copy = strdup(line);
    char *token = strtok(line_copy, delimiters);
    char binaryString[13]; // 12 bits + '\0' terminator

    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            long int num = strtol(token, NULL, 10);
            printf("\nNumber: %ld", num);
            intToBinaryString(num, binaryString);
            printf(" binary is - %s", binaryString);
            addStringToStringTable(table, binaryString);
            DC = DC + 1;
        }

        token = strtok(NULL, delimiters);
    }
    free(line_copy);
}


/////////////////////

/*
int isRegister(char *word) {
    printf("\n+++++  %c +++++\n", word[1]);
    return (word[1] == '@');
}
*/
/*
     int i;
    for (i = 0; i < REGISTER_SIZE; i++) {
        if (strcmp(word, regs[i]) == 0) {
            printf("\nis reg");
            return 0;
        }
    }
    return 1;
     */

int isNum(char *str) {
    char firstChar = str[0];
    return ((firstChar >= '0' && firstChar <= '9') || firstChar == '-' || firstChar == '+');
}

int isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == ' ');
}

//////

char *numberToBinaryString(const char *numberStr) {
    int num = atoi(numberStr);
    char *binaryString = (char *) malloc(11 * sizeof(char)); // 10 bits + null terminator
    if (binaryString == NULL) {
        // Handle memory allocation error
        return NULL;
    }

    int index = 0;

    if (num < 0) {
        binaryString[index++] = '1'; // Set the sign bit to 1 for negative numbers
        num = -num; // Convert negative number to positive

        // Calculate the two's complement of the positive value
        num = 1024 - num;
    } else {
        binaryString[index++] = '0'; // Set the sign bit to 0 for positive numbers
    }

    // Convert the number to binary representation
    for (int i = 8; i >= 0; i--) {
        binaryString[index++] = ((num >> i) & 1) + '0';
    }

    binaryString[10] = '\0'; // Null-terminate the string
    printf("\n binary is %s", binaryString);
    return binaryString;
}

//////

/////

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

/////

void convertToBinaryString(int num, char *binaryStr) {
    if (num < 0 || num > 15) {
        binaryStr[0] = '\0';  // אם המספר לא בטווח התקין, מחזירים מחרוזת ריקה
        return;
    }

    for (int i = 3; i >= 0; i--) {
        binaryStr[3 - i] = ((num >> i) & 1) + '0';
    }
    binaryStr[4] = '\0';  // מוסיף את התו הסיום למחרוזת
}


void concatenateWords(const char *word1, const char *word2, const char *word3, const char *word4, char *result) {
    strcpy(result, word1); // Copy the first word to the result string

    strcat(result, word2); // Add the second word

    strcat(result, word3); // Add the third word

    strcat(result, word4); // Add the third word
}


void binaryFirstLine(char *word1, char *word2, int act, StringTableBIN *table) {
    int actiun = act;
    char firstLine[13];
    char A[3] = "00";
    char B[3] = "01";
    char C[3] = "10";
    char ooraa[5];
    char yaad[4];
    char makor[4];
    printf("\n!!!!! word 1 is %s ", word1);
    printf("\n!!!!! word 2 is %s ", word2);
    if (isWordInArray1(word1) == 1) {
        strcpy(makor, "101");
        printf("\n is reg!!!");
    } else if ((isNum(word1) == 1))strcpy(makor, "001");
    else strcpy(makor, "011");
    if ((isWordInArray1(word2) == 1)) {
        printf("\n is reg too!!!");
        strcpy(yaad, "101");
    } else if ((isNum(word2) == 1))strcpy(yaad, "001");
    else strcpy(yaad, "011");
    if (strcmp(word1, "!") == 0)strcpy(makor, "000");
    if (strcmp(word2, "!") == 0)strcpy(yaad, "000");
    convertToBinaryString(actiun, ooraa);
    concatenateWords(makor, ooraa, yaad, A, firstLine);
    addStringToStringTable(table, firstLine);
    printf("first liine --- %s\n", firstLine);
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

char *registerToBinaryString2(char *reg) {
    char *binaryString;
    printf("----------- reg is  %s-----", reg);
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
        default:
            // Handle invalid register
            break;

    }
    return binaryString;
}

char *registerToBinaryString10(char *reg) {
    char *binaryString;
    printf("----------- reg is  %s-----", reg);
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
        default:
            // Handle invalid register
            break;

    }
    printf("\n ****** $s \n" , binaryString);
    return binaryString;
}

void intToBinaryString10(int num, char *binaryStr) {
    if (num < 0) {
        sprintf(binaryStr, "Negative numbers are not supported.");
        return;
    }

    if (num == 0) {
        sprintf(binaryStr, "0000000000");
        return;
    }

    int i = 9; // We start from the last character and move to the first
    while (num > 0 && i >= 0) {
        binaryStr[i] = (num % 2) + '0'; // Get the least significant bit
        num /= 2;
        i--;
    }

    // Fill the remaining characters with leading zeros
    while (i >= 0) {
        binaryStr[i] = '0';
        i--;
    }

    binaryStr[10] = '\0'; // Null-terminate the string
}


void base64_encode(const char* input, char* output) {
    const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    const int input_length = strlen(input);
    int output_length = 0;

    for (int i = 0; i < input_length; i += 6) {
        unsigned int value = 0;
        for (int j = 0; j < 6 && i + j < input_length; j++) {
            value = (value << 1) | (input[i + j] - '0');
        }
        output[output_length++] = base64_table[value];
    }

    output[output_length] = '\0';
}

// הפונקציה process_input_file מקבלת שני שמות של קבצים - קובץ קלט וקובץ פלט.
// הפונקציה פותחת את שני הקבצים, ולאחר מכן עוברת על התוכן של קובץ הקלט שבו כל שורה היא מחרוזת בינארית באורך 12 תווים.
// לכל מחרוזת בקובץ הקלט מתבצעת המרה לקוד base64 באמצעות הפונקציה base64_encode והתוצאה מודפסת לקובץ הפלט, עם תו נפרד '\n' בין שורות.
// כאשר כל הקובץ הקלט נסרק, הפונקציה סוגרת את שני קבצי הקלט והפלט ומדפיסה הודעת הצלחה.
void process_input_file(StringTableBIN *table, const char* output_filename) {
    char input_string[13];
    char output_string[9];
    int i=0;
    FILE* output_file = fopen(output_filename, "w");

    if (output_file == NULL) {
        printf("eror not can open the file\n");
        return;
    }
;

    // קריאה שורה אחת לכל פעם מהקובץ הקלט כל עוד יש מחרוזת לקרוא.
    while (i < table->nextIndex) {
        strcpy(input_string,table->strings[i]);
        // מחיקת התו '\n' שמיותר בסוף המחרוזת (הכריתה של התו האחרון).
        //[strcspn(input_string, "\n")] = '\0';
        // המרת המחרוזת בינארית לקוד base64 והדפסתה לקובץ הפלט עם תו נפרד '\n' בסוף כל שורה.
        base64_encode(input_string, output_string);
        fprintf(output_file, "%s\n", output_string);
        i++;
    }

    // סגירת קבצי הקלט והפלט.
    fclose(output_file);

    printf("all good\n");
}

void process_input_file_ent(const char* output_filename) {
    int i = 0;
    FILE *output_file = fopen(output_filename, "w");

    if (output_file == NULL) {
        printf("eror not can open the file\n");
        return;
    }
    while (i < MAX_TABLE_SIZE) {
        //printf("\n i is - %d\n",i);
        if (strcmp(tableLabel[i].Type, "entry") == 0) {
            //printf(" \n^&^& %d  ",tableLabel[i].ID);
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
        //printf("\n i is - %d\n",i);
        if (strcmp(table->strings[i], "000000000001") == 0) {
            //printf(" \n^&^& %d  ",tableLabel[i].ID);
            fprintf(output_file, "%s %d\n",table->ent[i],i+100);
        }
        i++;
    }
    fclose(output_file);
}