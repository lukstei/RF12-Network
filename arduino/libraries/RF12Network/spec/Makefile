CSPEC = cspec
CSPEC_DIR = D:/Dev/cspec/
CC = gcc

all: clean test
  
clean:
	
build_tests:
	$(CC) $(CSPEC_DIR)build/cspec.o test.c -std=c99 -I $(CSPEC_DIR)src -o ./test
		
parse_tests:
	$(CSPEC) < test.spec > test.c
		
test: parse_tests build_tests
	@echo
	@echo
	@echo
	@echo "--- STARTING TESTS ---"
	
	./test
	
	
