#ifndef ERROR_MESSAGE_POOL_H_
#define ERROR_MESSAGE_POOL_H_

#include <mutex>
#include <atomic>
#include <vector>
#include <string>
#include <memory>
#include "errorMessage.h"

namespace expr {
    class ErrorMessagePool {

        public:
            ~ErrorMessagePool();
            static ErrorMessagePool* getInstance();
            void init();
            void add(std::shared_ptr<ErrorMessage> sptr_err_msg);
            int size();
            std::shared_ptr<ErrorMessage> get(int i);

        private:
            ErrorMessagePool();
            std::vector<std::shared_ptr<ErrorMessage>> pool;

        private:
            static std::atomic<ErrorMessagePool*> _singleton;
            static std::mutex _mutex;
    };
}

#endif /* ERROR_MESSAGE_POOL_H_ */
