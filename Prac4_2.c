%{
#include <stdio.h>
%}

%%

charusat      { printf("university"); }  // Replace "charusat" with "university"
.|\n         { printf("%s", yytext); }  // Print all other characters as they are

%%

int yywrap() {
    return 1;
}

int main() {
    yylex();  // Start lexical analysis
    return 0;
}
