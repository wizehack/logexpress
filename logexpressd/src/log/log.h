#ifndef LOG_H_
#define LOG_H_

#include <string>
#include <list>

namespace expr {
    class Log {
        public:
            Log(std::string file);
            ~Log();

            void add_process_log_id(std::string id);
            void add_log(std::string process_log_id, std::string log);
            void write();
            std::string get_filePath();
            void print_process_log_id();

        private:
            bool is_myLog(std::string process_log_id);

        private:
            std::string filePath;
            std::list<std::string> list_process_log_id;
            std::list<std::string> log_buffer;
    };
}

#endif /*LOG_H_*/
