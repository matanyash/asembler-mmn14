#include <stdio.h>
#include <string.h>


#define MAX_TABLE_SIZE 1024

static int countTable = 0;

typedef struct {
    int ID;
    char Label[100];
    char Type[100];
    int nextIndex;
} ParamTable;

static ParamTable tableLabel[MAX_TABLE_SIZE];

void initParamTable() {
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        tableLabel[i].nextIndex = -1;
    }
}

int addParamToTable(int ID, const char *Label, const char *Type) {
    unsigned long long length = strlen(Label);
    int i;
    countTable++;
    for (i = 0; i < countTable && i< MAX_TABLE_SIZE; i++) {
        if (tableLabel[i].nextIndex == -1) {
            tableLabel[i].ID = ID;
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
    return -1;
}

void printParamTable() {
    printf("Parameter Table:\n");
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        if (tableLabel[i].nextIndex != -1) {
            printf("Index %d: ID: %d , Label: %s , Type: %s\n", i, tableLabel[i].ID, tableLabel[i].Label, tableLabel[i].Type);
        }
    }
}


void duplicateDataWithType(int number) {
    int i;
    for (i = 0; i < countTable && i < MAX_TABLE_SIZE; i++) {
        if (strcmp(tableLabel[i].Type, "data") == 0) {
            tableLabel[i].ID = tableLabel[i].ID+number;
        }
    }
}

int checkIfWordExists(ParamTable *table,char *word) {
    int i;
    for (i = 0; i < countTable && i < MAX_TABLE_SIZE; i++) {
        if (strcmp(table[i].Label, word) == 0) {
            strncpy(tableLabel[i].Type, "entry", sizeof(tableLabel[i].Type));
            return 1;
        }
    }
    return 0;
}
