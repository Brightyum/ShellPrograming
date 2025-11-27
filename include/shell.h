#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>

#define MAX_BUF 256
#define MAX_ARG 50

int getargs(char *cmd, char **argv);

void execute_command(char **argv);

void check_exit(char **argv);

void setup_signals();

#endif