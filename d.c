#include <stdio.h>
#include <string.h>

#define MAX_TABLE_SIZE 1024

typedef struct {
    int param1;
    char param2[100];
    char param3[100];
    int nextIndex;
} CustomTable;

CustomTable table;

void printCustomTable(const CustomTable *table) {
    for (int i = 0; i < table->nextIndex; i++) {
        printf("Index %d: Param1: %d, Param2: %s, Param3: %s\n", i, table->param1, table->param2[i], table->param3[i]);
    }
}

void initCustomTable(CustomTable *table) {
    table->nextIndex = 0;
}

void addToCustomTable(CustomTable *table, int p1, const char *p2, const char *p3) {
    if (table->nextIndex < MAX_TABLE_SIZE) {
        table->param1 = p1;
        strncpy(table->param2[table->nextIndex], p2, sizeof(table->param2[table->nextIndex]));
        strncpy(table->param3[table->nextIndex], p3, sizeof(table->param3[table->nextIndex]));
        table->nextIndex++;
    }
}


int findParam1ByString(const CustomTable *table, const char *searchString) {
    for (int i = 0; i < table->nextIndex; i++) {
        if (strcmp(table->param2, searchString) == 0) {
            return table->param1;
        }
    }
    return -1; // String not found in the table
}

int doesStringExist(const CustomTable *table, const char *searchString) {
    for (int i = 0; i < table->nextIndex; i++) {
        if (strcmp(table->param2, searchString) == 0) {
            return 1; // String exists in the table
        }
    }
    return 0; // String does not exist in the table
}

int main() {
    initCustomTable(&table);

    // Adding entries to the table
    addToCustomTable(&table, 1, "String1", "Value1");
    addToCustomTable(&table, 2, "String2", "Value2");
    addToCustomTable(&table, 3, "String3", "Value3");

    // Searching for a string and getting its param1 value
    const char *searchString = "String2";
    int param1Value = findParam1ByString(&table, searchString);

    if (param1Value != -1) {
        printf("Param1 value for '%s' is: %d\n", searchString, param1Value);
    } else {
        printf("String '%s' not found in the table.\n", searchString);
    }

    // Checking if a string exists in the table
    const char *checkString = "String3";
    if (doesStringExist(&table, checkString)) {
        printf("String '%s' exists in the table.\n", checkString);
    } else {
        printf("String '%s' does not exist in the table.\n", checkString);
    }
    printCustomTable(&table);
    return 0;
}
