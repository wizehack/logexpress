#include "commandErrorHandler.h"

expr::CommandErrorHandler::CommandErrorHandler(){}

expr::CommandErrorHandler::~CommandErrorHandler(){}

bool expr::CommandErrorHandler::request(expr::CommandMessage* cmd_msg)
{
    if(cmd_msg->get_number_of_command() < 2)
    {
        return false;
    }
    else
    {
        return this->next->request(cmd_msg);
    }
}
