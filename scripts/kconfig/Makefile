# Basic makefile for smoke-testing.
#
CFLAGS=-DKCONFIG_AUTOCONFIG=NULL -Wall -Wmissing-prototypes -Wstrict-prototypes

conf: conf.o parser.tab.o lexer.lex.o confdata.o expr.o preprocess.o symbol.o util.o
	$(CC) -o $@ $^

parser.tab.c: parser.y
	bison -l -t -d -o parser.tab.c parser.y
        #byacc -l -t -d -o parser.tab.c parser.y

lexer.lex.c: lexer.l parser.tab.c # For parsr.tab.h.
	flex -f -L -o lexer.lex.c lexer.l
        #reflex -L -o lexer.lex.c lexer.l

.PHONY: test
test: conf
	cd $(CURDIR)/../.. && python3 -B -m pytest $(CURDIR)/tests

.PHONY: clean
clean:
	rm -f conf *.o *.tab.[hc] *.lex.c
	rm -rf tests/.cache
