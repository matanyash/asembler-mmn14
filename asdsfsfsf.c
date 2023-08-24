#include <stdio.h>
#include <string.h>

void concatenateWords(const char *word1, const char *word2, const char *word3, char *result) {
    strcpy(result, word1); // Copy the first word to the result string
    //strcat(result, " ");   // Add a space separator
    strcat(result, word2); // Add the second word
    //strcat(result, " ");   // Add a space separator
    strcat(result, word3); // Add the third word
}

int main() {
    char word1[] = "011";
    char word2[] = "0000";
    char word3[] = "110";
    char result[13]; // Allocate enough space for the result

    concatenateWords(word1, word2, word3, result);

    printf("Concatenated string: %s\n", result);

    return 0;
}
