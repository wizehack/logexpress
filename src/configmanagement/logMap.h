#ifndef LOG_MAP_H_
#define LOG_MAP_H_

#include <string>

/**
 * @class expr::LogMap
 * @brief This parsed data set to be handled by expr::ConfigManager
 */
namespace expr {
    class LogMap {
        public:
            LogMap(std::string ps_log_id, std::string log_d_id, std::string log_f_path);
            ~LogMap();

            std::string get_process_log_id();
            std::string get_log_daemon_id();
            std::string get_log_file_path();

        private:
            std::string process_log_id; 
            std::string log_daemon_id;
            std::string log_file_path;
    };
}

#endif /* LOG_MAP_H_ */
