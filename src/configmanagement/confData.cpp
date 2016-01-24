#include "confData.h"

std::atomic<expr::ConfData*> expr::ConfData::_singleton;
std::mutex expr::ConfData::_mutex;

expr::ConfData::ConfData():
    log_priority(DEBUG),
    export_period(1),
    max_log_buffer_size(10),
    parsed(false){}

expr::ConfData::~ConfData()
{
    if(this->mapping_table.size())
    {
        this->mapping_table.clear();
    }
}

expr::ConfData* expr::ConfData::getInstance() { 
	expr::ConfData* inst = _singleton.load(std::memory_order_relaxed);
	std::atomic_thread_fence(std::memory_order_acquire);
	if(inst == 0) {
		std::lock_guard<std::mutex> lock(_mutex);
		inst = _singleton.load(std::memory_order_relaxed);
		if(inst == 0) {
			inst = new expr::ConfData();
			std::atomic_thread_fence(std::memory_order_release);
			_singleton.store(inst, std::memory_order_relaxed);
		}
	}
	return inst;
}

void expr::ConfData::set_log_priority(expr::PRIORITY priority)
{
    this->log_priority = priority;
}

void expr::ConfData::set_export_period(int period)
{
    this->export_period = period;
}

void expr::ConfData::set_max_log_buffer_size(int size)
{
    this->max_log_buffer_size = size;
}

void expr::ConfData::set_parsed(bool parsed)
{
    this->parsed = parsed;
}
expr::PRIORITY expr::ConfData::get_log_priority()
{
    return this->log_priority;
}

int expr::ConfData::get_export_period()
{
    return this->export_period;
}

int expr::ConfData::get_max_log_buffer_size()
{
    return this->max_log_buffer_size;
}

void expr::ConfData::add_to_table(std::string ps_log_id, std::string log_d_id, std::string log_file_path)
{
    std::shared_ptr<expr::LogMap> sptr_logMap = std::make_shared<expr::LogMap>(ps_log_id, log_d_id, log_file_path);
    this->mapping_table.push_back(sptr_logMap);
}

std::list<std::shared_ptr<expr::LogMap>> expr::ConfData::get_mapping_table()
{
    return this->mapping_table;
}

bool expr::ConfData::is_parsed()
{
    return parsed;
}

