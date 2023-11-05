CLANG_FORMAT = /usr/bin/clang-format-15
FORMAT_FLAGS = -Werror -i

STAGED_FILE_LIST := $(shell git diff --name-only --cached -- '*.h' '*.hpp' '*.c' '*.cpp')

.PHONY: pretty pretty_all tidy

help:
	@echo "make pretty -> prettier code"

pretty:
ifneq ($(STAGED_FILE_LIST),)
	@for file in ${STAGED_FILE_LIST}; do \
		${CLANG_FORMAT} ${FORMAT_FLAGS} $$file; \
	done
else
	@echo "No files ready for commit! To execute "make pretty", please stage the files."
endif

pretty_all:
	@find ./ -type f \( -name '*.c' -o -name '*.cpp' \) -exec ${CLANG_FORMAT} ${FLAGS} {} \;
