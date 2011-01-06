CSPEC = cspec
CSPEC_DIR = D:/Dev/cspec/
CC = gcc
CPP = c++

all: clean test
  
clean:
	
build_tests:
	$(CPP) RoutingTable.c -I $(CSPEC_DIR)src -I ../ -o ./objs.o
	$(CC) $(CSPEC_DIR)build/cspec.o RoutingTable.o -std=c99 -I $(CSPEC_DIR)src -I ../ -o ./test
		
parse_tests:
	$(CSPEC) < RoutingTable.spec > RoutingTable.c
		
test: parse_tests build_tests
	@echo
	@echo
	@echo
	@echo "--- STARTING TESTS ---"
	
	./test
	
	
