#ifndef UDP_CLIENT_H_
#define UDP_CLIENT_H_

#include <string>

class UDPClient {
    public:
        UDPClient(std::string ipaddr, unsigned short port);
        ~UDPClient();
        void send(char* data);

    private:
        std::string IPADDR;
        unsigned short PORT;
        int sockfd;
        int clilen;
};

#endif /* UDP_CLIENT_H_ */
