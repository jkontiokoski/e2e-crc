# Compiler and tools
CC      := gcc
AR      := ar
CFLAGS  := -Wall -Wextra -Wpedantic -std=c11 -O2
ARFLAGS := rcs

# Targets
LIB     := libcrc8.a
APP     := example

# Sources
SRC 	:= src
LIB_SRC := $(SRC)/crc8.c
LIB_OBJ := $(LIB_SRC:.c=.o)

APP_SRC := $(SRC)/example.c
APP_OBJ := $(APP_SRC:.c=.o)

.PHONY: all lib app clean

# Default target
all: lib

# Build static library
lib: $(LIB) OBJ_CLEAN

$(LIB): $(LIB_OBJ)
	$(AR) $(ARFLAGS) $@ $^

# Build example application
app: $(APP) OBJ_CLEAN

$(APP): $(APP_OBJ) $(LIB)
	$(CC) $(CFLAGS) -o $@ $(APP_OBJ) -L. -lcrc8

# Compilation rule
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

OBJ_CLEAN:
	rm -f *.o $(LIB_OBJ) $(APP_OBJ) 

clean: OBJ_CLEAN
	rm -f $(LIB) $(APP)
