/*
 * =====================================================================================
 *
 *       Filename:  gs_script.c
 *
 *    Description:  脚本控制器
 *
 *        Version:  1.0
 *        Created:  06/04/2013 09:36:18 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  evan (just think), cppmain@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "gs_script.h"

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

void v(void){

	lua_State *L = lua_open();
	luaopen_base(L);
	luaopen_table(L);
	luaopen_io(L);
	luaopen_string(L);
	luaopen_math(L);


}
