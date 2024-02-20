#include "information_content.h"
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

int approximate_alphabet(char *str) {
    // Like in HW2
    int upper = 0;
    int lower = 0;
    int digit = 0;
    int symbol = 0;

    for(int i = 0; str[i] != '\0'; ++i) {
        if (isdigit(str[i])) {
            digit = 10;
        }
        else if(islower(str[i])) {
            lower = 26;
        }
        else if(isupper(str[i])) {
            upper = 26;
        } else {
            // symbol
            symbol = 32;
        }
    }
    int count = upper + lower + digit + symbol;
    return count;
}

double information_content(int length, int alpha_size) {
    // Like in HW2
    return length * log2(alpha_size);
}

double approx_information_content(char *str) {
    int alpha = approximate_alphabet(str);
    return information_content(strlen(str), alpha);
}
