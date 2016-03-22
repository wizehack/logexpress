#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <iostream>
#include "udpClient.h"

UDPClient::UDPClient(std::string ipaddr, unsigned short port):
    IPADDR(ipaddr),
    PORT(port),
    sockfd(-1),
    clilen(-1)
{}

UDPClient::~UDPClient()
{
    close(this->sockfd);
}

void UDPClient::send(char* data)
{
    struct sockaddr_in serveraddr;
    this->clilen = sizeof(serveraddr);
    this->sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        std::perror("socket error : ");
        std::exit(0);
    }

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(this->IPADDR.c_str());
    serveraddr.sin_port = htons(this->PORT);

    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 100000;

    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv,sizeof(tv));

    sendto(sockfd, (void *)data, sizeof(data), 0, (struct sockaddr *)&serveraddr, clilen);
    char arc[5] = {0};

    if(recvfrom(sockfd, (void *)arc, sizeof(arc), 0, NULL, NULL) < 0)
    {
        std::cout << data << " " << static_cast<char*>(arc) << std::endl;
        std::cout << "fatal error" << std::endl;
    }

    if(arc)
    {
        std::cout << data << " " << static_cast<char*>(arc) << std::endl;
    }
}
