#ifndef LOG_MANAGER_H_
#define LOG_MANAGER_H_

#include <mutex>
#include <atomic>
#include <string>
#include <memory>
#include <list>
#include <glib-2.0/glib.h>

#include "logManager.h"
#include "log.h"

namespace expr {
    class LogManager {
        public:
            ~LogManager();
            static LogManager* getInstance();
            void add_logHandler(std::string process_log_id, std::string log_file_path);
            std::string get_process_log_id(char* msg_log);
            std::list<std::shared_ptr<expr::Log>> get_logHandlerPool();
            void debug_logHandlerPool();

        public:
            static gpointer _msg_processor_thread(void* data);

        private:
            LogManager();

        private:
            std::list<std::shared_ptr<expr::Log>> logHandlerPool;

        private:
            static std::atomic<LogManager*> _singleton;
            static std::mutex _mutex;
    };
}
#endif /*LOG_MANAGER_H_*/
