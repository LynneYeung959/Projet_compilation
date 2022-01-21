#ifndef _PASSE_2_H_
#define _PASSE_2_H_

#include "defs.h"

void gen_code_passe_2(node_t root);
void liste_decl_vars(node_t n);
void gen_main(node_t n);
void decl_vars(node_t n);
void gen_var(node_t n);
void block(node_t n);
void list_inst(node_t n);
void inst(node_t n);
void expr(node_t n);
void listparamprint(node_t n);
void paramprint(node_t n);


#endif

