#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>

namespace expr {
    class Logger {
        public:
            Logger();
            ~Logger();
            void show(std::string str);
    };
}

#endif /* LOGGER_H_ */
