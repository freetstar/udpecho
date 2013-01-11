/*
 * =====================================================================================
 *
 *       Filename:  client.c
 *
 *    Description:  client to link the server
 *
 *        Version:  1.0
 *        Created:  2013/01/11 10时13分18秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>

#define MAXBUF 100

int main(int argc, const char *argv[])
{
    if(argc!=4)
    {
        printf("Usage:%s [Server] [ServerPort] [Msg]\n",argv[0]);
        exit(-1);
    }

    char *server = argv[1];
    char *serverport = argv[2];
    char *echostring = argv[3];

    struct addrinfo client,*servinfo;
    memset(&client,0,sizeof(client));
    client.ai_family = AF_INET;
    client.ai_socktype = SOCK_DGRAM;
    client.ai_protocol= IPPROTO_UDP;

    if(getaddrinfo(server,serverport,&client,&servinfo)<0)
    {
        printf("error in getaddrinfo");
        exit(-1);
    }

    int sockfd = socket(servinfo->ai_family,servinfo->ai_socktype,servinfo->ai_protocol);
    if(sockfd <0)
    {
        printf("error in socket create");
        exit(-1);
    }

    ssize_t numBytes = sendto(sockfd,echostring,strlen(echostring),0,servinfo->ai_addr,servinfo->ai_addrlen);
    if(numBytes<0)
    {
        printf("error in send the data");
    }

    struct sockaddr_storage fromaddr;
    socklen_t fromaddrlen = sizeof(fromaddr);
    char buf[MAXBUF+1];
    numBytes = recvfrom(sockfd,buf,MAXBUF+1,0,(struct sockaddr *)&fromaddr,&fromaddrlen);

    freeaddrinfo(servinfo);

    printf("Received:%s \n",buf);
    close(sockfd);
    return 0;
}
