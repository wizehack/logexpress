#include <json-c/json.h>
#include <json-c/bits.h>
#include <json-c/linkhash.h> //lh_entry
#include <glib-2.0/glib.h>
#include <iostream>
#include <stdio.h>
#include "configManager.h"
#include "logMap.h"
#include "file.h"
#include "errorMessage.h"

expr::ConfigManager::ConfigManager(){}

expr::ConfigManager::~ConfigManager(){}

/**
 * @brief This parses configuration file such as (default.conf) and returns the instance of expr::ConfData class.
 */
expr::ConfData* expr::ConfigManager::parse_conf_json(std::string json_conf)
{
    json_object* jobj = NULL;
    json_object* confjobj = NULL;
    json_object* subjobj = NULL;

    char* payload = NULL;
    payload = g_strdup(json_conf.c_str());

    jobj = json_tokener_parse(payload);

    if(is_error(jobj))
    {
        expr::ErrorMessage::getInstance()->set_err_messageEx("Json syntex error");
        expr::ConfData::getInstance()->set_parsed(false);
        return NULL;
    }

    bool parsed = true;

    if(!json_object_object_get_ex(jobj, "conf", &confjobj))
    {
        expr::ErrorMessage::getInstance()->set_err_messageEx("cannot find conf");
        parsed = false;
    }
    else
    {
        if(!json_object_object_get_ex(confjobj, "log_priority", &subjobj))
        {
            expr::ErrorMessage::getInstance()->set_err_messageEx("cannot find log_priority");
            parsed = false;
        }
        else
        {
            std::string priority(json_object_get_string(subjobj));
            expr::PRIORITY level = this->get_priority(priority);

            if(level == NOT_DEFINED)
            {
                expr::ErrorMessage::getInstance()->set_err_messageEx("NOT defined Priority");
                parsed = false;
            }
            else
            {
                expr::ConfData::getInstance()->set_log_priority(level);
            }
        }

        if(!json_object_object_get_ex(confjobj, "export_period", &subjobj))
        {
            expr::ErrorMessage::getInstance()->set_err_messageEx("cannot find export_period");
            parsed = false;
        }
        else
        {
            expr::ConfData::getInstance()->set_export_period(json_object_get_int(subjobj));
        }

        if(!json_object_object_get_ex(confjobj, "max_log_buffer_size", &subjobj))
        {
            expr::ErrorMessage::getInstance()->set_err_messageEx("cannot find export_period");
            parsed = false;
        }
        else
        {
            expr::ConfData::getInstance()->set_max_log_buffer_size(json_object_get_int(subjobj));
        }

        if(!json_object_object_get_ex(confjobj, "mapping", &subjobj))
        {
            expr::ErrorMessage::getInstance()->set_err_messageEx("cannot find mapping");
            parsed = false;
        }
        else
        {
            struct array_list* arr_obj;
            struct lh_entry* entry;

            arr_obj = json_object_get_array(subjobj);

            if(arr_obj == NULL)
            {
                expr::ErrorMessage::getInstance()->set_err_messageEx("mapping list error");
                return false;
            }

            int arr_size = array_list_length(arr_obj);
            json_object* arr_item = NULL;
            int arr_index;
            std::string key;
            std::string value;

            std::string ps_log_id;
            std::string log_d_id;
            std::string log_F_path;

            for(arr_index = 0; arr_index < arr_size; arr_index++)
            {
                arr_item = static_cast<json_object*>(array_list_get_idx(arr_obj, arr_index));
                entry = json_object_get_object(static_cast<struct json_object*>(arr_item))->head;

                while(entry)
                {
                    key.assign(static_cast<const char*>(entry->k));
                    value.assign(json_object_get_string((struct json_object*)entry->v));

                    if(key.compare("process_log_id") == 0)
                    {
                        ps_log_id = value;
                    }
                    else if(key.compare("log_file_id") == 0)
                    {
                        log_d_id = value;
                    }
                    else if(key.compare("log_file_path") == 0)
                    {
                        log_F_path = value;
                    }
                    else
                    {
                        expr::ErrorMessage::getInstance()->set_err_messageEx("Invalid key: " + key);
                        parsed = false;
                    }

                    entry = entry->next;
                } //while

                expr::ConfData::getInstance()->add_to_table(ps_log_id, log_d_id, log_F_path);
            } //for
        }
    }

    if(jobj)
    {
        json_object_put(jobj);
    }
    
    if(payload)
    {
        g_free(payload);
        payload = NULL;
    }

    expr::ConfData::getInstance()->set_parsed(parsed);
    return expr::ConfData::getInstance();
}

expr::PRIORITY expr::ConfigManager::get_priority(std::string priority)
{
    if(priority.compare("debug") == 0)
    {
        return DEBUG;
    }
    else if(priority.compare("inform") == 0)
    {
        return INFORM;
    }
    else if(priority.compare("error") == 0)
    {
        return ERROR;
    }
    else if(priority.compare("critical") == 0)
    {
        return CRITICAL;
    }
    else if(priority.compare("failure") == 0)
    {
        return FAILURE;
    }
    else
    {
        return NOT_DEFINED;
    }
}
