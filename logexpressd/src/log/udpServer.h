#ifndef UDP_SERVER_H_
#define UDP_SERVER_H_

#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <glib-2.0/glib.h>

/**
 * @class UDPServer
 */
namespace expr {
    class UDPServer {
        public:
            UDPServer(int max_log_size, unsigned short int port);
            UDPServer(unsigned short int port);
            virtual ~UDPServer();
            bool setup();
            void start();
            void terminate();

        public:
            static gpointer _log_listener_thread(void* data);
            static gpointer _cmd_listener_thread(void* data);

        private:
            UDPServer();
            void add(char* str_log_id);

        private:
            const int MAX_LOG_SIZE;
            unsigned short int m_port;
            int sockfd;
            unsigned int clilen;
            struct sockaddr_in serveraddr;
            struct sockaddr_in clientaddr;
    };
}

#endif /* UDP_SERVER_H_ */
