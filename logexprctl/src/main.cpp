#include <iostream>
#include "udpClient.h"
#include "paramParser.h"

// ./logexprctl -m sync -p 1200
int main(int argc, char **argv)
{
    ParamParser* pParser = new ParamParser();

    if(pParser->check_parameters(argc, argv))
    {
        UDPClient* udp = new UDPClient("127.0.0.1", static_cast<unsigned short>(pParser->get_ctl_port()));
        udp->send(pParser->get_cmd());
        delete udp;
    }
    else
    {
        std::cout << "NOT Parsed" << std::endl;
    }
    
    return 0;
}
