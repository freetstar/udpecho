/*
 * =====================================================================================
 *
 *       Filename:  server.c
 *
 *    Description:  udpserverfortest
 *
 *        Version:  1.0
 *        Created:  2013/01/11 08时55分33秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (freetstar), 
 *        Company:  jiuan.com
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

#define MAXBUFSIZE 100

int main(int argc, const char *argv[])
{
    if(argc!=1)
    {
        printf("Usage: %s",argv[0]);
        exit(-1);
    }

    int sockfd;
    struct addrinfo hints,*servinfo;
    int new_fd;
    socklen_t client_addr_size;
    struct sockaddr_storage client_addr;

    int bufnum;
    char buf[MAXBUFSIZE];

    memset(&hints,0,sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol = IPPROTO_UDP;

        
    //get addrinfo
    if(0!=getaddrinfo(NULL,"3499",&hints,&servinfo))
    {
        printf("error!check the message!\n");
        exit(-1);
    }

    //create the socket
    sockfd = socket(servinfo->ai_family,servinfo->ai_socktype,servinfo->ai_protocol);
    if (sockfd==-1)
    {
        printf("error create the socket!\n");
        exit(-1);
    }
       
   //bind to the port
   if(bind(sockfd,servinfo->ai_addr,servinfo->ai_addrlen)==-1) 
   {
        printf("error in binding");
        exit(-1);
   }

   freeaddrinfo(servinfo);

    listen(sockfd,5);

    printf("server:waiting for connectons...\n");
    
    while(1)
    {
        //set length of client address structure 
         client_addr_size = sizeof(client_addr);

        ssize_t numBytesRcvd = recvfrom(sockfd,buf,MAXBUFSIZE,0,(struct sockaddr *)&client_addr,&client_addr_size);
        
         if(numBytesRcvd<0)
         {
             sleep(1);
             continue;
         }

        printf("ready to send the message back to client\n");
            
        ssize_t numBytesSent = sendto(sockfd,buf,numBytesRcvd,0,(struct sockaddr *)&client_addr,client_addr_size);
        if(numBytesSent<0)
        {
            printf("error byte sent\n");
            exit(-1);
        }
        printf("%d\n",numBytesSent);
        printf("%s\n",buf);

         close(new_fd);
    }

    return 0;
}



