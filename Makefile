CC=gcc

SRC=$(wildcard *.c)

OUT=emulator

all:
	$(CC) $(SRC) -o $(OUT)