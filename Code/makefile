SRC=parser.y parser.l ourgetopt.cpp semantic.cpp symbolTable.cpp TreeUtils.cpp yyerror.cpp parseerror.cpp memloc.cpp
HEADERS=scanType.h ASTreeNode.h ourgetopt.h semantic.h symbolTable.h TreeUtils.h yyerror.h parseerror.h memloc.h
STD=c++11

parser: clean bison flex
	g++ -std=${STD} -g lex.yy.o parser.tab.o -o c-

bison:
	bison -v -t -d parser.y
	g++ -std=${STD} -g -c -o parser.tab.o parser.tab.c

flex:
	flex parser.l
	g++ -std=${STD} -g -c -o lex.yy.o lex.yy.c

tm:
	g++ -std=${STD} -g tm.c -o tm

tar:
	tar -cvf parser.tar makefile ${SRC} ${HEADERS}

clean:
	rm -f test.out lex.yy.o parser.tab.o parser.tab.c lex.yy.c parser.tar c-
