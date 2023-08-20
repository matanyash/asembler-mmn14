#include "data.h"

// הפונקציה base64_encode מקבלת מחרוזת בינארית באורך 6 תווים וממירה אותה למספר בסיס 64 בעזרת הטבלה base64_table.
// עוברים על כל המחרוזת בצעדים של 6 תווים וממירים כל קטע בן 6 תווים למספר בסיס 64 ומוסיפים את התו התואם מהטבלה למחרוזת התוצאה.
// המחרוזת התוצאה מסתיימת בתו הנל (null terminator).
void base64_encode(const char* input, char* output) {
    const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    const int input_length = strlen(input);
    int output_length = 0;

    for (int i = 0; i < input_length; i += 6) {
        unsigned int value = 0;
        for (int j = 0; j < 6 && i + j < input_length; j++) {
            value = (value << 1) | (input[i + j] - '0');
        }
        output[output_length++] = base64_table[value];
    }

    output[output_length] = '\0';
}

// הפונקציה process_input_file מקבלת שני שמות של קבצים - קובץ קלט וקובץ פלט.
// הפונקציה פותחת את שני הקבצים, ולאחר מכן עוברת על התוכן של קובץ הקלט שבו כל שורה היא מחרוזת בינארית באורך 12 תווים.
// לכל מחרוזת בקובץ הקלט מתבצעת המרה לקוד base64 באמצעות הפונקציה base64_encode והתוצאה מודפסת לקובץ הפלט, עם תו נפרד '\n' בין שורות.
// כאשר כל הקובץ הקלט נסרק, הפונקציה סוגרת את שני קבצי הקלט והפלט ומדפיסה הודעת הצלחה.
void process_input_file(const char* input_filename, const char* output_filename) {
    FILE* input_file = fopen(input_filename, "r");
    FILE* output_file = fopen(output_filename, "w");

    if (input_file == NULL || output_file == NULL) {
        printf("eror not can open the file\n");
        return;
    }

    char input_string[13];
    char output_string[9];

    // קריאה שורה אחת לכל פעם מהקובץ הקלט כל עוד יש מחרוזת לקרוא.
    while (fgets(input_string, sizeof(input_string), input_file) != NULL) {
        // מחיקת התו '\n' שמיותר בסוף המחרוזת (הכריתה של התו האחרון).
        input_string[strcspn(input_string, "\n")] = '\0';
        // המרת המחרוזת בינארית לקוד base64 והדפסתה לקובץ הפלט עם תו נפרד '\n' בסוף כל שורה.
        base64_encode(input_string, output_string);
        fprintf(output_file, "%s\n", output_string);
    }

    // סגירת קבצי הקלט והפלט.
    fclose(input_file);
    fclose(output_file);

    printf("all good\n");
}

// הפונקציה main מהווה את נקודת ההתחלה של התוכנית.
// בפונקציה main קוראים לפונקציה process_input_file עם שמות הקבצים "x.am" ו-"output.txt" כפרמטרים.
// לאחר הקריאה לפונקציה, סיום התכנית מצוין על ידי החזרת ערך 0 מהפונקציה main.
int main() {
    process_input_file("x.am", "x.ob");

    return 0;
}
