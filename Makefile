all:sintatico.c parser.y scanner.l
	bison -d -y parser.y
	flex -l scanner.l
	gcc -c y.tab.c lex.yy.c 
	gcc -g y.tab.c lex.yy.c sintatico.c
	./a.out add.def saida	
