#include "test.h"

//פונקצית זיהוי טעיות תחביר
int chekLineEror(char * line_copy){
    printf("\nhere chek eror\n");
    flagEror++;
    return 0;
}



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
                    word = strtok(NULL, " ");
                    if (flagSimble) {
                        upTabelLabel(word2, IC, "code");//11
                        flagSimble=0;
                    }
                    if (isWordInArray(line_copy) == 0) { //12
                        printf("\nEror! the actiun not exist");
                        flagEror = 1;
                        break;
                    }
                    //binaryAction(line_copy,&tableBIN);//13
                    IC = IC + L;
                    break;
                }
            word = strtok(NULL, " ");
        }

    }
    printStringTable(&tableBIN);
    printParamTable(&tableLabel);
    fclose(file);
    if (flagEror)exit(1);//16
    upDataTable();//17
}








int main() {
const char *filename = "input.txt";
processFile(filename);

return 0;
}



//resetMemoryCounters();

/*while (fgets(line, sizeof(line), file) != NULL) {
    strtok(line, "\n");
    printf("%s\n", line);
    //chekLineEror(line);
    //word = strtok(line, " "); // מפצל את השורה למילים
    while (word != NULL) {
        /*if(isSimbele(word) == 1)
            flagSimble = 1;
        if(isDataString(word) == 1){
            if(flagSimble==1){
                upTabelLabel(word, DC, "data");
            }
        }
        if(isExtrtenEntry(word) == 1){
            if(isExtren(word) == 1){
                upTabelLabel(word, 0, "external");
            }
        }
        if (flagSimble == 1){
            upTabelLabel(word, IC, "code");
        }
        if(isOraa(word)==0)printf("eror, the name %s not good" ,word);
        L = howMach(line);

        IC = IC + L;
            translateWord(word); // קריאה לפונקציה הפנימית להמרת מילה
            word = strtok(NULL, " ");
        }
    }
    if (flagEror == 1){
        exit(1);
    }

        fclose(file);
    }

}
}*/