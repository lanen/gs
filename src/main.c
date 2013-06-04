#include <stdio.h>

#include "gs_logger.h"

int main(int argc, char **argv){

    gs_init_logger("/home/dev/Documents/Code/dyd/Server/etc/zlog.conf");
    
    gs_logger_info("开始初始化服务器");

    gs_logger_info("初始化数据库链接");

    gs_logger_info("加载静态数据");


    return 0;
}
