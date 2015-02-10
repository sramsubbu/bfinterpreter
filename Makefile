NAME= bfinterpreter
CFLAGS = -Wall -Wextra -rdynamic $(OPTFLAGS)

SOURCES= $(wildcard src/*.c)
OBJECTS= $(patsubst src/%.c,bin/%.o,$(SOURCES))

TARGET = bin/$(NAME)

bin/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $<


clean: 
	rm -rf bin/*


