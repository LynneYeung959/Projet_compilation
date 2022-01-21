#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "defs.h"
#include "passe_1.h"
#include "miniccutils.h"
#include "common.h"

extern int trace_level;

void analyse_passe_1(node_t root) {
    assert(root->nature == NODE_PROGRAM);
    //printf("%s\n", node_nature2string(root->nature));
    reset_env_current_offset(); 
    if (root -> opr[0] != NULL){
        push_global_context(); // variable 'global' = ture: variable globale
        analyse_listdeclvars(root->opr[0], true);
        analyse_mainfunc(root->opr[1]);
    }
    else{
        analyse_mainfunc(root->opr[1]);
    }
}

//main
void analyse_mainfunc(node_t n) {
    assert(n->nature == NODE_FUNC);
    reset_env_current_offset(); // reset l'offset
    //printf("fonction main : NODE_FUNC\n");
    // vérifier que le nom est main
    if (strcmp(n -> opr[1]-> ident, "main") != 0) {
        fprintf(stderr, "Error line %d: L'identifiacateur de NODE_FUNC n'est pas MAIN", n->lineno);
        exit(1);
    }
    // vérifier que le type de retour est void
    if(n -> opr[0]-> type != TYPE_VOID){
        fprintf(stderr, "Error line %d: Le type de du NODE_FUNC est fausse {mainfunc}", n->lineno);
        return;
    }
    //printf("NODE_TYPE : 'void'\nNODE_IDENT : 'main'\n");
    analyse_block(n->opr[2]);
    n-> offset = get_env_current_offset();
    //printf("offset est : %d\n", n->offset);
}

// expr
void analyse_expr(node_t n){
    //printf("%s\n", node_nature2string(n->nature)); 
    switch(n->nature){
        case NODE_LT:
        case NODE_GT:
        case NODE_LE:
        case NODE_GE:
            analyse_expr(n->opr[0]);
            analyse_expr(n->opr[1]);
            if((n->opr[0]->type == TYPE_INT) && (n->opr[0]-> type == n->opr[1]-> type)){
                n->type = TYPE_BOOL;
            }
            else{
                fprintf(stderr, "Error line %d: les deux expressions ne sont pas TYPE_INT {expr-LT_GT_etc}\n", n->lineno);
                exit(1);
            }
            break;
        case NODE_EQ:
        case NODE_NE:
            analyse_expr(n->opr[0]);
            analyse_expr(n->opr[1]);
            if (n->opr[0]-> type == n->opr[1]-> type){
                if(n->opr[0]->type == TYPE_INT || (n->opr[0]->type == TYPE_BOOL)){
                    n->type = TYPE_BOOL;
                }
                else{
                    fprintf(stderr, "Error line %d: les deux expressions ne sont pas de type BOOL or INT {expr-EQ_NE1}\n", n->lineno);
                    exit(1);
                }   
            }
            else{
                fprintf(stderr, "Error line %d: les deux expressions ne sont pas de même type {expr-EQ_NE2}\n", n->lineno);
                exit(1);
            }
            break;
        case NODE_AND:
        case NODE_OR:
            analyse_expr(n->opr[0]);
            analyse_expr(n->opr[1]);
            if((n->opr[0]->type == TYPE_BOOL) && (n->opr[0]-> type == n->opr[1]-> type)){
                n->type = TYPE_BOOL;
            }
            else{
                fprintf(stderr, "Error line %d: les deux expressions ne sont pas TYPE_BOOL {expr-AND_OR}\n", n->lineno);
                exit(1);
            }
            break;
        
        case NODE_DIV:
        case NODE_MOD:
            analyse_expr(n->opr[0]);
            analyse_expr(n->opr[1]);
            if(n->opr[1]->value == 0){
                fprintf(stderr, "Error line %d: %s ne peut pas divisé par 0  {expr-DIV-MOD}\n", n->lineno, n->opr[0]->ident);
                exit(1);
            }
            if(n->opr[0]-> type == n->opr[1]-> type && n->opr[0]->type == TYPE_INT){
                n->type = TYPE_INT;
            }
            else{
                fprintf(stderr, "Error line %d: les deux expressions ne sont pas TYPE_INT {expr-DIV-MOD}\n", n->lineno);
                exit(1);
            }
            break;
        case NODE_MINUS:
        case NODE_PLUS:
        case NODE_MUL:
        case NODE_BAND:
        case NODE_BOR:
        case NODE_BXOR:
        case NODE_SLL:
        case NODE_SRL:
        case NODE_SRA:
            analyse_expr(n->opr[0]);
            analyse_expr(n->opr[1]);
            if(n->opr[0]-> type == n->opr[1]-> type && n->opr[0]->type == TYPE_INT){
                n->type = TYPE_INT;
            }
            else{
                fprintf(stderr, "Error line %d: les deux expressions ne sont pas TYPE_INT {expr-OP_BINAIRE}\n", n->lineno);
                exit(1);
            }
            break;
        case NODE_UMINUS:
            analyse_expr(n->opr[0]);
            if(n->opr[0]->type == TYPE_INT){
                n->type = TYPE_INT;
            }
            else{
                fprintf(stderr, "Error line %d: l'expression n'est pas TYPE_INT {expr-UMINUS}\n", n->lineno);
                exit(1);
            }
            break;
        case NODE_NOT: // ! avec une variable de type bool
            analyse_expr(n->opr[0]);
            if(n->opr[0]->type == TYPE_BOOL || n->opr[0]->type == TYPE_INT){
                n->type = TYPE_BOOL;
            }
            else{
                fprintf(stderr, "Error line %d: l'expression n'est pas TYPE_BOOL {expr-NOT}\n", n->lineno);
                exit(1);
            }
            break;
        case NODE_BNOT: //~ avec une variable de type int
            analyse_expr(n->opr[0]);
            if(n->opr[0]->type == TYPE_INT){
                n->type = TYPE_INT;
            }
            else{
                fprintf(stderr, "Error line %d: l'expression n'est pas TYPE_INT {expr-BNOT}\n", n->lineno);
                exit(1);
            }
            break;
        case NODE_AFFECT:
            analyse_expr(n->opr[0]); //ident
            analyse_expr(n->opr[1]);
            //printf(" fonction expr : TYPE de 1er node fils %s\n", node_type2string(n->opr[0]->type));
            if(n->opr[0]->type == n->opr[1]->type){
                n->type = n->opr[0]->type;
            }
            else{
                fprintf(stderr, "Error line %d: ident et expression n'ont pas le même type {expr-AFFECT}\n", n->lineno);
                exit(1);
            }
            break;
        case NODE_INTVAL:
            n->type = TYPE_INT;
            //printf("\tvalue est : %ld\n",n->value);
            break;
        case NODE_BOOLVAL:
            n->type = TYPE_BOOL;
            break;
        case NODE_IDENT:
            {
                node_t result = get_decl_node(n->ident); 
                if (result){
                    n->type = result->type;
                    n->decl_node = result;
                    //printf("ident de type %s, est : '%s', offset est : %d \n",node_type2string(n->type), n->ident,n->decl_node->offset);
                }
                else{
                    fprintf(stderr, "Error line %d: la variable %s n'a pas été déclarée {expr-IDENT}\n", n->lineno, n->ident);
                    exit(1);
                }
            }
            break;
        default:
            fprintf(stderr, "Error line %d: NODE INCONNU %s {expr}\n", n->lineno, node_nature2string(n->nature));
            exit(1);
            //analyse_expr(n);
            //n->type = n->opr[0]->type;
            break;
    }
    
}

void analyse_listinst(node_t n){
    //printf("%s\t%d nb nodes fils\n",node_nature2string(n->nature),n->nops);
    //printf("fils sont %s\t%s\n",node_nature2string(n->opr[0]->nature),node_nature2string(n->opr[1]->nature));
    if(n){
        if (n->nature == NODE_LIST){
            analyse_listinst(n->opr[0]);
            analyse_inst(n->opr[1]);
            //return;
        }
        else {
            analyse_inst(n);
        }
    }
}
void analyse_inst(node_t n){
    //printf("%s\n",node_nature2string(n->nature));
    if(n == NULL){ // cas: TOK_SEMICOL
        return;
    }else{
        switch(n->nature){
            case NODE_IF:
                analyse_expr(n->opr[0]);
                if(n->opr[0]->type == TYPE_VOID){
                    fprintf(stderr, "Error line %d: '%s' n'exist pas\n", n->lineno, n->ident); 
                    exit(1);
                }else{
                    if(n->opr[0]->nops){
                        if(!(n->opr[0]->type == TYPE_BOOL)){
                            fprintf(stderr, "Error line %d: Expression dans IF n'est pas BOOL\n", n->opr[0]->lineno); 
                            exit(1);
                        }
                    }
                }
                analyse_inst(n->opr[1]);
                if(n->nops == 3){
                    analyse_inst(n->opr[2]);
                }
                break;
            case NODE_WHILE:
                analyse_expr(n->opr[0]);
                if(n->opr[0]->type == TYPE_VOID){
                    fprintf(stderr, "Error line %d: '%s' n'exist pas\n", n->lineno, n->ident); 
                    exit(1);
                }else{
                    if(n->opr[0]->nops !=0){
                        if(!(n->opr[0]->type == TYPE_BOOL)){
                            fprintf(stderr, "Error line %d: Expression dans WHILE n'est pas BOOL\n", n->opr[0]->lineno); 
                            exit(1);
                        }
                    }
                }
                analyse_inst(n->opr[1]);
                break;
            case NODE_FOR:
                analyse_expr(n->opr[0]);
                analyse_expr(n->opr[1]);
                if(n->opr[1]->type == TYPE_VOID){
                    fprintf(stderr, "Error line %d: '%s' n'exist pas\n", n->lineno, n->ident); 
                    exit(1);
                }else{
                    if(n->opr[1]->nops !=0){
                        if(!(n->opr[1]->type == TYPE_BOOL)){
                        fprintf(stderr, "Error line %d: Expression dans IF n'est pas BOOL\n", n->opr[0]->lineno); 
                        exit(1);
                        }
                    }
                }
                analyse_expr(n->opr[2]);
                analyse_inst(n->opr[3]);
                break;
            case NODE_DOWHILE:
                analyse_inst(n->opr[0]);
                analyse_expr(n->opr[1]);
                if(n->opr[1]->type == TYPE_VOID){
                    fprintf(stderr, "Error line %d: '%s' n'exist pas\n", n->lineno, n->ident); 
                    exit(1);
                }else{
                    if(n->opr[1]->nops !=0){
                        if(!(n->opr[1]->type == TYPE_BOOL)){
                        fprintf(stderr, "Error line %d: Expression dans DOWHILE n'est pas BOOL\n", n->opr[0]->lineno); 
                        exit(1);
                        }
                    }
                }
                break;
            case NODE_BLOCK:
                analyse_block(n);
                break;
            case NODE_PRINT:
                analyse_listparamprint(n->opr[0]);
                break;
            default:
                analyse_expr(n);
                break;
        }
    }
}

// liste_decl_vars
void analyse_listdeclvars(node_t n, bool global){
    //printf("%s\n", node_nature2string(n->nature)); 
    // vérifier que le 1er et le 2e node fils sont de type node 
    if(n->opr[0] == NULL){
        fprintf(stderr, "Error line %d: Le type du 1er node fils n'ont été déclaré\n", n->lineno);
        exit(1);
    }
    else if(n->nature == NODE_DECLS){
        //printf("\tliste_decl_vars, NODE_DECLS\n");
        analyse_declvars(n,global);//decl_vars
    }
    else if(n->nature == NODE_LIST){
        //printf("\tliste_decl_vars, NODE_LIST\n");
        //assert(n->nature == NODE_LIST);
        analyse_listdeclvars(n->opr[0], global); // avec n->opr[0]->type ?
        analyse_declvars(n->opr[1],global);//decl_vars
    }
}   

// block
void analyse_block(node_t n){
    assert(n->nature == NODE_BLOCK);
    //printf("NODE_BLOCK\n");
    // block peut être vide
    if(n == NULL){
        return;
    }
    push_context(); // variable 'global' = false: variable locale
    // vérifier les 2 nodes fils: list_inst (NODE_LIST)
    if(n->opr[0]){
        analyse_listdeclvars(n->opr[0],false);        
    }
    //analyse_inst(n->opr[1]);
    analyse_listinst(n->opr[1]);
    pop_context(); // dépilé et libère le contexte courant
}

// type
void analyse_type(node_t n){
    assert(n->nature == NODE_TYPE);
    if(n->type == TYPE_INT){
        //printf("NODE_TYPE, 'int'\n");
    }
    else if(n->type == TYPE_BOOL){
        //printf("NODE_TYPE, 'bool'\n");
    }
    else if(n->type == TYPE_VOID){
        //printf("NODE_TYPE, 'void'\n");
        fprintf(stderr, "Error line %d: type de node n'est pas un des INT, BOOL\n", n->lineno);
        exit(1);
    }
}


// decl_vars
void analyse_declvars(node_t n, bool global){
    assert(n->nature == NODE_DECLS);
    //printf("%s\n",node_nature2string(n->nature));
    analyse_type(n->opr[0]);
    analyse_listtypedecl(n->opr[1], n->opr[0]->type, global);  
}

// liste_decl_type
void analyse_listtypedecl(node_t n, node_type t, bool global){
    //printf("%s\n",node_nature2string(n->nature));
    // vérifier les variables sont de mm type, pas de variables avec le mm nom
    if (n->nature == NODE_LIST){
        //printf("liste_decl_type\t NODE_LIST\n");
        analyse_listtypedecl(n->opr[0],t,global); 
        analyse_vardecl(n->opr[1],t,global);
    }
    else if (n->nature == NODE_DECL) {
        //printf("liste_decl_type\t NODE_DECL\n");
        analyse_vardecl(n,t,global);  
    }
}

// decl_var
void analyse_vardecl(node_t n, node_type t, bool global){
    assert(n->nature == NODE_DECL);
    // ajoute dans le context courant l'association entre le nom 'ident' et le noeud 'node' 
    int result = env_add_element(n->opr[0]->ident, n->opr[0]);
    node_t nodeIdent;// = (node_t)malloc(sizeof(node_s));
    nodeIdent = n-> opr[0]; // varaible
    // si nom n'est pas dans env local
    if (result < 0 ){
        fprintf(stderr, "Error line %d: variable du même nom existe déjà {vardecl}\n", n->lineno);
        exit(1);
    }
    else{ // offset de la variable ds l'environnement
        //printf("\t Nouvelle variable \t\n");
        if(n->opr[1] != NULL) { // s'il y a une expression EX: int a = 1 ;
            if ( global == true ){ //variable gloable
                //printf("Fils: NODE_IDENT et Litteral\n");
                // valeur init litterale(nature => intval / boolval) (!= expr)
                if((n->opr[1]->nature == NODE_INTVAL && t == TYPE_INT)|| (n->opr[1]->nature == NODE_BOOLVAL && t == TYPE_BOOL)){
                    nodeIdent ->  value= n->opr[1]->value;
                    //printf(" variable %s de nature %s, value est :%ld\n",nodeIdent ->ident, node_nature2string(nodeIdent->nature), nodeIdent->value);
                }
                else{
                    fprintf(stderr, "Error line %d: valeur d'initialisation de la variable %s n'est pas correcte {vardecl-Litteral}\n", n->lineno, n->opr[0]->ident);
                    exit(1);
                }
            }// variable locale avec exp
            else{
                //printf("Fils: NODE_IDENT et EXPR\n");
                analyse_expr(n->opr[1]);
                // cas : bool a = 0/1 OU ture/false
                if(t == TYPE_BOOL){
                    if (n->opr[1]-> nature == NODE_BOOLVAL || n->opr[1]-> nature == NODE_INTVAL){
                        if(n->opr[1]->value == 1|| n->opr[1]->value == 0){
                            nodeIdent -> value = n->opr[1]-> value;
                        }
                        else{
                            fprintf(stderr, "Error line %d: valeur d'initialisation de la variable %s n'est pas 0 ou 1 {vardecl-Expr}\n", n->lineno, n->opr[0]->ident);
                            exit(1);
                        }
                    }else{
                        fprintf(stderr, "Error line %d: Nature de la valeur d'initialisation de la variable %s n'est pas BOOL or INTVAL {vardecl-Expr}\n", n->lineno, n->opr[0]->ident);
                            exit(1);
                    }
                }
                else if(t == TYPE_INT && n->opr[1]->nature == NODE_INTVAL){
                    nodeIdent -> value = n->opr[1]->value;
                }
                else if(n->opr[1]->type != t ){
                    fprintf(stderr, "Error line %d: valeur d'initialisation de la variable %s n'est pas correcte {vardecl-Expr}\n", n->lineno, n->opr[0]->ident);
                    exit(1);
                } 
            }  
        }
        // EX : int i --- pas de l'expression  
        //printf("Fils: NODE_IDENT et NULL\n");
        //printf("NODE_IDENT, variable globale ?  1 = globale, 0 = locale :%d\n", global);
        nodeIdent-> global_decl = global;
        nodeIdent-> type = t;
        if( t == TYPE_INT && global == true){
            nodeIdent->value = 0;
        }
        if(t == TYPE_BOOL && global == true){
            nodeIdent -> value = false;
        }
        n->opr[0]-> offset = result;
        
        //if(nodeIdent -> value){
            //printf("---------------valeur de vairable %s: %ld\n", nodeIdent->ident,nodeIdent->value);
        //}
        //printf("NODE_IDENT, variable globale ? (1/0) : %d\n", nodeIdent->global_decl);
        //printf("ident de type %s, est : '%s'\t offset est :%d\n",node_type2string(nodeIdent->type), nodeIdent->ident,nodeIdent->offset);   
        //free(nodeIdent);
        //nodeIdent = NULL;
    }
}


// liste_param_print
void analyse_listparamprint(node_t n){
    //printf("%s\n",node_nature2string(n->nature));;
    if(n->nature == NODE_LIST)
    {
        analyse_listparamprint(n->opr[0]);
        analyse_paramprint(n->opr[1]);
    }else{
        analyse_paramprint(n);
    }
}
// param_print
void analyse_paramprint(node_t n){
    //printf("param_print\n");
    if(n->nature != NODE_STRINGVAL){
        analyse_expr(n);
    }
    else{
        //printf("NODE_STRINGVAL : %s\n", n->str);
    }
}