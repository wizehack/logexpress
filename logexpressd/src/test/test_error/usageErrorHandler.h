#ifndef USAGE_ERROR_HANDLER_H_
#define USAGE_ERROR_HANDLER_H_

#include "errorHandler.h"

namespace expr {
    class UsageErrorHandler : public ErrorHandler {
        public:
            UsageErrorHandler();
            ~UsageErrorHandler();
            void request(expr::ErrorMessage* err_msg);
    };
}

#endif /* USAGE_ERROR_HANDLER_H_ */
