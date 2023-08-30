/*#include "global.h"*/
#include "function.h"

const char *wordArray[16] = {"mov", "cmp", "add", "sub", "not", "clr", "lea", "inc", "dec", "jmp", "bne", "red", "prn",
                             "jsr", "rts", "stop"};
const int numWords = sizeof(wordArray) / sizeof(wordArray[0]);


int isWordInArray(const char *line) {
    int i;
    char lineCopy[1000];
    char *token;
    unsigned int len = strlen(line);
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
    return 1;
}

int isSymbol(const char *word) {
    unsigned int length = strlen(word);

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

int containsStringKeyword(const char *line) {
    return strstr(line, ".string") != NULL;
}

int containsDataKeyword(const char *line) {
    return strstr(line, ".data") != NULL;
}

int containsExternKeyword(const char *line) {
    return strstr(line, ".extern") != NULL;
}

int containsEntryKeyword(const char *line) {
    return strstr(line, ".entry") != NULL;
}

int isNum(const char *str) {
    char firstChar = str[0];
    return ((firstChar >= '0' && firstChar <= '9') || firstChar == '-' || firstChar == '+');
}

void concatenateWords(const char *word1, const char *word2, const char *word3, const char *word4, char *result) {
    strcpy(result, word1);

    strcat(result, word2);

    strcat(result, word3);

    strcat(result, word4);
}


void tokenizeString(const char *input, char tokens[][MAX_WORD_LENGTH], int *numTokens) {
    int i;
    char inputCopy[MAX_WORD_LENGTH];
    char *wordStart = inputCopy;
    *numTokens = 0;

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


int isRegister(const char *word) {
    if (word[0] == '@' && word[1] == 'r') {
        if (word[2] >= '0' && word[2] <= '7')return 1;
        else printf("\nthe reg not exits\n");
        flagError = 1;
    }
    return 0;
}
