
# Requires 'moretutils', 'gcc', 'clang-format', 'gdbtui'

TARGET = trex
SRC = main.c lr.c common.c matcher.c ftree_matcher.c

DESTDIR=/usr/local/bin/trex

all: $(TARGET)

clean: 
	-rm -f $(TARGET)

format: $(addsuffix .format, $(SRC))

debug:
	gdbtui $(TARGET)

debug-lldb:
	lldb $(TARGET)

install: $(TARGET)
	install $< $(DESTDIR)

uninstall:
	rm -f $(DESTDIR)

$(TARGET): $(SRC)
	gcc -g -o $@ $^

%.format: %
	clang-format $< | sponge $<
	

.PHONY: all clean format install uninstall
