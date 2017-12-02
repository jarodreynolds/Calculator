CC=gcc
CFLAGS=-g -Wall -std=c99 -Iinclude
LIBS= -lm
TARGET=calc

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
_DEPS = calc.h help.h  
_OBJS = calc.o main.o help.o helpOrQuit.o isIllegal.o illegal.o divideZero.o

DEPS = $(patsubst %,$(INC_DIR)/%,$(_DEPS))
OBJS = $(patsubst %,$(OBJ_DIR)/%,$(_OBJS))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

.PHONY: clean
clean:
	$(RM) $(OBJS) $(TARGET)

