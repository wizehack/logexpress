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
    std::string e_type;
    std::string e_code;
    
    e_type = this->get_error_type_desc(err_msg->get_error_type());
    e_code = this->get_error_code_desc(err_msg->get_error_code());

    logger.show(e_type + ", " + e_code + ": " + err_msg->get_error_desc());
}

void expr::ErrorHandler::throw_msg(std::string msg)
{
    expr::Logger logger;
    logger.show("error msg: " + msg);
}

std::string expr::ErrorHandler::get_error_code_desc(expr::error_code err_code)
{
    std::string desc;

    if(err_code == expr::UNKNOWN_CODE)
    {
        desc.assign("Unknown error");
    }
    else if(err_code == expr::OPT_NUMBER)
    {
        desc.assign("Invalid number of option");
    }
    else if(err_code == expr::INVALID_OPT)
    {
        desc.assign("Invalid option");
    }
    else if(err_code == expr::CONFIG_FILE)
    {
        desc.assign("Invalid configuration file");
    }
    else if(err_code == expr::CONFIG_JSON)
    {
        desc.assign("Invalid json syntex");
    }
    else if(err_code == expr::CONFIG_PARSE)
    {
        desc.assign("Parsing error");
    }
    else
    {
        desc.assign("Fatal error code: " + std::to_string(err_code));
    }

    return desc;
}

std::string expr::ErrorHandler::get_error_type_desc(expr::error_type err_type)
{
    std::string desc;

    if(err_type == expr::UNKNOWN_TYPE)
    {
        desc.assign("Unknown Type");
    }
    else if(err_type == expr::USAGE)
    {
        desc.assign("Check input command...");
    }
    else if(err_type == expr::CONFIG)
    {
        desc.assign("Config...");
    }
    else
    {
        desc.assign("fatal error: " + std::to_string(err_type));
    }

    return desc;
}
