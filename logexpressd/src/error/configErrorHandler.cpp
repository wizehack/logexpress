#include "configErrorHandler.h"

expr::ConfigErrorHandler::ConfigErrorHandler(){}
expr::ConfigErrorHandler::~ConfigErrorHandler(){}

void expr::ConfigErrorHandler::request(expr::ErrorMessage* err_msg)
{
    if(err_msg->get_error_type() == expr::CONFIG)
    {
        if(err_msg->get_error_code() == expr::INVALID_OPT)
        {
            this->throw_error(err_msg, this->KNOWN_ERROR);
            this->throw_msg("logexpress [--config | -c] [conf file]");
        }
        else if(err_msg->get_error_code() == expr::CONFIG_FILE)
        {
            this->throw_error(err_msg, this->KNOWN_ERROR);
        }
        else if(err_msg->get_error_code() == expr::CONFIG_JSON)
        {
            this->throw_error(err_msg, this->KNOWN_ERROR);
        }
        else if(err_msg->get_error_code() == expr::CONFIG_PARSE)
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

