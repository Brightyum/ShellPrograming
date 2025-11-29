#include <stdio.h>
#include <unistd.h>   // getcwd 함수 사용을 위해 필요
#include <limits.h>   // PATH_MAX 상수 사용을 위해 필요 (경로 최대 길이)
#include "../../include/commands.h"

// PATH_MAX가 정의되지 않은 시스템을 위한 대비책
#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

void myshell_pwd(char **argv) {
    char cwd[PATH_MAX]; // 경로를 저장할 버퍼

    // getcwd(buffer, size): 현재 작업 디렉토리 경로를 buffer에 저장
    // 성공 시 버퍼 포인터 반환, 실패 시 NULL 반환
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        // 경로를 가져오는데 실패했을 경우 에러 메시지 출력
        perror("myshell: pwd error");
    }
}
