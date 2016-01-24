#include "commandErrorHandler.h"
#include "errorMessage.h"

expr::CommandErrorHandler::CommandErrorHandler(){}

expr::CommandErrorHandler::~CommandErrorHandler(){}

bool expr::CommandErrorHandler::request(expr::CommandMessage* cmd_msg)
{
    if(cmd_msg->get_number_of_command() < 2)
    {
        expr::ErrorMessage::getInstance()->set_err_name("Command Error");
        expr::ErrorMessage::getInstance()->set_err_message("logexpress [--config | -c] [value]");
        return false;
    }
    else
    {
        return this->next->request(cmd_msg);
    }
}
