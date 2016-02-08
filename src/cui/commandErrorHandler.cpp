#include "commandErrorHandler.h"
#include "errorMessagePool.h"
#include "errorMessage.h"

expr::CommandErrorHandler::CommandErrorHandler(){}

expr::CommandErrorHandler::~CommandErrorHandler(){}

void expr::CommandErrorHandler::request(expr::CommandMessage* cmd_msg)
{
    if(cmd_msg->get_number_of_command() < 2)
    {
        expr::error_type e_type;
        expr::error_code e_code;

        e_type = expr::USAGE;
        e_code = OPT_NUMBER;
        std::shared_ptr<expr::ErrorMessage> error_input_param = std::make_shared<expr::ErrorMessage>(e_type, e_code);
        error_input_param->set_error_desc("fatal error: no input configuration file");
        expr::ErrorMessagePool::getInstance()->add(error_input_param);
    }
    else
    {
        this->next->request(cmd_msg);
    }
}
