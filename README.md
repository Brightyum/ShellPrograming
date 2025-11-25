# ShellPrograming
리눅스 환경에서 간단한 쉘 프로그램 구현

```text
프로젝트/
├── bin/                 # 컴파일된 실행 파일이 저장될 곳
├── obj/                 # .o (목적 파일)들이 저장될 곳 (Makefile 관리용)
├── include/             # 헤더 파일 (.h) 모음
│   ├── shell.h          # 전역 구조체, 상수, 함수 프로토타입 정의
│   └── commands.h       # ls, cp 등 명령어 함수들의 프로토타입 정의
├── src/                 # 소스 코드 (.c) 모음
│   ├── main.c           # 메인 루프 (프롬프트 출력 -> 입력 대기 -> 실행)
│   ├── core/            # 쉘의 핵심 기능 구현
│   │   ├── parser.c     # 입력 문자열 파싱 (파이프, 리다이렉션, 백그라운드 기호 처리)
│   │   ├── executor.c   # 실제 명령 실행 (fork, exec, pipe, redirection 처리)
│   │   └── signal.c     # 시그널 핸들러 (SIGINT, SIGQUIT 등 처리)
│   ├── builtins/        # 쉘 내장 명령어 (쉘 상태를 변경해야 하는 것들)
│   │   ├── cd.c         # 요구사항 5번 (cd)
│   │   └── exit.c       # 요구사항 1번 (exit)
│   └── commands/        # 팀원들이 나누어 구현할 일반 명령어들 - 요구사항 5번
│       ├── cmd_ls.c
│       ├── cmd_cp.c
│       ├── cmd_grep.c
│       ├── cmd_cat.c
│       └── ... (나머지 명령어들 파일 분리)
├── Makefile             # 빌드 자동화 스크립트 (필수)
└── README.md            # 프로젝트 설명 및 팀원 역할 분담 명시
