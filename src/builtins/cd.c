#include <stdio.h>
#include <unistd.h>   
#include "../../include/shell.h"

void myshell_cd(char **argv) {
    // 인자가 없으면(그냥 'cd'만 치면) 보통 홈 디렉토리로 가거나 아무것도 안 함
    if (argv[1] == NULL) {
        fprintf(stderr, "cd: missing argument\n");
        return;
    }

    // chdir 실행. 성공하면 0, 실패하면 -1 반환
    if (chdir(argv[1]) != 0) {
        perror("cd failed"); // "cd failed: No such file..." 형태로 에러 출력
    }
}