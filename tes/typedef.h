#ifndef TYPEDEF
#define TYPEDEF
#include "lib.h"

typedef struct {
    char strings[MAX_TABLE_SIZE][MAX_STRING_LENGTH];
    char ent[10][10];
    int nextIndex;
} StringTableBIN;


typedef struct {
    int ID;
    char Label[100];
    char Type[100];
    int nextIndex;
} ParamTable;

#endif
