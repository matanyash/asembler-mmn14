#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void decode_file(FILE *file);
void testWork(char );
int erros = 0;
static unsigned int ID;
static unsigned int CD;
char word[10];
int main() {
    FILE *file;
    char filename[100];

    printf("Enter the filename: ");
    scanf("%s", filename);

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Call the function to decode the file
    decode_file(file);

    fclose(file);

    return 0;
}

void decode_file(FILE *file) {
    int i =0;
    char ch;
    ID = 0;
    CD = 0;
    int line_count = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            line_count++;
            printf("\n");
        } else{
            if(ch != ':') {
                word[i] = ch;
                i++;
            } else printf("LABAL IS : %s",word);
            putchar(ch);
        }
    }
    if (erros == 1)exit(0);//אם יש שגיאות בקובץ התוכנית מפסיקה

    printf("\nTotal lines in the file: %d\n", (int)line_count);
}

void testWork(char c)
{

}


