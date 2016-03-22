#include "errorMessagePool.h"

std::atomic<expr::ErrorMessagePool*> expr::ErrorMessagePool::_singleton;
std::mutex expr::ErrorMessagePool::_mutex;

expr::ErrorMessagePool::ErrorMessagePool(){}

expr::ErrorMessagePool::~ErrorMessagePool(){}

expr::ErrorMessagePool* expr::ErrorMessagePool::getInstance() { 
	expr::ErrorMessagePool* inst = _singleton.load(std::memory_order_relaxed);
	std::atomic_thread_fence(std::memory_order_acquire);
	if(inst == 0) {
		std::lock_guard<std::mutex> lock(_mutex);
		inst = _singleton.load(std::memory_order_relaxed);
		if(inst == 0) {
			inst = new expr::ErrorMessagePool();
			std::atomic_thread_fence(std::memory_order_release);
			_singleton.store(inst, std::memory_order_relaxed);
		}
	}
	return inst;
}

void expr::ErrorMessagePool::init()
{
    if(this->pool.size() > 0)
    {
        this->pool.clear();
    }
}

void expr::ErrorMessagePool::add(std::shared_ptr<expr::ErrorMessage> sptr_err_msg)
{
    this->pool.push_back(sptr_err_msg);
}

int expr::ErrorMessagePool::size()
{
    this->pool.size();
}

std::shared_ptr<expr::ErrorMessage> expr::ErrorMessagePool::get(int i)
{
    return this->pool[i];
}

