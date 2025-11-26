/* src/builtins/exit.c */
#include "../../include/shell.h"

void check_exit(char **argv) {
    if (argv[0] != NULL && strcmp(argv[0], "exit") == 0) {
        printf("Shell terminating...\n");
        exit(0);
    }
}