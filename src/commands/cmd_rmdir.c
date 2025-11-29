#include <stdio.h>
#include <unistd.h>
#include "../../include/commands.h"

void myshell_rmdir(char **argv) {
    // 1. 인자가 없는 경우 예외 처리
    if (argv[1] == NULL) {
        fprintf(stderr, "rmdir: missing operand\n");
        return;
    }

    // 2. 인자 개수만큼 반복하며 디렉토리 삭제
    int i = 1;
    while (argv[i] != NULL) {
        // rmdir(경로) - 성공 시 0, 실패 시 -1 반환
        // 주의: 비어있지 않은 디렉토리는 삭제할 수 없음 (리눅스 표준 동작)
        if (rmdir(argv[i]) != 0) {
            perror("rmdir failed");
        }
        i++;
    }
}
