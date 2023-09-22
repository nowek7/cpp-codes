BUILD_DIR=build
DATA_DIR=data

COMPARISON_CONTAINER_DIR=$(BUILD_DIR)/comparison_container
COMPARISON_MAP_DIR=$(BUILD_DIR)/comparison_map

ifeq ($(target), container)
	RUN_PROGRAM=$(COMPARISON_CONTAINER_DIR)/comparison_container
endif
ifeq ($(target), map)
	RUN_PROGRAM=$(COMPARISON_MAP_DIR)/comparison_map
endif

.PHONY: build
build:
	cmake -S . -B $(BUILD_DIR)
	@cmake --build $(BUILD_DIR)

run:
	@if [ ! -d data ]; then mkdir $(DATA_DIR); fi;

	$(RUN_PROGRAM)
	@mv *.csv data/

run_all:
	make run target=container
	make run target=map

clean:
	@rm -rf $(BUILD_DIR)/*
	@rm -rf $(DATA_DIR)