%{
#include <stdio.h>

int char_count = 0, word_count = 0, line_count = 0;
%}

%%
[\n]         { line_count++; char_count++; }  // Count newlines and characters
[ \t]+      { char_count += yyleng; }       // Count spaces and tabs
[^\t\n ]+ { word_count++; char_count += yyleng; } // Count words and characters
.           { char_count++; }               // Count other characters
%%

int main() {
    yylex();  // Start lexical analysis

    printf("Characters : %d\n", char_count);
    printf("Words : %d\n", word_count);
    printf("Lines : %d\n", line_count);

    return 0;
}

int yywrap() {
    return 1;
}
