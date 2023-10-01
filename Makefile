CC := gcc
CFLAGS := -std=c99 -Wall -O3

FILES := $(wildcard *.c)
HEADERS := $(wildcard *.h)
OBJECTS := $(addprefix bin/,$(notdir $(FILES:.c=.o)))

VPATH := src

all: bin ring

ring: $(OBJECTS)
	$(CC) -o ring $(OBJECTS)

bin/%.o: %.c | $(HEADERS)
	$(CC) $(CFLAGS) -Isrc -c $< -o $@

bin:
	mkdir -p bin

clean:
	rm -rf bin/* ring

