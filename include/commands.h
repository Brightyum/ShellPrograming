#ifndef COMMANDS_H
#define COMMANDS_H

/* ls 명령어 함수 선언 */
void myshell_ls(char **argv);
void myshell_pwd(char **argv);
void myshell_mkdir(char **argv);
void myshell_rmdir(char **argv);
void myshell_ln(char **argv);
void myshell_cp(char **argv);
void myshell_rm(char **argv);
void myshell_mv(char **argv);
void myshell_cat(char **argv);
void myshell_grep(char **argv);

#endif