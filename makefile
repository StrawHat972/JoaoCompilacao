all: program

program:
	bison -d parser.y
	flex scanner.l
	g++ -o compiler main.cpp parser.tab.c lex.yy.c util.c analyzer.cpp

clean:
	rm compiler parser.tab.h parser.tab.c lex.yy.c