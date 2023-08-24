#include "test.c"

//פונקצית זיהוי טעיות תחביר
int chekLineEror(char * line_copy){
    //printf("\nhere chek eror\n");
    flagEror++;
    return 0;
}
void pastTwo(const char *filename, StringTableBIN *tableBin, ParamTable *tableLabel);

void binaryOctihen(const char *line ,StringTableBIN *table) {
    //printf("\n i up the table");
    char extractedWords[2][10];
    char lineCopy[100];
    strcpy(lineCopy, line);
    int actiun = isWordInArray(line);
    //char extractedWords[2][20];
    char *position = NULL;
    char firstLine[13];
    char twoLine[13];
    char A[3] = "00";
    char B[3] = "01";
    char C[3] = "10";
    char *numBinaryString;
    char ooraa[5];
    char yaad[4] = "000";
    char makor[4] = "000";
    char *regBinString;

    // Find the first occurrence of any word from wordArray
    for (int i = 0; i < numWords; i++) {
        position = strstr(lineCopy, wordArray[i]);
        if (position != NULL) {
            break;
        }
    }

    if (position != NULL){
        //printf("+++%s", position);
        position += strlen(wordArray[0]); // Move past the found word
        char *token = strtok(position, ",");
        int count = 0;
        printf("+++%s", token);


        while (token != NULL && count < 2) {

            // Store the extracted word in the array
            strcpy(extractedWords[count], token);
            count++;

            token = strtok(NULL, ",");
        }
        // If only one word was found, set the second slot to -1
        if (count == 1) {
            char temp[50];  // Create a temporary buffer to hold word1
            strcpy(temp, extractedWords[0]);
            strcpy(extractedWords[0], "!");
            strcpy(extractedWords[1], temp);
        }
        // Print the extracted words
        printf("First word: %s\n", extractedWords[0]);
        printf("Second word: %s\n", extractedWords[1]);


    }
    printf("%c",extractedWords[0][0]);
    //קידוד שורה ראשונה
    binaryFirstLine(extractedWords[0],extractedWords[1],actiun, table);
    numBinaryString = numberToBinaryString(extractedWords[0]);
    regBinString = registerToBinaryString(extractedWords[0]);

    switch (actiun) {
        case 0:
            //printf("Performing action for value 0\n");
            //L = L+3; //test
            break;
        case 1:
            //printf("Performing action for value 1\n");;
            break;
        case 2:
            //printf("Performing action for value 2\n");
            break;
        case 3:
            //printf("Performing action for value 3\n");
            break;
        case 4:
            printf("Performing action for value 4\n");
            if (isRegister(extractedWords[1])){
                strcpy(twoLine, regBinString);
                strcat(twoLine, A);
                addStringToStringTable(table,twoLine);
            }else
                addStringToStringTable(table,extractedWords[1]);
            L = L+1;
            printf("two liine --- %s\n", twoLine);
            break;
        case 5:
            printf("Performing action for value 5\n");
            if (isRegister(extractedWords[1])){
                strcpy(twoLine, regBinString);
                strcat(twoLine, A);
                addStringToStringTable(table,twoLine);
            }else
                addStringToStringTable(table,extractedWords[1]);
            L = L+1;
            printf("two liine --- %s\n", twoLine);
            break;
        case 6:
            printf("Performing action for value 6\n");
            if (isRegister(extractedWords[1])){
                addStringToStringTable(table,"000110001100");
            }else
                addStringToStringTable(table,"000110010100");
            L = L+2;
            printf("two liine --- %s\n", twoLine);
            break;
        case 7: // not work
            printf("Performing action for value 7\n");
            if (isRegister(extractedWords[1])){
                strcpy(twoLine, regBinString);
                strcat(twoLine, A);
                addStringToStringTable(table,twoLine);
            }else
                addStringToStringTable(table,extractedWords[1]);
            L = L+1;
            printf("two liine --- %s\n", twoLine);
            break;
        case 8:
            printf("Performing action for value 8\n");
            if (isRegister(extractedWords[1])){
                strcpy(twoLine, regBinString);
                strcat(twoLine, A);
                addStringToStringTable(table,twoLine);
            }else
                addStringToStringTable(table,extractedWords[1]);
            L = L+1;
            printf("two liine --- %s\n", twoLine);
            break;
        case 9:
            printf("Performing action for value 9\n");
            if (isRegister(extractedWords[1])){
                strcpy(twoLine, regBinString);
                strcat(twoLine, A);
                addStringToStringTable(table,twoLine);
            }else
                addStringToStringTable(table,extractedWords[1]);
            L = L+1;
            printf("two liine --- %s\n", twoLine);
            break;
        case 10:
            printf("Performing action for value 10\n");
            if (isRegister(extractedWords[1])){
                strcpy(twoLine, regBinString);
                strcat(twoLine, A);
                addStringToStringTable(table,twoLine);
            }else
                addStringToStringTable(table,extractedWords[1]);
            L = L+1;
            printf("two liine --- %s\n", twoLine);
            break;
        case 11:
            printf("Performing action for value 11\n");
            if (isRegister(extractedWords[1])){
                strcpy(twoLine, regBinString);
                strcat(twoLine, A);
                addStringToStringTable(table,twoLine);
            }else
                addStringToStringTable(table,extractedWords[1]);
            L = L+1;
            printf("two liine --- %s\n", twoLine);
            break;
        case 12://prn
            printf("Performing action for value 12\n");
            if (isRegister(extractedWords[1])) {
                strcpy(twoLine, regBinString);
                strcat(twoLine, A);
                addStringToStringTable(table, twoLine);
            }
            else if (isNum(extractedWords[1]) == 0) {
                strcpy(twoLine, numberToBinaryString(extractedWords[1]));
                strcat(twoLine, A);
                addStringToStringTable(table, twoLine);

            }
            else addStringToStringTable(table, extractedWords[1]);
                L = L+1;
            printf("two liine --- %s\n", twoLine);
                break;
        case 13:
            printf("Performing action for value 13\n");
            if (isRegister(extractedWords[1])){
                strcpy(twoLine, regBinString);
                strcat(twoLine, A);
                addStringToStringTable(table,twoLine);
            }else
                addStringToStringTable(table,extractedWords[1]);
            L = L+1;
            printf("two liine --- %s\n", twoLine);
            break;
        /*
         case 14:
            addStringToStringTable(table,"000111000000");
            L++;
            break;
        case 15:
            addStringToStringTable(table,"000111100000");
            L++;
            break;
        */
        default:
            printf("Invalid value\n");
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
        printf("line %d is = %s", lineCount, line);
        //

        word = strtok(line, " "); // מפצל את השורה למילים
        while (word != NULL) {
            strcpy(word2, word);
            if (isSimbele(word))flagSimble = 1; //3,4
            if (containsStringKeyword(line_copy) || containsDataKeyword(line_copy)){ //5
                    word = strtok(NULL, " ");
                    if (isStringKeyword(word) || isDataKeyword(word)) {
                        if (flagSimble == 1){
                            upTabelLabel(word2, DC, "data");
                            flagSimble=0;
                        }
                        if(containsDataKeyword(line_copy))binaryData(line_copy,&tableBIN); //7
                        else binaryString(line_copy,&tableBIN);
                        break;
                    }
            }
            else if (containsExternKeyword(line_copy) || containsEntryKeyword(line_copy)) {
                    word = strtok(NULL, " ");
                    if (isExternKeyword(word2)) {
                        upTabelLabel(word, -1, "extrnal"); //9
                        flagSimble=0;
                        break;
                    }
            }
            else {
                    //word = strtok(NULL, " ");
                    if (flagSimble) {
                        upTabelLabel(word2, IC, "code");//11
                        flagSimble=0;
                    }
                    if (isWordInArray(line_copy) == -1) { //12
                        printf("\nEror! the actiun not exist");
                        flagEror = 1;
                        break;
                    }
                    binaryOctihen(line_copy,&tableBIN);//13
                    IC = IC + L;
                    break;
                }
            word = strtok(NULL, " ");
        }

    }
    printStringTable(&tableBIN);
    //printParamTable(&tableLabel);
    fclose(file);
    //if (flagEror)exit(1);//16
    duplicateDataWithType(IC);//17
    printParamTable(&tableLabel);
    pastTwo(filename,&tableBIN,&tableLabel);
}

void pastTwo(const char *filename, StringTableBIN *tableBin1, ParamTable *tableLabel1 ){
    int lineCount = 0;
    char line[memoryData];
    char line_copy[memoryData];
    char *word;
    char word2[100];
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
        if(chekLineEror(line_copy))continue;
        //זמני
        lineCount++;
        printf("line %d is = %s", lineCount, line);
        //

        word = strtok(line, " "); // מפצל את השורה למילים
        while (word != NULL) {
            strcpy(word2, word);
            if (containsStringKeyword(line_copy) || containsDataKeyword(line_copy) || containsExternKeyword(line_copy)) //4
                break;
            if (containsEntryKeyword(line_copy)) { //5
                word = strtok(NULL, " ");
                printf("\n ********%s********\n", word);
                if (checkIfWordExists(tableLabel1,word)==0){
                    printf("\n Eror! the label not entry\n");
                    break;
                }
            }else{
                printf("");
            }
                IC = IC + L;
                break;
            }
            word = strtok(NULL, " ");
        }

    }





int main() {
const char *filename = "input.txt";
processFile(filename);

return 0;
}

