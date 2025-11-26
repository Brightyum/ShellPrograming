#include "../include/shell.h"

int main() {
	char buf[MAX_BUF];
	char *argv[MAX_ARG];
	int narg;

	while (1) {
		printf("Yum_Seoal_Shell>>");

		//stdin이 닫히거나 에러가 나면(Ctrl+D 등) 루프 종료
		if(fgets(buf, sizeof(buf), stdin) == NULL) {
			break;
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