%{
#include <stdio.h>
#include <string.h>

int has_upper = 0, has_lower = 0, has_digit = 0, has_symbol = 0;
%}

%%

[a-z]      { has_lower = 1; }
[A-Z]      { has_upper = 1; }
[0-9]      { has_digit = 1; }
[*;#$@]    { has_symbol = 1; }
.          { }  /* Ignore other characters */

%%

int main() {
    char password[100];  

    printf("Enter password: ");
    scanf("%s", password);

    int len = strlen(password);

    if (len >= 9 && len <= 15) {
        yy_scan_string(password);
        yylex();
        
        if (has_upper && has_lower && has_digit && has_symbol) {
            printf("Valid password\n");
        } else {
            printf("Invalid password\n");
        }
    } else {
        printf("Invalid password\n");
    }
    
    return 0;
}

int yywrap() { return 1; }
