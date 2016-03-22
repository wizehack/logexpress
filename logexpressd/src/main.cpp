#include <memory>
#include "commandMessage.h"
#include "userInteractionManager.h"
#include <glib-2.0/glib.h>

GMainLoop *main_loop;

int main(int argc, char* argv[])
{
    main_loop = g_main_loop_new (NULL, TRUE);

    expr::UserInteractionManager* user_interaction_mgr = new expr::UserInteractionManager();

    std::shared_ptr<expr::CommandMessage> sptr_cm = std::make_shared<expr::CommandMessage>();
    sptr_cm->set_number_of_command(argc);
    sptr_cm->set_opt_conf(const_cast<const char*>(argv[1]));
    sptr_cm->set_path_conf(const_cast<const char*>(argv[2]));

    if(user_interaction_mgr->process_command(sptr_cm.get()) == false)
    {
        return -1;
    }

    g_main_loop_run (main_loop);

    if(user_interaction_mgr)
    {
        delete user_interaction_mgr;
    }
}

