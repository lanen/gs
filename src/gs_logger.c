#include "gs_logger.h"
#include "zlog.h"
#include <stdio.h>
static zlog_category_t *zlog_category;
static zlog_resource_int;

void gs_init_logger(const char* confpath){
    zlog_resource_int  = dzlog_init(confpath, "my_cat");
    //zlog_category      = zlog_get_category("my_cat");
    if( zlog_resource_int ){
        printf("初始化日志模块失败！\n");
    }
}

void gs_logger_info(const char *plaintext){

    dzlog_info(plaintext);
}

