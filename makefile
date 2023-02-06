all: program

program:
	bison -d analysis/parser.y
	flex analysis/scanner.l
	g++ -o compiler main.cpp parser.tab.c lex.yy.c analysis/*.cpp synthesis/*.cpp
clean:
	rm compiler parser.tab.h parser.tab.c lex.yy.c tests/*.s
