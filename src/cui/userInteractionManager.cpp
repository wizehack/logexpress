#include <algorithm> 

#include "userInteractionManager.h"
#include "commandHandler.h"
#include "commandErrorHandler.h"
#include "commandConfOptionHandler.h"
#include "confData.h"
#include "logger.h"

expr::UserInteractionManager::UserInteractionManager(){}

expr::UserInteractionManager::~UserInteractionManager(){}

/**
 * @brief This throws user's command to CommandHandler to start logexpress daemon 
 */
void expr::UserInteractionManager::process_command(expr::CommandMessage* cmd_msg)
{
    expr::CommandHandler* cmdErrHandler = new expr::CommandErrorHandler();
    expr::CommandHandler* cmdConfigHandler = new expr::CommandConfOptionHandler();
    cmdErrHandler->set_next(cmdConfigHandler);
    bool processed = cmdErrHandler->request(cmd_msg);

    expr::Logger logger;

    if(processed)
    {
        std::list<std::shared_ptr<expr::LogMap>> log_map_table = expr::ConfData::getInstance()->get_mapping_table();
        std::list<std::shared_ptr<expr::LogMap>>::iterator itor;

        //test code to show parsed results 
        for(itor = log_map_table.begin(); itor != log_map_table.end(); itor++)
        {
            logger.log((*itor)->get_process_log_id() + " : " + (*itor)->get_log_daemon_id() + " : " + (*itor)->get_log_file_path());
        }
    }
    else
    {
        logger.log("failed");
        //get error message
    }
}

