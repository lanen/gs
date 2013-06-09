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


void gs_script_engine_start(gs_script_engine_t *engine){

	gs_info("初始化lua 脚本引擎");


	engine->luaState = luaL_newstate();

 
    luaL_openlibs(engine->luaState);
    luaL_dofile(engine->luaState, "test.lua");
    //lua_close(engine->luaState);

}

void gs_script_engine_stop(gs_script_engine_t *engine){

    //关闭lua 引擎

    lua_close(engine->luaState);

}

void gs_script_run(gs_script_engine_t *engine, const char *scriptname){

    luaL_dofile(engine->luaState, scriptname);
}
