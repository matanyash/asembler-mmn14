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

//base64
void process_input_file(const char* input_filename, const char* output_filename);
void base64_encode(const char* input, char* output) ;