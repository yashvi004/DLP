%{
#include <stdio.h>
#include <stdlib.h>

FILE *yyin;  // File pointer for input file
%}

/* Token Definitions */
KEYWORD      "int"|"float"|"if"|"else"|"return"|"void"|"while"
IDENTIFIER   [a-zA-Z_][a-zA-Z0-9_]*
CONSTANT     [0-9]+(\.[0-9]+)?
STRING       \"([^\\\"]*)\"
PUNCTUATION  [(){};,]
OPERATOR     [=+\-*/%<>!&|]
COMMENT      \/\\*([^*]|\*+[^/])*\*+\/|\/\/.*
WHITESPACE   [ \t\n]+

%%

{KEYWORD}      { printf("Keyword: %s\n", yytext); }
{IDENTIFIER}   { printf("Identifier: %s\n", yytext); }
{CONSTANT}     { printf("Constant: %s\n", yytext); }
{STRING}       { printf("String: %s\n", yytext); }
{PUNCTUATION}  { printf("Punctuation: %s\n", yytext); }
{OPERATOR}     { printf("Operator: %s\n", yytext); }
{COMMENT}      { /* Ignore comments */ }
{WHITESPACE}   { /* Ignore spaces */ }
.              { printf("Lexical Error: Unexpected character %s\n", yytext); }

%%

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror("Error opening file");
        return 1;
    }

    yylex();  // Start lexical analysis
    fclose(yyin);

    return 0;
}

int yywrap() {
    return 1;
}
