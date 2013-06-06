#include <stdio.h>

#include "gs_logger.h"
#include "gs_script.h"

static gs_script_engine_t lua_engine;

#pragma comment(lib, "liblua.lib");
int main(int argc, char **argv){

    gs_init_logger("etc/zlog.conf");
    
    gs_logger_info("开始初始化服务器");

    gs_logger_info("初始化数据库链接");

    gs_logger_info("加载静态数据");

    gs_script_engine_start( &lua_engine );	

    gs_script_run(&lua_engine, "scripts/main.lua");

    gs_script_engine_stop( &lua_engine );
    
    return 0;

}
