#include "messageQueue.h"

std::atomic<expr::MessageQueue*> expr::MessageQueue::_singleton;
std::mutex expr::MessageQueue::_mutex;

expr::MessageQueue::MessageQueue()
{
    this->listenerQueue = g_async_queue_new();
    this->controlMessageQueue = g_async_queue_new();
}

expr::MessageQueue::~MessageQueue(){}

expr::MessageQueue* expr::MessageQueue::getInstance() { 
	expr::MessageQueue* inst = _singleton.load(std::memory_order_relaxed);
	std::atomic_thread_fence(std::memory_order_acquire);
	if(inst == 0) {
		std::lock_guard<std::mutex> lock(_mutex);
		inst = _singleton.load(std::memory_order_relaxed);
		if(inst == 0) {
			inst = new expr::MessageQueue();
			std::atomic_thread_fence(std::memory_order_release);
			_singleton.store(inst, std::memory_order_relaxed);
		}
	}
	return inst;
}

GAsyncQueue* expr::MessageQueue::get_listenerQueue()
{
    return this->listenerQueue;
}

GAsyncQueue* expr::MessageQueue::get_Ctl_msg_Queue()
{
    return this->controlMessageQueue;
}
