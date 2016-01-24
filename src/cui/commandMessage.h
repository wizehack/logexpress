#ifndef COMMAND_MESSAGE_H_
#define COMMAND_MESSAGE_H_

#include <string>

namespace expr {
    class CommandMessage {

        public:
            CommandMessage();
            ~CommandMessage();

            void set_number_of_command(int num);
            void set_opt_conf(const char* opt);
            void set_path_conf(const char* path);

            int get_number_of_command();
            std::string get_opt_conf();
            std::string get_path_conf();

        private:
            int number_of_command;
            std::string opt_conf;
            std::string path_conf;
    };
}

#endif /* COMMAND_MESSAGE_H_ */
