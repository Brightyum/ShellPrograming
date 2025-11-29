#include <stdio.h>
#include <string.h>    
#include <sys/stat.h>
#include "../../include/commands.h"

void myshell_mv(char **argv) {
    struct stat sb;
    char dest_path[1024]; // 경로를 합칠 임시 버퍼

    // 1. 인자 확인
    if (argv[1] == NULL || argv[2] == NULL) {
        fprintf(stderr, "mv: missing file operand\n");
        return;
    }

    // 2. 목적지(argv[2])가 존재하는지, 그리고 디렉토리인지 확인
    // stat 함수는 파일 정보를 읽어옵니다. 성공 시 0 반환.
    if (stat(argv[2], &sb) == 0 && S_ISDIR(sb.st_mode)) {
        
        // --- [상황 A: 목적지가 디렉토리인 경우] ---
        // 예: mv a.txt mydir  -> 실제로는 mydir/a.txt 로 옮겨야 함

        // 2-1. 원본 파일명만 추출 (경로에 '/'가 있을 수 있으므로)
        // 예: src/a.txt -> a.txt 추출
        char *filename = strrchr(argv[1], '/'); 
        if (filename != NULL) {
            filename++; // '/' 다음 글자부터가 진짜 이름
        } else {
            filename = argv[1]; // '/'가 없으면 그 자체가 이름
        }

        // 2-2. 경로 합치기 (목적지 + "/" + 파일명)
        sprintf(dest_path, "%s/%s", argv[2], filename);

        // 2-3. 합친 경로로 이동
        if (rename(argv[1], dest_path) != 0) {
            perror("mv failed");
        }
    } 
    else {
        // --- [상황 B: 목적지가 파일이거나 없는 경우 (그냥 이름 변경)] ---
        // 예: mv old.txt new.txt
        
        if (rename(argv[1], argv[2]) != 0) {
            perror("mv failed");
        }
    }
}
