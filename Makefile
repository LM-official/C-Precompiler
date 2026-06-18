# Makefile — cpre (C precompiler)
# Sistemi Operativi 2 — Homework 1

CC      := gcc
CFLAGS  := -Wall -std=c11
SRCDIR  := src
TESTDIR := tests
TARGET  := cpre
SRC     := $(SRCDIR)/main.c $(SRCDIR)/functions.c
OBJ     := $(SRC:.c=.o)
HDR     := $(SRCDIR)/functions.h

.PHONY: all run test clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

$(SRCDIR)/%.o: $(SRCDIR)/%.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

# Runs a demo on the first test file.
# The tests run from inside tests/ because the #include "..." directives are
# resolved relative to the current working directory.
run: $(TARGET)
	cd $(TESTDIR) && ../$(TARGET) --in=test1.c -v

# Runs the demo on all the test files
test: $(TARGET)
	@echo "===== test1.c ====="
	cd $(TESTDIR) && ../$(TARGET) --in=test1.c -v
	@echo
	@echo "===== test2.c ====="
	cd $(TESTDIR) && ../$(TARGET) --in=test2.c -v

# Removes every generated file (build artifacts and runtime output)
clean:
	sh clean.sh