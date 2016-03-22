#ifndef PARAM_PARSER_H_
#define PARAM_PARSER_H_

#include <string>

class ParamParser {
    public:
        ParamParser();
        ~ParamParser();
        int get_ctl_port();
        char* get_cmd();
        bool check_parameters(int argc, char** argv);

    private:
        int port;
        char cmd[5];
};
#endif /*PARAM_PARSER_H_*/
