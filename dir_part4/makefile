CC = gcc
CFLAGS = -Wall -std=c99
TARGET = esub
SOURCES = esub.c
OBJECTS = $(SOURCES:.c=.o)
TESTS = test1 test2 test3 test4 test5
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
%.o: %.c
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f $(OBJECTS) $(TARGET)

test1:
	@echo "Running test1..."
	@output=$$(echo "this is a foo test foo" | ./esub "foo" "bar" "this is a foo test foo"); \
	expected="this is a bar test foo"; \
	if [ "$$output" = "$$expected" ]; then \
		echo "Test 1 passed"; \
	else \
		echo "Test 1 failed: expected '$$expected', got '$$output'"; \
	fi
test2:
	@echo "Running test2..."
	@output=$$(echo "no match here" | ./esub "foo" "bar" "no match here"); \
	expected="no match here"; \
	if [ "$$output" = "$$expected" ]; then \
		echo "Test 2 passed"; \
	else \
		echo "Test 2 failed: expected '$$expected', got '$$output'"; \
	fi
test3:
	@echo "Running test3..."
	@output=$$(echo "apple123 banana456" | ./esub "[a-z]+[0-9]+" "fruit" "apple123 banana456"); \
	expected="fruit banana456"; \
	if [ "$$output" = "$$expected" ]; then \
		echo "Test 3 passed"; \
	else \
		echo "Test 3 failed: expected '$$expected', got '$$output'"; \
	fi
test4:
	@echo "Running test4..."
	@output=$$(echo "foo bar" | ./esub "foo" "" "foo bar"); \
	expected=" bar"; \
	if [ "$$output" = "$$expected" ]; then \
		echo "Test 4 passed"; \
	else \
		echo "Test 4 failed: expected '$$expected', got '$$output'"; \
	fi
test5:
	@echo "Running test5..."
	@output=$$(echo "this is a test" | ./esub "test" "example" "this is a test"); \
	expected="this is a example"; \
	if [ "$$output" = "$$expected" ]; then \
		echo "Test 5 passed"; \
	else \
		echo "Test 5 failed: expected '$$expected', got '$$output'"; \
	fi
test: $(TESTS)
rebuild: clean $(TARGET)

.PHONY: clean $(TESTS) test rebuild
