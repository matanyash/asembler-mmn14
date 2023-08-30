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

bool OpenMacro(char *s);
/* @ Description of function: The function gets a char *s, the string it checks whether it is the opening of a macro or not.
         The function checks if char *s is equal to the constant MACRO (defines - mcro), returns true if it is, and false if it isn't
*/

bool CloseMacro(char *s);
/* @ Description of function: as same as the opening macro function, The function gets a char *s,  checks whether it is the closing of a macro or not.
    The function checks if char *s is equal to the constant endmacro(defines - endmcro), returns true if it is, and false if it is not
*/

bool isPossiblyUseOfMacro(char *s);
/* @ Description of function: The function gets a char *s,  checks whether it can be a macro or not.
    The function checks if char *s can be a macro, by illuminating the other things it can be (an instruction, a label,..etc).
   Returns true if it could be a macro and false if it couldn't.
*/

bool ValidMacroName(char *s);
/* @ Description of function: The function gets a char *s,  checks whether it is a legal macro name or not.
 *  The function checks if char *s is a legal macro name by verifying that it's name is not a name of an instruction or an operation.
    Returns true if it is a legal macro name and false if it is not.
*/

bool isInstruction(char *s);
/* @ Description of function: The function gets a char *s,  checks whether it or a part of it is an instruction or not.
   The function checks if char *s or a part of it is an instruction by comparing it to the name of the instructions or checking if one of the instructions are a substring of it.
   Returns true if it or a part of it is an instruction, and false if it isn't.
*/

bool isInstructionStrict(char *s);
/* @ Description of function: The function gets a char *s,  checks whether it is an instruction sentence or not.
    The function checks if char *s is an instruction by comparing it to the name of the instructions.
   Returns true if it is an instruction, and false if it isn't.
*/

bool isRegistery(char *s);
/* @ Description of function: The function gets a char *s,  checks whether it is a register or not.
    The function checks if char *s is a legal register by checking if the first char is 'r' and the others are int numbers between 0-7.
   Returns true if it is a register, and false if it isn't.
*/

bool isValidImmediateParameter(char *s);
/* @ Description of function: The function gets a char *s,  checks whether it is a valid immediate parameter or not.
    The function checks if char *s is a valid immediate parameter by verifying the first token us a -, a + or a digit and the other vhars are digits.
   Returns true if it is a valid immediate parameter, and false if it isn't.

*/

bool isValidIndexParameter(char *s);
/* @ Description of function: The function gets a char *s,  checks whether it is a valid index parameter or not.
   The function checks if char *s is a valid index parameter by checking if it is a label and a register in parenthesis afterwards
   Returns true if it is a valid index parameter, and false if it isn't.
*/

bool isIndexParameter(char *s);
/* @ Description of function: The function gets a char *s,  checks whether it is a index parameter or not.
   The function checks if char *s is a valid index parameter by checkin if it is a label and a register (any register) in parenthesis afterwards
   Returns true if it is a valid index parameter, and false if it isn't.
*/

bool isComment(char *s);

int  isEmptyLine(char *s);
/*
 * @Description of function: this function gets char *s which represents the line it checks,checks if it is an empty line
 * if it is return 1, if it is not return 0.
 */
bool DeclarationOfLabel(char *s);


int getRegisteryNumber(char *s);

bool isInstructionOp(char *s);

#endif