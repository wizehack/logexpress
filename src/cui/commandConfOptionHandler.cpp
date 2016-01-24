#include <string>

#include "commandConfOptionHandler.h"
#include "configManager.h"
#include "file.h"
#include "errorMessage.h"

expr::CommandConfOptionHandler::CommandConfOptionHandler(){}

expr::CommandConfOptionHandler::~CommandConfOptionHandler(){}

bool expr::CommandConfOptionHandler::request(expr::CommandMessage* cmd_msg)
{
    std::string opt_conf = cmd_msg->get_opt_conf();
    std::string path_conf = cmd_msg->get_path_conf();
    expr::ConfigManager* configManager = NULL;

    // ./logexpress --config ~/cpp_proj/logexpress/resource/default.conf
    if( (opt_conf.compare("--config") == 0) || (opt_conf.compare("-c") == 0) )
    {
        expr::File file_conf = expr::File(path_conf);

        if(file_conf.is_exist())
        {
            configManager = new expr::ConfigManager();           
            std::string json_conf_payload(file_conf.get_contents());
            
            expr::ConfData* obj_conf = configManager->parse_conf_json(json_conf_payload);

            if(obj_conf->is_parsed())
            {
                if(next)
                {
                    return next->request(cmd_msg);
                }
                else
                {
                    return true;
                }
            }
            else
            {
                // throw errorMessage
                expr::ErrorMessage::getInstance()->set_err_name("Configuration Error");
                expr::ErrorMessage::getInstance()->set_err_message("Invalid Configuration File");
                return false;
            }
        }
        else
        {
            expr::ErrorMessage::getInstance()->set_err_name("Configuration Error");
            expr::ErrorMessage::getInstance()->set_err_message("configuration file is NOT found");
            return false;
        }
    }
    else
    {
        expr::ErrorMessage::getInstance()->set_err_name("COnfiguration Error!");
        expr::ErrorMessage::getInstance()->set_err_message("logexpress [--config | -c] [value]");

        return false;
    }
}
