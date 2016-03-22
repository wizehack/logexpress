
#include "errorMessage.h"
#include "errorMessagePool.h"
#include "errorHandler.h"
#include "usageErrorHandler.h"
#include "configErrorHandler.h"
#include <iostream>

void setup()
{
    expr::ErrorMessagePool::getInstance()->init();
    expr::error_type e_type;
    expr::error_code e_code;

    e_type = expr::CONFIG;
    e_code = expr::CONFIG_FILE;
    std::shared_ptr<expr::ErrorMessage> error_file = std::make_shared<expr::ErrorMessage>(e_type, e_code);
    error_file->set_error_desc("test config file");

    e_code = expr::CONFIG_JSON;
    std::shared_ptr<expr::ErrorMessage> error_json = std::make_shared<expr::ErrorMessage>(e_type, e_code);
    error_json->set_error_desc("test config json");

    e_code = expr::CONFIG_PARSE;
    std::shared_ptr<expr::ErrorMessage> error_parse = std::make_shared<expr::ErrorMessage>(e_type, e_code);
    error_parse->set_error_desc("test config parse");

    expr::ErrorMessagePool::getInstance()->add(error_file);
    expr::ErrorMessagePool::getInstance()->add(error_json);
    expr::ErrorMessagePool::getInstance()->add(error_parse);
}

bool test_error_message_pool()
{
    bool ret = false;

    std::cout << "tc1 start" << std::endl;
    if(expr::ErrorMessagePool::getInstance()->size() == 3)
    {
        std::cout << "ok" << std::endl;
        ret = true;
    }
    else
    {
        std::cout << "fail" << std::endl;
        ret = false;
    }

    if(expr::ErrorMessagePool::getInstance()->get(0)->get_error_type() == expr::CONFIG)
    {
        std::cout << "ok" << std::endl;
        ret = true;
    }
    else
    {
        std::cout << "fail" << std::endl;
        ret = false;
    }

    if(expr::ErrorMessagePool::getInstance()->get(1)->get_error_code() == expr::CONFIG_JSON)
    {
        std::cout << "ok" << std::endl;
        ret = true;
    }
    else
    {
        std::cout << "fail" << std::endl;
        ret = false;
    }

    if(expr::ErrorMessagePool::getInstance()->get(2)->get_error_code() == expr::CONFIG_PARSE)
    {
        std::cout << "ok" << std::endl;
        ret = true;
    }
    else
    {
        std::cout << "fail" << std::endl;
        ret = false;
    }

    return ret;
}

bool test_error_handler()
{
    bool ret = false;

    std::cout << "tc2 start" << std::endl;

    expr::ErrorHandler* usage_err_handler = new expr::UsageErrorHandler();
    expr::ErrorHandler* config_err_handler = new expr::ConfigErrorHandler();

    usage_err_handler->set_next(config_err_handler);

    int i;
    for(i = 0; i < expr::ErrorMessagePool::getInstance()->size(); i++)
    {
        usage_err_handler->request(expr::ErrorMessagePool::getInstance()->get(i).get());
    }

    if(i == 3)
    {
        ret = true;
    }

    if(usage_err_handler)
    {
        delete usage_err_handler;
        usage_err_handler = NULL;
    }

    if(config_err_handler)
    {
        delete config_err_handler;
        usage_err_handler = NULL;
    }

    return ret;
}

int main()
{
    setup();
    if(test_error_message_pool())
    {
        std::cout << "tc1 success" << std::endl;
    }
    else
    {
        std::cout << "tc1 failure" << std::endl;
    }

    if(test_error_handler())
    {
        std::cout << "tc2 success" << std::endl;
    }
    else
    {
        std::cout << "tc2 failure" << std::endl;
    }

    return 0;
}
