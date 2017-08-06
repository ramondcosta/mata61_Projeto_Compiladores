%{
/*
Igor Paim
Ramon Dias
*/
#include <stdio.h>
#include "parser.h"
#include "y.tab.h"



%}


%%




"def" 		return T_DEF;
"let"		return T_LET;
"if"	  	return T_IF;
"else"		return T_ELSE;
"while"		return T_WHILE;
"return"	return T_RETURN;
"break"		return T_BREAK;
"continue"	return T_CONTINUE;		
"print"		return T_PRINT;

[0-9][0-9]*     	     {
		  	    	  yylval.numero = atoi(yytext);
		    	  	  return NUMBER;
		   	     }

[a-zA-Z][0-9a-zA-Z_]*        { 
              			  strcpy(yylval.id, yytext);
            			  return T_NOME;
          		     }

"("		return T_PARENTESE_ESQ;
")"  		return T_PARENTESE_DIR;
[{]		return T_CHAVE_ESQ;
[}]  		return T_CHAVE_DIR;
[,]  		return T_VIRGULA;
[;]  		return T_PONTO_VIRGULA;
"<="  		return T_MENOR_IGUAL;
">="  		return T_MAIOR_IGUAL;
"=="  		return T_IGUAL_IGUAL;
"!=" 		return T_DIFERENTE;
"="  		return T_IGUAL;
"+"  		return T_ADICAO;
"-"  		return T_SUBTRACAO;
"*"  		return T_PRODUTO;
"/"  		return T_DIVISAO;
"<" 		return T_MENOR;
">"  		return T_MAIOR;
"&&"  		return T_E;
"||"  		return T_OU;
"!"  		return T_NAO;

[ \t\n]+        ; 

           yyerror("ERRO");

%%
int yywrap(void) {
    return 1;
}
