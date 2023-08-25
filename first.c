#include "test.c"

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 50

//פונקצית זיהוי טעיות תחביר
int chekLineEror(char * line_copy){
    //printf("\nhere chek eror\n");
    //flagEror++;
    return 0;
}

void pastTwo(const char *filename, StringTableBIN *tableBin, ParamTable **tableLabel);

void tokenizeString(const char *input, char tokens[][MAX_WORD_LENGTH], int *numTokens) {
    *numTokens = 0;
    // יצירת עותק ניתן לשינוי של המחרוזת המקורית
    char inputCopy[MAX_WORD_LENGTH];
    strcpy(inputCopy, input);

    // מרכז המחרוזת משמש נקודת התחלה של חיתוך כל מילה
    char *wordStart = inputCopy;

    // עבור כל תו במחרוזת
    for (int i = 0; inputCopy[i] != '\0'; i++) {
        if (inputCopy[i] == ',' || isspace(inputCopy[i])) {
            inputCopy[i] = '\0'; // החלף תו המפריד בתו סיום מחרוזת

            // אם אינו מילה ריקה, הוסף אותה למערך המילים
            if (wordStart != &inputCopy[i]) {
                strncpy(tokens[*numTokens], wordStart, MAX_WORD_LENGTH);
                tokens[*numTokens][MAX_WORD_LENGTH - 1] = '\0'; // ודא תמיד סיום מחרוזת
                (*numTokens)++;
            }

            // הזז את מצב התחלה של המילה לאחר תו המפריד
            wordStart = &inputCopy[i + 1];
        }
    }

    // בדוק אם יש מילה שנותרה בסיום השורה
    if (wordStart != &inputCopy[strlen(inputCopy)]&&wordStart[0] != '\0') {
        strncpy(tokens[*numTokens], wordStart, MAX_WORD_LENGTH);
        tokens[*numTokens][MAX_WORD_LENGTH - 1] = '\0'; // ודא תמיד סיום מחרוזת
        (*numTokens)++;
    }
}

void binaryOctihen(char *line ,StringTableBIN *table) {
    //printf("\n i up the table");
    char extractedWords[2][50];
    char lineCopy[100];
    strcpy(lineCopy, line);
    int actiun = isWordInArray(line);
    char twoLine[13];
    char regBinString[13];
    char A[3] = "00";
    char B[3] = "01";
    char C[3] = "10";
    char *numBinaryString;
    char tokens[MAX_WORDS][MAX_WORD_LENGTH];
    int numTokens;
    int count;
    int i;
    tokenizeString(line, tokens, &numTokens);
    for (i = 0; i < numTokens; i++) {
        printf("%s ", tokens[i]);
        //if(strcmp(tokens[i],"This")==0)break;
    }
    count = numTokens -1;
    if ((strcmp(tokens[numTokens-1], "rts") == 0)){
        //printf("\n this is rts - -\n");
        addStringToStringTable(table,"000111000000");
        L++;
    }

    if(strcmp(tokens[numTokens-1], "stop") == 0){
        //printf("\n this is stop - -\n");
        addStringToStringTable(table, "000111100000");
        L++;
        return;
    }
    //printf("\n^^ %d ^^^^ %d", numTokens,count);
    //printf("\n ^^^ %s", tokens[0]);
    if (isSimbele(tokens[0])==1) {
        count--;
        //printf("\n is simbele! \n");
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

    binaryFirstLine(extractedWords[0], extractedWords[1], actiun, table);
    numBinaryString = numberToBinaryString(extractedWords[0]);

    switch (actiun) {
        case 0:
            //printf("\nPerforming action for value 0\n");
            if (isWordInArray1(extractedWords[0]) && isWordInArray1(extractedWords[1])){
                strcpy(twoLine, registerToBinaryString2(extractedWords[0]));
                strcat(twoLine, registerToBinaryString2(extractedWords[1]));
                strcat(twoLine, A);
                addStringToStringTable(table, twoLine);
                L++;
                //printf("\ntwo liine --- %s\n", twoLine);
                break;
            }
            if(isWordInArray1(extractedWords[0])){
                strcpy(regBinString, registerToBinaryString2(extractedWords[0]));
                strcat(regBinString, "0000000");
                addStringToStringTable(table, regBinString);
                L++;
                //printf("\ntwo liine --- %s\n", regBinString);
            }

            else if(isNum(extractedWords[0])){
                strcpy(twoLine, numberToBinaryString(extractedWords[0]));
                strcat(twoLine, A);
                addStringToStringTable(table, twoLine);
                L++;
                //printf("\ntwo liine --- %s\n", twoLine);
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
        case 6: // not work
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
            //printf("two liine --- %s\n", twoLine);
            break;
        case 8:
            //printf("Performing action for value 8\n");
            if (isWordInArray1(extractedWords[1])) {
                strcpy(twoLine, regBinString);
                strcat(twoLine, A);
                addStringToStringTable(table, twoLine);
            } else
                addStringToStringTable(table, extractedWords[1]);
            L++;
            //printf("two liine --- %s\n", twoLine);
            break;
        case 9:
            //printf("Performing action for value 9\n");
            if (isWordInArray1(extractedWords[1])) {
                strcpy(twoLine, regBinString);
                strcat(twoLine, A);
                addStringToStringTable(table, twoLine);
            } else
                addStringToStringTable(table, extractedWords[1]);
            L++;
            //printf("two liine --- %s\n", twoLine);
            break;
        case 10:
            //printf("Performing action for value 10\n");
            if (isWordInArray1(extractedWords[1])) {
                strcpy(twoLine, regBinString);
                strcat(twoLine, A);
                addStringToStringTable(table, twoLine);
            } else
                addStringToStringTable(table, extractedWords[1]);
            L++;
            //printf("two liine --- %s\n", twoLine);
            break;
        case 11:
            //printf("Performing action for value 11\n");
            if (isWordInArray1(extractedWords[1])) {
                strcpy(twoLine, regBinString);
                strcat(twoLine, A);
                addStringToStringTable(table, twoLine);
            } else
                addStringToStringTable(table, extractedWords[1]);
            L++;
            //printf("two liine --- %s\n", twoLine);
            break;
        case 12://prn
            //printf("Performing action for value 12\n");
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
            //printf("two liine --- %s\n", twoLine);
            break;
        case 13:
            //printf("Performing action for value 13\n");
            if (isWordInArray1(extractedWords[1])) {
                strcpy(twoLine, regBinString);
                strcat(twoLine, A);
                addStringToStringTable(table, twoLine);
            } else
                addStringToStringTable(table, extractedWords[1]);
            L ++;
            //printf("two liine --- %s\n", twoLine);
            break;
        default:
            break;
    }
    //free(numBinaryString);
    //free(position);

}
/////////////////
void processFile(const char *filename) {
    StringTableBIN tableBIN;
    initStringTable(&tableBIN);
    initParamTable();
    int lineCount = 0;
    char line[memoryData];
    char line_copy[memoryData];
    char *word;
    char word2[100];
    char tokens[MAX_WORDS][MAX_WORD_LENGTH];
    int numTokens;
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    //resetMemoryCounters();
    while (fgets(line, sizeof(line), file) != NULL) {
        L = 0;
        strcpy(line_copy, line);
        if(chekLineEror(line_copy))continue;
        //זמני
        lineCount++;
        //printf("line %d is = %s", lineCount, line);
        //
        tokenizeString(line_copy, tokens, &numTokens);
        if (isSimbele(tokens[0]))flagSimble = 1; //3,4
        if (containsStringKeyword(line_copy) || containsDataKeyword(line_copy)){ //5
            if (isStringKeyword(tokens[1]) || isDataKeyword(tokens[1])) {
                if (flagSimble == 1){
                    upTabelLabel(tokens[0], DC, "data");
                    flagSimble=0;
                }
                if(containsDataKeyword(line_copy)){

                    binaryData(line_copy,&tableBIN); //7
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
                upTabelLabel(tokens[1], -1, "extrnal"); //9
                flagSimble=0;
                continue;
            }
        }
        else {
            if (flagSimble) {
                upTabelLabel(tokens[0], IC, "code");//11
                flagSimble=0;
            }
            if (isWordInArray(line_copy) == -1) { //12
                printf("\nEror! the actiun not exist");
                flagEror = 1;
                continue;
            }
            binaryOctihen(line_copy,&tableBIN);//13
            IC = IC + L;
            continue;
        }
    }
    printStringTable(&tableBIN);
    //printParamTable(&tableLabel);
    duplicateDataWithType(IC);//17
    printParamTable(&tableLabel);
    pastTwo(filename, &tableBIN, &tableLabel);
    fclose(file);
    if(flagEror)exit(1);//16
    process_input_file(&tableBIN,"x.ob");
    process_input_file_ent("ps.ent");
    process_input_file_ext("ps.ext", &tableBIN);

}

void pastTwo(const char *filename, StringTableBIN *tableBin1, ParamTable ** tableLabel1 ) {
    char line[memoryData];
    char line_copy[memoryData];
    char tokens[MAX_WORDS][MAX_WORD_LENGTH];
    int numTokens;

    IC = 0;
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    //resetMemoryCounters();
    while (fgets(line, sizeof(line), file) != NULL) {
        L = 0;
        strcpy(line_copy, line);
        if (chekLineEror(line_copy))continue;
        tokenizeString(line_copy, tokens, &numTokens);
        if (containsStringKeyword(line_copy) || containsDataKeyword(line_copy) || containsExternKeyword(line_copy)) //4
            continue;
        if (containsEntryKeyword(line_copy)) {
            //5
            if (checkIfWordExists(tableLabel1, tokens[1]) == 0) {
                printf("\n Eror! the label not entry\n");
                flagEror = 1;
                continue;
            }
        }
        IC = IC + L;
        //replaceStringInTable(tableBin1, tableLabel1);
    }
    updateTables(tableBin1);
    //replaceStringInTable(tableBin1, tableLabel1);
    printParamTable(tableLabel1);
    printStringTable(tableBin1);
}



int main() {
const char *filename = "input.txt";
processFile(filename);

return 0;
}