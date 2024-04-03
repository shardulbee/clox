# Specify the compiler
CC=clang

# Specify the output name
OUTPUT=clox

# List of source files
SOURCES=lexer.c token.c parser.c linked_list.c
TEST_SOURCES=test_lexer.c

all:
	$(CC) $(SOURCES) main.c -o $(OUTPUT)

run: all
	./$(OUTPUT)

test: $(TEST_SOURCES)
	$(CC) $(SOURCES) $(TEST_SOURCES) -o test_lexer
	./test_lexer
