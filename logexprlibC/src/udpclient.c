#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "udpclient.h"
#include "config.h"

void send_log(const char* msg)
{
    int sockfd;
    int clilen;
    int state;
    char buf[MAX_LOG_SIZE] = {0,};

    (char*)memcpy(buf, msg, MAX_LOG_SIZE);

    struct sockaddr_in serveraddr;

    clilen = sizeof(serveraddr);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0)
    {
        perror("socket error : ");
	return;
    }

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr((const char*)confdata->address);
    serveraddr.sin_port = htons((unsigned short int)confdata->port);

    sendto(sockfd, (void *)buf, sizeof(buf), 0, (struct sockaddr *)&serveraddr, clilen);
    close(sockfd);
}
