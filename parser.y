%{


#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "parser.h"


#define YYDEBUG 1


extern FILE *yyout;

int yylex(void);


astNode *constante(int valor);
astNode *id(char value[20]);
astNode *criarTreeNode(int no_token, int nfilhos, ...);

void yyerror(char *s);



%}

%union {
	int numero;
	char id[20];
	astNode *ASTPonteiro;
};

%token T_DEF T_LET T_IF T_ELSE T_WHILE WHILE
%token T_RETURN 
%token T_PARENTESE_ESQ T_CHAVE_ESQ T_COCHETE_ESQ 
%token T_COCHETE_DIR T_CHAVE_DIR T_PARENTESE_DIR 
%token T_VIRGULA T_IGUAL 
%token T_ADICAO T_SUBTRACAO T_PRODUTO T_DIVISAO 
%token T_MENOR T_MAIOR T_MENOR_IGUAL T_MAIOR_IGUAL 
%token T_IGUAL_IGUAL T_DIFERENTE T_E T_OU 
%token T_ID T_DEC T_NAO T_PRINT
%token T_STMT T_TIPO TYPE STMT
%token BLOCK DCVAR ASSIGNSTMT COMPPARAM COMPASSIGN EXPR RETURNSTMT STMTSTMT NEXPRFUNCCALL PARAMETROS
%token VOLTASTMT STMTBREAK STMTIF STMTELSE STMTCONTINUE STMTFUNCCALL FUNCCALL FUNCNARGLIST FUNCNNARGLIST FUNCARGLIST


%token <numero> NUMBER
%token <id> T_NOME T_CONTINUE T_BREAK T_PONTO_VIRGULA


%type <ASTPonteiro> program decvar compdecvar 
%type <ASTPonteiro> paramlist compparamlist block
%type <ASTPonteiro> inicio arglist stmt
%type <ASTPonteiro> ndecvar nelse nstmt
%type <ASTPonteiro> funccall nnarglist narglist 
%type <ASTPonteiro> decfunc assign expr nexpr


%left T_OU
%left T_E
%left T_IGUAL_IGUAL T_DIFERENTE
%left T_MENOR T_MAIOR T_MENOR_IGUAL T_MAIOR_IGUAL   
%left  T_ADICAO T_SUBTRACAO
%left  T_PRODUTO T_DIVISAO
%right  T_NAO
%left  T_USUBTRACAO
%left T_PARENTESE_ESQ T_PARENTESE_DIR

%start inicio

%%


inicio:      program {fprintf(yyout, "[program "); criaTree($1); fprintf(yyout, "]\n"); printf("inicio->program\n");} ;

program:     decvar program {$$ = criarTreeNode(STMT, 2, $1, $2);}
            |decfunc program {$$ = criarTreeNode(STMT, 2, $1, $2);printf("program->decfunc program\n");}
            |{$$ = NULL;} 
            ;


decvar:       T_LET T_NOME compdecvar T_PONTO_VIRGULA {$$ = criarTreeNode(T_TIPO, 2, id($2),$3);printf("decvar-> t-let t-nome compdecvar t-ponto-virgula\n"); }
;


decfunc:      T_DEF T_NOME T_PARENTESE_ESQ paramlist T_PARENTESE_DIR block {$$ = criarTreeNode(T_DEF,3,id($2),$4, $6);printf("decfunc-> t-def t-nome t-paren-esq paramlis t-paren-dir block\n");}
;

paramlist:    {$$ = NULL;printf("paramlist->null\n");} |
		T_LET T_NOME compparamlist{$$ = criarTreeNode(PARAMETROS, 2, id($2), $3);}
		
;

compdecvar: 	{$$ = NULL;printf("compdecvar->null\n");} |
		T_IGUAL expr {$$ = criarTreeNode(T_PONTO_VIRGULA, 1, $2);printf("compdecvar->t-igual\n");}
;

compparamlist: T_VIRGULA T_NOME compparamlist {$$ = criarTreeNode(COMPPARAM,2,id($2),$3);}
;		

block:        T_CHAVE_ESQ ndecvar nstmt T_CHAVE_DIR {$$ = criarTreeNode(BLOCK, 3, $2, $3);printf("block-> t-chave-esq ndevcar nstmt t-chav-dir\n");}  
;

ndecvar: {$$ = NULL ;printf("ndecvar->null\n");}
     | decvar ndecvar {$$ = criarTreeNode(DCVAR, 2, $1, $2);printf("ndecvar->decvar ndecvar\n");}
;

nstmt :	{$$ = NULL;} |
	stmt nstmt {$$ = criarTreeNode(RETURNSTMT, 2, $1, $2);} 
;


stmt:         assign T_PONTO_VIRGULA {$$ = criarTreeNode(ASSIGNSTMT, 1, $1);}|	      	

              funccall T_PONTO_VIRGULA{$$ = criarTreeNode(STMTFUNCCALL, 1, $2);} |

              T_IF T_PARENTESE_ESQ expr T_PARENTESE_DIR block nelse{$$ = criarTreeNode(STMTIF, 3, $3,$5,$6);printf("expr-> t-if t-par-es expr t-par-dir nelse\n");} |

              T_WHILE T_PARENTESE_ESQ expr T_PARENTESE_DIR block{$$ = criarTreeNode(T_WHILE, 2, $3,$5);} |

              T_RETURN nexpr T_PONTO_VIRGULA {$$ = criarTreeNode(RETURNSTMT, 1, $2);printf("expr->t-return nexpr t-ponto-virg\n");} |

              T_BREAK T_PONTO_VIRGULA {$$ = criarTreeNode(STMTBREAK,2,$1, $2);} |

              T_CONTINUE T_PONTO_VIRGULA{$$ = criarTreeNode(STMTCONTINUE, 2, $1, $2);}

;

nelse: 		{$$ = NULL;printf("nelse->null\n");}|
		T_ELSE block {$$ = criarTreeNode(STMTELSE, 1,$2);}
;

assign:       T_NOME T_IGUAL expr{$$ = criarTreeNode(COMPASSIGN, 2, id($1), $3);}
;

funccall:     T_NOME T_PARENTESE_ESQ narglist T_PARENTESE_DIR{$$ = criarTreeNode(FUNCCALL, 2, id($1), $3);};

arglist:      expr nnarglist{$$ = criarTreeNode(FUNCARGLIST, 2, $1, $2);};

narglist: {$$ = NULL;}|
	arglist {$$ = criarTreeNode(FUNCNARGLIST, 1, $1);};

nnarglist: {$$ = NULL;}|
	T_VIRGULA expr nnarglist{$$ = criarTreeNode(FUNCNNARGLIST, 2, $2, $3);};


expr: NUMBER {$$ = constante($1);printf("expr->number\n");}|
	T_NOME {$$ = id($1);printf("expr->t-nome\n");} |
	T_SUBTRACAO expr %prec T_USUBTRACAO {$$ = criarTreeNode(T_USUBTRACAO, 1, $2);} |
	T_NAO expr {$$ = criarTreeNode(T_NAO, 1, $2);} |
	expr T_ADICAO expr {$$ = criarTreeNode(T_ADICAO, 2, $1, $3);} |
	expr T_SUBTRACAO expr {$$ = criarTreeNode(T_SUBTRACAO, 2, $1, $3);}|
	expr T_PRODUTO expr {$$ = criarTreeNode(T_PRODUTO, 2, $1, $3);} |
	expr T_DIVISAO expr {$$ = criarTreeNode(T_DIVISAO, 2, $1, $3);} |
        expr T_MENOR expr {$$ = criarTreeNode(T_MENOR, 2, $1, $3);} |
        expr T_MAIOR expr {$$ = criarTreeNode(T_MAIOR, 2, $1, $3);} |
        expr T_MENOR_IGUAL expr {$$ = criarTreeNode(T_MENOR_IGUAL, 2, $1, $3);} |
        expr T_MAIOR_IGUAL expr {$$ = criarTreeNode(T_MAIOR_IGUAL, 2, $1, $3);}|
        expr T_IGUAL_IGUAL expr {$$ = criarTreeNode(T_IGUAL_IGUAL, 2, $1, $3);} |
        expr T_DIFERENTE expr {$$ = criarTreeNode(T_DIFERENTE, 2, $1, $3);} |
        expr T_E expr {$$ = criarTreeNode(T_E, 2, $1, $3);} |
        expr T_OU expr {$$ = criarTreeNode(T_OU, 2, $1, $3);}
;
nexpr: {$$ = NULL;}|
	expr {$$ = criarTreeNode(EXPR, 1, $1);}
;

%%
extern char *yytexto;

astNode *constante(int valor) {
    astNode *an = malloc(sizeof(astNode));

    an->tipoNodo = Const;
    an->constante.valorConst = valor;
    return an;
}

astNode *id(char value[20]) {
    astNode *an = malloc(sizeof(astNode));
	
     an->tipoNodo = Identif;
     strcpy(an->ident.valor, value);

    return an;
}

astNode *criarTreeNode(int no_token, int nfilhos, ...) {
    va_list ap; 
    
    astNode *an = malloc(sizeof(astNode));
    int i;
	
	an->astn.filhos = malloc(nfilhos * sizeof(astNode *));
	va_start(ap, nfilhos); 
    
    an->tipoNodo = Ast;
    an->astn.token = no_token;
    an->astn.n_filhos = nfilhos;

    i = 0;
    while (i < nfilhos) {
		an->astn.filhos[i] = va_arg(ap, astNode*);
		i++;
    }
         
    va_end(ap);
    return an;
}

void yyerror(char *s) {
    printf("Erro");
}

int main(int argc, char *argv[])
{
	if (argc != 3){
			printf("Erro. Entrada fora do padrao.");
			return 1;
		} 
		FILE *output = fopen(argv[2], "w");
		FILE *input = fopen(argv[1], "r"); 
		extern FILE *yyin;
		extern FILE *yyout;
		yyout = output;
		yyin = input;

		yyparse();
	 
	    return 0;
}
