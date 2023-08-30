#include "data.h"
#include "MacrosTable.h"
/*
 * the pre Assembler is meant to parse the .as file and replacing macros if existing using hash table to
store the starting and ending index of each macro in file. for any errors in the macro parsing, syntax we return error message.
 */


/*
 * @ Description of function: This function gets char *line, char *token, FILE *src, FILE *target.
   the *src FILE pointer - is a file pointer to the original source code file (".as" file) and the *target FILE
   pointer argument is for an empty file that will be the expanded source file version of the src
   file without the macros.
   line is the copy of the current line we parsed from the source file and token is the
   first non-empty space token found in that line.
   this function is invoked by parseSourceFile function and is in take write the
   line into the new ".am" expanded file after checking if there are macros on the line (macro opening/closing/mentioning)
   and ignoring/replacing them correspondingly as we asked to do.
 */
int ParsingMacros(char *line, FILE* src, MacroData *macros);

/*
 * @ Description of function: This function gets char *line, MacroItem macros which defined as Data structure and FILE *target.
 * takes the macro itself as is in the source file( for instance, the macro is "m1") and doing a layout in the target file.
 */
int MacroLayOut(char *line,MacroData *macros,FILE *target);
/*
 * @ Description of function: This function gets FILE *src, FILE *target.
 the FILE *src and *target pointers as same as the function 'ParseMacros' above.
 This function splits the source file content to different lines, and it passes each
   seperated line to the parseMacros(char *line, char *token, FILE *src, FILE *target)
 */

int parsingSourcefile(FILE* src, FILE* target);


int main(int argc, char *argv[]);