#ifndef NG_SCRIPT_H
#define NG_SCRIPT_H

#include "lua.h"
type struct {

	lua_State *luaState;

} gs_script_engine_t;


void gs_script_engine_start(gs_script_engine_t *engine);
void gs_script_engine_stop(gs_script_engine_t *engine);

#endif
