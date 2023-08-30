#include "data.h"
#include "test.h"
#include "PreAssembler.h"

/*
 * this is the PreAssembler file, the file that holds the parsing macros and used to using this functions for the parsing macros
 * parsing the source file and forward it into target file(.am). this is the part before the first pass.
 */

/*
 * this is flag for checking errors and printing errors.
 * when error occur the flag is on, the error has been printed and the program continue looking for errors despite the errors occured before
 * and does not stop the working.
 */
static int  FlagError;

int ParsingMacros(char *line, FILE* src, MacroData *macros) 
{
    int lines = 0;
    char *macroName = NULL;
    char *next = NULL;
    char *MacroContent = NULL;
    char *tempArr=NULL;

    const int VecStartValue = 5;
    const int vecGrowth = 2;
    int vecCapacity = VecStartValue;
    char macroLine[MAX_LINE_LEN] = {0};

    macroName = strtok(MoveToEnd(line), " \t\n\f\r");
    next = strtok(NULL, " \t\n\f\r");

    if (next == NULL) 
    {

        fprintf(stderr, "Macro declaration Without Defining a Macro Name!\n");
        return FAIL;
    }
    if (!ValidMacroName(next)) {

        fprintf(stderr, "illegal Macro Name!\n ");
        return FAIL;
    }
    strncpy(macroName, next, MAX_LINE_LEN);

    MacroContent =  malloc(MAX_LINE_LEN * VecStartValue * sizeof(char));

    if (MacroContent == NULL) {

            fprintf(stderr, "Error in memory allocation!");
            return FAIL;
    }
        while (fgets(macroLine, MAX_LINE_LEN, src) != NULL) 
	{

            if (CloseMacro(macroLine)) 
           {

                AddNewMacro(macroName, MacroContent, lines, macros);
                break;

            }
            strncpy(MacroContent + (lines * MAX_LINE_LEN), macroLine, MAX_LINE_LEN);

             ++lines;

            if (lines >= vecCapacity) 
            {
                vecCapacity *= vecGrowth;

                 tempArr = (char*)realloc(MacroContent, MAX_LINE_LEN * vecCapacity * sizeof(char));

                if (NULL == tempArr) 
                {
                    fprintf(stderr, "Error in allocation,no memory available!");
                    free(MacroContent);

                    return FAIL;
                }

                MacroContent = tempArr;

            }
	}

        return  SUCCESS;

}


int MacroLayOut(char *line,MacroData *macros,FILE *target)
{
    int i;
    char *LabelMacro;
    MacroItem *mt;

    LabelMacro = GetMacroName(line);

    mt =FindMacroName(macros, LabelMacro);

    if (NULL == mt)
    {
        return FAIL;

    }

    for (i =0; i < mt->Numlines; ++i) 
	{

        fprintf(target, "%s", &mt->DataLines[i * MAX_LINE_LEN]);

	}

    return SUCCESS;


}


int parsingSourcefile(FILE* src, FILE* target)
{
    char line[MAX_LINE_LEN] = {0};
    char token[MAX_LINE_LEN] = {0};

    MacroData *macros=CreateMacroData();

    if(macros == NULL)
    {
        fprintf(stderr,"No memory available!\n");

        FlagError=1;
    }

    while (fgets(line, MAX_LINE_LEN, src) != NULL)
    {
        strncpy(token,line,MAX_LINE_LEN);

        if(! isComment(line)&& !isEmptyLine(line))
        {
            if(OpenMacro(line))
            {
                if (FAIL == ParsingMacros(line,src,macros))
                {
                    DestroyMacroData(macros);

                    return FAIL;
                }

            }

            else if(isPossiblyUseOfMacro(line))
            {
                MacroLayOut(line,macros,target);
            }

            else
            {
                fprintf(target,"%s",line);
            }
        }

    }
    DestroyMacroData(macros);

    return SUCCESS;
}






int main(int argc, char *argv[])
{
    /* for (int i = 1 ,0 is  executable name i < argc; ++i) { */
        FILE *src;
        FILE *trg;
        /*src= fopen(argv[i],"r"); */
        src = fopen("o2.txt", "r");
        trg = fopen("target_file.am", "w");
        if (src == NULL) {
            fprintf(stderr, "error in opening source file!");
            return 1;
        }

        parsingSourcefile(src, trg);


        fclose(src);
        fclose(trg);
        processFile("target_file.am");
   /* } */
        return 0;
    }









