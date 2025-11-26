#include "../include/shell.h"

int main() {
	char buf[MAX_BUF];
	char *argv[MAX_ARG];
	int narg;

	while (1) {
		printf("Yum_Seoal_Shell>>");

		gets(buf);
		clearerr(stdin);

		narg = getargs(buf, argv);

		if (narg == 0) {
			continue;
		}

		check_exit(argv);

		execute_command(argv);
	}
	return 0;
}