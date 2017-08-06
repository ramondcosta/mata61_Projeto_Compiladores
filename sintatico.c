#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "y.tab.h"

#define SIZE_TABLE 50
extern FILE *yyout;


void criaTree(astNode *an);


void criaTree(astNode *an)
{
    if(an != NULL) {

     switch(an->tipoNodo)
     {
		 case Ast:
			switch(an->astn.token) {
				case T_ADICAO:
					fprintf(yyout, "[+");
					criaTree(an->astn.filhos[0]);
					criaTree(an->astn.filhos[1]);
					fprintf(yyout, "]");
					break;
				
				case T_SUBTRACAO:
					fprintf(yyout, "[-");
					criaTree(an->astn.filhos[0]);
					criaTree(an->astn.filhos[1]);
					fprintf(yyout, "]");
					break;
				
				case T_PRODUTO:
					fprintf(yyout, "[*");
					criaTree(an->astn.filhos[0]);
					criaTree(an->astn.filhos[1]);
					fprintf(yyout, "] ");
					break;
				
				case T_DIVISAO:
					fprintf(yyout, "[/");
					criaTree(an->astn.filhos[0]);
					criaTree(an->astn.filhos[1]);
					fprintf(yyout, "] ");
					break;
				
				case T_USUBTRACAO:
					fprintf(yyout, " [-");
					criaTree(an->astn.filhos[0]);
					fprintf(yyout, "]");
					break;
				
				case T_PARENTESE_ESQ:
					criaTree(an->astn.filhos[0]);
					break;
				
				case T_E:
					fprintf(yyout, " [&&");
					criaTree(an->astn.filhos[0]);
					criaTree(an->astn.filhos[1]);
					fprintf(yyout, "]");	
					break;
				
				case T_OU:
					fprintf(yyout, " [||");
					criaTree(an->astn.filhos[0]);
					criaTree(an->astn.filhos[1]);
					fprintf(yyout, "]");
					break;
				
				case T_NAO:
					fprintf(yyout, "[!");
					criaTree(an->astn.filhos[0]);
					fprintf(yyout, "]");
					break;
				
				case T_IF:
					criaTree(an->astn.filhos[0]);
					criaTree(an->astn.filhos[1]);
					//Se for um IF-ELSE
					if(an->astn.n_filhos > 2){
						criaTree(an->astn.filhos[2]);
					}
					break;
				
				case T_WHILE:
					fprintf(yyout, "[while ");
					criaTree(an->astn.filhos[0]);
					criaTree(an->astn.filhos[1]);
					fprintf(yyout, "] ");
					break;
				
				case STMT:
					if(an->astn.n_filhos >= 2) { 
						if(an->astn.filhos[0] != NULL) 
							
							criaTree(an->astn.filhos[0]);
							criaTree(an->astn.filhos[1]);
						}
						else {criaTree(an->astn.filhos[0]);}
					
					break;
				
				case T_IGUAL:
			             	criaTree(an->astn.filhos[0]);
				     	fprintf(yyout, "[assign ");     
				     	fprintf(yyout, "[%s]", an->astn.filhos[0]->ident.valor);
				     	fprintf(yyout, "]");     
			        	break;
			        
			        case T_PONTO_VIRGULA:
			         	criaTree(an->astn.filhos[0]); 
				 	fprintf(yyout, "]");  
				  	break;
			        
			        case DCVAR:
			        	criaTree(an->astn.filhos[0]); 
					if(an->astn.filhos[1] != NULL) {
						criaTree(an->astn.filhos[1]); 
					}
					break;
			        
			        case EXPR:
			        	criaTree(an->astn.filhos[0]); 
					break;
					
				 case NEXPRFUNCCALL:
					fprintf(yyout,"[funccall ");
			        	criaTree(an->astn.filhos[0]);
			        	criaTree(an->astn.filhos[1]);
			        	fprintf(yyout, "]"); 
					break;
			        
			        case STMTSTMT:
			        	criaTree(an->astn.filhos[0]); 
				  	break;
			        
			        case RETURNSTMT:
			         	fprintf(yyout, " [return");     
			        	criaTree(an->astn.filhos[0]);
			        	fprintf(yyout, "]");  
					break;
			       		        
			        case T_TIPO:			            	
				if(an->astn.n_filhos >= 2) { 
						if(an->astn.filhos[1] != NULL) {
							fprintf(yyout, "[decvar ");
							fprintf(yyout, "[%s]", an->astn.filhos[0]->ident.valor);
							criaTree(an->astn.filhos[1]);
				   		} else {fprintf(yyout, " [decvar [%s]] ", an->astn.filhos[0]->ident.valor);}
				     	}
			        	break;
			        
			        case T_DEF:
			           	fprintf(yyout, "[decfunc [%s] ",an->astn.filhos[0]->ident.valor);
			           	criaTree(an->astn.filhos[1]);
			           	if(an->astn.filhos[1] == NULL) {
			           		fprintf(yyout, "[paramlist] ");
			           	}
			           	criaTree(an->astn.filhos[2]);
			           	fprintf(yyout, "]");
			        	break;
			        
			        case PARAMETROS:
			           	fprintf(yyout, "[paramlist [%s]",an->astn.filhos[0]->ident.valor);
			           	criaTree(an->astn.filhos[1]);			           
			          	fprintf(yyout, "]");
			        	break;
			        
			        case COMPPARAM:
			          	fprintf(yyout, "[%s]",an->astn.filhos[0]->ident.valor);
			           	criaTree(an->astn.filhos[1]);			           
			        	break;
			        
			        case BLOCK:
					fprintf(yyout, "[block ");
					if(an->astn.filhos[0] != NULL) {
						criaTree(an->astn.filhos[0]);
					}
					if(an->astn.filhos[1] != NULL) {
						   criaTree(an->astn.filhos[1]);
					}
					fprintf(yyout, "]");
			         	break;
			     			         
			         case ASSIGNSTMT:
			           	fprintf(yyout, "[assign ");
			           	criaTree(an->astn.filhos[0]);
			        	break;
			        
			         case COMPASSIGN:
			           	fprintf(yyout, "[%s] ", an->astn.filhos[0]->ident.valor);   
    			           	criaTree(an->astn.filhos[1]); 
			           	fprintf(yyout, "]");
					break;
			        
			         case VOLTASTMT:
			           	criaTree(an->astn.filhos[0]); 
	   		       	 	 if(an->astn.filhos[1] != NULL) {
						criaTree(an->astn.filhos[1]); 
					}			          			           
			        	break;
			         
			         case STMTBREAK:
			           	fprintf(yyout, "[break]");
				 	break;
				
				 case STMTIF:
			           	fprintf(yyout, "[if ");
			           	criaTree(an->astn.filhos[0]); 
			    	   	criaTree(an->astn.filhos[1]);
			    	   	criaTree(an->astn.filhos[2]);
			    	   	fprintf(yyout, "] "); 
			        	break;
				 
				 case STMTELSE:
			           	//fprintf(yyout, "[else]");
			           	criaTree(an->astn.filhos[0]);
				 	break;
				 
				 case STMTCONTINUE:
			           	fprintf(yyout," [continue]");
				 	break;
				 
				 case STMTFUNCCALL:
				 	fprintf(yyout,"[funccall ");
			           	criaTree(an->astn.filhos[0]); 
			         	fprintf(yyout,"]");
				 	break;
				 
				 case FUNCCALL:
					if(an->astn.filhos[1] != NULL) {
						fprintf(yyout,"[%s]", an->astn.filhos[0]->ident.valor); 
			           		criaTree(an->astn.filhos[1]); 
					}
					else {
						fprintf(yyout,"[%s]", an->astn.filhos[0]->ident.valor); 
			           		 fprintf(yyout,"[arglist]");
					}
					break;
				 
				 case FUNCNARGLIST:
				   	fprintf(yyout,"[arglist");
			           	criaTree(an->astn.filhos[0]);
			           	fprintf(yyout,"]");
			    	 	break;
				 
				 case FUNCARGLIST:
			           	criaTree(an->astn.filhos[0]); 
			          	criaTree(an->astn.filhos[1]); 
			        	break;
				 
				 case FUNCNNARGLIST:
					criaTree(an->astn.filhos[0]);
					criaTree(an->astn.filhos[1]); 
				      	break;
				
				case T_MAIOR:
					fprintf(yyout,"[>");
					criaTree(an->astn.filhos[0]);
					criaTree(an->astn.filhos[1]);
					fprintf(yyout,"] ");
					break;
				
				case T_MAIOR_IGUAL:
					fprintf(yyout,"[>=");
					criaTree(an->astn.filhos[0]);
					criaTree(an->astn.filhos[1]);
					fprintf(yyout,"] ");
					break;
				
				case T_MENOR_IGUAL:
					fprintf(yyout,"[<=");
					criaTree(an->astn.filhos[0]);
					criaTree(an->astn.filhos[1]);
					fprintf(yyout,"] ");
					break;
				
				case T_MENOR:
					fprintf(yyout,"[<");
					criaTree(an->astn.filhos[0]);
					criaTree(an->astn.filhos[1]);
					fprintf(yyout,"] ");
					break;
					
				case T_IGUAL_IGUAL:
					fprintf(yyout,"[==");
					criaTree(an->astn.filhos[0]);
					criaTree(an->astn.filhos[1]);
				  	fprintf(yyout,"] ");
					break;
				
				case T_DIFERENTE:
				    	fprintf(yyout,"[!=");
					criaTree(an->astn.filhos[0]);
					criaTree(an->astn.filhos[1]);
					fprintf(yyout,"] ");
					break;
				
				case T_PRINT:
					criaTree(an->astn.filhos[0]);
					break;
		   }
		   
		 break;
		 
		 case Identif:
			fprintf(yyout," [%s]", an->ident.valor);
			break;
		
		case Const:
			fprintf(yyout," [%d]", an->constante.valorConst);	
			break;	
	}
  }
  
}

