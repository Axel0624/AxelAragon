#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>


int approximate_alphabet(char *str);
double information_content(int alphabet_size, size_t length);

int main() {
    printf("Enter the string: ");
    char str[101];
    scanf("%100s", str);
    int alpha = approximate_alphabet(str);
    printf("Approximate alphabet: %d \n", alpha);
    int len = strlen(str);
    printf("Length: %d\n", len);
    double ic = information_content(alpha, len);
    printf("Information Content: %.2lf\n",ic );


    return 0;
}

int approximate_alphabet(char *str) {
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

double information_content(int alphabet_size, size_t length){
    return length * log2(alphabet_size);
}