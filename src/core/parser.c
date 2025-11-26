#include "../../include/shell.h"

int getargs(char *cmd, char **argv) {
    int narg = 0;

    while (*cmd) {
        if (*cmd == ' ' || *cmd == '\t') {
            *cmd++ = '\0';
        } else {
            argv[narg++] = cmd++;
            while (*cmd != '\0' && *cmd != ' ' && *cmd != '\t') {
                cmd++;
            }
        }
    }
    argv[narg] = NULL;
    return narg;
}