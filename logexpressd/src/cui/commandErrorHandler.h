#ifndef COMMAND_ERROR_HANDLER_H_
#define COMMAND_ERROR_HANDLER_H_

#include "commandHandler.h"

namespace expr {
    class CommandErrorHandler : public CommandHandler{
        public:
            CommandErrorHandler();
            ~CommandErrorHandler();
            void request(expr::CommandMessage* cmd_msg); 
    };
}

#endif /* COMMAND_ERROR_HANDLER_H_ */
