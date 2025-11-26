/* src/core/executor.c */
#include "../../include/shell.h"

void execute_command(char **argv) {
    pid_t pid;

    pid = fork();
    
    if (pid == 0) {
        // 자식 프로세스
        execvp(argv[0], argv);
        // execvp 실패 시
        perror("exec failed");
        exit(1);
    } else if (pid > 0) {
        // 부모 프로세스
        wait(NULL); // wait((int)0) 대신 표준인 NULL 사용 권장
    } else {
        perror("fork failed");
    }
}