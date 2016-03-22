#ifndef ERROR_HANDLER_H_
#define ERROR_HANDLER_H_

#include "errorMessage.h"

namespace expr {
    class ErrorHandler {
        public: 
            ErrorHandler();
            virtual ~ErrorHandler();
            void set_next(expr::ErrorHandler* err_handler);
            virtual void request(expr::ErrorMessage* err_msg) = 0;

        protected:
            void throw_error(expr::ErrorMessage* err_msg, bool known_error);
            void throw_msg(std::string msg);
            std::string get_error_code_desc(expr::error_code err_code);
            std::string get_error_type_desc(expr::error_type err_type);

        protected:
            expr::ErrorHandler* next;
            const bool UNKNOWN_ERROR;
            const bool KNOWN_ERROR;
    };
}

#endif /* ERROR_HANDLER_H_ */
