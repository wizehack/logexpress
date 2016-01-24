#include "commandHandler.h"

expr::CommandHandler::CommandHandler():
    next(NULL)
{}

expr::CommandHandler::~CommandHandler(){}

void expr::CommandHandler::set_next(expr::CommandHandler* cmd_handler)
{
    this->next = cmd_handler;
}
 
