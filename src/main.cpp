#include <memory>
#include "logger.h"
#include "commandMessage.h"
#include "userInteractionManager.h"
#include "file.h"

int main(int argc, char* argv[])
{
    expr::Logger logger;
    logger.log("test log");

    expr::UserInteractionManager* user_interaction_mgr = new expr::UserInteractionManager();

    std::shared_ptr<expr::CommandMessage> sptr_cm = std::make_shared<expr::CommandMessage>();
    sptr_cm->set_number_of_command(argc);
    sptr_cm->set_opt_conf(const_cast<const char*>(argv[1]));
    sptr_cm->set_path_conf(const_cast<const char*>(argv[2]));
    user_interaction_mgr->process_command(sptr_cm.get());

    if(user_interaction_mgr)
    {
        delete user_interaction_mgr;
    }
}

