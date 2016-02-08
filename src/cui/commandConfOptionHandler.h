#ifndef COMMAND_CONF_OPT_HANDLER_H_
#define COMMAND_CONF_OPT_HANDLER_H_

#include "commandHandler.h"

namespace expr {
    class CommandConfOptionHandler : public CommandHandler{
        public:
            CommandConfOptionHandler();
            ~CommandConfOptionHandler();
            void request(expr::CommandMessage* cmd_msg); 
    };
}

#endif /* COMMAND_CONF_OPT_HANDLER_H_ */
