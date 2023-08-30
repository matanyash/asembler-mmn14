#include "data.h"
#include "utils.h"


const char *regs[REGISTER_SIZE] = {"@r0", "@r1", "@r2", "@r3", "@r4", "@r5", "@r6" , "@r7"};

char *MoveToEnd(char *s)
{
    while(*s!='\0' && isspace(*s))
        s++;

    return s;
}
int OpenMacro(char *s)
{
    return (NULL != strstr(s, OpMACRO)) ? 1 : 0;
}

int CloseMacro(char *s)
{
    return (NULL != strstr(s, endmacro)) ? 1 : 0;
}
int isPossiblyUseOfMacro(char *s)
{
    return  (!CloseMacro(s) && !OpenMacro(s) && !DeclarationOfLabel(s)  && !isComment(s) && !isInstructionStrict(s) && !isInstructionOp(s)) ? 1 : 0;
}

int ValidMacroName(char *s)
{
    return !isInstructionStrict(s)  ? 1 : 0;
}

int isInstruction(char *s)
{

    if ((!strcmp(s, DATA) || !strcmp(s, STRING) || !strcmp(s, ENTRY) || !strcmp(s, EXTERNAL)))
        return 1;

    else if (strstr(s, DATA) != NULL || strstr(s, STRING) != NULL || strstr(s, ENTRY) != NULL || strstr(s, EXTERNAL) != NULL)
    {
        return 1;
    }
    else
        return 0;
}

int isInstructionOp(char *s)
{
    if(strstr(s,"mov") !=NULL || strstr(s,"cmp") !=NULL|| strstr(s,"add") !=NULL || strstr(s,"sub") !=NULL || strstr(s,"not") !=NULL || strstr(s,"clr") !=NULL || strstr(s,"lea") !=NULL || strstr(s,"inc") !=NULL ||strstr(s,"dec") !=NULL|| strstr(s,"jmp") !=NULL||strstr(s,"bne") !=NULL||strstr(s,"red") !=NULL||strstr(s,"prn") !=NULL||strstr(s,"jsr") !=NULL||strstr(s,"rts") !=NULL||strstr(s,"stop") !=NULL)
    {
        return 1;
    }
    return 0;
}

int isInstructionStrict(char *s)
{
    return strstr(s,DATA) || strstr(s,STRING) || strstr(s,ENTRY) || strstr(s,EXTERNAL) ? 1 : 0; 
}

int isComment(char *s)
{
    s=MoveToEnd(s);

    return s[0] == ';' ? 1 : 0;
}


int isLabelDeclarationStrict(char *s)
{
    return s[strlen(s) - 1] == ':' ? 1 : 0;
}

int DeclarationOfLabel(char *s)
{
    return strchr(s, ':') != NULL ? 1 : 0;
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

