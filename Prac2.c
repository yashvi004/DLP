#include <stdio.h>
#include <string.h>

// Checks whether string starts and ends with the same letter.
void startendsame(const char *inputString) {
    int length = strlen(inputString);

    if (length == 0) {
        printf("Test Failed: Empty string provided.\n");
        return;
    }

    if (inputString[0] == inputString[length - 1]) {
        printf("Test Passed: The string '%s' starts and ends with the same letter.\n", inputString);
    } else {
        printf("Test Failed: The string '%s' does not start and end with the same letter.\n", inputString);
    }
}

// Only a, b, c
void testOnlyABC(const char *inputString) {
    for (int i = 0; inputString[i] != '\0'; i++) {
        char input = inputString[i];
        if (input != 'a' && input != 'b' && input != 'c') {
            printf("Test Failed: The string '%s' contains invalid character '%c'.\n", inputString, input);
            return;
        }
    }

    printf("Test Passed: The string '%s' contains only 'a', 'b', and 'c'.\n", inputString);
}

// Checks whether string adheres to the rules in the transition table
int processString(const char *inputString, int initialState, int table[4][2]) {
    int currentState = initialState;
    int length = strlen(inputString);

    for (int i = 0; i < length; i++) {
        char input = inputString[i];

        if (input == 'a') {
            currentState = table[currentState - 1][0];
        } else if (input == 'b') {
            currentState = table[currentState - 1][1];
        } else {
            printf("Invalid input '%c' encountered\n", input);
            return -1;
        }
    }

    return currentState; // Return the final state
}

// every 0 must be immediately followed by 11
void zeroOneOne() {
    char inputString[50];
    printf("Enter a binary string (0 and 1): ");
    scanf("%s", inputString);

    int length = strlen(inputString);

    for (int i = 0; i < length; i++) {
        if (inputString[i] == '0') {
            if (i + 2 >= length || inputString[i + 1] != '1' || inputString[i + 2] != '1') {
                printf("Invalid String ");
                return;
            }
            i += 2; // Skip the next two characters as they form "11"
        } else if (inputString[i] != '1') {
            printf("Invalid Characters");
            return;
        }
    }

    printf("Test Passed: The string '%s' satisfies the rule.\n", inputString);
}

int main() {
    int states = 4;
    int sState = 1;
    int fState = 2;

    int table[4][2] = {
        {2, 3},
        {1, 4},
        {4, 1},
        {3, 2}
    };

    char inputString[] = "abbabab";

    // Function to process String
    int finalState = processString(inputString, sState, table);

    // Check the final state
    if (finalState == -1) {
        return 1;
    } else if (finalState == fState) {
        printf("The input string '%s' is accepted\n", inputString);
    } else {
        printf("The input string '%s' is rejected\n", inputString);
    }

    printf("\nRunning Test Cases:\n");

    char inputString2[20];
    printf("Enter string here: ");
    scanf("%s", inputString2);
    startendsame(inputString2);
    testOnlyABC(inputString2);

    // Call the new function
    zeroOneOne();

    return 0;
}
