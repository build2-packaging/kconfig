# Basic makefile for smoke-testing.
#
CFLAGS=-DKCONFIG_AUTOCONFIG=NULL -Wall -Wmissing-prototypes -Wstrict-prototypes

conf: conf.o parser.tab.o lexer.lex.o confdata.o expr.o preprocess.o symbol.o util.o
	$(CC) -o $@ $^

parser.tab.c: parser.y
	bison -oparser.tab.c -d -t -l parser.y

lexer.lex.c: lexer.l parser.tab.c # For parsr.tab.h.
	flex -olexer.lex.c -L lexer.l

.PHONY: clean
clean:
	rm -f conf *.o *.tab.[hc] *.lex.c
