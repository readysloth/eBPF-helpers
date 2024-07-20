.PHONY: clean, mrproper

PYTHON ?= python3
CC = gcc
CFLAGS = -Og -g -Wall -I ..

all: unit-tests

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.gen.c:
	$(PYTHON) -m cogapp $(shell echo $@ | sed s/.gen//) > $@

unit-tests: unit-tests.gen.o
	$(CC) $(CFLAGS) -o $@ $+

clean:
	rm -f *.o core.*

mrproper: clean
	rm -f unit-tests
