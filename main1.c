#include "dir_stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage(const char *prog_name) {
    fprintf(stderr, "Usage: %s pushd <directory> | popd\n", prog_name);
}

int main(int argc, char *argv[]) {
    static DirStack dir_stack;
    init_stack(&dir_stack);

    if (argc < 2) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "pushd") == 0) {
        if (argc != 3) {
            print_usage(argv[0]);
            return EXIT_FAILURE;
        }
        if (pushd(&dir_stack, argv[2]) != 0) {
            return EXIT_FAILURE;
        }
    } else if (strcmp(argv[1], "popd") == 0) {
        if (argc != 2) {
            print_usage(argv[0]);
            return EXIT_FAILURE;
        }
        if (popd(&dir_stack) != 0) {
            return EXIT_FAILURE;
        }
    } else {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    cleanup_stack(&dir_stack);
    return EXIT_SUCCESS;
}
