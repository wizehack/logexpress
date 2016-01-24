#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>

namespace expr {
    class Logger {
        public:
            Logger();
            ~Logger();
            void log(std::string str);
    };
}

#endif /* LOGGER_H_ */
