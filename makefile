# Compiler
CC 				 = gcc
LIB_CREATE = ar rcs
DEBUG			?=

# Directories
BINDIR 		 = ./bin
BUILDDIR 	 = ./build
LIBDIR  	 = ./lib
ARENA_DIR  = $(LIBDIR)/arena
AST_DIR 	 = $(LIBDIR)/ast
ERROR_DIR  = $(LIBDIR)/error
LEXER_DIR  = $(LIBDIR)/lexer
PARSER_DIR = $(LIBDIR)/parser
TEST_DIR 	 = test

# Include files
ARENA_INC  = $(ARENA_DIR)/include
AST_INC 	 = $(AST_DIR)/include
ERROR_INC  = $(ERROR_DIR)/include
PARSER_INC = $(PARSER_DIR)/include

# Source files
SRC 			 = $(wildcard ./src/*.c)
ARENA_SRC  = $(ARENA_DIR)/src/arena.c
AST_SRC 	 = $(AST_DIR)/src/ast.c
ERROR_SRC  = $(ERROR_DIR)/src/error.c
LEXER_SRC  = $(LEXER_DIR)/src/lexer.x
PARSER_SRC = $(PARSER_DIR)/src/parser.y

# Object files
OBJ 			 = $(patsubst ./src/%.c, $(BUILDDIR)/%.o, $(SRC)) 
ARENA_OBJ  = $(ARENA_DIR)/build/arena.o
AST_OBJ    = $(AST_DIR)/build/ast.o
ERROR_OBJ  = $(ERROR_DIR)/build/error.o
LEXER_OBJ  = $(LEXER_DIR)/build/lexer.o
PARSER_OBJ = $(PARSER_DIR)/build/parser.o

# Lib Files
ARENA_LIB  = $(ARENA_DIR)/build
AST_LIB 	 = $(AST_DIR)/build
ERROR_LIB  = $(ERROR_DIR)/build

# Dependencies
AST_DEP  	 = -I$(AST_INC) -I$(ARENA_INC) -I$(ERROR_INC) -larena -L$(ARENA_LIB) -lerror -L$(ERROR_LIB)
PARSER_DEP = -I$(PARSER_INC) -I$(AST_INC) -I$(ARENA_INC) -I$(ERROR_INC) -last -L$(AST_LIB) -larena -L$(ARENA_LIB) -lerror -L$(ERROR_LIB)

# Executable
TARGET = $(BINDIR)/kotlin

# Create necessary directories
DIRS = $(BINDIR) $(BUILDDIR) $(ERROR_DIR)/build $(ARENA_DIR)/build $(AST_DIR)/build $(LEXER_DIR)/build $(PARSER_DIR)/build

# Compiler flags
CFLAGS = -Wall -Werror -Wpedantic

# Bison and Flex commands
BISON = bison -d
FLEX  = flex

# Flags
FLEX_FLAGS 	?=
BISON_FLAGS ?=

VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes
VFLAG 	:= 0

# Default target
all: $(TARGET)

# Rule to build the target
$(TARGET): $(OBJ) $(PARSER_OBJ) $(LEXER_OBJ) $(AST_LIB) $(ARENA_LIB) $(ERROR_LIB)
	@$(CC) -o $@ $^

# Rule to compile source files
$(BUILDDIR)/%.o: ./src/%.c | $(BUILDDIR)
	@$(CC) $(CFLAGS) $(DEBUG) -c $< -o $@
	@echo "Compiled main src file"

$(ARENA_DIR)/build/libarena.a: $(ARENA_SRC)
	@$(CC) $(CFLAGS) $(DEBUG) -o $(ARENA_OBJ) -c $< -I$(ARENA_INC)
	@$(LIB_CREATE) $@ $(ARENA_OBJ)
	@echo "Compiled Arena"

$(AST_DIR)/build/libast.a: $(AST_SRC)
	@$(CC) $(CFLAGS) $(DEBUG) -o $(AST_OBJ) -c $< $(AST_DEP)
	@$(LIB_CREATE) $@ $(AST_OBJ)
	@echo "Compiled AST"

$(ERROR_DIR)/build/liberror.a: $(ERROR_SRC)
	@$(CC) $(CFLAGS) $(DEBUG) -o $(ERROR_OBJ) -c $< -I$(ERROR_INC)
	@$(LIB_CREATE) $@ $(ERROR_OBJ)
	@echo "Compiled Error"

# Rule to compile lexer
$(LEXER_DIR)/build/lexer.yy.c: $(LEXER_SRC) | $(LEXER_DIR)/build
	@$(FLEX) $(FLEX_FLAGS) -o $@ $<
	@echo "Compiled Lexer"

# Rule to compile parser
$(PARSER_DIR)/build/parser.tab.c: $(PARSER_SRC)
	@$(BISON) $(BISON_FLAGS) -o $@ $<
	@echo "Generated Parser C file"

$(PARSER_DIR)/build/parser.o: $(PARSER_DIR)/build/parser.tab.c
	@$(CC) $(CFLAGS) $(DEBUG) -o $@ -c $< $(PARSER_DEP)
	@echo "Compiled Parser"

$(TEST_DIR)/arena/tarena.o: $(TEST_DIR)/arena/tarena.c
	@$(CC) $(CFLAGS) $(DEBUG) -o $@ -c $< -I$(ARENA_DIR)/include -L$(ARENA_DIR)/build -larena
	@echo "Compiled Arena Object"

$(TEST_DIR)/arena/tarena: $(TEST_DIR)/arena/tarena.o
	@$(CC) $(CFLAGS) -o $@ $< -L$(ARENA_DIR)/build -larena
	@echo "Linked Arena Test Executable"

run-tarena: $(TEST_DIR)/arena/tarena
	@chmod +x $<
	@if [ "$(VFLAG)" = "1" ]; then \
		$(VALGRIND) ./$<; \
	else \
		./$<; \
	fi

# Rule to create directories
$(DIRS):
	@mkdir -p $@

# Clean rule
clean:
	@rm -f $(BUILDDIR)/*.o $(ARENA_DIR)/build/* $(AST_DIR)/build/* $(ERROR_DIR)/build/* $(LEXER_DIR)/build/*.c $(PARSER_DIR)/build/* $(TARGET)
	@echo "Cleaned all build directories"

clean_test:
	@rm -f $(TEST_DIR)/arena/tarena.o $(TEST_DIR)/arena/tarena

# Phony targets for testing individual components
.PHONY: all clean clean_test arena ast error lexer parser tarena run-tarena

arena:  $(ARENA_DIR)/build/libarena.a
ast:	  $(AST_DIR)/build/libast.a
error:  $(ERROR_DIR)/build/liberror.a
lexer:  $(LEXER_DIR)/build/lexer.yy.c
parser: $(PARSER_DIR)/build/parser.o
tarena: $(TEST_DIR)/arena/tarena
