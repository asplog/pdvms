#include<m_pd.h>
#include<luavm.h>
#include<lua.h>
#include<lualib.h>
#include<lauxlib.h>
#include<string.h>
#include<stdlib.h>
void luavm_call(luavm*const ins,const t_symbol*const s,const int argc,t_atom*const argv)
{
	void load(lua_State*vm,char*arg)
	{
		int push(lua_State*vm,int top,const char*arg)
		{
			if(top)
			{
				lua_getfield(vm,top,arg);
				lua_remove(vm,top-1);
			}
			else	lua_getglobal(vm,arg);
			--top;
			return top;
		};
		register size_t	len=strlen(arg);
		register char*	via=alloca(len);
		register char*	cur=via;
		register short	top=0;
		strcpy(via,arg);
		while(*cur)
		{
			if(cur[1]=='.')
			{
				cur[1]=0;
				top=push(vm,top,via);
				via=cur+2;
				cur=via;
			}
			++cur;
		}
		push(vm,top,via);
	};
	register int k,K;
	load(ins->vm,s->s_name);
	for(k=0,K=argc;k<K;++k)
	switch(argv[k].a_type)
	{
		case A_FLOAT:
			lua_pushnumber(ins->vm,atom_getfloat(argv+k));
			break;
		case A_SYMBOL:
			lua_pushstring(ins->vm,atom_getsymbol(argv+k)->s_name);
			break;
		default:
			lua_pushnil(ins->vm);
			break;
	}
	lua_pcall(ins->vm,argc,-1,0);
	luavm_send(ins);
	lua_settop(ins->vm,0);
}
void luavm_bang(luavm*const ins)
{
	lua_getglobal(ins->vm,"bang");
	luavm_send(ins);
	lua_settop(ins->vm,0);
}
void luavm_dofn(luavm*const ins,const t_floatarg f)
{
	lua_getglobal(ins->vm,"number");
	lua_pushnumber(ins->vm,f);
	lua_pcall(ins->vm,1,-1,0);
	luavm_send(ins);
	lua_settop(ins->vm,0);
}
