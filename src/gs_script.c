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

#include "gs_logger.h"


gs_script_engine_t *gs_script_engine_start(){

	gs_logger_info("初始化lua 脚本引擎");


	gs_script_engine_t *engine;


	engine.lua_state = lua_open();

	luaopen_base(engine.lua_state);
	luaopen_table(engine.lua_state);
	luaopen_io(engine.lua_state);
	luaopen_string(engine.lua_state);
	luaopen_math(engine.lua_state);

	return engine;
}

void gs_script_engine_stop(gs_script_engine_t *engine){



}
}
