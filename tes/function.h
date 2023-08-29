#ifndef FUNCTION
#define FUNCTION


/*A function to check if an action exists*/
int isWordInArray(const char *line);

/*A function that checks whether the word is a "symbol" according to the definition*/
int isSymbol(const char *word);

/*A function that checks whether the word is a string*/
int isStringKeyword(const char *word);

/*A function that checks whether the word is a data*/
int isDataKeyword(const char *word);

/*A function that checks whether the word is an extern*/
int isExternKeyword(const char *word);

/*A function that checks whether the word is an entry*/
int isEntryKeyword(const char *word);

/*Checks if the string contains the word ".string"*/
int containsStringKeyword(const char *line);

/*Checks if the string contains the word ".data"*/
int containsDataKeyword(const char *line);

/*Checks if the string contains the word ".extern"*/
int containsExternKeyword(const char *line);

/*Checks if the string contains the word ".entry"*/
int containsEntryKeyword(const char *line);

/*A function that accepts a word and returns whether it is a number*/
int isNum(const char *str);

/*A function that accepts 4 strings and connects them*/
void concatenateWords(const char *word1, const char *word2, const char *word3, const char *word4, char *result);



void tokenizeString(const char *input, char tokens[][MAX_WORD_LENGTH], int *numTokens);
#endif