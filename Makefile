PROFILE ?= Debug

ifeq ($(OS),Windows_NT)
    MKDIR_CMD = if not exist "build" (mkdir build)
    RMDIR_CMD = if exist "build" (rmdir /s /q build)
    BINARY = ./build/$(PROFILE)/aoc_2023.exe
else
    MKDIR_CMD = mkdir -p build
    RMDIR_CMD = rm -rf build
    BINARY = ./build/$(PROFILE)/aoc_2023
endif

.PHONY: all setup build debug release run clean

all: setup build

setup:
	@$(MKDIR_CMD)
	@cd build && cmake -DCMAKE_BUILD_TYPE=$(PROFILE) ..

build:
	@cmake --build ./build --config $(PROFILE)

debug:
	@$(MAKE) all PROFILE=Debug

release:
	@$(MAKE) all PROFILE=Release

run:
	@$(BINARY)

clean:
	@$(RMDIR_CMD)
