#include "errorMessage.h"

expr::ErrorMessage::ErrorMessage():
    e_type(UNKNOWN_TYPE),
    e_code(UNKNOWN_CODE),
    e_desc(""),
    e_unknown("unknown error"){}
    

expr::ErrorMessage::ErrorMessage(expr::error_type type, expr::error_code code):
    e_type(type),
    e_code(code),
    e_desc(""){}

expr::ErrorMessage::~ErrorMessage(){}

void expr::ErrorMessage::set_error_type(expr::error_type type)
{
    this->e_type = type;
}

void expr::ErrorMessage::set_error_code(expr::error_code code)
{
    this->e_code = code;
}

void expr::ErrorMessage::set_error_desc(std::string desc)
{
    this->e_desc = desc;
}

expr::error_type expr::ErrorMessage::get_error_type()
{
    return this->e_type;
}

expr::error_code expr::ErrorMessage::get_error_code()
{
    return this->e_code;
}

std::string expr::ErrorMessage::get_error_desc()
{
    return this->e_desc;
}

const char* expr::ErrorMessage::get_error_unknown()
{
    return this->e_unknown;
}
