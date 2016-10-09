
# Requires 'moretutils', 'gcc', 'clang-format', 'gdbtui'

TARGET = trex
SRC = main.c lr.c common.c matcher.c

INSTALL_DST=/usr/bin/trex

all: $(TARGET)

clean: 
	-rm -f $(TARGET)

format: $(addsuffix .format, $(SRC))

debug:
	gdbtui $(TARGET)

install: $(TARGET)
	install $< $(INSTALL_DST)

uninstall:
	rm -f $(INSTALL_DST)

$(TARGET): $(SRC)
	gcc -o $@ $^

%.format: %
	clang-format $< | sponge $<
	

.PHONY: all clean format install uninstall
