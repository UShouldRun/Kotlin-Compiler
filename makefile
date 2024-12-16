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
GEN_A_DIR  = $(LIBDIR)/gen_assembly
INTER_DIR  = $(LIBDIR)/intercode
HASH_DIR   = $(LIBDIR)/hashmap
LEXER_DIR  = $(LIBDIR)/lexer
PARSER_DIR = $(LIBDIR)/parser
TEST_DIR 	 = test
ZIP 			 = COMP_TP2_T01_G13.zip

# Include files
ARENA_INC  = $(ARENA_DIR)/include
AST_INC 	 = $(AST_DIR)/include
ERROR_INC  = $(ERROR_DIR)/include
GEN_A_INC  = $(GEN_A_DIR)/include
INTER_INC  = $(INTER_DIR)/include
HASH_INC 	 = $(HASH_DIR)/include
PARSER_INC = $(PARSER_DIR)/build/

# Source files
SRC 			 = $(wildcard ./src/*.c)
ARENA_SRC  = $(ARENA_DIR)/src/arena.c
AST_SRC 	 = $(AST_DIR)/src/ast.c
ERROR_SRC  = $(ERROR_DIR)/src/error.c
GEN_A_SRC  = $(GEN_A_DIR)/src/gen_assembly.c
INTER_SRC  = $(INTER_DIR)/src/intercode.c
HASH_SRC   = $(HASH_DIR)/src/hashmap.c
HASHT_SRC  = $(AST_DIR)/src/hashtable.c
LEXER_SRC  = $(LEXER_DIR)/src/lexer.x
PARSER_SRC = $(PARSER_DIR)/src/parser.y
SYMBOL_SRC = $(INTER_DIR)/src/symboltable.c

# Object files
ARENA_OBJ  = $(ARENA_DIR)/build/arena.o
AST_OBJ    = $(AST_DIR)/build/ast.o
ERROR_OBJ  = $(ERROR_DIR)/build/error.o
INTER_OBJ  = $(INTER_DIR)/build/intercode.o
GEN_A_OBJ  = $(GEN_A_DIR)/build/gen_assembly.o
HASH_OBJ   = $(HASH_DIR)/build/hashmap.o
HASHT_OBJ  = $(AST_DIR)/build/hashtable.o
LEXER_OBJ  = $(LEXER_DIR)/build/lexer.yy.c
PARSER_OBJ = $(PARSER_DIR)/build/parser.o
SYMBOL_OBJ = $(INTER_DIR)/build/symboltable.o

OBJ 			 = $(patsubst ./src/%.c, $(BUILDDIR)/%.o, $(SRC)) 

# Lib Files
ARENA_LIB  = $(ARENA_DIR)/build
AST_LIB 	 = $(AST_DIR)/build
ERROR_LIB  = $(ERROR_DIR)/build
GEN_A_LIB  = $(GEN_A_DIR)/build
INTER_LIB  = $(INTER_DIR)/build
HASH_LIB   = $(HASH_DIR)/build

# Dependencies
AST_DEP  	 = -I$(AST_INC) -I$(ARENA_INC) -I$(ERROR_INC) -I$(HASH_INC) -lhashtable -L$(AST_LIB) -larena -L$(ARENA_LIB) -lerror -L$(ERROR_LIB) -lhashmap -L$(HASH_LIB)
LEXER_DEP  = -I$(PARSER_DIR)/build/parser.tab.h
PARSER_DEP = -I$(PARSER_INC) -I$(AST_INC) -I$(ARENA_INC) -I$(ERROR_INC) -lhashtable -L$(AST_LIB) -last -L$(AST_LIB) -larena -L$(ARENA_LIB) -lerror -L$(ERROR_LIB) -lhashmap -L$(HASH_LIB)

# Executable
TARGET = kotlin
DEP 	 = $(PARSER_OBJ) $(LEXER_OBJ) -I$(GEN_A_INC) -I$(INTER_INC) -I$(PARSER_INC) -I$(AST_INC) -I$(ARENA_INC) -I$(ERROR_INC) -I$(HASH_INC) -lgenassembly -L$(GEN_A_LIB) -lintercode -lsymboltable -L$(INTER_LIB) -last -lhashtable -L$(AST_LIB) -larena -L$(ARENA_LIB) -lerror -L$(ERROR_LIB) -lhashmap -L$(HASH_LIB)

# Create necessary directories
DIRS = $(BINDIR) $(BUILDDIR) $(ERROR_DIR)/build $(ARENA_DIR)/build $(AST_DIR)/build $(LEXER_DIR)/build $(PARSER_DIR)/build $(INTER_DIR)/build $(GEN_A_DIR)/build

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

$(ZIP):
	@zip -r $@ .
	@echo "Zipped the directory to $@"

# Rule to build the final binary executable
$(TARGET): $(SRC) | error arena hashmap hashtable ast parser lexer symboltable intercode gen_assembly
	@$(CC) -o $(BINDIR)/$(TARGET) $< $(DEP)
	@echo "Built the target binary $(BINDIR)/$(TARGET)"

# Rule to compile source files
$(BUILDDIR)/$(TARGET).o: $(SRC) | error arena hashmap hashtable ast parser lexer symboltable intercode gen_assembly
	@$(CC) $(DEBUG) -o $@ $< $(DEP)
	@echo "Compiled $@"

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

$(GEN_A_DIR)/build/libgenassembly.a: $(GEN_A_SRC)
	@$(CC) $(CFLAGS) $(DEBUG) -o $(GEN_A_OBJ) -c $< -I$(GEN_A_INC) -I$(INTER_INC) -I$(AST_INC) -I$(ARENA_INC) -I$(ERROR_INC) -I$(HASH_INC)
	@$(LIB_CREATE) $@ $(GEN_A_OBJ)
	@echo "Compiled MIPS Generator"

$(INTER_DIR)/build/libintercode.a: $(INTER_SRC)
	@$(CC) $(CFLAGS) $(DEBUG) -o $(INTER_OBJ) -c $< -I$(INTER_INC) -I$(AST_INC) -I$(ARENA_INC) -I$(ERROR_INC) -I$(HASH_INC)
	@$(LIB_CREATE) $@ $(INTER_OBJ)
	@echo "Compiled InterCode"

$(HASH_DIR)/build/libhashmap.a: $(HASH_SRC)
	@$(CC) $(CFLAGS) $(DEBUG) -o $(HASH_OBJ) -c $< -I$(HASH_INC)
	@$(LIB_CREATE) $@ $(HASH_OBJ)
	@echo "Compiled HashMap"

$(AST_DIR)/build/libhashtable.a: $(HASHT_SRC)
	@$(CC) $(CFLAGS) $(DEBUG) -o $(HASHT_OBJ) -c $< -I$(AST_INC) -I$(ARENA_INC) -I$(ERROR_INC) -I$(HASH_INC)
	@$(LIB_CREATE) $@ $(HASHT_OBJ)
	@echo "Compiled HashTable"

# Rule to compile lexer
$(LEXER_DIR)/build/lexer.yy.c: $(LEXER_SRC) | $(LEXER_DIR)/build
	@$(FLEX) $(FLEX_FLAGS) -o $@ $<
	@echo "Compiled Lexer"

# Rule to compile parser
$(PARSER_DIR)/build/parser.tab.c: $(PARSER_SRC)
	@$(BISON) $(BISON_FLAGS) -o $@ $<
	@echo "Generated Parser C file"

$(PARSER_DIR)/build/parser.o: $(PARSER_DIR)/build/parser.tab.c
	@$(CC) -Wall $(DEBUG) -o $@ -c $< $(PARSER_DEP)
	@echo "Compiled Parser"

$(INTER_DIR)/build/libsymboltable.a: $(SYMBOL_SRC)
	@$(CC) $(CFLAGS) $(DEBUG) -o $(SYMBOL_OBJ) -c $< -I$(INTER_INC) -I$(AST_INC) -I$(ARENA_INC) -I$(ERROR_INC) -I$(HASH_INC)
	@$(LIB_CREATE) $@ $(SYMBOL_OBJ)
	@echo "Compiled SymbolTable"

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
	@rm -f $(BINDIR)/* $(BUILDDIR)/*.o $(ARENA_DIR)/build/* $(AST_DIR)/build/* $(ERROR_DIR)/build/* $(GEN_A_DIR)/build/* $(INTER_DIR)/build/* $(HASH_DIR)/build/* $(LEXER_DIR)/build/*.c $(PARSER_DIR)/build/* $(TARGET)
	@if ls *.zip 1> /dev/null 2>&1; then \
		rm -f *.zip; \
	fi
	@echo "Cleaned all build directories and zip files"

clean_test:
	@rm -f $(TEST_DIR)/arena/tarena.o $(TEST_DIR)/arena/tarena

# Phony targets for testing individual components
.PHONY: all install root-install build clean clean_test arena ast error gen_assembly intercode lexer parser symboltable tarena run-tarena

arena:  		  $(ARENA_DIR)/build/libarena.a
ast:	  		  $(AST_DIR)/build/libast.a
error:  		  $(ERROR_DIR)/build/liberror.a
gen_assembly: $(GEN_A_DIR)/build/libgenassembly.a
intercode:	  $(INTER_DIR)/build/libintercode.a
hashmap:      $(HASH_DIR)/build/libhashmap.a
hashtable:    $(AST_DIR)/build/libhashtable.a
lexer:  		  $(LEXER_DIR)/build/lexer.yy.c
parser: 		  $(PARSER_DIR)/build/parser.o
parser_tab:   $(PARSER_DIR)/build/parser.tab.c
symboltable:  $(INTER_DIR)/build/libsymboltable.a
tarena: 		  $(TEST_DIR)/arena/tarena

# Default
all: 				  build
build:			  $(BUILDDIR)/$(TARGET).o
install:		  $(TARGET)
dirs: 			  $(DIRS)
zip:          $(ZIP)
