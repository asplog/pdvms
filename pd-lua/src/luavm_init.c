#include<m_pd.h>
#include<luavm.h>
#include<lua.h>
#include<lualib.h>
#include<lauxlib.h>
int print(lua_State*vm)
{
	post(lua_tostring(vm,-1));
	lua_settop(vm,0);
	return 0;
}
/*
void luavm_regs(void*vm)
{
	int gc(lua_State*vm)
	{
		return 0;
	}
	int ts(lua_State*vm)
	{
		lua_pushstring(L,"pd");
		return 1;
	}
	lua_newtable(vm);
	int methods=lua_gettop(vm);
	
	lua_newtable(vm,"pd");
	int metatable=lua_gettop(vm);

	lua_pushstring(vm,"pd");
	lua_pushvalue(vm,methods);
	lua_settable(vm,LUA_GLOBALSINDEX);

	lua_pushliteral(vm,"__metatable");
	lua_pushvalue(vm,methods);
	lua_settable(vm,metatable);
	
	lua_pushliteral(vm,"__index");
	lua_pushvalue(vm,methods);
	lua_settable(vm,metatable);
	
	lua_pushliteral(vm,"__tostring");
	lua_pushvalue(vm,methods);
	lua_settable(vm,metatable);
}
*/
void luavm_init(luavm*const ins)
{
	luaopen_base(ins->vm);
	luaopen_table(ins->vm);
	//luaopen_io(ins->vm);
	luaopen_string(ins->vm);
	luaopen_math(ins->vm);
	//luaopen_debug(ins->vm);
	lua_register(ins->vm,"print",print);
	lua_settop(ins->vm,0);
}
