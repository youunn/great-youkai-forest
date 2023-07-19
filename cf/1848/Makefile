CC     = gcc
CFLAGS = --std=gnu11

.PHONY: all
all: clean

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf *.o *.ti *.to
