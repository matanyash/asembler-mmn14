#ifndef UTILS
#define UTILS

#include "data.h"
/* the utils.c files contains most of all helpers functions that are used for verifying and checking and
 validating tokens ,identity , function here are mainly used outside of this file by other functions that deals
with parsing the assembly code, functions here are prototype.


*/
char *MoveToEnd(char *s);
/*
 * @ Description of function: the function gets char *s , the string it checks .
 * it trims the  white spaces and tabs from left and move to the end of it, meaning it ignores the spaces and tabs.
 */

int OpenMacro(char *s);
/* @ Description of function: The function gets a char *s, the string it checks whether it is the opening of a macro or not.
         The function checks if char *s is equal to the constant MACRO (defines - mcro), returns true if it is, and false if it isn't
*/

int CloseMacro(char *s);
/* @ Description of function: as same as the opening macro function, The function gets a char *s,  checks whether it is the closing of a macro or not.
    The function checks if char *s is equal to the constant endmacro(defines - endmcro), returns true if it is, and false if it is not
*/

int isPossiblyUseOfMacro(char *s);
/* @ Description of function: The function gets a char *s,  checks whether it can be a macro or not.
    The function checks if char *s can be a macro, by illuminating the other things it can be (an instruction, a label,..etc).
   Returns true if it could be a macro and false if it couldn't.
*/

int ValidMacroName(char *s);
/* @ Description of function: The function gets a char *s,  checks whether it is a legal macro name or not.
 *  The function checks if char *s is a legal macro name by verifying that it's name is not a name of an instruction or an operation.
    Returns true if it is a legal macro name and false if it is not.
*/

int isInstruction(char *s);
/* @ Description of function: The function gets a char *s,  checks whether it or a part of it is an instruction or not.
   The function checks if char *s or a part of it is an instruction by comparing it to the name of the instructions or checking if one of the instructions are a substring of it.
   Returns true if it or a part of it is an instruction, and false if it isn't.
*/

int isInstructionStrict(char *s);
/* @ Description of function: The function gets a char *s,  checks whether it is an instruction sentence or not.
    The function checks if char *s is an instruction by comparing it to the name of the instructions.
   Returns true if it is an instruction, and false if it isn't.
*/

int isComment(char *s);
/* @Description of function: this function gets char *s .
  The function checks if char *s is a comment by checking if it's first char is ; .
   Returns true if it is a comment, and false if it isn't.

*/

int  isEmptyLine(char *s);
/*
 * @Description of function: this function gets char *s which represents the line it checks,checks if it is an empty line
 * if it is return 1, if it is not return 0.
 */
int DeclarationOfLabel(char *s);


int isInstructionOp(char *s);

#endif