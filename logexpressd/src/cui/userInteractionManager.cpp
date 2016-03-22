#include <algorithm> 
#include <glib-2.0/glib.h>
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
#include "logManager.h"
#include "udpServer.h"
#include "timer.h"

expr::UserInteractionManager::UserInteractionManager(){}

expr::UserInteractionManager::~UserInteractionManager(){}

/**
 * @brief This throws user's command to CommandHandler to start logexpress daemon 
 */
bool expr::UserInteractionManager::process_command(expr::CommandMessage* cmd_msg)
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

        return false;
    }
    else
    {
        std::list<std::shared_ptr<expr::LogMap>> log_map_table = expr::ConfData::getInstance()->get_mapping_table();
        std::list<std::shared_ptr<expr::LogMap>>::iterator itor;

        //test code to show parsed results 
        expr::Logger logger;
        for(itor = log_map_table.begin(); itor != log_map_table.end(); itor++)
        {
            //fill logHandlerPool
            expr::LogManager::getInstance()->add_logHandler((*itor)->get_process_log_id(), (*itor)->get_log_file_path());
        }

        expr::LogManager::getInstance()->debug_logHandlerPool();

        logger.show("start threads...");
        
        //start msg processor thread
        g_thread_create(expr::LogManager::_msg_processor_thread, NULL, TRUE, NULL);

        //start command listener thread
        g_thread_create(expr::UDPServer::_cmd_listener_thread, NULL, TRUE, NULL);

        //start timer thread 
        g_thread_create(expr::Timer::_timer_thread, NULL, TRUE, NULL);

        /* launch log listener daemon */
        g_thread_create(expr::UDPServer::_log_listener_thread, NULL, TRUE, NULL);

        logger.show("threads are started");
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

    return true;
}


