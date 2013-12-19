#ifndef PD_LUA_BASE
#define PD_LUA_BASE
#include"m_pd.h"
typedef struct __luavm
{
	t_object	self;
	char*		name;
	void*		vm;
	void*		outlet;
}luavm;
void luavm_setup(void);
void*luavm_new(const t_symbol*);
void luavm_del(luavm*const);
void luavm_get(luavm*const,const t_symbol*const,const int,t_atom*const);
void luavm_set(luavm*const,const t_symbol*const,const int,t_atom*const);
void luavm_bang(luavm*const);
void luavm_dofn(luavm*const,const t_floatarg);
void luavm_init(luavm*const);
void luavm_term(luavm*const);
void luavm_load(luavm*const,const t_symbol*const);
void luavm_eval(luavm*const,const t_symbol*const,const int,t_atom*const);
void luavm_call(luavm*const,const t_symbol*const,const int,t_atom*const);
void luavm_send(luavm*const);
void luavm_allock(luavm*const);
void luavm_unlock(luavm*const);
#endif
