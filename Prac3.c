#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SYMBOLS 100
#define MAX_TOKEN_LEN 50

// Keywords in C
const char *keywords[] = {"int", "float", "char", "if", "else", "for", "while", "return", "void", "double", "long", "short", "switch",
    "case", "default", "break", "continue", "do", "sizeof", "struct", "typedef", "union", "enum", "const",
    "static", "extern", "volatile", "register", "signed", "unsigned", "goto", "include", "define","main"};

const char operators[] = "+-*/=%";
const char punctuations[] = "(),;{}";

char symbolTable[MAX_SYMBOLS][MAX_TOKEN_LEN];
int symbolCount = 0;
int lastKeywordType = 0;
int inComment = 0;  // Flag to track if inside a comment

// Check if a string is a keyword
int isKeyword(const char *token) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(token, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

// Check if a character is an operator
int isOperator(char ch) {
    return strchr(operators, ch) != NULL;
}

// Check if a character is punctuation
int isPunctuation(char ch) {
    return strchr(punctuations, ch) != NULL;
}

// Check if a string is a valid identifier
int isIdentifier(const char *token) {
    if (!isalpha(token[0]) && token[0] != '_') return 0;
    for (int i = 1; token[i]; i++) {
        if (!isalnum(token[i]) && token[i] != '_') return 0;
    }
    return 1;
}

// Check if an identifier is already in the symbol table
int isInSymbolTable(const char *token) {
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i], token) == 0)
            return 1;
    }
    return 0;
}

// Add an identifier to the symbol table only if it's a variable (not a function)
void addSymbol(const char *token) {
    if (lastKeywordType && isIdentifier(token) && !isInSymbolTable(token)) {
        strcpy(symbolTable[symbolCount++], token);
    }
    lastKeywordType = 0;
}

// Print the symbol table
void printSymbolTable() {
    printf("\nSYMBOL TABLE:\n");
    for (int i = 0; i < symbolCount; i++) {
        printf("%d) %s\n", i + 1, symbolTable[i]);
    }
}

// Function to analyze C source code from file
void analyzeCode(FILE *file) {
    char token[MAX_TOKEN_LEN];
    int index = 0;
    char ch, nextCh;

    while ((ch = fgetc(file)) != EOF) {
        // Handle comments
        if (ch == '/') {
            nextCh = fgetc(file);
            if (nextCh == '/') {
                while ((ch = fgetc(file)) != EOF && ch != '\n');  // Skip single-line comments
                continue;
            } else if (nextCh == '*') {
                inComment = 1;
                while (inComment && (ch = fgetc(file)) != EOF) {
                    if (ch == '*' && (nextCh = fgetc(file)) == '/') inComment = 0;
                }
                continue;
            } else {
                ungetc(nextCh, file);
            }
        }

        if (inComment) continue; // Ignore everything inside comments

        // Skip whitespace
        if (isspace(ch)) continue;

        // Handle operators
        if (isOperator(ch)) {
            printf("Operator: %c\n", ch);
            continue;
        }

        // Handle punctuations
        if (isPunctuation(ch)) {
            printf("Punctuation: %c\n", ch);
            continue;
        }

        // Handle constants
        if (isdigit(ch)) {
            while (isdigit(ch)) { ch = fgetc(file); }
            ungetc(ch, file);
            continue;
        }

        // Handle identifiers and keywords
        if (isalpha(ch) || ch == '_') {
            while (isalnum(ch) || ch == '_') {
                token[index++] = ch;
                ch = fgetc(file);
            }
            token[index] = '\0';
            index = 0;
            ungetc(ch, file);

            if (isKeyword(token)) {
                printf("Keyword: %s\n", token);
                lastKeywordType = 1; // Set flag if it's a type keyword
            } else if (isIdentifier(token)) {
                printf("Identifier: %s\n", token);
                addSymbol(token);
            }
        }
    }
}

int main() {
    char filename[100];

    // Get filename from user
    printf("Enter the C source file name: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        return 1;
    }

    printf("\nAnalyzing %s\n", filename);
    analyzeCode(file);
    fclose(file);

    printSymbolTable();

    return 0;
}
