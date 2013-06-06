#ifndef GS_NET_H
#define GS_NET_H

typedef struct gs_socket_server_s{

    int port;

} gs_socket_server_t;


int gs_net_server_start(gs_socket_server_t *socket_server);
void gs_net_server_stop(gs_socket_server_t *socket_server);



#endif
