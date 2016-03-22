#include "errorHandler.h"
#include "logger.h"

expr::ErrorHandler::ErrorHandler():
    next(NULL),
    UNKNOWN_ERROR(false),
    KNOWN_ERROR(true)
{}

expr::ErrorHandler::~ErrorHandler(){}

void expr::ErrorHandler::set_next(expr::ErrorHandler* err_handler)
{
    this->next = err_handler;
}

void expr::ErrorHandler::throw_error(expr::ErrorMessage* err_msg, bool known_error)
{            
    expr::Logger logger;
    std::string e_code;
    e_code = std::to_string(err_msg->get_error_code());

    if(known_error)
    {            
        logger.show("error [" + e_code + "]: " + err_msg->get_error_desc());
    }
    else
    {
        std::string unknown(err_msg->get_error_unknown());
        logger.show("error [" + e_code + "]: " + unknown);
    }
}
