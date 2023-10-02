CLANG_FORMAT = /usr/bin/clang-format-15
FLAGS        = -Werror -i

STAGED_FILE_LIST := $(shell git diff --name-only --cached -- '*.h' '*.hpp' '*.c' '*.cpp')
ALL_CXX_FILES    := $(shell find ./ -type f -regex '.*\.\(hpp\|h\)')
ALL_HXX_FILES    := $(shell find ./ -type f -regex '.*\.\(hpp\|h\)')

.PHONY: pretty

help:
	@echo "make pretty -> prettier code"

pretty:
ifneq ($(STAGED_FILE_LIST),)
	@for file in ${STAGED_FILE_LIST}; do \
		${CLANG_FORMAT} ${FLAGS} $$file; \
	done
else
	@echo "No files ready for commit! To execute "make pretty", please stage the files."
endif

pretty_all:
	@for file in ${ALL_CXX_FILES}; do \
		${CLANG_FORMAT} ${FLAGS} $$file; \
	done

	@for file in ${ALL_HXX_FILES}; do \
		${CLANG_FORMAT} ${FLAGS} $$file; \
	done