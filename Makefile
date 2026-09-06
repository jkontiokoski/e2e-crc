CC      := gcc
AR      := ar
CFLAGS  := -Wall -Wextra -Wpedantic -std=c11 -O2 -Isrc -Itests/unity
ARFLAGS := rcs

LIB     := libcrc8.a
EXAMPLE := crc8_example
TEST	:= test_runner

SRC 	:= src
LIB_SRC := $(SRC)/crc8.c
LIB_OBJ := $(LIB_SRC:.c=.o)

EXAMPLE_SRC := example/example.c
EXAMPLE_OBJ := $(EXAMPLE_SRC:.c=.o)

TEST_SRC := tests/test_crc8.c tests/unity/unity.c
TEST_OBJ := $(TEST_SRC:.c=.o)

.PHONY: all lib example clean

all: lib

lib: $(LIB)

$(LIB): $(LIB_OBJ)
	$(AR) $(ARFLAGS) $@ $^

example: $(EXAMPLE)

$(EXAMPLE): $(EXAMPLE_OBJ) $(LIB)
	$(CC) $(CFLAGS) -o $@ $(EXAMPLE_OBJ) -L. -lcrc8

test: $(TEST)
	./$(TEST) -v

$(TEST): $(TEST_OBJ) $(LIB)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJ) -L. -lcrc8

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(LIB_OBJ) $(EXAMPLE_OBJ) $(TEST_OBJ) \
		  $(TEST) $(LIB) $(EXAMPLE)
