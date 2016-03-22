#include "log.h"
#include "file.h"
#include "logger.h"
#include "confData.h"
#include <fstream>

expr::Log::Log(std::string file):
    filePath(file)
{}

expr::Log::~Log()
{
    if(this->list_process_log_id.empty() == false)
    {
        this->list_process_log_id.clear();
    }

    if(this->log_buffer.empty() == false)
    {
        this->write();
    }
}

void expr::Log::add_process_log_id(std::string id)
{
    this->list_process_log_id.push_back(id);
}

void expr::Log::add_log(std::string process_log_id, std::string log)
{
    expr::Logger logger;

    if(this->is_myLog(process_log_id))
    {
        this->log_buffer.push_back(log);

        if(static_cast<int>(this->log_buffer.size()) >= expr::ConfData::getInstance()->get_max_log_buffer_size())
        {
            this->write();
        }
    }
}

void expr::Log::write()
{
    expr::File* file_write = NULL;
    std::list<std::string>::iterator it = this->log_buffer.begin();

    file_write = new expr::File(this->filePath, "write");

    if(file_write->is_open())
    {
        while(it != this->log_buffer.end())
        {
            file_write->write((*it));
            ++it;
        }

        this->log_buffer.clear();
        file_write->sync();
        file_write->close();
    }

    if(file_write)
    {
        delete file_write;
        file_write = NULL;
    }
}

std::string expr::Log::get_filePath()
{
    return this->filePath;
}

bool expr::Log::is_myLog(std::string process_log_id)
{
    std::list<std::string>::iterator itor;

    if(process_log_id.empty() == true)
    {
        return false;
    }

    for(itor = this->list_process_log_id.begin(); itor != this->list_process_log_id.end(); itor++)
    {
        if((*itor).compare(process_log_id) == 0)
        {
            return true;
        }
    }

    return false;
}

void expr::Log::print_process_log_id()
{
    expr::Logger logger;
    std::list<std::string>::iterator itor;
    logger.show(">>>> process_log_id");
    for(itor = this->list_process_log_id.begin(); itor != this->list_process_log_id.end(); itor++)
    {
        logger.show((*itor));
    }
}
