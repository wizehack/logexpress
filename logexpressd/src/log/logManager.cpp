#include "logManager.h"
#include "logger.h"
#include "messageQueue.h"
#include <json-c/json.h>
#include <json-c/bits.h>

std::atomic<expr::LogManager*> expr::LogManager::_singleton;
std::mutex expr::LogManager::_mutex;

expr::LogManager::LogManager(){}
expr::LogManager::~LogManager(){}

expr::LogManager* expr::LogManager::getInstance() { 
	expr::LogManager* inst = _singleton.load(std::memory_order_relaxed);
	std::atomic_thread_fence(std::memory_order_acquire);
	if(inst == 0) {
		std::lock_guard<std::mutex> lock(_mutex);
		inst = _singleton.load(std::memory_order_relaxed);
		if(inst == 0) {
			inst = new expr::LogManager();
			std::atomic_thread_fence(std::memory_order_release);
			_singleton.store(inst, std::memory_order_relaxed);
		}
	}
	return inst;
}


void expr::LogManager::add_logHandler(std::string process_log_id, std::string log_file_path)
{
    bool is_found = false;
    std::list<std::shared_ptr<expr::Log>>::iterator itor;

    for(itor = this->logHandlerPool.begin(); itor != this->logHandlerPool.end(); itor++)
    {
        if((*itor)->get_filePath().compare(log_file_path) == 0)
        {
            is_found = true;
            (*itor)->add_process_log_id(process_log_id);
        }
    }

    if(is_found == false)
    {
        std::shared_ptr<expr::Log> logHandler = std::make_shared<expr::Log>(log_file_path);
        logHandler->add_process_log_id(process_log_id);
        this->logHandlerPool.push_back(logHandler);
    }
}

gpointer expr::LogManager::_msg_processor_thread(void* data)
{
    gpointer msg;
    expr::Logger logger;
    std::string str_msg_log;
    std::list<std::shared_ptr<expr::Log>>::iterator itor; 

    while(true)
    {
        msg = g_async_queue_pop(expr::MessageQueue::getInstance()->get_listenerQueue());
        str_msg_log.assign(static_cast<char*>(msg));

//        logger.show(str_msg_log);
        if(str_msg_log.compare("sync") == 0)
        {
            for(itor = expr::LogManager::getInstance()->logHandlerPool.begin(); itor != expr::LogManager::getInstance()->logHandlerPool.end(); itor++)
            {
                (*itor)->write();
            }
        }
        else
        {
            for(itor = expr::LogManager::getInstance()->logHandlerPool.begin(); itor != expr::LogManager::getInstance()->logHandlerPool.end(); itor++)
            {
                (*itor)->add_log(expr::LogManager::getInstance()->get_process_log_id(static_cast<char*>(msg)), str_msg_log);
            }
        }

        if(msg)
        {
            g_free(msg);
            msg = NULL;
        }
    }

    return NULL;
}

std::string expr::LogManager::get_process_log_id(char* msg_log)
{
    std::string process_log_id;
    json_object* jobj = NULL;
    json_object* subjobj = NULL;

    jobj = json_tokener_parse(msg_log);

    expr::Logger logger;
    if((jobj == NULL) || is_error(jobj))
    {
        logger.show("can not get json object");
        process_log_id.clear();
        return process_log_id;
    }

    if(json_object_object_get_ex(jobj, "process_log_id", &subjobj))
    {
        process_log_id.assign(json_object_get_string(subjobj));
    }

    if(jobj)
    {
        json_object_put(jobj);
    }

    return process_log_id;
}

std::list<std::shared_ptr<expr::Log>> expr::LogManager::get_logHandlerPool()
{
    return this->logHandlerPool;
}

void expr::LogManager::debug_logHandlerPool()
{
    expr::Logger logger;
    std::list<std::shared_ptr<expr::Log>>::iterator itor;

    for(itor = this->logHandlerPool.begin(); itor != this->logHandlerPool.end(); itor++)
    {
        logger.show((*itor)->get_filePath());
        (*itor)->print_process_log_id();
    }
}
