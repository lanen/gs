#ifndef NG_SCRIPT_H
#define NG_SCRIPT_H

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

typedef struct gs_script_engine_s {

	lua_State *luaState;

} gs_script_engine_t;


void gs_script_engine_start(gs_script_engine_t *engine);
void gs_script_engine_stop(gs_script_engine_t *engine);
void gs_script_run(gs_script_engine_t *engine, const char *scriptname);
#endif
