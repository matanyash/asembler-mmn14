#include "data.h"
#include "utils.h"


const char *regs[REGISTER_SIZE] = {"@r0", "@r1", "@r2", "@r3", "@r4", "@r5", "@r6" , "@r7"};

char *MoveToEnd(char *s)
{
    while(*s!='\0' && isspace(*s))
        s++;

    return s;
}
bool OpenMacro(char *s)
{
    return (NULL != strstr(s, OpMACRO)) ? true : false;
}

bool CloseMacro(char *s)
{
    return (NULL != strstr(s, endmacro)) ? true : false;
}
bool isPossiblyUseOfMacro(char *s)
{
    return  (!CloseMacro(s) && !OpenMacro(s) && !DeclarationOfLabel(s)  && !isComment(s) && !isInstructionStrict(s) && !isInstructionOp(s)) ;
}

bool ValidMacroName(char *s)
{
    return !isInstructionStrict(s)  ? true : false;
}

bool isInstruction(char *s)
{

    if ((!strcmp(s, DATA) || !strcmp(s, STRING) || !strcmp(s, ENTRY) || !strcmp(s, EXTERNAL)))
        return true;

    else if (strstr(s, DATA) != NULL || strstr(s, STRING) != NULL || strstr(s, ENTRY) != NULL || strstr(s, EXTERNAL) != NULL)
    {
        return true;
    }
    else
        return false;
}

bool isInstructionOp(char *s)
{
    if(strstr(s,"mov") !=NULL || strstr(s,"cmp") !=NULL|| strstr(s,"add") !=NULL || strstr(s,"sub") !=NULL || strstr(s,"not") !=NULL || strstr(s,"clr") !=NULL || strstr(s,"lea") !=NULL || strstr(s,"inc") !=NULL ||strstr(s,"dec") !=NULL|| strstr(s,"jmp") !=NULL||strstr(s,"bne") !=NULL||strstr(s,"red") !=NULL||strstr(s,"prn") !=NULL||strstr(s,"jsr") !=NULL||strstr(s,"rts") !=NULL||strstr(s,"stop") !=NULL)
    {
        return true;
    }
    return false;
}

bool isInstructionStrict(char *s)
{
    return strstr(s,DATA) || strstr(s,STRING) || strstr(s,ENTRY) || strstr(s,EXTERNAL) ? true : false; 
}

bool isRegistery(char *s)
{
    int len = strlen(s);
    int i = 0;
    if (s[0] == '@' && s[1] =='r' && s[2]<=7 && s[2]>=0  && len == 3)
    {
        while (i < REGISTER_SIZE)
        {
            if ((strcmp(regs[i], s) == 0))
                return true;
            i++;
        }
    }
    return false;
}
bool isValidImmediateParameter(char *s)
{
    int i, len = strlen(s);
    if (len < 2 || s[0] != '#' || (!(s[1] == '-' || s[1] == '+' || isdigit(s[1]))))
        return false;
    for (i = 2; i < len; i++)
        if (!isdigit(s[i]))
            return false;
    return true;
}
bool isIndexParameter(char *s)
{
    int len = strlen(s);
    char *opening = 0, *closing = 0;
    bool result = true;
    if (len < 5)
        return false;
    else if ((opening = strchr(s, '[')) == NULL || (closing = strchr(s, ']')) == NULL)
        return false;
    else if (closing < opening || (s[len - 1] != ']'))
        return false;
    else
    {
        opening++;
        *closing = '\0';
        if (!isRegistery(opening))
            result = false;
        *closing = ']';
    }
    return result;
}

bool isValidIndexParameter(char *s)
{
    int len = strlen(s);
    bool result = true;
    if (len < 6)
        return false;

    else if (!(s[len - 1] == ']' && s[len - 4] == 'r' && s[len - 5] == '['))
        return false;
    else
    {
        char *opening = 0;
        opening = strchr(s, '[');
        opening++;
        s[len - 1] = '\0';

        if (isRegistery(opening) && getRegisteryNumber(opening) < 8)
        {
            result = false;
        }
        s[len - 1] = ']';
    }
    return result;
}

bool isComment(char *s)
{
    s=MoveToEnd(s);

    return s[0] == ';' ? true : false;
}
/*bool isAction(char *s)
{
    return (getActionName(s) != NULL) ? true : false;
}
 */

bool isLabelDeclarationStrict(char *s)
{
    return s[strlen(s) - 1] == ':' ? true : false;
}

bool DeclarationOfLabel(char *s)
{
    return strchr(s, ':') != NULL ? true : false;
}

int getInstructionType(char *s)
{
    if (strstr(s, DATA) != NULL)
        return _TYPE_DATA;
    if (strstr(s, STRING) != NULL)
        return _TYPE_STRING;
    if (strstr(s, ENTRY) != NULL)
        return _TYPE_ENTRY;
    if (strstr(s, EXTERNAL) != NULL)
        return _TYPE_EXTERNAL;
    return false;
}

int getRegisteryNumber(char *s)
{
    s++;
    return atoi(s);
}

char *getInstructionName(char *s)
{
    if (strstr(s, DATA) != NULL)
        return DATA;
    if (strstr(s, STRING) != NULL)
        return STRING;
    if (strstr(s, ENTRY) != NULL)
        return ENTRY;
    if (strstr(s, EXTERNAL) != NULL)
        return EXTERNAL;

    return 0;
}

bool verifyLabelNaming(char *s)
{
    int i = 0;
    int labelLength = strlen(s);

    /* if label name doesn't start with an alphabet letter */
    if (isalpha(s[0]) == 0)
        return false;
    if (labelLength > MAX_LABEL_LEN || labelLength < 1)
        return false;
    if (isRegistery(s))
        return false;

    else
    {

        while (i < labelLength)
        {
            if (!isalnum(s[i]))
                return false;
            i++;
        }
    }

    return true;
}

bool VerifyLabelNamingByPrintErrors(char *s)
{
    int i = 0;
    int labelLength = strlen(s);

    /* if label name does not start with an alphabet letter */
    if (isalpha(s[0]) == 0)
        fprintf(stderr, "illegal label name use Of Characters");

        /* maximum label name length is 31 characters */
    else if (labelLength > MAX_LABEL_LEN || labelLength < 1 )
        fprintf(stderr, "illegal label name Length");

    else if (isRegistery(s))
        fprintf(stderr, "illegal label name using Registery name");

   /* else if (isActionName(s))
        fprintf(stderr, "illegal Label name using Action name");
        */

    else
    {

        while (i < labelLength)
        {
            if (!isalnum(s[i]))
                fprintf(stderr, "illegal label name use Of Characters");

            i++;
        }
    }

    return true;
}
int isEmptyLine(char *s)
{
    char *j;

   j= MoveToEnd(s);

   if(*j=='\0')
   {
       return 1;
   }

    return 0;
}

