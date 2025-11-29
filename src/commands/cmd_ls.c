#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>     // 디렉토리 처리를 위한 헤더
#include <sys/types.h>
#include <unistd.h> 
#include "../../include/commands.h"

void myshell_ls(char **argv) {
    DIR *dp;
    struct dirent *entry;
    char *path;

    // 1. 경로 설정 (인자가 없으면 현재 디렉토리 ".")
    if (argv[1] == NULL) {
        path = ".";
    } else {
        path = argv[1];
    }

    // 2. 디렉토리 열기
    dp = opendir(path);
    if (dp == NULL) {
        perror("ls failed"); // 없는 폴더거나 권한 없을 때 에러 출력
        return;
    }

    int is_terminal = isatty(STDOUT_FILENO);

    // 3. 내용물 읽어서 출력하기
    while ((entry = readdir(dp)) != NULL) {
        if (is_terminal) {
            // 숨김 파일(점으로 시작)은 굳이 안 보여줘도 되지만 일단 다 출력
            printf("%s ", entry->d_name);
        } else {
            printf("%s\n", entry->d_name);
        }
    }

    // 4. 디렉토리 닫기
    closedir(dp);
}