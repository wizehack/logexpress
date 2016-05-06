#ifndef LOG_LIB_H_
#define LOG_LIB_H_ 

#include <stdarg.h>
#include <stdbool.h>

#define LOG_DEBUG(...) log_debug(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...) log_info(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) log_error(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define LOG_FAILURE(...) log_failure(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define LOG_CRITICAL(...) log_critical(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

typedef enum priority {
    DEBUG,
    INFO,
    ERROR,
    FAILURE,
    CRITICAL,
    NONE
} PRIORITY;

void throw_log(PRIORITY log_level, const char* file_name, const char* function_name, int line_number, const char *log_msg);
void log_debug(const char* file_name, const char* function_name, int line_number, const char *format, ...);
void log_info(const char* file_name, const char* function_name, int line_number, const char *format, ...);
void log_error(const char* file_name, const char* function_name, int line_number, const char *format, ...);
void log_failure(const char* file_name, const char* function_name, int line_number, const char *format, ...);
void log_critical(const char* file_name, const char* function_name, int line_number, const char *format, ...);
bool config_logexpr(const char* filename);

#endif /* LOG_LIB_H_ */ 
