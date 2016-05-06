#include "loglib.h"
#include <stdio.h>

//gcc -o test test.c -L /home/wizehack/cpp_proj/logexpress/logexprlibC/bin/ -llogexpr -L/usr/local/lib -ljson-c -I/usr/local/include/json-c/

int main()
{
	bool log_ok = false;
	const char* filename = "../../resource/logexpr.json";
	log_ok = config_logexpr(filename);
	
	if(log_ok)
	{
		LOG_DEBUG("log %s", "debug");
		LOG_INFO("log %s", "info");
		LOG_ERROR("log %s", "error");
		LOG_FAILURE("log %s", "failure");
		LOG_CRITICAL("log %s", "critical");
	}
	else
	{
		printf("log_ok: %d", log_ok);
	}

	return 0;
}
