#ifndef CONFIG_MANAGER_H_
#define CONFIG_MANAGER_H_

#include <string>
#include "confData.h"

/**
 * @class expr::ConfigManager
 * @brief This configs handles configuration file or sets coniguration data received through user input
 */
namespace expr {
    class ConfigManager {
        public: 
            ConfigManager();
            virtual ~ConfigManager();
            expr::ConfData* parse_conf_json(std::string json_conf);

        private:
            expr::PRIORITY get_priority(std::string priority);
    };
}

#endif /* CONFIG_MANAGER_H_ */
