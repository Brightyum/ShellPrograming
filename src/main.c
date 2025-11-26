#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int getargs(char *cmd, char **argv);

int main() {
	char buf[256]; /* 사용자 입력 */
	char *argv[50]; /* 명령어 */
	int narg;
	pid_t pid;
	
	while (1) {
		printf("Yum_Seoal_Shell>>");
		scanf("%s", buf);
		clearerr(stdin);
		narg = getargs(buf, argv);

		if (narg > 0 && strcmp(argv[0], "exit") == 0) {
            printf("Shell terminating...\n");
            exit(0); // 부모 프로세스 종료
        }

		pid = fork();
		if (pid == 0) {
			execvp(argv[0], argv);
		} else if (pid > 0) {
			wait((int)0);
		} else {
			perror("fork failed");
		}
	}
}

int getargs(char *cmd, char **argv) {
	int narg=0;

	while (*cmd) {
		if (*cmd==' ' || *cmd == '\t') {
			*cmd++ = '\0';
		} else {
			argv[narg++] = cmd++;
			while (*cmd != '\0' && *cmd != ' ' && *cmd != '\t') {
				cmd++;
			}
			
		}
	}
	argv[narg] = NULL;
	return narg;
}
