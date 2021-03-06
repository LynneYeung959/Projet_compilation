#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <inttypes.h>
#include <unistd.h>
#include <getopt.h>

#include "defs.h"
#include "common.h"
#include "arch.h"


extern char * infile;
extern char * outfile;
extern char * optarg;
extern int optind, optopt; 
int32_t trace_level = DEFAULT_TRACE_LEVEL;
int32_t nb_reg = 8;
extern bool stop_after_syntax;
extern bool stop_after_verif;


void parse_args(int argc, char ** argv) {
    int o; //caractere
    int sflg=0; //option s utilisee
    int vflg=0; //option v utilisee
    int errflg=0; //erreur
    int oflg= 0; //options utilisées
    int hflg = 0; // option h utilise
    int bflg = 0; //option b utilisee
    int aflg =0; //argument flag
    int tflg = 0; //argument t 
    int rflg =0;  //argument r
    int inflg =0;  //flag in file
    int outflg = 0; //flag out file
    int c = 0; //nombre de fichier c 
    char last_letter;
    int length_arg =0;
    outfile = DEFAULT_OUTFILE;

//regarde si un des arguments se termine par c 
    for(int i =1 ; i<argc; i++){
        if(argv[i][strlen(argv[i])-1] == 'c'){
            c++;
            infile = argv[i];
        }  
    }
 //S'il y a plus d'un fichier .c ou qu'il n'y en a pas, il y a une erreur
    if((c > 1)||(infile == NULL)){
        inflg++;
        errflg++;
    }

//arguments parsing 
    while(((o=getopt(argc, argv, ":bsvho:t:r:"))!=-1)){
        switch(o){
            case 'o' :
                if(bflg){
                    errflg++;
                }
                else{
                    if(optarg[0]=='-'){ //Si l'élément suivant est une option il y a une erreur
                        outflg++;
                        errflg++;
                    }
                    else{
                        outfile = optarg;
                        //printf("output file %s\n", outfile);  
                    }
                }
                aflg++;
                oflg++;
                break;

            case 't' :
                if(bflg)
                    errflg++;
                else{
                    if((optarg[0]=='-')||(atoi(optarg)>5)){ //SI le prochain element commence par '-' (option ou chiffre neg), si l'arg est supp à 5  erreur.  
                        tflg++;
                        errflg++;
                    }
                    else{
                        trace_level= atoi(optarg);
                        //printf("trace_level %d \n", trace_level);
                    }
                }
                aflg++;
                oflg++;
                break;

            case 'r' :
                if(bflg){
                    errflg++;
                }
                else{
                    if((optarg[0]=='-')||(atoi(optarg)<4)||(atoi(optarg)>8)){ //Si prochaine element = option ou pas entre 4 et 8 erreur.
                        rflg++;
                        errflg++;
                    }
                    else{
                        nb_reg = atoi(optarg);
                        //printf("nb registers %d \n", nb_reg);
                    }
                }
                aflg++;
                oflg++;
                break;

            case 's' : 
                oflg++;
                if(vflg||bflg)
                    errflg++;
                else{
                    stop_after_syntax = true;
                }
                sflg++;
                break;

            case 'v' : 
                oflg++;
                if(sflg||bflg)
                    errflg++;
                else{
                    stop_after_verif = true;
                }
                vflg++;
                break;

            case 'h' : 
                if(bflg){
                    errflg++;
                }
                else{
                    hflg++;
                }                
                oflg++;
                break;

            case ':' :
                printf("Option -%c requires an argument\n", optopt);
                errflg++;
                oflg++;
                break;

            case '?' :
                printf("Unrecognize option -%c \n", optopt);
                printf("Please note that the compiler is case sensitive\n");
                hflg++;
                break;

            case 'b' : 
                if(oflg){
                    errflg++;
                }
                bflg++;
                oflg++;
                break;
        }
    }

    if(bflg){
        if(argc==2){
            int i =0;
            printf("***************************************************\n");
            printf("*                Compilateur minicc               *\n");
            printf("*              AlexiaTran & LiyunYang             *\n");
            printf("*                                                 *\n");
            printf("***************************************************\n");

            exit(0);
        }
        else{
            errflg++;
        }
    }
    if(hflg &&(!bflg)){
        printf("Options available are : \n");
        printf(" -b : Print compiler name and team member\n");
        printf(" -o <filename>: Define output file name\n");
        printf(" -t <int> : Define trace_level, between 0 and 5\n");
        printf(" -r <int>  : Define maximum number of registers to used\n");
        printf(" -s : Stop compiling after syntax validation\n");
        printf(" -v : Stop compiling after verification\n");
        printf(" -h : Print compiler options\n");
        if(oflg==1){
            exit(0);
        }
    }
    if(errflg){
            if(bflg){
                printf("***************************************************\n");
                printf("*                Compilateur minicc               *\n");
                printf("*              AlexiaTran & LiyunYang             *\n");
                printf("*                                                 *\n");
                printf("***************************************************\n");
                printf("Error : Option -b can not be used with any other options or input files\n");
                exit(2);
            }
            else if(sflg && vflg){
                printf("Error : Options -s and -v can not be used together\n");
            }
            else{
                if(tflg){
                    printf("Error : Option -t requires an argument between 0 and 5.\n");
                }
                if(rflg){
                    printf("Error : Option -r requires an argument between 4 and 8.\n");
                }
                if(inflg){
                    if(c > 1){
                        printf("Error : Command line has too many input files. \n");
                        errflg++;
                    }
                    if(infile == NULL){
                        printf("Error : No input file. \n");
                    }
                }
                if(outflg){
                    printf("Error: Option -o requires an argument.\n");
                }
                printf("Usage : ./minicc [-b] [-o] <Outputfilename> [-t]<int> [-r]<int> [-s] [-v] [-h] <Inputfilename>\n");
            }        
        exit(2);
    }
}

//https://pubs.opengroup.org/onlinepubs/009696899/functions/getopt.html


void free_nodes(node_t n) {
    // A implementer
    if(n){
        if (n -> opr[0] != NULL){
            f_listdeclvars(n->opr[0]);
            f_mainfunc(n->opr[1]);
        }
        else{
            f_mainfunc(n->opr[1]);
        }
        free(n->opr); n->opr = NULL;
        free(n);
        n=NULL;
        //printf("------------Free PROG OK-------------\n");
    }
    else{
        exit(1);
    }
}

//main
void f_mainfunc(node_t n) {
    if (n){
        f_block(n->opr[2]);

        free(n->opr[0]);
        n->opr[0] = NULL;
        
        free(n->opr[1]);
        n->opr[1] = NULL;
        
        free(n->opr[2]);
        n->opr[2] = NULL;

        free(n->opr); n->opr = NULL;
        free(n);
        n=NULL;
        //printf("------------Free MAIN OK-------------\n");
    }
}

// block
void f_block(node_t n){
    if(n){
        if(n->opr[0]){
            f_listdeclvars(n->opr[0]);  
            //printf("------------Free list_decl_vars OK-------------\n");     
        }
        f_listinst(n->opr[1]);
        free(n->opr[1]);
        n->opr[1] = NULL;

        free(n->opr); n->opr = NULL;
        //printf("------------Free BLOCK OK-------------\n");
    }   
}

void f_listinst(node_t n){
    //printf("%s\t%d nb nodes fils\n",node_nature2string(n->nature),n->nops);
    //printf("fils sont %s\t%s\n",node_nature2string(n->opr[0]->nature),node_nature2string(n->opr[1]->nature));
    if(n){
        if (n->nature == NODE_LIST){
            f_listinst(n->opr[0]);
            free(n->opr[0]);
            n->opr[0] = NULL;

            f_inst(n->opr[1]);
            free(n->opr[1]);
            n->opr[1] = NULL;
        }
        else {
            f_inst(n);
        }
        free(n->opr); n->opr = NULL;
    }
}

void f_listdeclvars(node_t n){
    //printf("****************%s\n",node_nature2string(n->nature));
    if(n->nature == NODE_DECLS){
        f_declvars(n);//decl_vars
    }
    else if(n->nature == NODE_LIST){
        f_listdeclvars(n->opr[0]); // avec n->opr[0]->type ?
        f_declvars(n->opr[1]);//decl_vars
    }
    free(n->opr); n->opr = NULL;
    //printf("------------Free list_decl_vars OK-------------\n");
}

// decl_vars
void f_declvars(node_t n){
    //printf("***************%s\n",node_nature2string(n->nature));
    f_type(n->opr[0]);        
    f_listtypedecl(n->opr[1]);
    free(n->opr); n->opr = NULL;
    free(n);
    n=NULL; 
    //printf("------------Free DECLS OK-------------\n");
}

// liste_decl_type
void f_listtypedecl(node_t n){
    //printf("*************%s\n",node_nature2string(n->nature));
    // vérifier les variables sont de mm type, pas de variables avec le mm nom
    if (n->nature == NODE_LIST){
        f_listtypedecl(n->opr[0]); 
        //expression
        f_declvar(n->opr[1]);
        free(n->opr); n->opr = NULL;
    }
    else if (n->nature == NODE_DECL) {
        f_declvar(n);
    }
    free(n);
    n= NULL;
}

// decl_var
void f_declvar(node_t n){
    //node_t nodeIdent = n-> opr[0]; // varaible
    if(n->opr[1] ) { // s'il y a une expression EX: int a = 1 ;

        f_expr(n->opr[1]);   
    }
    if(n->opr[0]){
        free(n->opr[0]->ident); n->opr[0]->ident=NULL;
        free(n->opr[0]);
        n->opr[0]=NULL;
    }
    //printf("------------Free IDENT (dans decl) OK-------------\n");
}

// type
void f_type(node_t n){
    free(n->opr); n->opr = NULL;
    //printf("------------Free TYPE OK-------------\n");
    free(n);
    n=NULL;
}

void f_inst(node_t n){
    //printf("%s\n",node_nature2string(n->nature));
    if(n == NULL){ // cas: TOK_SEMICOL
        return;
    }else{
        switch(n->nature){
            case NODE_IF:
                f_expr(n->opr[0]); //free(n->opr[0]); n->opr[0] = NULL;
                f_inst(n->opr[1]); //free(n->opr[1]); n->opr[1] = NULL;
                if(n->nops == 3){
                    f_inst(n->opr[2]);
                    free(n->opr[2]);
                    n->opr[2] = NULL;
                }
                free(n->opr); n->opr = NULL;
                break;
            case NODE_WHILE:
                f_expr(n->opr[0]);//free(n->opr[0]); n->opr[0] = NULL;
                f_inst(n->opr[1]);//free(n->opr[1]); n->opr[1] = NULL;
                free(n->opr); n->opr = NULL;
                //free(n);
                //n=NULL;
                break;
            case NODE_FOR:
                f_expr(n->opr[0]); //free(n->opr[0]); n->opr[0] = NULL;
                f_expr(n->opr[1]); //free(n->opr[1]); n->opr[1] = NULL;
                f_expr(n->opr[2]); //free(n->opr[2]); n->opr[2] = NULL;
                f_inst(n->opr[3]); //free(n->opr[3]); n->opr[3] = NULL;
                free(n->opr); n->opr = NULL;
                //free(n);
                //n=NULL;
                break;
            case NODE_DOWHILE:
                f_inst(n->opr[0]); //free(n->opr[0]); n->opr[0] = NULL;
                f_expr(n->opr[1]); //free(n->opr[1]); n->opr[1] = NULL;
                free(n->opr); n->opr = NULL;
                break;
            case NODE_BLOCK:
                f_block(n);
                free(n->opr); n->opr = NULL;
                //printf("passe ------------  sous block\n");
                break;
            case NODE_PRINT:
                f_listparamprint(n->opr[0]);
                //free(n->opr[0]);    n->opr[0] = NULL;
                free(n->opr); n->opr = NULL;
                break;
            default:
                f_expr(n);
                free(n->opr); n->opr = NULL;
                break;
        }
    }
}

// expr
void f_expr(node_t n){
    //printf("********************%s\n", node_nature2string(n->nature)); 
    switch(n->nature){
        case NODE_LT:
        case NODE_GT:
        case NODE_LE:
        case NODE_GE:
            f_expr(n->opr[0]); //free(n->opr[0]); n->opr[0] = NULL;
            f_expr(n->opr[1]); //free(n->opr[1]); n->opr[1] = NULL;
            free(n->opr); n->opr = NULL;
            break;
        case NODE_EQ:
        case NODE_NE:
            f_expr(n->opr[0]); //free(n->opr[0]); n->opr[0] = NULL;
            f_expr(n->opr[1]); //free(n->opr[1]); n->opr[1] = NULL;
            free(n->opr); n->opr = NULL;
            break;
        case NODE_AND:
        case NODE_OR:
            f_expr(n->opr[0]); //free(n->opr[0]); n->opr[0] = NULL;
            f_expr(n->opr[1]); //free(n->opr[1]); n->opr[1] = NULL;
            free(n->opr); n->opr = NULL;
            break;
        case NODE_MINUS:
        case NODE_PLUS:
        case NODE_MUL:
        case NODE_DIV:
        case NODE_MOD:
        case NODE_BAND:
        case NODE_BOR:
        case NODE_BXOR:
        case NODE_SLL:
        case NODE_SRL:
        case NODE_SRA:
            f_expr(n->opr[0]); //free(n->opr[0]); n->opr[0] = NULL;
            f_expr(n->opr[1]); //free(n->opr[1]); n->opr[1] = NULL;
            free(n->opr); n->opr = NULL;
            break;
        case NODE_UMINUS:
        case NODE_NOT: // ! avec une variable de type bool
        case NODE_BNOT: //~ avec une variable de type int
            f_expr(n->opr[0]); //free(n->opr[0]); n->opr[0] = NULL;
            free(n->opr); n->opr = NULL;
            break;
        case NODE_AFFECT:
            //if(n->opr[0]){
                f_expr(n->opr[0]);
            //}
            //if(n->opr[1]){
                f_expr(n->opr[1]);  
            //}
             //free(n->opr[0]); n->opr[0] = NULL;
             //free(n->opr[1]); n->opr[1] = NULL;
            free(n->opr); n->opr = NULL;
            //printf("------------Free Affect OK--------------\n");
            //free(n->opr); n->opr = NULL;
            break;
        case NODE_INTVAL:
            //free(n->opr[0]); n->opr[0] = NULL;
            /*
            if(n->value){
                free(n->value); n->value = NULL;
            }
            */
            // free node fils 
            free(n->opr); n->opr = NULL;
            free(n); n = NULL;
            //printf("------------Free INTVAL OK-------------\n");
            break;
        case NODE_IDENT:
            if(n){
                if(n->ident){
                free(n->ident); n->ident= NULL;
            }
                free(n->opr); n->opr = NULL;
                free(n); n = NULL; 
            //printf("------------Free Ident OK-------------\n");
            }
            break;
        case NODE_BOOLVAL:
        default:
            free(n);
            n=NULL;
            break;
    }
}


// liste_param_print
void f_listparamprint(node_t n){
    //printf("%s\n",node_nature2string(n->nature));;
    if(n->nature == NODE_LIST)
    {
        f_listparamprint(n->opr[0]); //free(n->opr[0]); n->opr[0] = NULL;
        f_paramprint(n->opr[1]); //free(n->opr[1]); n->opr[1] = NULL;
        free(n->opr); n->opr = NULL;
    }else{
        f_paramprint(n);
    }
}
// param_print
void f_paramprint(node_t n){
    //printf("param_print\n");
    if(n->nature != NODE_STRINGVAL){
        f_expr(n);
    }
    else{
        free(n->str); n->str = NULL;
        free(n->opr); n->opr = NULL; // review
        free(n);
        n=NULL;   
    } 
}


char * strdupBis(char * s) {
    char * r = malloc(strlen(s) + 1);
    strcpy(r, s);
    return r;
}


static int32_t dump_tree2dot_rec(FILE * f, node_t n, int32_t node_num) {

    if (n == NULL) {
        fprintf(f, "    N%d [shape=record, label=\"{{NULL}}\"];\n", node_num);
        return node_num;
    }

    switch (n->nature) {
        case NODE_IDENT:
            {
                node_t decl_node = n-> decl_node;
                fprintf(f, "    N%d [shape=record, label=\"{{NODE %s|Type: %s}|{<decl>Decl      |Ident: %s|Offset: %d}}\"];\n", node_num, node_nature2string(n->nature), node_type2string(n->type), n->ident, n->offset);
                if (decl_node != NULL && decl_node != n) {
                    fprintf(f, "    edge[tailclip=false];\n");
                    fprintf(f, "    \"N%d\":decl:c -> \"N%d\" [style=dashed]\n", node_num, decl_node->node_num);
                }
                break;
            }
        case NODE_INTVAL:
        case NODE_BOOLVAL:
            fprintf(f, "    N%d [shape=record, label=\"{{NODE %s|Type: %s}|{Value: %" PRId64 "}}\"];\n", node_num, node_nature2string(n->nature), node_type2string(n->type), n->value);
            break;
        case NODE_STRINGVAL:
            {
                char str[32];
                int32_t i = 1;
                while (true) {
                    str[i - 1] = n->str[i];
                    i += 1;
                    if (n->str[i] == '"') {
                        str[i - 1] = '\0';
                        break;
                    }
                }
                fprintf(f, "    N%d [shape=record, label=\"{{NODE %s|Type: %s}|{val: %s}}\"];\n", node_num, node_nature2string(n->nature), node_type2string(n->type), str);
            }
            break;
        case NODE_TYPE:
            fprintf(f, "    N%d [shape=record, label=\"{{NODE %s|Type: %s}}\"];\n", node_num, node_nature2string(n->nature), node_type2string(n->type));
            break;
        case NODE_LIST:
            fprintf(f, "    N%d [shape=record, label=\"{{NODE LIST}}\"];\n", node_num);
            break;
        case NODE_PROGRAM:
        case NODE_BLOCK:
        case NODE_DECLS:
        case NODE_DECL:
        case NODE_IF:
        case NODE_WHILE:
        case NODE_FOR:
        case NODE_DOWHILE:
        case NODE_PRINT:
            fprintf(f, "    N%d [shape=record, label=\"{{NODE %s|Nb. ops: %d}}\"];\n", node_num, node_nature2string(n->nature), n->nops);
            break;
        case NODE_FUNC:
            fprintf(f, "    N%d [shape=record, label=\"{{NODE %s|Nb. ops: %d}|{offset: %d}}\"];\n", node_num, node_nature2string(n->nature), n->nops, n->offset);
            break;
        case NODE_PLUS:
        case NODE_MINUS:
        case NODE_MUL:
        case NODE_DIV:
        case NODE_MOD:
        case NODE_LT:
        case NODE_GT:
        case NODE_LE:
        case NODE_GE:
        case NODE_EQ:
        case NODE_NE:
        case NODE_AND:
        case NODE_OR:
        case NODE_BAND:
        case NODE_BOR:
        case NODE_BXOR:
        case NODE_SRA:
        case NODE_SRL:
        case NODE_SLL:
        case NODE_NOT:
        case NODE_BNOT:
        case NODE_UMINUS:
        case NODE_AFFECT:
            fprintf(f, "    N%d [shape=record, label=\"{{NODE %s|Type: %s|Nb. ops: %d}}\"];\n", node_num, node_nature2string(n->nature), node_type2string(n->type), n->nops);
            break;
        default:
            printf("*** Error in %s: unknow nature : %s\n", __func__, node_nature2string(n->nature));
            assert(false);
    }

    n->node_num = node_num;

    int32_t curr_node_num = node_num + 1;
    for (int32_t i = 0; i < n->nops; i += 1) {
        int32_t new_node_num = dump_tree2dot_rec(f, n->opr[i], curr_node_num);

        fprintf(f, "    edge[tailclip=true];\n");
        fprintf(f, "    N%d -> N%d\n", node_num, curr_node_num);
        curr_node_num = new_node_num + 1;
    }

    return curr_node_num - 1;
}



static void dump_tree2dot(FILE * f, node_t root) {
    assert(root->nature == NODE_PROGRAM);

    int32_t curr_node_num = 1;
    dump_tree2dot_rec(f, root, curr_node_num);
}


void dump_tree(node_t prog_root, const char * dotname) {

    FILE * f;

    f = fopen(dotname, "w");
    fprintf(f, "digraph global_vars {\n");
    dump_tree2dot(f, prog_root);
    fprintf(f, "}");    
    fclose(f);
}


const char * node_type2string(node_type t) {
    switch (t) {
        case TYPE_NONE:
            return "TYPE NONE";
        case TYPE_INT:
            return "TYPE INT";
        case TYPE_BOOL:
            return "TYPE BOOL";
        case TYPE_VOID:
            return "TYPE VOID";
        case TYPE_STRING:
            return "TYPE STRING";
        default:
            assert(false);
    }
}


const char * node_nature2string(node_nature t) {
    switch (t) {
        case NONE:
            return "NONE";
        case NODE_PROGRAM:
            return "PROGRAM";
        case NODE_BLOCK:
            return "BLOCK";
        case NODE_LIST:
            return "LIST";
        case NODE_DECLS:
            return "DECLS";
        case NODE_DECL:
            return "DECL";
        case NODE_IDENT:
            return "IDENT";
        case NODE_TYPE:
            return "TYPE";
        case NODE_INTVAL:
            return "INTVAL";
        case NODE_BOOLVAL:
            return "BOOLVAL";
        case NODE_STRINGVAL:
            return "STRINGVAL";
        case NODE_FUNC:
            return "FUNC";
        case NODE_IF:
            return "IF";
        case NODE_WHILE:
            return "WHILE";
        case NODE_FOR:
            return "FOR";
        case NODE_DOWHILE:
            return "DOWHILE";
        case NODE_PLUS:
            return "PLUS";
        case NODE_MINUS:
            return "MINUS";
        case NODE_MUL:
            return "MUL";
        case NODE_DIV:
            return "DIV";
        case NODE_MOD:
            return "MOD";
        case NODE_LT:
            return "LT";
        case NODE_GT:
            return "GT";
        case NODE_LE:
            return "LE";
        case NODE_GE:
            return "GE";
        case NODE_EQ:
            return "EQ";
        case NODE_NE:
            return "NE";
        case NODE_AND:
            return "AND";
        case NODE_OR:
            return "OR";
        case NODE_BAND:
            return "BAND";
        case NODE_BOR:
            return "BOR";
        case NODE_BXOR:
            return "BXOR";
        case NODE_SLL:
            return "SLL";
        case NODE_SRA:
            return "SRA";
        case NODE_SRL:
            return "SRL";
        case NODE_NOT:
            return "NOT";
        case NODE_BNOT:
            return "BNOT";
        case NODE_UMINUS:
            return "UMINUS";
        case NODE_AFFECT:
            return "AFFECT";
        case NODE_PRINT:
            return "PRINT";
        default:
            fprintf(stderr, "*** Error in %s: Unknown node nature: %d\n", __func__, t);
            exit(1);
    }
}




const char * node_nature2symb(node_nature t) {
    switch (t) {
        case NONE:
        case NODE_PLUS:
            return "+";
        case NODE_MINUS:
            return "-";
        case NODE_MUL:
            return "*";
        case NODE_DIV:
            return "/";
        case NODE_MOD:
            return "%";
        case NODE_LT:
            return "<";
        case NODE_GT:
            return ">";
        case NODE_LE:
            return "<=";
        case NODE_GE:
            return ">=";
        case NODE_EQ:
            return "==";
        case NODE_NE:
            return "!=";
        case NODE_AND:
            return "&&";
        case NODE_OR:
            return "||";
        case NODE_BAND:
            return "&";
        case NODE_BOR:
            return "|";
        case NODE_BXOR:
            return "^";
        case NODE_SRA:
            return ">>";
        case NODE_SRL:
            return ">>>";
        case NODE_SLL:
            return "<<";
        case NODE_NOT:
            return "!";
        case NODE_BNOT:
            return "~";
        case NODE_UMINUS:
            return "-";
        default:
            fprintf(stderr, "*** Error in %s: Unknown node nature: %d\n", __func__, t);
            exit(1);
    }
}