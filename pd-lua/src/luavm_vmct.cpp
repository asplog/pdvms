extern"C"
{
	#include<m_pd.h>
	#include<luavm.h>
	#include<lua.h>
	#include<lualib.h>
	#include<lauxlib.h>
}
#include<map>
#include<string>
static std::map<std::string,std::pair<unsigned int,lua_State*> > vms;
void luavm_allock(luavm*const ins)
{
	if(ins->name)
	{
		if(!vms[ins->name].first++)
			vms[ins->name].second=luaL_newstate();
		ins->vm=vms[ins->name].second;
	}
	else ins->vm=luaL_newstate();
}
void luavm_unlock(luavm*const ins)
{
	if(ins->name)
	{
		if(!--vms[ins->name].first)
			lua_close(vms[ins->name].second);
		ins->vm=0;
	}
	else lua_close((lua_State*)ins->vm),ins->vm=0;
}
