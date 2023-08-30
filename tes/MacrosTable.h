#include "data.h"

/*
 * #######################################################################################
 * this file "MacrosTable.h" it is the header file of MacrosTable.c . it holds the prototypes of the function using there,
 * the typedef structs of the macro item and its data and enum for status of parsing functions.
 *#######################################################################################
 */
/*
 * this typedef enum is the status for the parsing functions and accordingly return in the function if the process failed or succeed.
 */
typedef enum {
    FAIL,
    SUCCESS
} Status;
/* MacroItem is the data structure for holding the macro fields (the name, the data,the lines of data).
 * we use linked list to follow the lines of the content.
 */

typedef struct MacroItem
{
    char name[MAX_LABEL_LEN];
    char *DataLines;
    int Numlines;
    struct MacroItem *next;
} MacroItem;
/* MacroData is struct linked list that hold the data of the macro . this helps following the macro and add it to the
 * MacroItem and save it in the Data structure. this helps us follow the macro until its end.
 */
typedef struct MacroData
{
    MacroItem *head;
} MacroData;

/*
 * @ Description of function:This function gets pointer defined MacroData and char *name which represents the name of macro.
 * it searches and looks for this name in every line in the file for the using of parsing the macro.
 *
 */
MacroItem *FindMacroName(MacroData *md, char *name);

/*
 *@ Description of function: this function does not get any parameters. the return type is MacroData we defined.
 * its purpose is to create a macro data for each macro in the file using linked list.
 */
MacroData *CreateMacroData(void);

/*
 *@ Description of function: this function gets MacroData pointer to the data of the macro and destroy the data after using it
 * as part of memory manage in the program. after we create macro data up there ,
 * then we destroyed after finish the using in it.
 */
void DestroyMacroData(MacroData *md);

/*
 * @ Description of function: this function gets char *macroname, char *lines, int linesnumber and MacroData *md.
 * the purpose of the function is to add new macro data into the data structure holding the name of the macro in macroname,
 * the data in char *lines and the amount of lines in linesnumber. the MacroData holds in a node all the data of the macro.
 */
int AddNewMacro(char *macroName, char *lines, int linesnumber, MacroData *md);

/*
 *@ Description of function: this function gets char *s and gets the name of the macro itself in the file, while it keeps
 * ignoring spaces and tabs, same as MoveToEnd.
 */
char *GetMacroName(char *s);






