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
#include <stdio.h>
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
#include <fcntl.h>
#include <errno.h> 
#include <netdb.h>

#define MAX_EVENTS 10

int  gs_epoll_init();
void gs_epoll_run();
void make_socket_unblock(int fd);
void gs_accept_connect();
void gs_read(int fd);

static int gs_epollfd;
static int gs_sockfd;


int gs_server_socket(const char *hostname, const char *port){
	
	struct addrinfo hints;
	struct addrinfo *hints_result, *hints_tmp;
	
	int sockfd , err;
	
	//setup addrinfo
	memset (&hints, 0, sizeof (struct addrinfo));
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	
	err = getaddrinfo(hostname, port, &hints, &hints_result);
	
	if(err){
		gs_error("%s",gai_strerror(err));
		return -1;
	}
		
	//for(hints_tmp =  hints_result; hints_tmp !=  ; hints_tmp = hints_tmp->ai_next){
	for(hints_tmp = hints_result; hints_tmp; hints_tmp = hints_tmp->ai_next){
		sockfd = socket(hints_tmp->ai_family, hints_tmp->ai_socktype, hints_tmp->ai_protocol);
		if(-1 == sockfd){
			continue;
		}
	
		//bind
		int bind_err = bind(sockfd, hints_tmp->ai_addr, hints_tmp->ai_addrlen);
		if(bind_err == 0){
			break;
		}	
		
	}
	
	if(NULL == hints_tmp){
		gs_error("无法绑定端口[%s:%s]",hostname,port);
		return -1;
	}
	
	//listen
	listen(sockfd,5);
	
	freeaddrinfo(hints_result);
	
	return sockfd;
}

void gs_accept_connect(){
	
	while(1){
		
		struct sockaddr in_addr;
		socklen_t in_len;
		
		int clientfd;
		
		char hbuf[NI_MAXHOST],sbuf[NI_MAXSERV];
		
		in_len = sizeof(in_addr);
		
		clientfd = accept(gs_sockfd, &in_addr, &in_len);
		
		if( -1 == clientfd){
			if ((errno == EAGAIN) || (errno == EWOULDBLOCK)){
							  
				 /* We have processed all incoming
							 connections. */
				 break;
			}else{						
				break;
			}
		}

		int err = getnameinfo (&in_addr, in_len,
								   hbuf, sizeof hbuf,
								   sbuf, sizeof sbuf,
								   NI_NUMERICHOST | NI_NUMERICSERV);
		if (err == 0){
			printf("Accepted connection on descriptor %d "
							 "(host=%s, port=%s)\n", clientfd, hbuf, sbuf);
		}
		
		make_socket_unblock(clientfd);
		struct epoll_event event;
		event.data.fd = clientfd;
		event.events = EPOLLIN | EPOLLET;
		epoll_ctl (gs_epollfd, EPOLL_CTL_ADD, clientfd, &event);
	}

		
}

void gs_read(int fd){
					
	int done ;
	
	gs_info("收到新包");
	
	while(1){
		ssize_t count;
		char buf[512];
		
		count = read(fd, buf, sizeof buf);
		if(-1== count){
			if(errno == EAGAIN){
				done = 1;
			}
			break;
		}else if(0 == count){
			//end of file.
			done = 1;
			break;
		}else{
			
			gs_debug("受到数据");
		}		
	}
	
	if(done){
		gs_debug("通过fd关闭客户端链接");
		close(fd);
	}

}


void *gs_socket_subroutin(void *args){

    const char *hostname = "0.0.0.0";
    const char *port = "8123";
    
    gs_sockfd = gs_server_socket(hostname,port);
	
	if(-1 != gs_sockfd){
	}
	//设置server socket 为非阻塞		
	make_socket_unblock(gs_sockfd);
	
	//开始epoll 模型
	gs_epollfd = gs_epoll_init();
	gs_epoll_run();
	
    return ((void *)0);
}


int gs_epoll_init(){
    
    int epollfd;

    epollfd = epoll_create(MAX_EVENTS);
    
    struct epoll_event ep_event;
        
    ep_event.events  = EPOLLIN;
    ep_event.data.fd = gs_sockfd;

    if(epoll_ctl(epollfd, EPOLL_CTL_ADD, gs_sockfd, &ep_event) == -1){

        gs_info("建立epoll错误");

        return  -1;
    }

	return epollfd;

}

void gs_epoll_run(){
	
	int event_count;
	struct epoll_event event;
    struct epoll_event events[MAX_EVENTS];
	gs_info("create epoll %d",111);
    while (1){
        
		gs_info("epoll_wait"); 
		event_count = epoll_wait(gs_epollfd, events, MAX_EVENTS, -1);
        if(event_count == -1){
			gs_info("exit when epoll failed");
            exit(EXIT_FAILURE);
        }

		gs_info("get epoll event");
       
		int i ;
        for( i =0; i<event_count; i++){
		
			if( (events[i].events & EPOLLERR) ||
              (events[i].events & EPOLLHUP) ||
              (!(events[i].events & EPOLLIN))){
				//链接错误
				gs_error("链接发生错误");
				
				close(events[i].data.fd);
				continue;
			}else if(events[i].data.fd == gs_sockfd){
				
				gs_info("建立新链接");
				gs_accept_connect();
				
				//gs_accept_socket(sockfd,&events[i]);
				continue;
			}else{
				gs_read(events[i].data.fd);
			}
        }
       
        
    }
     
        free(events);
        gs_info("关闭服务器");
        close(gs_sockfd); 

}

int gs_net_server_start(gs_socket_server_t *socket_server){


    int err = 0;

    gs_info("gs_net_server_start");

    pthread_t socket_thread_fd;


	gs_socket_subroutin(NULL);
//    errno = pthread_create(&socket_thread_fd, NULL, gs_socket_subroutin, socket_server);

    return err;
}

void gs_net_server_stop(gs_socket_server_t *socket_server){


    gs_info("gs_net_server_stop");

}

void make_socket_unblock(int fd){
	int flags = fcntl (fd, F_GETFL, 0);
	flags |= O_NONBLOCK;
	fcntl (fd, F_SETFL, flags);

}
