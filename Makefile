
TARGET = trex
SRC = main.c lr.c common.c matcher.c

all: $(TARGET)

clean: 
	-rm -f $(TARGET)

debug:
	gdbtui $(TARGET)

$(TARGET): $(SRC)
	gcc -ggdb -o $@ $^

.PHONY: all clean
