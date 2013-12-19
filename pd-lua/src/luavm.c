#include<stdlib.h>
#include<string.h>
#include<luavm.h>
#include<lua.h>
#include<lualib.h>
#include<lauxlib.h>
static t_class*luavm_class;
void luavm_setup(void)
{
	luavm_class=class_new
	(
		gensym("luavm"),
		(t_newmethod)luavm_new,
		(t_method)luavm_del,
		sizeof(luavm),
		CLASS_DEFAULT,
		A_DEFSYMBOL,
		0
	);
	class_addbang(luavm_class,(t_method)luavm_bang);
	class_doaddfloat(luavm_class,(t_method)luavm_dofn);
	//class_addmethod(luavm_class,(t_method)luavm_set,gensym("set"),A_GIMME,0);
	//class_addmethod(luavm_class,(t_method)luavm_get,gensym("get"),A_GIMME,0);
	class_addmethod(luavm_class,(t_method)luavm_init,gensym("init"),0);
	class_addmethod(luavm_class,(t_method)luavm_load,gensym("load"),A_DEFSYMBOL,0);
	class_addmethod(luavm_class,(t_method)luavm_eval,gensym("eval"),A_GIMME,0);
	class_addmethod(luavm_class,(t_method)luavm_call,&s_anything,A_GIMME,0);
}
void*luavm_new(const t_symbol*s)
{
	luavm*ins=(luavm*)pd_new(luavm_class);
	ins->name=strlen(s->s_name)?strcpy(malloc(strlen(s->s_name)+1),s->s_name):0;
	luavm_allock(ins);
	luavm_init(ins);
	ins->outlet=outlet_new(&ins->self,&s_anything);
	return(void*)ins;
}
void luavm_del(luavm*ins)
{
	if(ins->vm)luavm_unlock(ins);
	if(ins->name)free(ins->name);
	outlet_free(ins->outlet);
}
void luavm_set(luavm*const ins,const t_symbol*const s,const int argc,t_atom*argv)
{

}
void luavm_get(luavm*const ins,const t_symbol*const s,const int argc,t_atom*argv)
{
	lua_pushstring(ins->vm,atom_getsymbol(argv+1)->s_name);
	lua_rawget(ins->vm,LUA_GLOBALSINDEX);
	luavm_send(ins);
	lua_settop(ins->vm,0);
}
void luavm_load(luavm*const ins,const t_symbol*const s)
{
	if(luaL_dofile(ins->vm,s->s_name))
		post("luavm: Script file is not correct");
	else
		luavm_send(ins);	
	lua_settop(ins->vm,0);
}
void luavm_eval(luavm*const ins,const t_symbol*const s,const int argc,t_atom*const argv)
{
	register int k,K;
	char*	src=0;
	int	sum=0;
	for(k=0,K=argc;k<K;++k)
	{
		switch(argv[k].a_type)
		{
		case A_SYMBOL:
			{
				int pch=strlen(atom_getsymbol(argv+k)->s_name);
				src=realloc(src,sum+pch+1);
				memcpy(src+sum,atom_getsymbol(argv+k)->s_name,pch);
				src[sum+pch]=' ';
				sum+=pch+1;
			}
			break;
		case A_FLOAT:
			{
				char	buff[64];
				sprintf(buff,"%lf",atom_getfloat(argv+k));
				int pch=strlen(buff);
				src=realloc(src,sum+pch+1);
				memcpy(src+sum,buff,pch);
				src[sum+pch]=' ';
				sum+=pch+1;
			}
			break;
		default:
			break;
		}
	}
	src[sum-1]=0;
	if(luaL_dostring(ins->vm,src))
		post("luam: Script source is not correct");
	else
		luavm_send(ins);	
	lua_settop(ins->vm,0);
	free(src);
}
