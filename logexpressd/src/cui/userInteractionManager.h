#ifndef USER_INTERACTION_MANAGER_H_
#define USER_INTERACTION_MANAGER_H_

#include "commandMessage.h"

/**
 * @class expr::UserInteractionManager
 * @brief This receives command from user and sends daemon's messages to user
 */
namespace expr {
    class UserInteractionManager {

        public:
            UserInteractionManager();
            ~UserInteractionManager();
            bool process_command(expr::CommandMessage* cmd_msg);
    };
}


#endif /* USER_INTERACTION_MANAGER_H_ */
