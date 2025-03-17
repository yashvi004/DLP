%{
#include <stdio.h>
%}

%%

[0-9]+ {
    printf("%s\n", yytext);  // Print the matched number
}

.|\n    ;  // Ignore any other characters

%%

int yywrap() {
    return 1;  // Terminate the scanner
}

int main() {
    yylex();  // Start the lexical analysis
    return 0;
}
