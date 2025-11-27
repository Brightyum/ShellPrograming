/* src/core/executor.c */
#include "../../include/shell.h"

int handle_redirection(char **argv) {
    int i;
    int fd;

    for (i=0; argv[i] != NULL; i++) {
        if (strcmp(argv[i], "<") == 0) {
            argv[i] = NULL; // 명령어 끝
            if (argv[i+1] == NULL) {
                fprintf(stderr, "Error: No input file specified.\n");
                return -1;
            }
            fd = open(argv[i+1], O_RDONLY);
            if (fd < 0) {
                perror("Error opening input file");
                return -1;
            }
            dup2(fd, STDIN_FILENO); // 표준 입력을 파일로 리다이렉트
            close(fd);
        } else if (strcmp(argv[i], ">") == 0) {
            argv[i] = NULL;
            if (argv[i+1] == NULL) {
                fprintf(stderr, "Error: No output file specified.\n");
                return -1;
            }
            fd = open(argv[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0) {
                perror("Error opening output file");
                return -1;
            }
            dup2(fd, STDOUT_FILENO); // 표준 출력을 파일로 리다이렉트
            close(fd);
        }
    }
    return 0; // 성공적으로 리다이렉션 처리됨
}
void execute_command(char **argv) {
    pid_t pid;
    int background = 0; // 백그라운드 실행 여부 플래그
    int i = 0;
    int pipe_idx = -1;  // 파이프 기호 인덱스

    // 1. 백그라운드 기호(&) 확인 및 제거 (기존 로직 유지)
    while (argv[i] != NULL) {
        i++;
    }
    // 맨 마지막 인자가 & 라면
    if (i > 0 && strcmp(argv[i-1], "&") == 0) {
        background = 1;    // 백그라운드 모드 켜기
        argv[i-1] = NULL;  // & 기호는 명령어에서 삭제
        i--;               // 인자 개수 줄임
    }

    // 2. 파이프(|) 확인 로직 (새로 추가됨)
    for (int j = 0; argv[j] != NULL; j++) {
        if (strcmp(argv[j], "|") == 0) {
            pipe_idx = j;
            break;
        }
    }

    // ==========================================
    // CASE A: 파이프가 있는 경우 (|)
    // ==========================================
    if (pipe_idx != -1) {
        int fd[2];
        pid_t pid1, pid2;

        argv[pipe_idx] = NULL;       // 파이프 기호를 기준으로 명령 분리
        char **argv1 = argv;         // 앞쪽 명령
        char **argv2 = &argv[pipe_idx + 1]; // 뒤쪽 명령

        if (pipe(fd) < 0) {
            perror("pipe failed");
            return;
        }

        // 첫 번째 자식 (Write)
        pid1 = fork();
        if (pid1 == 0) {
            close(fd[0]);
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
            
            handle_redirection(argv1); // 재지향 처리
            execvp(argv1[0], argv1);
            perror("exec1 failed");
            exit(1);
        }

        // 두 번째 자식 (Read)
        pid2 = fork();
        if (pid2 == 0) {
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);

            handle_redirection(argv2); // 재지향 처리
            execvp(argv2[0], argv2);
            perror("exec2 failed");
            exit(1);
        }

        // 부모 프로세스
        close(fd[0]);
        close(fd[1]);

        if (background == 0) {
            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);
        } else {
             printf("[Background Pipeline Process IDs: %d, %d]\n", pid1, pid2);
        }
    }
    // ==========================================
    // CASE B: 파이프가 없는 일반 실행 (기존 로직 + 재지향 추가)
    // ==========================================
    else {
        pid = fork();
        
        if (pid == 0) {
            // [중요] 자식 프로세스에서 재지향 처리 함수 호출
            if (handle_redirection(argv) < 0) {
                exit(1); // 파일 열기 실패 시 종료
            }

            execvp(argv[0], argv);
            perror("exec failed");
            exit(1);
        } else if (pid > 0) {
            if (background == 0) {
                // 부모 프로세스
                wait(NULL); 
            } else {
                printf("[Background Process ID: %d]\n", pid);
            }
        } else {
            perror("fork failed");
        }
    }
}