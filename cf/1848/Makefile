CC     = gcc
CFLAGS = --std=gnu11
name   = main

.PHONY: default
default:
	@echo do nothing

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf *.o *.in.txt *.out.txt

.PHONY: new
new:
	cp ../../tpl/a.c $(name).c
