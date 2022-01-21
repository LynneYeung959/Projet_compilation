
#ifndef _PASSE_1_
#define _PASSE_1_

#include "defs.h"


void analyse_passe_1(node_t root);
void analyse_mainfunc(node_t n);
void analyse_expr(node_t n);
void analyse_listinst(node_t n);
void analyse_inst(node_t n);
void analyse_listdeclvars(node_t n, bool global);
void analyse_block(node_t n);
void analyse_type(node_t n);
void analyse_declvars(node_t n, bool global);
void analyse_listtypedecl(node_t n, node_type t, bool global);
void analyse_vardecl(node_t n, node_type t, bool global);
void analyse_listparamprint(node_t n);
void analyse_paramprint(node_t n);

#endif

