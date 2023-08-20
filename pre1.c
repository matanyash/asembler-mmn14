#include "data.h"

// פונקציה לטיפול במילה
void processWord(const char* word) {
    // כאן ניתן להוסיף את הלוגיקה לטיפול במילה
    // לדוגמה:
    printf("%s\n", word);
}

// פונקציה לטיפול בשורה
void processLine(char* line) {
    // מסיר רווחים מהתחלה ומסוף המחרוזת
    char* start = line;
    char* word = strtok(start, " ");
    increaseDataCounter(1);
    increaseInstructionCounter(1);
    // מטפלים בכל מילה בשורה
    while (word != NULL) {
        if (isSemel(word) == 1){

        }
        processWord(word); // קריאה לפונקציה לטיפול במילה
        word = strtok(NULL, " ");
    }
}








int main() {
    const char* filename = "example.txt";
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        resetMemoryCounters();
        processLine(line); // קריאה לפונקציה לטיפול בשורה
    }

    fclose(file);
    return 0;
    }