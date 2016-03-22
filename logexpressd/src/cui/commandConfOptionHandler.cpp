#include <string>

#include "commandConfOptionHandler.h"
#include "configManager.h"
#include "file.h"
#include "errorMessage.h"
#include "errorMessagePool.h"

expr::CommandConfOptionHandler::CommandConfOptionHandler(){}

expr::CommandConfOptionHandler::~CommandConfOptionHandler(){}

void expr::CommandConfOptionHandler::request(expr::CommandMessage* cmd_msg)
{
    expr::error_type e_type = expr::CONFIG;
    expr::error_code e_code = expr::UNKNOWN_CODE;

    std::string opt_conf = cmd_msg->get_opt_conf();
    std::string path_conf = cmd_msg->get_path_conf();

    if(path_conf.empty())
    {
        e_code = expr::CONFIG_FILE;
        std::shared_ptr<expr::ErrorMessage> error_input_param = std::make_shared<expr::ErrorMessage>(e_type, e_code);
        error_input_param->set_error_desc("please set configuration file. [-c | --config] file");
        expr::ErrorMessagePool::getInstance()->add(error_input_param);
    }

    // ./logexpress --config ~/cpp_proj/logexpress/resource/default.conf
    if( (opt_conf.compare("--config") == 0) || (opt_conf.compare("-c") == 0) )
    {
        expr::File* file_conf = new expr::File(path_conf, "read");

        if(file_conf->is_exist())
        {
            expr::ConfigManager configManager;
            std::string json_conf_payload(file_conf->get_contents());

            if(configManager.parse_conf_json(json_conf_payload) == NULL)
            {
                e_code = expr::CONFIG_PARSE;
                std::shared_ptr<expr::ErrorMessage> error_input_param = std::make_shared<expr::ErrorMessage>(e_type, e_code);
                error_input_param->set_error_desc(path_conf + " is NOT json");
                expr::ErrorMessagePool::getInstance()->add(error_input_param);
            }
            else
            {
                configManager.start_log_manager();
            }
        }
        else
        {
            if(path_conf.empty() == false)
            {
                e_code = expr::CONFIG_FILE;
                std::shared_ptr<expr::ErrorMessage> error_input_param = std::make_shared<expr::ErrorMessage>(e_type, e_code);
                error_input_param->set_error_desc(path_conf + " is NOT found");
                expr::ErrorMessagePool::getInstance()->add(error_input_param);
            }
        }

        if(file_conf)
        {
            delete file_conf;
            file_conf = NULL;
        }
    }
    else
    {
        e_code = expr::INVALID_OPT;
        std::shared_ptr<expr::ErrorMessage> error_input_param = std::make_shared<expr::ErrorMessage>(e_type, e_code);
        error_input_param->set_error_desc("please set configuration file");
        expr::ErrorMessagePool::getInstance()->add(error_input_param);
    }

    if(next)
    {
        next->request(cmd_msg);
    }
}
