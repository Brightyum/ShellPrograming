#include "../include/shell.h"
#include <string.h>
#include <stdio.h>

int main() {
	char buf[MAX_BUF];
	char *argv[MAX_ARG];
	int narg;

	//프로그램 시작 시 시그널 핸들러 등록
	setup_signals();

	while (1) {
		printf("Yum_Seoal_Shell>>");

		//stdin이 닫히거나 에러가 나면(Ctrl+D 등) 루프 종료
		if(fgets(buf, sizeof(buf), stdin) == NULL) {
			//Ctrl-D (EOF) 입력 시 루프 종료하고 쉘 끄기
			if (feof(stdin)) {
                printf("\n"); // 줄바꿈 후 종료
			break;
			}

			// 만약 시그널(Ctrl-C) 때문에 fgets가 끊긴 거라면,
            clearerr(stdin); // 에러 상태 풀고
            continue;
		}
		
		if (buf[strlen(buf) - 1] == '\n') {
            buf[strlen(buf) - 1] = '\0';
        }

		// 엔터만 쳤을 때 재입력 받기
        if (strlen(buf) == 0) continue;

		narg = getargs(buf, argv);

		if (narg == 0) {
			continue;
		}

		check_exit(argv);

		execute_command(argv);
	}
	return 0;
}