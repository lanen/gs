#ifndef GS_LOGGER_H
#define GS_LOGGER_H

#include "zlog.h"

#define gs_info(format, args...)   dzlog_info(format, ##args)
#define gs_fatal(format, args...)  dzlog_fetal(format, ##args)
#define gs_error(format, args...)  dzlog_error(format, ##args)
#define gs_warn(format, args...)   dzlog_warn(format, ##args)
#define gs_notice(format, args...) dzlog_notice(format, ##args)
#define gs_debug(format, args...)  dzlog_debug(format, ##args)

void gs_init_logger(const char* confpath, const char* cat);
void gs_close_logger();


#endif
