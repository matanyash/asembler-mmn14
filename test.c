#include "typedef.h"
#include "function.h"
#include "binDataString.h"
#include "global.h"
#include "test.h"

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
                strcpy( table1->strings[i], newBin);
                continue;
            }
        }
    }
}

void printStringTable(const StringTableBIN *table) {
    int i;
    for (i = 0; i < table->nextIndex; i++) {
        printf("\nString %d: %s\n", i, table->strings[i]);
    }
}

void upTabelLabel(char *label, int counter, char *type) {
    addParamToTable(counter, label, type);
}

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
    for (p = startQuote + 1; p < endQuote; p++) {
        asciiToBinaryString(*p, binaryString);
        addStringToStringTable(table, binaryString);
        DC = DC + 1;
    }
    addStringToStringTable(table, andString);
    DC = DC + 1;
}

void binaryData(char *line, StringTableBIN *table) {
    const char *delimiters = " ,";
    char *line_copy = strcpy(malloc(strlen(line) + 1), line);
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

void binaryFirstLine(char *word1, char *word2, int act, StringTableBIN *table) {
    int action = act;
    char firstLine[13];
    char directive[5];
    char target[4];
    char source[4];

    if (isRegister(word1) == 1) {
        strcpy(source, "101");
    } else if ((isNum(word1) == 1))strcpy(source, "001");
    else strcpy(source, "011");

    if ((isRegister(word2) == 1)) {
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

void binaryActioen(char *line , StringTableBIN *table) {
    char extractedWords[2][50];
    char lineCopy[100];
    int action = isWordInArray(line);
    char twoLine[13];
    char regBinString[13];
    /*char *numBinaryString;*/
    char tokens[MAX_WORDS][MAX_WORD_LENGTH];
    int numTokens;
    int count;
    int i;

    strcpy(lineCopy, line);
    tokenizeString(line, tokens, &numTokens);
    count = numTokens -1;

    for (i = 0; i < numTokens; i++){
        if(strcmp(tokens[i], "rts")==0){
            if(numTokens > i + 1){
                printf("Error! after rts can't be any word");
                flagError = 1;
            }
        }
        if(strcmp(tokens[i], "stop")==0){
            if(numTokens > i + 1){
                printf("Error! after stop can't be any word");
                flagError = 1;
            }
        }
    }

    if ((strcmp(tokens[numTokens-1], "rts") == 0)){
        addStringToStringTable(table,"000111000000");
        L++;
        return;
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

    if ((isRegister(extractedWords[0])) == 1)strcpy(regBinString, registerToBinaryString10(extractedWords[0]));
    if ((isRegister(extractedWords[1])) == 1)strcpy(regBinString, registerToBinaryString10(extractedWords[1]));

    binaryFirstLine(extractedWords[0], extractedWords[1], action, table);
    /*numBinaryString = numberToBinaryString(extractedWords[0]);*/

    switch (action) {
        case 0:
            if (isRegister(extractedWords[0]) && isRegister(extractedWords[1])){
                strcpy(twoLine, registerToBinaryString2(extractedWords[0]));
                strcat(twoLine, registerToBinaryString2(extractedWords[1]));
                strcat(twoLine, A);
                addStringToStringTable(table, twoLine);
                L++;
                break;
            }
            if(isRegister(extractedWords[0])){
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

            if (isRegister(extractedWords[1])){
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
            if (isRegister(extractedWords[0]) && isRegister(extractedWords[1])){
                strcpy(twoLine, registerToBinaryString2(extractedWords[0]));
                strcat(twoLine, registerToBinaryString2(extractedWords[1]));
                strcat(twoLine, A);
                addStringToStringTable(table, twoLine);
                L++;
                break;
            }
            break;
        case 4:
            if (isRegister(extractedWords[1])) {
                strcpy(twoLine, regBinString);
                strcat(twoLine, A);
                addStringToStringTable(table, twoLine);
            } else
                addStringToStringTable(table, extractedWords[1]);
            L++;
            break;
        case 5:
            if (isRegister(extractedWords[1])) {
                strcpy(twoLine, regBinString);
                strcat(twoLine, A);
                addStringToStringTable(table, twoLine);
            } else
                addStringToStringTable(table, extractedWords[1]);
            L++;
            break;
        case 6:
            if (isRegister(extractedWords[1])) {
                addStringToStringTable(table, "000110001100");
            } else
                addStringToStringTable(table, "000110010100");
            L++;
            break;
        case 7:
            if (isRegister(extractedWords[1])) {
                strcpy(twoLine, regBinString);
                strcat(twoLine, A);
                addStringToStringTable(table, twoLine);
            } else
                addStringToStringTable(table, extractedWords[1]);
            L++;
            break;
        case 8:
            if (isRegister(extractedWords[1])) {
                strcpy(twoLine, regBinString);
                strcat(twoLine, A);
                addStringToStringTable(table, twoLine);
            } else
                addStringToStringTable(table, extractedWords[1]);
            L++;
            break;
        case 9:
            if (isRegister(extractedWords[1])) {
                strcpy(twoLine, regBinString);
                strcat(twoLine, A);
                addStringToStringTable(table, twoLine);
            } else
                addStringToStringTable(table, extractedWords[1]);
            L++;
            break;
        case 10:
            if (isRegister(extractedWords[1])) {
                strcpy(twoLine, regBinString);
                strcat(twoLine, A);
                addStringToStringTable(table, twoLine);
            } else
                addStringToStringTable(table, extractedWords[1]);
            L++;
            break;
        case 11:
            if (isRegister(extractedWords[1])) {
                strcpy(twoLine, regBinString);
                strcat(twoLine, A);
                addStringToStringTable(table, twoLine);
            } else
                addStringToStringTable(table, extractedWords[1]);
            L++;
            break;
        case 12:
            if (isRegister(extractedWords[1])) {
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
            if (isRegister(extractedWords[1])) {
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
    /*printf("\nhere chek eror\n");
    flagError++;*/
    return 0;
}

void initParamTable() {
    int i;
    for (i = 0; i < MAX_TABLE_SIZE; i++) {
        tableLabel[i].nextIndex = -1;
    }
}

int addParamToTable(int ID, const char *Label, const char *Type) {
    unsigned int length = strlen(Label);
    int i;
    countTable++;
    for (i = 0; i < countTable && i< MAX_TABLE_SIZE; i++) {
        if (tableLabel[i].nextIndex == -1) {
            tableLabel[i].ID = ID;
            if (Label[length - 1] == ':') {
                strncpy(tableLabel[i].Label, Label, length - 1);
                tableLabel[i].Label[length - 1] = '\0';
            } else {
                strncpy(tableLabel[i].Label, Label, sizeof(tableLabel[i].Label));
            }
            strncpy(tableLabel[i].Type, Type, sizeof(tableLabel[i].Type));
            tableLabel[i].nextIndex = i + 1;
            return i;
        }
    }
    return -1;
}

void printParamTable() {
    int i;
    printf("Parameter Table:\n");
    for (i = 0; i < MAX_TABLE_SIZE; i++) {
        if (tableLabel[i].nextIndex != -1) {
            printf("Index %d: ID: %d , Label: %s , Type: %s\n", i, tableLabel[i].ID, tableLabel[i].Label, tableLabel[i].Type);
        }
    }
}

void duplicateDataWithType(int number) {
    int i;
    for (i = 0; i < countTable && i < MAX_TABLE_SIZE; i++) {
        if (strcmp(tableLabel[i].Type, "data") == 0) {
            tableLabel[i].ID = tableLabel[i].ID+number;
        }
    }
}

int checkIfWordExists(ParamTable *table,char *word) {
    int i;
    for (i = 0; i < countTable && i < MAX_TABLE_SIZE; i++) {
        if (strcmp(table[i].Label, word) == 0) {
            strncpy(tableLabel[i].Type, "entry", sizeof(tableLabel[i].Type));
            return 1;
        }
    }
    return 0;
}

void base64_encode(const char* input, char* output) {
    const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    unsigned int input_length = strlen(input);
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
        printf("error not can open the file\n");
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

void processFile(const char *filename) {
    char line[memoryData];
    char line_copy[memoryData];
    char tokens[MAX_WORDS][MAX_WORD_LENGTH];
    int numTokens;
    FILE *file;
    StringTableBIN tableBIN;
    initStringTable(&tableBIN);
    initParamTable();
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    IC = 100;
    DC = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        L = 0;
        strcpy(line_copy, line);
        /*if(checkLineError(line_copy))continue;*/
        tokenizeString(line_copy, tokens, &numTokens);
        if (isSymbol(tokens[0]))flagSymbol = 1;
        if (containsStringKeyword(line_copy) || containsDataKeyword(line_copy)){
            if (isStringKeyword(tokens[1]) || isDataKeyword(tokens[1])) {
                if (flagSymbol == 1){
                    upTabelLabel(tokens[0], DC, "data");
                    flagSymbol=0;
                }
                if(containsDataKeyword(line_copy)){

                    binaryData(line_copy,&tableBIN);
                    continue;
                }
                else {
                    binaryString(line_copy,&tableBIN);
                    continue;
                }

            }
        }
        else if (containsExternKeyword(line_copy) || containsEntryKeyword(line_copy)) {
            if (isExternKeyword(tokens[0])) {
                upTabelLabel(tokens[1], -1, "extrnal");
                flagSymbol=0;
                continue;
            }
        }
        else {
            if (flagSymbol) {
                upTabelLabel(tokens[0], IC, "code");
                flagSymbol=0;
            }
            if (isWordInArray(line_copy) == -1) {
                printf("\nError! the action not exist");
                flagError = 1;
                continue;
            }
            binaryActioen(line_copy, &tableBIN);
            IC = IC + L;
            continue;
        }
    }
    duplicateDataWithType(IC);
    SecondPass(filename, &tableBIN);
    fclose(file);
    if(flagError !=0)exit(1);
    process_input_file(&tableBIN,"ps.ob");
    process_input_file_ent("ps.ent");
    process_input_file_ext("ps.ext", &tableBIN);
}

void SecondPass(const char *filename, StringTableBIN *tableBin1) {
    char line[memoryData];
    char line_copy[memoryData];
    char tokens[MAX_WORDS][MAX_WORD_LENGTH];
    int numTokens;
    FILE *file;
    IC = 0;
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        L = 0;
        strcpy(line_copy, line);
        /*if (checkLineError(line_copy))continue;*/
        tokenizeString(line_copy, tokens, &numTokens);
        if (containsStringKeyword(line_copy) || containsDataKeyword(line_copy) || containsExternKeyword(line_copy))
            continue;
        if (containsEntryKeyword(line_copy)) {
            if (checkIfWordExists(tableLabel, tokens[1]) == 0) {
                printf("\n Error! the label not entry\n");
                flagError = 1;
                continue;
            }
        }
        IC = IC + L;
    }
    updateTables(tableBin1);
}

int main() {
    const char *filename = "target_file.am";
    processFile(filename);
    /*
     * remove(filename);
     * */

    return 0;
}