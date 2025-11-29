#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>      // O_RDONLY, O_WRONLY, O_CREAT 등의 상수 정의
#include "../../include/commands.h"

#define BUFFER_SIZE 4096 // 한 번에 읽고 쓸 버퍼 크기

void myshell_cp(char **argv) {
    // 1. 인자 개수 확인
    // argv[0]: cp, argv[1]: 원본, argv[2]: 대상
    if (argv[1] == NULL || argv[2] == NULL) {
        fprintf(stderr, "usage: cp [source] [destination]\n");
        return;
    }

    // 2. 원본 파일 열기 (읽기 전용)
    int src_fd = open(argv[1], O_RDONLY);
    if (src_fd < 0) {
        perror("myshell: cp: source open error");
        return;
    }

    // 3. 대상 파일 열기
    // O_WRONLY: 쓰기 전용
    // O_CREAT: 파일이 없으면 생성
    // O_TRUNC: 파일이 이미 있으면 내용을 싹 비움 (덮어쓰기)
    // 0644: 파일 권한 (rw-r--r--)
    int dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        perror("myshell: cp: destination open error");
        close(src_fd); // 열린 원본 파일 닫기
        return;
    }

    // 4. 데이터 복사 루프 (버퍼링)
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;

    // 원본에서 읽어서(read) -> 대상에 씀(write)
    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        
        // 읽은 만큼 쓰지 못했으면 에러 (디스크 꽉 참 등)
        if (bytes_written != bytes_read) {
            perror("myshell: cp: write error");
            close(src_fd);
            close(dest_fd);
            return;
        }
    }

    // 5. 파일 닫기
    close(src_fd);
    close(dest_fd);
}