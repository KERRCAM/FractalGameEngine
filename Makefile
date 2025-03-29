BUILD_DIR = testBuild/debug
CC = gcc
GAME_DIR = src
GAME_FILES = $(wildcard $(GAME_DIR)/*.c)
EDITOR_DIR = editor
EDITOR_FILES = $(wildcard $(EDITOR_DIR)/*.c)
OBJ_NAME = game
EDIT_NAME = editor
INCLUDE_PATHS = -Iinclude
LIBRARY_PATHS = -L/opt/homebrew/Cellar/sdl2/2.30.12/lib/ -L/opt/homebrew/Cellar/sdl2_image/2.8.4/lib/
COMPILER_FLAGS = -Wall -std=c99
LINKER_FLAGS = -lsdl2

build:
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(GAME_FILES) editor/levels.c editor/sectors.c editor/walls.c -o $(BUILD_DIR)/$(OBJ_NAME)

run:
	./testBuild/debug/game

clean:
	rm testBuild/debug/game

be:
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(EDITOR_FILES) -o $(BUILD_DIR)/$(EDIT_NAME)

re:
	./testBuild/debug/editor