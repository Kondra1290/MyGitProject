LIBRARY = libprotect.so
TEST = test_protect
SRC_LIB = libprotect.c
SRC_TEST = test_protect.c
CC = cc
CFLAGS_LIB = -fPIC
CFLAGS_TEST = 
LDFLAGS = -shared
.PHONY: all clean run
all: $(LIBRARY) $(TEST)
$(LIBRARY): $(SRC_LIB)
	$(CC) $(LDFLAGS) $(CFLAGS_LIB) -o $@ $^ -ldl
$(TEST): $(SRC_TEST)
	$(CC) $(CFLAGS_TEST) -o $@ $^
run: all
	LD_PRELOAD=./$(LIBRARY) ./$(TEST)
clean:
	rm -f $(LIBRARY) $(TEST) PROTECT_me.txt
