#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int checkKeyword(const char *line) {
    const char *stop = "stop";
    const char *rts = "rts";

    if (strstr(line, stop) != NULL) {
        if (strstr(line, rts) != NULL) {
            printf("eror!");
            return 0;
        }
        return 1;
    } else if (strstr(line, rts) != NULL) {
        return 2;
    } else {
        return 0;
    }
}

//פונקצית ניתוח פעולות
/*void binaryAction(char * line, StringTableBIN *table){
    char StopString[13] = "000111100000";
    char RtsString[13] = "000111000000";
    printf("\nhere i do binary kod");
    if(checkKeyword(line) == 1){
        addStringToStringTable(table,StopString);
    }
    if(checkKeyword(line) == 2){
        addStringToStringTable(table,RtsString);
    }
    if (checkKeyword(line) == 0){
        return;
    }

}
*/