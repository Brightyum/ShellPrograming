#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/commands.h"

#define MAX_LINE 1024  // 한 번에 읽을 줄의 최대 길이

// 스트림(파일 또는 stdin)에서 패턴을 찾아 출력하는 헬퍼 함수
void grep_stream(FILE *fp, char *pattern) {
    char buffer[MAX_LINE];

    // fgets로 한 줄씩 읽음
    while (fgets(buffer, MAX_LINE, fp) != NULL) {
        // strstr(대상문자열, 찾을패턴): 패턴이 포함되어 있으면 해당 위치 포인터 반환, 없으면 NULL
        if (strstr(buffer, pattern) != NULL) {
            printf("%s", buffer);
        }
    }
}

void myshell_grep(char **argv) {
    // 1. 인자 확인
    // argv[0]: grep, argv[1]: pattern, argv[2]: file(optional)
    if (argv[1] == NULL) {
        fprintf(stderr, "usage: grep [pattern] [file...]\n");
        return;
    }

    char *pattern = argv[1];

    // 2. 파일 인자가 없는 경우 -> 표준 입력(stdin)에서 검색
    // 예: cat file.txt | grep "hello"
    if (argv[2] == NULL) {
        grep_stream(stdin, pattern);
        return;
    }

    // 3. 파일 인자가 있는 경우 -> 해당 파일들에서 검색
    // 예: grep "hello" file1.txt file2.txt
    for (int i = 2; argv[i] != NULL; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            fprintf(stderr, "myshell: grep: ");
            perror(argv[i]); // 파일 열기 실패 에러 메시지
            continue;
        }
        
        grep_stream(fp, pattern);
        fclose(fp);
    }
}