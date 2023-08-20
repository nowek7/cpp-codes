help:
	@echo "make lint -> run code formatter clang-format"

lint:
	@find ./ -type f -name "*.*pp" -exec clang-format-12 -i {} \;