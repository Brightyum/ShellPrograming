#include <stdio.h>
#include <sys/stat.h> 
#include <sys/types.h>
#include "../../include/commands.h"

void myshell_mkdir(char **argv) {
    // 1. 인자가 없는 경우 예외 처리
    if (argv[1] == NULL) {
        fprintf(stderr, "mkdir: missing operand\n");
        return;
    }

    // 2. 인자 개수만큼 반복하며 디렉토리 생성
    // 사용 예: mkdir dir1 dir2 dir3
    int i = 1;
    while (argv[i] != NULL) {
        // mkdir(경로, 권한)
        // 0755: 리눅스 기본 폴더 권한 (소유자 rwx, 그룹 rx, 기타 rx)
        if (mkdir(argv[i], 0755) != 0) {
            perror("mkdir failed"); // 이미 있거나 권한 없을 때 에러 출력
        }
        i++;
    }
}
