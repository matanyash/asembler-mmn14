#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SYMBOLS 1000

// הכנסת הקוד הבינארי לקובץ היעד
void writeBinary(FILE *outputFile, int binary) {
    fwrite(&binary, sizeof(int), 1, outputFile);
}

// טבלת הסמלים
struct SymbolTable {
    char name[50];
    int value;
};

// פונקציה להוספת סמל לטבלת הסמלים
void addSymbol(struct SymbolTable *table, char *name, int value, int *symbolsCount) {
    strcpy(table[*symbolsCount].name, name);
    table[*symbolsCount].value = value;
    (*symbolsCount)++;
}

// פונקציה לחיפוש סמל בטבלת הסמלים
int findSymbol(struct SymbolTable *table, char *name, int symbolsCount) {
    for (int i = 0; i < symbolsCount; i++) {
        if (strcmp(table[i].name, name) == 0) {
            return table[i].value;
        }
    }
    return -1; // אם לא נמצא הסמל בטבלה
}

int main() {
    FILE *inputFile, *outputFile;
    char line[50];
    char op[10];
    char operand1[20];
    char operand2[20];
    int IC = 0; // מונה ההוראות
    int DC = 0; // מונה הנתונים
    int symbolsCount = 0;
    struct SymbolTable symbolTable[MAX_SYMBOLS];

    // פתיחת קובץ קלט
    inputFile = fopen("x.am", "r");
    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    // פתיחת קובץ פלט
    outputFile = fopen("output.txt", "wb");
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        fclose(inputFile);
        return 1;
    }

    while (fgets(line, sizeof(line), inputFile)) {
        // קוד ההמרה כאן - עם sscanf וכו'

        // ...

        // עדכון ערכי המונים IC ו-DC
        // נניח ש-IC עומד כעת על 100
        // הקוד הבינארי של ההוראה הראשונה הוא 0x01234567
        // נעביר את הבינארי לקובץ היעד בצורה כזו:
        writeBinary(outputFile, 0x01234567);

        // המילה הבינארית הבאה בקוד מכונה היא 0x89ABCDEF
        // נכתוב אותה לקובץ היעד:
        writeBinary(outputFile, 0x89ABCDEF);

        // המילה הבינארית הבאה בקוד מכונה היא 0x12345678
        // נכתוב אותה לקובץ היעד:
        writeBinary(outputFile, 0x12345678);

        // בנוסף נוסיף את התווית A ואת המען שלה לטבלת הסמלים
        // אז אם A מוגדרה במקום 120, נכתוב:
        addSymbol(symbolTable, "A", 120, &symbolsCount);

        // וכמובן, נגדיר כל המידע הנוסף עבור ההוראות שלנו
        // ונשמור גם את המספרים המקוריים של התוויות בקוד המכונה
        // על מנת לאפשר הפעלה חוזרת בהמשך

        // ...

        // הדפסת טבלת הסמלים
        printf("Symbol Table:\n");
        printf("----------------------------\n");
        printf("Symbol\tValue\n");
        printf("----------------------------\n");
        for (int i = 0; i < symbolsCount; i++) {
            printf("%s\t%d\n", symbolTable[i].name, symbolTable[i].value);
        }

    }

    // סגירת קובץ הקלט והפלט
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
