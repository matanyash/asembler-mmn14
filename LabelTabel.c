#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_TABLE_SIZE 1024

typedef struct {
    int ID;
    char Label[100];
    char Type[100];
    int nextIndex;
} ParamTable;

ParamTable tableLabel[MAX_TABLE_SIZE];

void initParamTable() {
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        tableLabel[i].nextIndex = -1;
    }
}

int addParamToTable(int ID, const char *Label, const char *Type) {
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        if (tableLabel[i].nextIndex == -1) {
            tableLabel[i].ID = ID;

            // Copy Label without colon
            int length = strlen(Label);
            if (Label[length - 1] == ':') {
                strncpy(tableLabel[i].Label, Label, length - 1);
                tableLabel[i].Label[length - 1] = '\0';
            } else {
                strncpy(tableLabel[i].Label, Label, sizeof(tableLabel[i].Label));
            }

            strncpy(tableLabel[i].Type, Type, sizeof(tableLabel[i].Type));
            tableLabel[i].nextIndex = i + 1;
            return i;
        }
    }
    return -1; // Table is full
}
/*
int addParamToTable(int ID, const char *Label, const char *Type) {
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        if (tableLabel[i].nextIndex == -1) {
            tableLabel[i].ID = ID;
            strncpy(tableLabel[i].Label, Label, sizeof(tableLabel[i].Label));
            strncpy(tableLabel[i].Type, Type, sizeof(tableLabel[i].Type));
            tableLabel[i].nextIndex = i + 1;
            return i;
        }
    }
    return -1; // Table is full
}
*/

void printParamTable() {
    printf("Parameter Table:\n");
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        if (tableLabel[i].nextIndex != -1) {
            printf("Index %d: ID: %d , Label: %s , Type: %s\n", i, tableLabel[i].ID, tableLabel[i].Label, tableLabel[i].Type);
        }
    }
}

/*int main() {
    initParamTable();

    addParamToTable(1, "Label1", "Type1");
    addParamToTable(2, "Label2", "Type2");
    addParamToTable(3, "Label3", "Type3");

    printParamTable();

    return 0;
}
*/