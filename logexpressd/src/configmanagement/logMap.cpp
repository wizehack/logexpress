
#include "logMap.h"

expr::LogMap::LogMap(std::string ps_log_id, std::string log_d_id, std::string log_f_path):
    process_log_id(ps_log_id),
    log_daemon_id(log_d_id),
    log_file_path(log_f_path){}

expr::LogMap::~LogMap(){}

std::string expr::LogMap::get_process_log_id()
{
    return this->process_log_id;
}

std::string expr::LogMap::get_log_daemon_id()
{
    return this->log_daemon_id;
}

std::string expr::LogMap::get_log_file_path()
{
    return this->log_file_path;
}


