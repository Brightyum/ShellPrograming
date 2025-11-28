# Makefile

# 컴파일러 설정
CC = gcc
CFLAGS = -Wall -g -Iinclude 
# -Iinclude: 헤더 파일을 include 폴더에서 찾으라는 의미

# 디렉토리 설정
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# 실행 파일 이름
TARGET = $(BINDIR)/myshell

# 소스 파일 목록 (와일드카드 사용)
SRCS = $(SRCDIR)/main.c \
       $(SRCDIR)/core/parser.c \
       $(SRCDIR)/core/executor.c \
       $(SRCDIR)/builtins/exit.c \
	   $(SRCDIR)/core/signal.c\
	   $(SRCDIR)/builtins/cd.c\
	   $(SRCDIR)/commands/cmd_ls.c\
	   $(SRCDIR)/commands/cmd_pwd.c\
	   $(SRCDIR)/commands/cmd_mkdir.c\
	   $(SRCDIR)/commands/cmd_rmdir.c\
	   $(SRCDIR)/commands/cmd_ln.c\
	   $(SRCDIR)/commands/cmd_cp.c\
	   $(SRCDIR)/commands/cmd_rm.c\
	   $(SRCDIR)/commands/cmd_mv.c\
	   $(SRCDIR)/commands/cmd_cat.c\
	   $(SRCDIR)/commands/cmd_grep.c

# 오브젝트 파일 목록 자동 생성 (.c -> .o)
# 예: src/main.c -> obj/main.o
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

# 기본 타겟
all: directories $(TARGET)

# 디렉토리 생성 (bin, obj 폴더가 없으면 에러나므로)
directories:
	@mkdir -p $(BINDIR)
	@mkdir -p $(OBJDIR)/core
	@mkdir -p $(OBJDIR)/builtins

# 실행 파일 링크
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# 각 소스 파일을 오브젝트 파일로 컴파일
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# 정리 (make clean)
clean:
	rm -rf $(OBJDIR) $(BINDIR)