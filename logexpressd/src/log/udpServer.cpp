#include "udpServer.h"
#include "logManager.h"
#include "confData.h"
#include "messageQueue.h"
#include <string.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <glib-2.0/glib.h>

expr::UDPServer::UDPServer(int max_log_size, unsigned short int port):
    MAX_LOG_SIZE(max_log_size),
    m_port(port){}

expr::UDPServer::UDPServer(unsigned short int port):
    MAX_LOG_SIZE(5),
    m_port(port){}

expr::UDPServer::UDPServer():
    MAX_LOG_SIZE(1024*5),
    m_port(1234){}

expr::UDPServer::~UDPServer(){}

/**
 * @brief This member function initializes JSONLogD 
 */
bool expr::UDPServer::setup()
{
    this->clilen = sizeof(clientaddr);
    this->sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (this->sockfd < 0)
    {
        std::perror("socket error : ");
        return false;
    }

    bzero(&(this->serveraddr), sizeof(this->serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(this->m_port);

    int bind_state;
    bind_state = bind(this->sockfd, (struct sockaddr *)&(this->serveraddr), sizeof(serveraddr));

    if (bind_state == -1)
    {
        std::perror("bind error : ");
        return false;
    }

    return true;
}

/**
 * @brief This member function starts JSONLogD
 */
void expr::UDPServer::start()
{
    bool INFINITE_LOOP = true;
//    ssize_t recv_size;
    char recv_log[MAX_LOG_SIZE];

//    std::cout << "start...." << std::endl;

    while (INFINITE_LOOP)
    {
        (char *)memset(recv_log, 0, MAX_LOG_SIZE);
        /*
        recv_size = recvfrom(this->sockfd, (void *)&recv_log, sizeof(recv_log), 0, 
                (struct sockaddr *)&(this->clientaddr), &this->clilen);

        std::cout << "size: " << recv_size << std::endl;
        */

        recvfrom(this->sockfd, (void *)&recv_log, sizeof(recv_log), 0, 
                (struct sockaddr *)&(this->clientaddr), &this->clilen);

        this->add(recv_log);
//        std::cout << "recv: " << recv_log << std::endl;

        char confirm[5] = "ok";

        if(this->m_port == expr::ConfData::getInstance()->get_ctl_port())
        {
            sendto(this->sockfd, (void *)&confirm, sizeof(confirm), 0, (struct sockaddr *)&clientaddr, clilen);
        }

    }
}

void expr::UDPServer::terminate()
{
    close(this->sockfd);
}

void expr::UDPServer::add(char* log)
{
    std::string str_log;
    str_log.assign(log);
   // std::cout << "str_log: " << str_log << std::endl;
    char* msg = g_strdup(log);
    g_async_queue_push(expr::MessageQueue::getInstance()->get_listenerQueue(), static_cast<gpointer>(msg)); 
}

gpointer expr::UDPServer::_log_listener_thread(void* data)
{
    int MAX_LOG_SIZE = 1024 * 5;
    unsigned short int port = expr::ConfData::getInstance()->get_log_port();
    expr::UDPServer* listener = new expr::UDPServer(MAX_LOG_SIZE, port);

    if(listener->setup())
    {
        listener->start();
    }
    else
    {
        std::cout << "log listener is NOT ready" << std::endl;
    }

    return NULL;
}

gpointer expr::UDPServer::_cmd_listener_thread(void* data)
{
    expr::UDPServer* listener = new expr::UDPServer(expr::ConfData::getInstance()->get_ctl_port());

    if(listener->setup())
    {
        listener->start();
    }
    else
    {
        std::cout << "control command listener is NOT ready" << std::endl;
    }

    return NULL;
}
