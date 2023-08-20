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
    char input_string[] = "000000010110";
    char output_string[100]; // מחרוזת שמכילה את התוצאה

    base64_encode(input_string, output_string);

    printf("קלט: %s\n", input_string);
    printf("תוצאה בבסיס 64: %s\n", output_string);

    return 0;
}
