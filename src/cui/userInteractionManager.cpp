#include <algorithm> 

#include "userInteractionManager.h"
#include "commandHandler.h"
#include "commandErrorHandler.h"
#include "commandConfOptionHandler.h"
#include "confData.h"
#include "logger.h"
#include "errorMessage.h"
#include "errorMessagePool.h"
#include "errorHandler.h"
#include "usageErrorHandler.h"
#include "configErrorHandler.h"

expr::UserInteractionManager::UserInteractionManager(){}

expr::UserInteractionManager::~UserInteractionManager(){}

/**
 * @brief This throws user's command to CommandHandler to start logexpress daemon 
 */
void expr::UserInteractionManager::process_command(expr::CommandMessage* cmd_msg)
{
    expr::ErrorMessagePool::getInstance()->init();
    expr::CommandHandler* cmdErrHandler = new expr::CommandErrorHandler();
    expr::CommandHandler* cmdConfigHandler = new expr::CommandConfOptionHandler();
    cmdErrHandler->set_next(cmdConfigHandler);
    cmdErrHandler->request(cmd_msg);

    if(expr::ErrorMessagePool::getInstance()->size() > 0)
    {
        expr::ErrorHandler* usage_err_handler = new expr::UsageErrorHandler();
        expr::ErrorHandler* config_err_handler = new expr::ConfigErrorHandler();

        usage_err_handler->set_next(config_err_handler);

        int i;
        for(i = 0; i < expr::ErrorMessagePool::getInstance()->size(); i++)
        {
            usage_err_handler->request(expr::ErrorMessagePool::getInstance()->get(i).get());
        }

        if(usage_err_handler)
        {
            delete usage_err_handler;
            usage_err_handler = NULL;
        }

        if(config_err_handler)
        {
            delete config_err_handler;
            usage_err_handler = NULL;
        }
    }
    else
    {
        std::list<std::shared_ptr<expr::LogMap>> log_map_table = expr::ConfData::getInstance()->get_mapping_table();
        std::list<std::shared_ptr<expr::LogMap>>::iterator itor;

        //test code to show parsed results 
        expr::Logger logger;
        for(itor = log_map_table.begin(); itor != log_map_table.end(); itor++)
        {
            logger.show((*itor)->get_process_log_id() + " : " + (*itor)->get_log_daemon_id() + " : " + (*itor)->get_log_file_path());
        }
    }

    if(cmdErrHandler)
    {
        delete cmdErrHandler;
        cmdErrHandler = NULL;
    }

    if(cmdConfigHandler)
    {
        delete cmdConfigHandler;
        cmdErrHandler = NULL;
    }
}

