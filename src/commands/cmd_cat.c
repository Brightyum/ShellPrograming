#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../include/commands.h"

// 파일 스트림의 내용을 읽어 표준 출력으로 내보내는 헬퍼 함수
void cat_stream(FILE *fp) {
    // char buffer[1024];  <-- 이 줄이 경고의 원인이었습니다. 삭제합니다.
    
    int c;
    // fgetc를 사용하여 한 글자씩 읽어서 출력 (버퍼 변수 불필요)
    while ((c = fgetc(fp)) != EOF) {
        if (putchar(c) == EOF) {
            perror("myshell: write error");
            break;
        }
    }
}

void myshell_cat(char **argv) {
    // 1. 인자가 없는 경우: 표준 입력(stdin)을 그대로 출력
    if (argv[1] == NULL) {
        cat_stream(stdin);
        return;
    }

    // 2. 인자가 있는 경우: 나열된 파일들을 순서대로 읽어서 출력
    for (int i = 1; argv[i] != NULL; i++) {
        FILE *fp = fopen(argv[i], "r");
        
        if (fp == NULL) {
            fprintf(stderr, "myshell: cat: ");
            perror(argv[i]);
            continue; 
        }

        cat_stream(fp);
        fclose(fp);
    }
}