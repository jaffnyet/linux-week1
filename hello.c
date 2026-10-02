#include <stdio.h>
#include <string.h>

/*
 * Prints the command-line usage message for the hello program.
 *
 * This function explains how to invoke the program and lists the
 * supported help option. It is called when the user passes -h or
 * --help so they can see the program's usage information and exit
 * without running the greeting logic.
 */
void print_help() {
    printf("Usage: hello [NAME]\n");
    printf("A simple CLI tool to greet the user.\n\n");
    printf("Options:\n");
    printf("  -h, --help    Show this help message and exit\n");
}

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_help();
            return 0;
        }
    }
    if (argc > 2) {
        fprintf(stderr, "Error: Too many arguments provided.\n");
        fprintf(stderr, "Try 'hello --help' for more information.\n");
        return 1;
    }
    if (argc == 2) {
        printf("Hello, %s!\n", argv[1]);
    } else {
        printf("Hello, World!\n");
    }
    return 0;
}