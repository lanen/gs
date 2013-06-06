/*
 * =====================================================================================
 *
 *       Filename:  gs_net.c
 *
 *    Description:  网路层
 *
 *        Version:  1.0
 *        Created:  06/04/2013 08:00:41 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  evan (just think), cppmain@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "gs_net.h"

#include "gs_logger.h"

#include <pthread.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#include <sys/epoll.h>
#include <arpa/inet.h>



#define MAX_EVENTS 10

void gs_epoll_event(int *socketfd,  struct epoll_event *ep_event);
void gs_epoll_init( int *socketfd );
void gs_socket_create(int *socketfd, struct sockaddr_in *local_addr);


void *gs_socket_subroutin(void *args){


    int socktport = 8123;
    
    int socketfd = -1;
    
    struct sockaddr_in local_addr;
   
    //初始化服务器的端口
    local_addr.sin_port         = htons ( socktport );
    local_addr.sin_family       = AF_INET;
    local_addr.sin_addr.s_addr  = INADDR_ANY;

    memset(&local_addr, 0, sizeof(local_addr));

    gs_socket_create(&socketfd, &local_addr);

    //开始epoll 模型
    gs_epoll_init( &socketfd );

    return ((void *)0);
}

void gs_socket_error(const char *err_msg){

    gs_logger_info(err_msg);
}

void gs_socket_create(int *socketfd, struct sockaddr_in *local_addr){

    *socketfd = socket(AF_INET, SOCK_STREAM, 0);

    if( *socketfd < 0){
        
        gs_logger_info("建立socket 失败");

        return ;
    }

    int rc = bind(*socketfd, (struct sockaddr *)local_addr, sizeof(struct sockaddr));

    if( rc == -1){
        gs_logger_info("bad bind");
        return ;
    }

    rc = listen(*socketfd, 5);


}

void gs_epoll_init( int *socketfd ){
    
    int epollfd;

    epollfd = epoll_create(MAX_EVENTS);
    
    struct epoll_event ep_event;
    struct epoll_event events[MAX_EVENTS];
    
    ep_event.events  = EPOLLIN;
    ep_event.data.fd = *socketfd;

    if(epoll_ctl(epollfd, EPOLL_CTL_ADD, *socketfd, &ep_event) == -1){

        gs_logger_info("建立epoll错误");

        return;
    }

    int nfds;
    
    while (1){
        nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        if(nfds == -1){
            exit(EXIT_FAILURE);
        }

        int i;
        for(i =0;i<nfds;i++){

            gs_epoll_event(socketfd, &events[i]);
       }
    }

}

void gs_epoll_event(int *socketfd,struct epoll_event *ep_event){
     
    if(ep_event->data.fd == *socketfd){
    }else{
    }
 
}

int gs_net_server_start(gs_socket_server_t *socket_server){


    int errno = 0;

    gs_logger_info("gs_net_server_start");

    pthread_t socket_thread_fd;


    errno = pthread_create(&socket_thread_fd, NULL, gs_socket_subroutin, socket_server);

    return errno;
}

void gs_net_server_stop(gs_socket_server_t *socket_server){


    gs_logger_info("gs_net_server_stop");

}
