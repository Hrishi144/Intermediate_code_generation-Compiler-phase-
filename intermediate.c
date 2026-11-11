#include <stdio.h>
#include <string.h>

int main(void) {
    char input[100], expr[100];
    char target, temp = 'Z';

    printf("Enter the expression: ");
    if (scanf("%99s", input) != 1)
        return 1;

    int start;

    if (input[1] == '=') {
        start = 2;
    } else if (input[1] == ':' && input[2] == '=') {
        start = 3;
    } else {
        printf("Use a=b+c or a:=b+c\n");
        return 1;
    }

    target = input[0];
    strcpy(expr, input + start);

    int length = strlen(expr);

    if (target < 'a' || target > 'z' ||
        length == 0 || length % 2 == 0) {
        printf("Invalid expression\n");
        return 1;
    }

    // Check that operands and operators alternate.
    for (int i = 0; i < length; i++) {
        if (i % 2 == 0) {
            if (!((expr[i] >= 'a' && expr[i] <= 'z') ||
                  (expr[i] >= '0' && expr[i] <= '9'))) {
                printf("Use single lowercase letters or digits\n");
                return 1;
            }
        } else if (strchr("+-*/", expr[i]) == NULL) {
            printf("Invalid operator\n");
            return 1;
        }
    }

    if (length / 2 > 26) {
        printf("Too many operations\n");
        return 1;
    }

    printf("The intermediate code:\n");

    while (strlen(expr) > 1) {
        int pos = -1;

        // Find the first multiplication or division.
        for (int i = 1; expr[i] != '\0'; i += 2) {
            if (expr[i] == '*' || expr[i] == '/') {
                pos = i;
                break;
            }
        }

        // Otherwise, process the first addition or subtraction.
        if (pos == -1)
            pos = 1;

        printf("%c := %c %c %c\n",
               temp, expr[pos - 1], expr[pos], expr[pos + 1]);

        // Replace the operation with its temporary variable.
        expr[pos - 1] = temp--;
        memmove(expr + pos, expr + pos + 2,
                strlen(expr + pos + 2) + 1);
    }

    printf("%c := %s\n", target, expr);
    return 0;
}