#ifndef NG_SCRIPT_H
#define NG_SCRIPT_H

#include "lua.h"
typedef struct gs_script_engine {

	lua_State *lua_state;

} gs_script_engine_t;


gs_script_engine_t *gs_script_engine_start();
void gs_script_engine_stop(gs_script_engine_t *engine);

#endif
