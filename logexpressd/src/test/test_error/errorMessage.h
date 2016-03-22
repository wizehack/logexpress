#ifndef ERROR_MESSAGE_H_
#define ERROR_MESSAGE_H_

#include <string>

namespace expr {

    enum error_type {
        UNKNOWN_TYPE,
        USAGE,
        CONFIG
    };

    enum error_code {
        UNKNOWN_CODE,
        OPT_NUMBER,
        INVALID_OPT,
        CONFIG_FILE,
        CONFIG_JSON,
        CONFIG_PARSE
    };

    class ErrorMessage {
        public:
            ErrorMessage();
            ErrorMessage(expr::error_type type, expr::error_code code);
            ~ErrorMessage();
            void set_error_type(expr::error_type type);
            void set_error_code(expr::error_code desc);
            void set_error_desc(std::string desc);

            expr::error_type get_error_type();
            expr::error_code get_error_code();
            std::string get_error_desc();
            const char* get_error_unknown();

        private:
            expr::error_type e_type;
            expr::error_code e_code;
            std::string e_desc; //error description
            const char* e_unknown;
    };
}

#endif /* ERROR_MESSAGE_H_ */
