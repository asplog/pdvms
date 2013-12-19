#include<stdlib.h>
#include<m_pd.h>
#include<luavm.h>
#include<lua.h>
#include<lualib.h>
#include<lauxlib.h>
void luavm_send(luavm*ins)
{
	register int k,K;
	register int depth=lua_gettop(ins->vm);
	switch(depth)
	{
	case 0:
		break;
	case 1:
		if(lua_isnil(ins->vm,-1));
		else if(lua_isnumber(ins->vm,-1))
			outlet_float(ins->outlet,lua_tonumber(ins->vm,-1));
		else if(lua_isstring(ins->vm,-1))
			outlet_symbol(ins->outlet,gensym(lua_tostring(ins->vm,-1)));
		else
			outlet_symbol(ins->outlet,&s_anything);
		break;
	default:
		{
			t_atom*atom=(t_atom*)alloca(sizeof(t_atom)*depth);
			for(k=0,K=depth;k<K;++k)
			{
				register int index=-depth+k;
				if(lua_isnil(ins->vm,index))
					SETSYMBOL(atom+k,&s_);
				else if(lua_isnumber(ins->vm,index))
					SETFLOAT(atom+k,lua_tonumber(ins->vm,index));
				else if(lua_isstring(ins->vm,index))
					SETSYMBOL(atom+k,gensym(lua_tostring(ins->vm,index)));
				else
					SETSYMBOL(atom+k,&s_anything);
			}
			outlet_list(ins->outlet,gensym("list"),depth,atom);
		}
		break;	
	}
}
