#include "paramParser.h"
#include <string.h>
#include <stdexcept>
#include <string>
#include <iostream>

ParamParser::ParamParser():
    port(0){}

ParamParser::~ParamParser(){}

int ParamParser::get_ctl_port()
{
    return this->port;
}

char* ParamParser::get_cmd()
{
    return this->cmd;
}

bool ParamParser::check_parameters(int argc, char** argv)
{
    if(argc < 4)
    {
        std::cout << "argc : " << argc << std::endl;
        return false;
    }

    std::string str_port;

    int i = 1;
    const int size_argv = 4;
    
    while(i < size_argv)
    {
        if(strcmp(argv[i], "-m") == 0)
        {
            strcpy(this->cmd, argv[i+1]);
        }
        else if (strcmp(argv[i], "-p") == 0)
        {
            str_port.assign(argv[i+1]);
        }
        else
        {
            std::cout << "argv " << i << " : " << argv[i] << std::endl;
            return false;
        }

        i = i + 2;
    }

    try 
    {
        this->port = std::stoi(str_port);
    }
    catch (const std::invalid_argument& ia)
    {
        std::cerr << "Invalid argument: " << ia.what() << '\n';
        return false;
    }

    return true;
}

