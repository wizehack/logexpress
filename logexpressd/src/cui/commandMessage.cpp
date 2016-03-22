#include "commandMessage.h"

expr::CommandMessage::CommandMessage():
    number_of_command(0),
    opt_conf(""),
    path_conf("")
{}

expr::CommandMessage::~CommandMessage(){}

void expr::CommandMessage::set_number_of_command(int num)
{
    this->number_of_command = num;
}

void expr::CommandMessage::set_opt_conf(const char* opt)
{
    if(opt)
    {
        this->opt_conf.assign(opt);
    }
    else
    {
        this->opt_conf.clear();
    }
}

void expr::CommandMessage::set_path_conf(const char* path)
{
    if(path)
    {
        this->path_conf.assign(path);
    }
    else
    {
        this->path_conf.clear();
    }
}

int expr::CommandMessage::get_number_of_command()
{
    return this->number_of_command;
}

std::string expr::CommandMessage::get_opt_conf()
{
    return this->opt_conf;
}

std::string expr::CommandMessage::get_path_conf()
{
    return this->path_conf;
}
