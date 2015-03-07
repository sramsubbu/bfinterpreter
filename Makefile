NAME= bfl
CFLAGS = -Wall -Wextra -Iincludes $(OPTFLAGS)

SOURCES= $(wildcard src/*.c)
OBJECTS= $(patsubst src/%.c,bin/%.o,$(SOURCES))

TARGET = bin/$(NAME)

bin/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)


clean: 
	rm -rf bin/*
	rm -rf *.out */*.out


