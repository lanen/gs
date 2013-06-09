#ifndef GS_NET_H
#define GS_NET_H


typedef struct gs_socket_server_s{
	int port;

} gs_socket_server_t;

/*
 * 
 * name: 建立并监听socket
 * @param hostname
 * @param port
 * @return
 * 
 */
int gs_server_socket(const char *hostname, const char *port);


//启动网络模块
int gs_net_server_start(gs_socket_server_t *socket_server);

//关闭网络模块
void gs_net_server_stop(gs_socket_server_t *socket_server);



#endif
