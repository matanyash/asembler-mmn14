#include <stdio.h>
#include <string.h>

void base64_encode(const char* input, char* output) {
    const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    const int input_length = strlen(input);
    int output_length = 0;

    // ביצוע המרה של כל 6 סיביות לתו Base64
    for (int i = 0; i < input_length; i += 6) {
        unsigned int value = 0;

        // קביעת הערך הבינארי מהסיביות בקלט
        for (int j = 0; j < 6 && i + j < input_length; j++) {
            value = (value << 1) | (input[i + j] - '0');
        }

        // הוספת תו Base64 לתוצאה
        output[output_length++] = base64_table[value];
    }

    // הוספת סיומת
    output[output_length] = '\0';
}

int main() {
    FILE* input_file = fopen("x.am", "r"); // קובץ קלט
    FILE* output_file = fopen("output.txt", "w"); // קובץ פלט

    if (input_file == NULL || output_file == NULL) {
        printf("eror\n");
        return 1;
    }

    char input_string[13]; // מחרוזת שמכילה את הקלט מהקובץ (12 סיביות + סיומת תו)
    char output_string[9]; // מחרוזת שמכילה את התוצאה המבוקשת (8 תווים Base64 + סיומת תו)

    while (fgets(input_string, sizeof(input_string), input_file) != NULL) {
        input_string[strcspn(input_string, "\n")] = '\0'; // מחיקת התו הנוסף של "\n" אם קיים
        base64_encode(input_string, output_string);
        fputs(output_string, output_file);
        fputc('\n', output_file);
    }

    fclose(input_file);
    fclose(output_file);

    printf("all good\n");

    return 0;
}
