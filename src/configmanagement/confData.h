#ifndef CONF_DATA_H_
#define CONF_DATA_H_

#include <mutex>
#include <atomic>
#include <string>
#include <memory>
#include <list>
#include "logMap.h"

namespace expr {

    /**
     * @enum expr::PRIORITY
     * @brief This is a priority level to judge whether each log should be written or discarded
     */
    enum PRIORITY 
    {
        DEBUG,
        INFORM,
        ERROR,
        CRITICAL,
        FAILURE,
        NOT_DEFINED
    };

    /**
     * @class expr::ConfData
     * @brief This parsed data set to be handled by expr::ConfigManager
     */
    class ConfData {
        public:
            ~ConfData();
            static ConfData* getInstance();

            void set_log_priority(expr::PRIORITY priority);
            void set_export_period(int period);
            void set_max_log_buffer_size(int size);
            void set_parsed(bool parsed);
            void add_to_table(std::string ps_log_id, std::string log_d_id, std::string log_file_path);

            expr::PRIORITY get_log_priority();
            int get_export_period();
            int get_max_log_buffer_size();
            std::list<std::shared_ptr<LogMap>> get_mapping_table();
            bool is_parsed();

        private:
            ConfData();

        private:
            expr::PRIORITY log_priority;
            int export_period;
            int max_log_buffer_size;
            bool parsed;
            std::list<std::shared_ptr<LogMap>> mapping_table;

        private:
            static std::atomic<ConfData*> _singleton;
            static std::mutex _mutex;
    };
}
#endif /*CONF_DATA_H_*/
