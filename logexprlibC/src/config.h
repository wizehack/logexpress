#ifndef CONFIG_H_ 
#define CONFIG_H_

#include <stdbool.h>

typedef struct conf {
    char* processid;
    char* priority;
    char* address;
    int port;
} CONFDATA;

CONFDATA *confdata;
CONFDATA* parse_config_file(const char* filename);


#endif /* CONFIG_H */
