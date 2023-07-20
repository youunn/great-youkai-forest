CC     = gcc
CFLAGS = --std=gnu11

.PHONY: default
default:
	@echo do nothing

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf *.o *.ti *.to
