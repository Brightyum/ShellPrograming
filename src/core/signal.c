#include "../../include/shell.h"
#include <signal.h>
#include <stdio.h>

//Ctrl-C (SIGUNT)가 발생했을 때 호출될 함수
void handle_sigint(int signo){
    printf("\n");
    printf("Yum_Seoal_Shell>>");
    fflush(stdout); //버퍼를 바꿔서 즉시 출력되게
}

// Ctrl-Z (SIGQUIT)가 발생했을 때 호출될 함수
void handle_sigquit(int signo) {
    printf("\n");
    printf("Yum_Seoal_Shell>>");
    fflush(stdout);
}

void setup_signals() {
    // SIGINT (Ctrl-C)가 오면 handle_sigint 실행
    signal(SIGINT, handle_sigint);
    
    // SIGQUIT (Ctrl-\ 또는 Ctrl-Z)가 오면 handle_sigquit 실행
    signal(SIGQUIT, handle_sigquit); 
}