
# Requires 'moretutils', 'gcc', 'clang-format', 'gdbtui'

TARGET = trex
SRC = main.c lr.c common.c matcher.c

all: $(TARGET)

clean: 
	-rm -f $(TARGET)

format: $(addsuffix .format, $(SRC))

debug:
	gdbtui $(TARGET)

$(TARGET): $(SRC)
	gcc -ggdb -o $@ $^

%.format: %
	clang-format $< | sponge $<
	

.PHONY: all clean format
