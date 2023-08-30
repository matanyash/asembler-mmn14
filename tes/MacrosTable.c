#include "data.h"
#include "MacrosTable.h"
/*
 * this is the source file "MacrosTable.c". it holds the functions to find macro name, to create macro data,
 * to destroy the macro data, and to add new macro to the macro data structure.
 * this source file is used for the parsing macros and file functions in "PreAssembler.h" .
 *
 */
MacroItem *FindMacroName(MacroData *md, char *name) {

    MacroItem *current = NULL;

    if (!md || !name)
    {
        return NULL;
    }

    current = md->head;

    while (current)
    {
        if (strcmp(current->name, name) == 0)
        {
            return current;
        }

        current = current->next;
    }


    return NULL;
}

MacroData *CreateMacroData(void) {
    MacroData *md;

    md = (MacroData *)malloc(sizeof(MacroData));

    if (md)
    {
        md->head = NULL;
    }
    return md;
}

void DestroyMacroData(MacroData *md) {
    MacroItem *current= NULL;

    MacroItem *next=NULL;

    if (!md)
        return;

    current = md->head;
    while (current) {
        next = current->next;
        free(current->DataLines);
        free(current);
        current = next;
    }
    md->head= NULL;

    free(md);
}

int AddNewMacro(char *macroName, char *lines, int LinesNum, MacroData *md) {

    MacroItem *newMacro= NULL;

    if (!md || !macroName || LinesNum <= 0)
        return FAIL;

     newMacro = (MacroItem *)malloc(sizeof(MacroItem));

    if (!newMacro)
        return FAIL;

    strncpy(newMacro->name,macroName,MAX_LABEL_LEN);

    newMacro->Numlines = LinesNum;

    newMacro->DataLines = lines;

    newMacro->next = md->head;

    md->head = newMacro;

    return SUCCESS;
}
char *GetMacroName(char *s)
{
    char *j;

    j= strtok( MoveToEnd(s), " \t\n\f\r");

    return j;
}

