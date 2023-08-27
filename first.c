#include "test.c"


int chekLineEror(char * line_copy){
    //printf("\nhere chek eror\n");
    //flagEror++;
    return 0;
}

void pastTwo(const char *filename, StringTableBIN *tableBin, ParamTable **tableLabel);



void processFile(const char *filename) {
    char line[memoryData];
    char line_copy[memoryData];
    char tokens[MAX_WORDS][MAX_WORD_LENGTH];
    int numTokens;

    StringTableBIN tableBIN;
    initStringTable(&tableBIN);
    initParamTable();
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    IC = 0;
    DC = 100;
    while (fgets(line, sizeof(line), file) != NULL) {
        L = 0;
        strcpy(line_copy, line);
        //if(chekLineEror(line_copy))continue;
        tokenizeString(line_copy, tokens, &numTokens);
        if (isSimbele(tokens[0]))flagSimble = 1;
        if (containsStringKeyword(line_copy) || containsDataKeyword(line_copy)){
            if (isStringKeyword(tokens[1]) || isDataKeyword(tokens[1])) {
                if (flagSimble == 1){
                    upTabelLabel(tokens[0], DC, "data");
                    flagSimble=0;
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
                flagSimble=0;
                continue;
            }
        }
        else {
            if (flagSimble) {
                upTabelLabel(tokens[0], IC, "code");
                flagSimble=0;
            }
            if (isWordInArray(line_copy) == -1) { //12
                printf("\nEror! the actiun not exist");
                flagEror = 1;
                continue;
            }
            binaryOctihen(line_copy,&tableBIN);
            IC = IC + L;
            continue;
        }
    }
    printStringTable(&tableBIN);
    duplicateDataWithType(IC);
    pastTwo(filename, &tableBIN, &tableLabel);
    fclose(file);
    if(flagEror)exit(1);
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

    while (fgets(line, sizeof(line), file) != NULL) {
        L = 0;
        strcpy(line_copy, line);
        //if (chekLineEror(line_copy))continue;
        tokenizeString(line_copy, tokens, &numTokens);
        if (containsStringKeyword(line_copy) || containsDataKeyword(line_copy) || containsExternKeyword(line_copy))
            continue;
        if (containsEntryKeyword(line_copy)) {
            if (checkIfWordExists(tableLabel1, tokens[1]) == 0) {
                printf("\n Eror! the label not entry\n");
                flagEror = 1;
                continue;
            }
        }
        IC = IC + L;
    }
    updateTables(tableBin1);
    printParamTable(tableLabel1);
    printStringTable(tableBin1);
}



int main() {
const char *filename = "input.txt";
processFile(filename);

return 0;
}