#ifndef CONFIG_ERROR_HANDLER_H_
#define CONFIG_ERROR_HANDLER_H_

#include "errorHandler.h"

namespace expr {
    class ConfigErrorHandler : public ErrorHandler {
        public:
            ConfigErrorHandler();
            ~ConfigErrorHandler();
            void request(expr::ErrorMessage* err_msg);
    };
}

#endif /* CONFIG_ERROR_HANDLER_H_ */
