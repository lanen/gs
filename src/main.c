#include <stdio.h>
#include "gs_net.h"
#include "gs_logger.h"
#include "gs_script.h"

static gs_script_engine_t lua_engine;

static gs_socket_server_t socket_server;


int main(int argc, char **argv){

    gs_init_logger("etc/zlog.conf");
    
    gs_logger_info("开始初始化服务器");

    gs_logger_info("初始化数据库链接");

    gs_logger_info("加载静态数据");

    gs_script_engine_start( &lua_engine );	

    gs_script_run(&lua_engine, "scripts/main.lua");


    int running = 1;

    int socketErrno = gs_net_server_start( &socket_server);
    if( 0 != socketErrno){
        gs_logger_info("faile at socket");
        running = 0;
    }

/*/	 
    while(running){
    
        sleep(3);
        gs_logger_info("主线程启动一次统计");

    }

    gs_script_engine_stop( &lua_engine );
    gs_net_server_stop( &socket_server );
*/
    return 0;

}


