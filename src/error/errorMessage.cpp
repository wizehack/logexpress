#include "errorMessage.h"

std::atomic<expr::ErrorMessage*> expr::ErrorMessage::_singleton;
std::mutex expr::ErrorMessage::_mutex;

expr::ErrorMessage::ErrorMessage():
    error(false),
    err_name(""),
    err_message(""),
    err_messageEx(""){}
expr::ErrorMessage::~ErrorMessage(){}

expr::ErrorMessage* expr::ErrorMessage::getInstance() { 
	expr::ErrorMessage* inst = _singleton.load(std::memory_order_relaxed);
	std::atomic_thread_fence(std::memory_order_acquire);
	if(inst == 0) {
		std::lock_guard<std::mutex> lock(_mutex);
		inst = _singleton.load(std::memory_order_relaxed);
		if(inst == 0) {
			inst = new expr::ErrorMessage();
			std::atomic_thread_fence(std::memory_order_release);
			_singleton.store(inst, std::memory_order_relaxed);
		}
	}
	return inst;
}

void expr::ErrorMessage::initialize()
{
    this->error = false;
    err_name.clear();
    err_message.clear();
    err_messageEx.clear();
}

bool expr::ErrorMessage::is_error_found()
{
    return this->error;
}

void expr::ErrorMessage::set_err_name(std::string name)
{
    if(name.empty() == false)
    {
        this->error = true;
        this->err_name = name;
    }
}

void expr::ErrorMessage::set_err_message(std::string msg)
{
    if(msg.empty() == false)
    {
        this->err_message = msg;
    }
}

void expr::ErrorMessage::set_err_messageEx(std::string msg)
{
    this->err_messageEx = msg;
}

std::string expr::ErrorMessage::get_err_name()
{
    return this->err_name;
}

std::string expr::ErrorMessage::get_err_message()
{
    return this->err_message;
}

std::string expr::ErrorMessage::get_err_messageEx()
{
    return this->err_messageEx;
}
