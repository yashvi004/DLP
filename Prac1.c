#include<stdio.h>
#include<string.h>

int isValidString(char *c) {
    int n = strlen(c);
    if (n >= 2 && c[n - 2] == 'b' && c[n - 1] == 'b') {
        for (int i = 0; i < (n - 2); i++) {
            if (c[i] != 'a') {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

int main() {
    char c[20];
    printf("Enter a string: ");
    scanf("%s", c);

    if (isValidString(c)) {
        printf("Valid String\n");
    } else {
        printf("Invalid string\n");
    }

    return 0;
}
