#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "alphabet.h"
#include "information_content.h"
#include "pw_generator.h"
#include <time.h>


int main(int argc, char **argv) {
    // Process command line args
    if (argc < 3) {
        printf("Not enough args\n");
        return 1;
    }
    // Seed rand
    // TODO
    srand(time(NULL));

    // Grab password length
    long length = strtol(argv[1], NULL, 10);
    // Grab password count
    long count = strtol(argv[2], NULL, 10);

    // Setup alphabet_flags
    bool alphabet_flags[128];
    // Set alphabet_flags to all false
    for (int i = 0; i < 128; ++i) {
        alphabet_flags[i] = false;
    }
    // no luds flags
    if (argc == 3) {
        process_luds_flags("-luds", alphabet_flags);
    }

    // Process remaining command line args
    for (int i = 3; i < argc; ++i) {
        if (argv[i][0] == '-') {
            // It is a LUDS flag
            process_luds_flags(argv[i], alphabet_flags);
        } else {
            // It is an alphabet_flags
            process_alphabet(argv[i], alphabet_flags);
        }
    }

    char alphabet[128];
    calculate_alphabet(alphabet_flags, alphabet);

    printf("Using alphabet: %s\n", alphabet);

    for (long i = 0; i < count; ++i) {
        printf("Password %ld:\n", i + 1);
        char password[100];
        gen_password(length, alphabet, password);
        printf("Password: %s\n", password);
        double ic = approx_information_content(password);
        printf("Information content: %.2lf bits\n", ic);
    }

    return 0;
}