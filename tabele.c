#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100


// פריט בטבלה - מחרוזת ומספר
typedef struct {
    char str[MAX_SIZE];
    int num;
} TableItem;

// הגדרת הטבלה כמערך דינמי של פריטים
typedef struct {
    TableItem* items;
    int size;
} Table;

// פונקציות לניהול טבלת הסמלים
void initTable(Table* table);
void addItem(Table* table, const char* str, int num);
int findItem(const Table* table, const char* str);
void updateItem(Table* table, const char* str, int num);
void deleteItem(Table* table, const char* str);
void printTable(const Table* table);

// ...


void initTable(Table* table) {
    table->items = NULL;
    table->size = 0;
}

void addItem(Table* table, const char* str, int num) {
    // בדיקה אם הפריט כבר קיים בטבלה
    int index = findItem(table, str);
    if (index != -1) {
        printf("Item already exists in the table.\n");
        return;
    }

    // הגדלת גודל הטבלה
    table->size++;
    table->items = (TableItem*)realloc(table->items, table->size * sizeof(TableItem));

    // הוספת הפריט לטבלה
    strcpy(table->items[table->size - 1].str, str);
    table->items[table->size - 1].num = num;
}

int findItem(const Table* table, const char* str) {
    int i;
    for (i = 0; i < table->size; i++) {
        if (strcmp(table->items[i].str, str) == 0) {
            return i; // מצאנו את הפריט בטבלה, מחזירים את המיקום שלו
        }
    }
    return -1; // לא מצאנו את הפריט בטבלה
}

void updateItem(Table* table, const char* str, int num) {
    int index = findItem(table, str);
    if (index == -1) {
        printf("Item not found in the table.\n");
        return;
    }
    table->items[index].num = num;
}

void deleteItem(Table* table, const char* str) {
    int i;
    int index = findItem(table, str);
    if (index == -1) {
        printf("Item not found in the table.\n");
        return;
    }

    // מחיקת הפריט מהטבלה
    for (i = index; i < table->size - 1; i++) {
        strcpy(table->items[i].str, table->items[i + 1].str);
        table->items[i].num = table->items[i + 1].num;
    }

    // הקטנת גודל הטבלה
    table->size--;
    table->items = (TableItem*)realloc(table->items, table->size * sizeof(TableItem));
}

void printTable(const Table* table) {
    int i;
    printf("Table:\n");
    printf("--------------------------------------\n");
    printf("Num\t|\tString\n");
    printf("--------------------------------------\n");
    for (i = 0; i < table->size; i++) {
        printf("%d\t|\t%s\n", table->items[i].num, table->items[i].str);
    }
    printf("--------------------------------------\n");
}


int main() {
    Table table;
    initTable(&table);

    // הוספת שני פריטים לטבלה
    addItem(&table, "Hello", 101);
    addItem(&table, "World", 102);

    // עדכון פריט בטבלה
    updateItem(&table, "Hello", 201);

    // מחיקת פריט מהטבלה
    deleteItem(&table, "World");

    // הדפסת הטבלה
    printTable(&table);

    // שחרור זיכרון שנתקבל לטבלה
    free(table.items);

    return 0;
}
