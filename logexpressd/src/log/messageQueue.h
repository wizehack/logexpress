#ifndef MESSAGE_QUEUE_H_
#define MESSAGE_QUEUE_H_

#include <mutex>
#include <atomic>
#include <glib-2.0/glib.h>

namespace expr {
    class MessageQueue {
        public:
            ~MessageQueue();
            static MessageQueue* getInstance();
            GAsyncQueue* get_listenerQueue();
            GAsyncQueue* get_Ctl_msg_Queue();

        private:
            MessageQueue();

        private:
            GAsyncQueue* listenerQueue;
            GAsyncQueue* controlMessageQueue;

            static std::atomic<MessageQueue*> _singleton;
            static std::mutex _mutex;
    };
}

#endif /* MESSAGE_QUEUE_H_ */
