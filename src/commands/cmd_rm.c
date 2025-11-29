#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include "../../include/commands.h"

// 내부적으로 사용할 재귀 삭제 함수
int recursive_delete(char *path) {
    DIR *dp;
    struct dirent *entry;
    char full_path[1024];
    struct stat st;

    // 1. 파일/디렉토리 정보 확인
    if (lstat(path, &st) < 0) {
        perror("rm stat failed");
        return -1;
    }

    // 2. 디렉토리가 아니면 그냥 unlink(삭제) 하고 끝
    if (!S_ISDIR(st.st_mode)) {
        if (unlink(path) < 0) {
            perror("rm unlink failed");
            return -1;
        }
        return 0;
    }

    // 3. 디렉토리라면? 내부 탐색 시작
    if ((dp = opendir(path)) == NULL) {
        perror("rm opendir failed");
        return -1;
    }

    while ((entry = readdir(dp)) != NULL) {
        // 현재(.)와 부모(..)는 건너뜀
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // 경로 합치기: "폴더명/파일명"
        sprintf(full_path, "%s/%s", path, entry->d_name);

        // 재귀 호출! (다시 자기 자신을 불러서 삭제 시도)
        recursive_delete(full_path);
    }
    closedir(dp);

    // 4. 내용물을 다 지웠으니 이제 빈 껍데기(디렉토리) 삭제
    if (rmdir(path) < 0) {
        perror("rm rmdir failed");
        return -1;
    }

    return 0;
}

void myshell_rm(char **argv) {
    int recursive = 0;
    int start_idx = 1;

    // 1. 인자 확인
    if (argv[1] == NULL) {
        fprintf(stderr, "rm: missing operand\n");
        return;
    }

    // 2. -r 옵션 체크
    if (strcmp(argv[1], "-r") == 0) {
        recursive = 1;
        start_idx = 2; // -r 다음부터가 진짜 삭제할 대상
        if (argv[2] == NULL) {
            fprintf(stderr, "rm: missing operand\n");
            return;
        }
    }

    // 3. 삭제 루프 실행
    int i = start_idx;
    while (argv[i] != NULL) {
        if (recursive) {
            // -r 옵션이 있으면 재귀 삭제 함수 호출
            recursive_delete(argv[i]);
        } else {
            // 없으면 그냥 파일 삭제 (unlink)
            if (unlink(argv[i]) != 0) {
                // 실패했는데 디렉토리라서 실패한 거라면 메시지 출력
                struct stat st;
                if (stat(argv[i], &st) == 0 && S_ISDIR(st.st_mode)) {
                    fprintf(stderr, "rm: cannot remove '%s': Is a directory\n", argv[i]);
                } else {
                    perror("rm failed");
                }
            }
        }
        i++;
    }
}
