CLANG_FORMAT = /usr/bin/clang-format-15
FLAGS        = -Werror -i

help:
	@echo "make lint -> run code formatter clang-format"

lint_staged:
	@git diff --name-only --cached -- '*.h' '*.hpp' '*.c' '*.cpp' | xargs -n1 ${CLANG_FORMAT} ${FLAGS}