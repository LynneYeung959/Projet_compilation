#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "defs.h"
#include "passe_2.h"
#include "miniccutils.h"
#include "common.h"

int32_t nb_label;
int32_t reg_stack;
bool data_fini = 0;
int nb_string;
int32_t lireChaine = 0;

void gen_code_passe_2(node_t root){
    assert(root->nature == NODE_PROGRAM);
    set_temporary_start_offset(8);
    for(int i = 0; i<2;i++){
        if (root -> opr[0] != NULL){ // Declaration des variables avant 'main'
            //printf(" Declaration des variables globales\n");
            if(i==0){
                create_inst_data_sec();
            }
            liste_decl_vars(root->opr[0]); // variables globales
            gen_main(root->opr[1]);// main
        }
        else{
            gen_main(root->opr[1]); // main
        }
        data_fini=1;
    }
    // exit
    create_inst_ori((int32_t)2, get_r0(),(int32_t)10);
    create_inst_syscall();
}

//liste_decl_vars
void liste_decl_vars(node_t n){
    if(n->nature == NODE_LIST){
        liste_decl_vars(n->opr[0]);
        decl_vars(n->opr[1]);
    }else if(n->nature == NODE_DECLS){
        decl_vars(n);
    }else if(n->nature == NODE_STRINGVAL){
        if(!data_fini){
            create_inst_asciiz(NULL, n->str);
        }
    }
}

void gen_main(node_t n){
    //printf(" Programme 'main'\n");
    assert(n->nature == NODE_FUNC);
    // affichage label 'main'
    if(data_fini){
        create_inst_text_sec();
        create_inst_label_str(n -> opr[1]-> ident); // lable 'main'
        //push_temporary(n->offset);
        create_inst_stack_allocation();
        reg_stack = get_stack_reg();
    }
    block(n -> opr[2]);
    nb_string = (int)get_global_strings_number();
    //printf("nb de string est %d \n", nb_string);
    if(data_fini){
        create_inst_stack_deallocation(n->offset);
    }
}

void decl_vars(node_t n){
    //printf("\t%s\n", node_nature2string(n->nature));
    node_t nodeInter = n->opr[1];
    if(nodeInter->nature == NODE_LIST){
        decl_vars(nodeInter->opr[0]);
        gen_var(nodeInter->opr[1]);
    }
    else if(nodeInter->nature == NODE_DECL){
        gen_var(nodeInter);
    }
}

void gen_var(node_t n){
        // variables globales
        if(n -> opr[0]-> global_decl && (! data_fini)){
            char* var = n->opr[0]->ident;
            int32_t valeur;
            if( n->opr[1] != NULL ){ // si int a = b;
                valeur = n->opr[1]->value;
                //printf(" type var_globale = var;\n");    
            }
            else{ // si int a;
                valeur = 0;
                //printf(" type var_globale;\n");
            }
            // écrit dans .data
            create_inst_word(var,valeur); 
        }
        else if (!(n -> opr[0]-> global_decl ) && data_fini){ // variables locales  -  écrit dans .text
            if(n->opr[1] != NULL){
                // int/bool a = IDENT/INTVAL
                //printf(" type var_locale = var;\n");
                node_t nodeInter = n->opr[1]; // coté droite de l'égalité
                if(nodeInter-> nature == NODE_IDENT){
                    create_inst_lui(get_first_reg(), get_data_sec_start_addr());
                    node_t nodeInter_init = nodeInter-> decl_node;
                    create_inst_lw(get_current_reg(), nodeInter_init->offset , get_current_reg());
                }
                else{
                    expr(nodeInter);
                }
                // les variables locales sont toujour dans $29
                create_inst_sw(get_current_reg(), n->opr[0]->offset, reg_stack);
                //printf("----%d----\n",get_temporary_curr_offset());
            }
            else{
                 
                //printf(" type var_locale;\n");
            }
        } 
}

void block(node_t n){
    if(n){
        if(n -> opr[0]){
            liste_decl_vars(n -> opr[0]);
        }
        list_inst(n -> opr[1]);
    }
}

void list_inst(node_t n){
    if(n){
        if(n->nature == NODE_LIST){
            list_inst(n->opr[0]);
            inst(n->opr[1]);
        }
        else{
            inst(n);
        }
    }
}

void inst(node_t n){
    if(n){
        //printf("\t%s\n", node_nature2string(n->nature));
        switch(n->nature){
            case NODE_IF:
                expr(n->opr[0]);
                inst(n->opr[1]);
                inst(n->opr[2]);
                break;
            case NODE_WHILE:
                expr(n->opr[0]);
                inst(n->opr[1]);
                if(data_fini){
                    create_inst_j(nb_label);
                    nb_label = get_new_label();
                    create_inst_label(nb_label); // nouvelle label
                }
                break;
            case NODE_FOR:
                expr(n->opr[0]);
                expr(n->opr[1]);
                expr(n->opr[2]);
                inst(n->opr[3]);
                if(data_fini){
                    create_inst_j(nb_label);
                    nb_label = get_new_label();
                    create_inst_label(nb_label); // nouvelle label
                }
                break;
            case NODE_DOWHILE:
                inst(n->opr[0]);
                expr(n->opr[1]);
                if(data_fini){
                    create_inst_j(nb_label);
                    nb_label = get_new_label();
                    create_inst_label(nb_label); // nouvelle label
                }
                break;
            case NODE_BLOCK:
                block(n);
                break;
            case NODE_PRINT:
                listparamprint(n->opr[0]);
                lireChaine = 0;
                break;
            default:
                expr(n);
                break;
        }
    }
}

void expr(node_t n){
    //printf("\t%s\n", node_nature2string(n->nature));
    switch(n->nature){
        case NODE_LT:
        //printf("------------------");
            if(data_fini){
                nb_label = get_new_label();
                create_inst_label(nb_label);
                int32_t reg_src2;
                // fils 1
                if(n->opr[0]->nature != NODE_IDENT){
                    expr(n->opr[0]);
                }
                else{
                    node_t nodeInter_1 = n->opr[0] -> decl_node;
                    create_inst_lw(get_current_reg(), nodeInter_1->offset , reg_stack);  
                }
                // fils 2
                if(n->opr[1]->nature != NODE_IDENT){
                    expr(n->opr[1]);
                }
                else{
                    node_t nodeInter_2 = n->opr[1]-> decl_node;
                    if(reg_available()){
                        allocate_reg();
                    }
                    reg_src2 = get_current_reg();
                    create_inst_lw(reg_src2, nodeInter_2->offset , reg_stack); 
                    release_reg(); 
                }
                if(n->opr[1]->nature == NODE_INTVAL){
                    // slti - set if less than immediate
                    create_inst_slti(get_current_reg(), get_current_reg(), n->opr[1]->value);
                }else{
                    // set if less than (Rd < -1 if R1 < R2 else 0)
                    create_inst_slt(get_current_reg(), get_current_reg(), reg_src2);
                }
                create_inst_beq(get_current_reg(), get_r0(), nb_label+1);
            }
            else{
                expr(n->opr[0]);
                expr(n->opr[1]);
            }
            break;
        case NODE_GT:
            if(data_fini){
                nb_label = get_new_label();
                create_inst_label(nb_label);
            }
            expr(n->opr[0]);
            expr(n->opr[1]);
            if(data_fini){
                // set if less than (Rd < -1 if R1 < R2 else 0)
                create_inst_slt(get_current_reg(),get_restore_reg(),get_current_reg());
                create_inst_beq(get_current_reg(), get_restore_reg(), nb_label+1);
                //create_inst_beq(int32_t r_src_1, int32_t r_src_2, int32_t label);
            }
            break;
        case NODE_LE:
        case NODE_GE:
            if (data_fini){
                create_inst_beq(get_current_reg(), get_restore_reg(), nb_label+1);
            //create_inst_beq(int32_t r_src_1, int32_t r_src_2, int32_t label);

            }
            break;
        case NODE_EQ:
        case NODE_NE:
            if(!data_fini){
                expr(n->opr[0]);
                expr(n->opr[1]);
            }
            else{

            }
            
        
            break;
        case NODE_AND:
        
        case NODE_OR:
            expr(n->opr[0]);
            expr(n->opr[1]);
        
            break;
        case NODE_MINUS:
            if(!data_fini){
                expr(n->opr[0]);
                expr(n->opr[1]);
            }
            else{
                int32_t reg_lw;
                int32_t reg_src2;
                // fils 1
                expr(n->opr[0]);
                if(!reg_available()){
                    push_temporary(get_current_reg());
                }
                // fils 2    
                if(reg_available()){
                    reg_src2 = get_current_reg();
                    allocate_reg();
                    expr(n->opr[1]);
                    create_inst_subu(reg_src2, reg_src2, get_current_reg());
                    release_reg();
                }else{
                    expr(n->opr[1]);
                    reg_lw = get_current_reg()+1;
                    pop_temporary(reg_lw);
                    create_inst_subu(get_current_reg(), reg_lw, get_current_reg());  
                }     
            }
            break;
        case NODE_PLUS:
            if(!data_fini){
                expr(n->opr[0]);
                expr(n->opr[1]);
            }
            else{
                int32_t reg_lw;
                int32_t reg_src2;
                // fils 1
                expr(n->opr[0]);
                if(!reg_available()){
                    push_temporary(get_current_reg());
                }
                // fils 2    
                if(reg_available()){
                    reg_src2 = get_current_reg();
                    allocate_reg();
                    expr(n->opr[1]);
                    create_inst_addu(reg_src2, reg_src2, get_current_reg());
                    release_reg();
                }else{
                    expr(n->opr[1]);
                    reg_lw = get_current_reg()+1;
                    pop_temporary(reg_lw);
                    create_inst_addu(get_current_reg(), reg_lw, get_current_reg());  
                }     
            }
            break;
        case NODE_MUL:
            if(!data_fini){
                expr(n->opr[0]);
                expr(n->opr[1]);
            }else{
                int32_t reg_lw;
                int32_t reg_src2;
                // fils 1
                expr(n->opr[0]);
                if(!reg_available()){
                    push_temporary(get_current_reg());
                }
                // fils 2    
                if(reg_available()){
                    reg_src2 = get_current_reg();
                    allocate_reg();
                    expr(n->opr[1]);
                    create_inst_mult(reg_src2, get_current_reg());
                    release_reg();
                }else{
                    expr(n->opr[1]);
                    reg_lw = get_current_reg()+1;
                    pop_temporary(reg_lw);
                    create_inst_mult(reg_lw, get_current_reg()); 
                }  
            }
            break;
        case NODE_DIV:
            if(!data_fini){
                expr(n->opr[0]);
                expr(n->opr[1]);
            }else{
                int32_t reg_lw;
                int32_t reg_src2;
                // fils 1
                expr(n->opr[0]);
                if(!reg_available()){
                    push_temporary(get_current_reg());
                }
                // fils 2    
                if(reg_available()){
                    reg_src2 = get_current_reg();
                    allocate_reg();
                    expr(n->opr[1]);
                    create_inst_div(reg_src2, get_current_reg());
                    release_reg();
                }else{
                    expr(n->opr[1]);
                    reg_lw = get_current_reg()+1;
                    pop_temporary(reg_lw);
                    create_inst_div(reg_lw, get_current_reg()); 
                }  
            }
            break;
        case NODE_MOD:
        case NODE_BAND:
        case NODE_BOR:
        case NODE_BXOR:
        case NODE_SLL:
        case NODE_SRL:
        case NODE_SRA:
            break;
        case NODE_UMINUS:
            expr(n->opr[0]);    
            break;
        case NODE_NOT:
            expr(n->opr[0]);
            break;
        case NODE_BNOT:
            expr(n->opr[0]);
            break;
        case NODE_AFFECT:
            //expr(n->opr[0]); //ident gauche
            expr(n->opr[1]);
            if(data_fini)
            { 
                node_t nodeInter = n-> opr[0]-> decl_node ; // partie gauche (ident)
                create_inst_sw(get_current_reg(), nodeInter->offset , reg_stack);
            }
            break;
        case NODE_INTVAL:
            if(data_fini){
                create_inst_addiu(get_current_reg(), get_r0(), (int32_t) n->value);
                //printf("value est : %ld\n",n->value);
            }
            break;
        case NODE_BOOLVAL:
            break;
        case NODE_IDENT:
            {
                if(data_fini){
                    node_t nodeInter = n-> decl_node;
                    if(lireChaine == 0){
                        create_inst_lw(get_current_reg(), nodeInter->offset , reg_stack);
                    }else{ // si pour lire la chaine de caractère de IDENT
                        create_inst_lw((int32_t)4, nodeInter->offset , reg_stack);
                    }
                    
                }  
            }
            break;
        default:
            //expr(n);
            break;
    }
}

void listparamprint(node_t n){
    if(n->nature == NODE_LIST){
        listparamprint(n->opr[0]);
        paramprint(n->opr[1]);
    }
    else{
        paramprint(n);
    }
    if(data_fini){
        
        create_inst_syscall();
    }
}

void paramprint(node_t n){
    
    if(n->nature == NODE_STRINGVAL){
        if(data_fini){
            //printf("\t%s\n", node_nature2string(n->nature));
            create_inst_lui((int32_t) 4, get_data_sec_start_addr());
            // à corriger registre et offset
            create_inst_ori((int32_t) 4, (int32_t)4,(int32_t)n->offset);
            create_inst_ori((int32_t)2,get_r0(),(int32_t)4);
            //printf( "ori nb_string est :%d\n", nb_string);   
        }
        else{
            create_inst_asciiz(NULL,n->str);   
        } 
        n->offset = add_string(n->str);
    }
    else{
        expr(n);
        if(data_fini){
            create_inst_ori((int32_t)2,get_r0(),(int32_t)1);
        } 
    }
}