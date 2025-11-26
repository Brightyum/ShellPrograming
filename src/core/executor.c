/* src/core/executor.c */
#include "../../include/shell.h"
#include <string.h>

void execute_command(char **argv) {
    pid_t pid;
    int background =0; //백그라운드 실행 여부 플래그
    int i = 0;

    //1. 내장 명령어 처리
    if(strcmp(argv[0], "exit")==0){
        printf("Shell termination...\n");
        exit(0);
    }

    //2. 백그라운드 기호(&) 확인 로직
    while(argv[i]!=NULL){
        i++;
    }

    //맨 마지막 인자가 & 라면
    if(i>0 && strcmp(argv[i-1],"&")==0){
        background = 1;     //백그라운드 모드 켜기
        argv[i-1]=NULL;     //& 기호는 명령어에서 삭제(execvp에 전달하면 안됨)
    }

    //3 프로세스 생성 및 실행
    pid = fork();
    
    if (pid == 0) {
        // 자식 프로세스
        execvp(argv[0], argv);
        // execvp 실패 시
        perror("exec failed");
        exit(1);
    } else if (pid > 0) {
        if(background==0){
        // 부모 프로세스
        wait(NULL); // wait((int)0) 대신 표준인 NULL 사용 권장
        }else{
            printf("[Background Process ID: %d]\n", pid);
        }
    } else {
        perror("fork failed");
    }
}