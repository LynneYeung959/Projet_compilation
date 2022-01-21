%{
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "defs.h"
#include "common.h"
#include "y.tab.h"

int yyparse(node_t * program_root);
void analyse_tree(node_t root);
char * infile = NULL;
char * outfile = DEFAULT_OUTFILE;
bool stop_after_syntax = false;
bool stop_after_verif = false;

#if YYDEBUG
extern int yydebug;
#endif


%}

%option yylineno


LETTRE          [a-zA-Z]
/* A completer ; fausses definitions pour passer la compilation */
CHIFFRE	        [0-9]
IDF             {LETTRE}({LETTRE}|{CHIFFRE}|"_")*
CHIFFRE_NON_NUL [1-9]
/*ne peut pas avoir des espace entre 0 | CHIFFRE_NON_NUL*/
ENTIER_DEC 	    "0"|{CHIFFRE_NON_NUL}({CHIFFRE})*
/*avec + et *, il faut mettre () pour l'ensemble de langages*/
ENTIER_HEXA	    "0x"({CHIFFRE}|{LETTRE_HEXA})+
LETTRE_HEXA 	  [a-fA-F]
ENTIER          {ENTIER_DEC}|{ENTIER_HEXA}
CHAINE_CAR	    [\x20\x21\x23-\x5B\x5D-\x7E]
/* pour connaitre c'est une chaine de caractère, on met \" pour " */
CHAINE          "\""({CHAINE_CAR}|"\\\""|"\\n")*("\"")
/*COMMENTAIRE     "//"({CHAINE_CAR}|\x09)*  */ 
COMMENTAIRE     "//".*  

/*TEST : Verif pour chaque cas que la bonne valeur du token est renvoyee*/
%%

"void"  return TOK_VOID;
"int"	return TOK_INT;
"bool" 	return TOK_BOOL; 
"true" 	return TOK_TRUE;
"false" return TOK_FALSE;	
"if"	return TOK_IF;
"else"	return TOK_ELSE;
"while" return TOK_WHILE;
"for" 	return TOK_FOR;
"do" 	return TOK_DO; 
"print" return TOK_PRINT;
"+" 	return TOK_PLUS;
"-"		return TOK_MINUS; 
"*"		return TOK_MUL;
"/"		return TOK_DIV;
"%"		return TOK_MOD;
">"		return TOK_GT;
"<"		return TOK_LT; 
"!"		return TOK_NOT;
"~"		return TOK_BNOT;
"&"		return TOK_BAND;			
"|" 	return TOK_BOR; 
"^"		return TOK_BXOR;
"="		return TOK_AFFECT;
";"		return TOK_SEMICOL;
","		return TOK_COMMA; 
"("		return TOK_LPAR;
")"		return TOK_RPAR;
"{"		return TOK_LACC;
"}"		return TOK_RACC; 	
">>"	return TOK_SRL;
">>>"	return TOK_SRA;
"<<"	return TOK_SLL;
">="	return TOK_GE;
"<="	return TOK_LE;
"=="	return TOK_EQ;
"!="	return TOK_NE;
"&&"	return TOK_AND; 
"||"	return TOK_OR; 

{IDF} {
	yylval.strval = strdupBis(yytext);
                return TOK_IDENT;
}

{ENTIER} {/* A completer : affecter yylval.intval et faire des verifications */
		yylval.intval = atoi(strdupBis(yytext));
                return TOK_INTVAL;
}

{CHAINE} {
                /* A completer : affecter yylval.strval */
                yylval.strval = strdupBis(yytext);
                return TOK_STRING;
}

{COMMENTAIRE} {
}


[ \t\n]+

. {
                fprintf(stderr, "Error line %d: Lexical error\n", yylineno);
                exit(1);
}


%%

int yywrap(void) {
    return 1;
};

int main(int argc, char ** argv) {
    node_t program_root;
    parse_args(argc, argv);
    #if YYDEBUG
    yydebug = 1;
    #endif
    
    yyin = fopen(infile, "r");
    if(!yyin){
      printf("No such file : %s .\n", infile);
      printf("Or error loading file.\n");
      exit(1);
    }

    yyparse(&program_root);
    fclose(yyin);
    analyse_tree(program_root);
    yylex_destroy();
    return 0;
}



