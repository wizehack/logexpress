#ifndef COMMAND_HANDLER_H_
#define COMMAND_HANDLER_H_

#include "commandMessage.h"

namespace expr {
    class CommandHandler{
        public:
            CommandHandler();
            virtual ~CommandHandler();

            void set_next(expr::CommandHandler* cmd_handler);
            virtual void request(expr::CommandMessage* cmd_msg) = 0;

        protected:
            expr::CommandHandler* next;
    };
}

#endif /* COMMAND_HANDLER_H_ */
