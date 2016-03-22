#include "usageErrorHandler.h"

expr::UsageErrorHandler::UsageErrorHandler(){}
expr::UsageErrorHandler::~UsageErrorHandler(){}

void expr::UsageErrorHandler::request(expr::ErrorMessage* err_msg)
{
    if(err_msg->get_error_type() == expr::USAGE)
    {
        if(err_msg->get_error_code() == expr::OPT_NUMBER)
        {
            this->throw_error(err_msg, this->KNOWN_ERROR);
        }
        else
        {
            this->throw_error(err_msg, this->UNKNOWN_ERROR);
        }
    }
    else
    {
        if(this->next)
        {
            return this->next->request(err_msg);
        }
    }
}

