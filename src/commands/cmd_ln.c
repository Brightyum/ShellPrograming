#include <stdio.h>
#include <unistd.h> 
#include <string.h>
#include "../../include/commands.h"

void myshell_ln(char **argv) {
    // 1. 인자가 부족한 경우 예외 처리
    if (argv[1] == NULL) {
        fprintf(stderr, "ln: missing file operand\n");
        return;
    }

    // 2. 심볼릭 링크 (-s 옵션) 처리
    // 입력 예시: ln -s 원본 타겟
    if (strcmp(argv[1], "-s") == 0) {
        // 인자가 3개 이상이어야 함 (ln, -s, 원본, 타겟)
        if (argv[2] == NULL || argv[3] == NULL) {
            fprintf(stderr, "ln: missing file operand\n");
            return;
        }

        // symlink(원본경로, 타겟경로)
        if (symlink(argv[2], argv[3]) != 0) {
            perror("ln -s failed");
        }
    } 
    
    // 3. 하드 링크 (기본) 처리
    // 입력 예시: ln 원본 타겟
    else {
        // 인자가 2개 이상이어야 함 (ln, 원본, 타겟)
        if (argv[2] == NULL) {
            fprintf(stderr, "ln: missing destination file\n");
            return;
        }

        // link(원본경로, 타겟경로)
        if (link(argv[1], argv[2]) != 0) {
            perror("ln failed");
        }
    }
}