#include <iostream>
//#include "file.h"
#include "configManager.h"
#include "confData.h"
#include <algorithm> 

/*
void test_read_file()
{
    std::string conf_file_path("./conf/jsonLogger.conf");
    jsonLog::File file = jsonLog::File(conf_file_path);

    if(file.is_exist())
    {
        std::string file_contents(file.get_contents());
        std::cout << file_contents << std::endl;
    }
    else
    {
        std::cout << "file is NOT exist" << std::endl;
    }
}
*/

void test_json()
{
    std::string conf_file_path("/home/wizehack/cpp_proj/json-C/conf/jsonLogger_conf.json");
    ConfigManager configMgr;
    std::string json_conf(configMgr.get_conf_file(conf_file_path));
    bool is_parsed = configMgr.parse_conf_json(json_conf);

    if(is_parsed)
    {
        ConfData* confData = configMgr.get_obj_confData();
        std::list<std::shared_ptr<LogMap>> log_map_table = confData->get_mapping_table();

        std::list<std::shared_ptr<LogMap>>::iterator itor;

        for(itor = log_map_table.begin(); itor != log_map_table.end(); itor++)
        {
            std::cout<< (*itor)->get_process_log_id() << " : " << (*itor)->get_log_daemon_id() << " : " << (*itor)->get_log_file_path() << std::endl;
        }
    }
}

int main()
{
    test_json();
}
