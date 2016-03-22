#include "logger.h"
#include <iostream>

expr::Logger::Logger(){}
expr::Logger::~Logger(){}

void expr::Logger::show(std::string str)
{
    std::cout << str << std::endl; 
}

