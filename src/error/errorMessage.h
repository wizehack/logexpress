#ifndef ERROR_MESSAGE_H_
#define ERROR_MESSAGE_H_

#include <mutex>
#include <atomic>
#include <string>
#include <memory>

#include <string>

namespace expr {
    class ErrorMessage {
        public:
            ~ErrorMessage();
            static ErrorMessage* getInstance();
            void initialize();
            bool is_error_found();
            void set_err_name(std::string name);
            void set_err_message(std::string msg);
            void set_err_messageEx(std::string msg);
            std::string get_err_name();
            std::string get_err_message();
            std::string get_err_messageEx();

        private: 
            ErrorMessage();

        private:
            bool error;
            std::string err_name;
            std::string err_message;
            std::string err_messageEx;

        private:
            static std::atomic<ErrorMessage*> _singleton;
            static std::mutex _mutex;
    };
}

#endif /* ERROR_MESSAGE_H_ */
