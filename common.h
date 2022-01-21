#ifndef _COMMON_H_
#define _COMMON_H_

#include "defs.h"


void parse_args(int argc, char ** argv);
void free_nodes(node_t n);
char * strdupBis(char * s);
void dump_tree(node_t prog_root, const char * filename);
const char * node_type2string(node_type t);
const char * node_nature2string(node_nature t);
const char * node_nature2symb(node_nature t);

void f_mainfunc(node_t n);
void f_block(node_t n);
void f_listinst(node_t n);
void f_listdeclvars(node_t n);
void f_declvars(node_t n);
void f_listtypedecl(node_t n);
void f_declvar(node_t n);
void f_type(node_t n);
void f_inst(node_t n);
void f_expr(node_t n);
void f_listparamprint(node_t n);
void f_paramprint(node_t n);

#endif
