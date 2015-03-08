NAME= bfl
CFLAGS = -Wall -Wextra -Iincludes $(OPTFLAGS)

SOURCES= $(wildcard src/*.c)
OBJECTS= $(patsubst src/%.c,bin/%.o,$(SOURCES))

TARGET = bin/$(NAME)

bin/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)
	help2man $(TARGET) doc/$(NAME).1

install:
	install $(TARGET) /usr/bin/
	install doc/$(NAME).1 /usr/share/man/man1/

clean: 
	rm -rf bin/*.o


