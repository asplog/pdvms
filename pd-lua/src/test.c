#include<lua.h>
#include<lualib.h>
#include<lauxlib.h>
int main(int argc,char**argv)
{
	lua_State*vm=luaL_newstate();
	luaL_openlibs(vm);
	//luaL_dostring(vm,"math.log(2)");
	lua_getglobal(vm,"math");
	lua_getglobal(vm,"log");
	lua_pushnumber(vm,4);
	lua_pcall(vm,1,1,0);
	double r=lua_tonumber(vm,-1);
	printf("%f",r);
	lua_close(vm);
	return 0;
}
