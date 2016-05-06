#include <json-c/json.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "config.h"
#include "loglib.h"
#include "udpclient.h"

const char* get_log_level(PRIORITY log_level);
PRIORITY get_log_priority(const char* level);

CONFDATA *confdata = NULL;

bool config_logexpr(const char* filename)
{
	CONFDATA* confdata_tmp  = parse_config_file(filename);

	if((confdata == NULL) && (confdata_tmp != NULL))
	{
		confdata = (CONFDATA*)malloc(sizeof(CONFDATA));

		confdata->processid = (char*)malloc(sizeof(confdata_tmp->processid));
		confdata->priority = (char*)malloc(sizeof(confdata_tmp->priority));
		confdata->address = (char*)malloc(sizeof(confdata_tmp->address));

		(char*)memcpy(confdata->processid, confdata_tmp->processid, strlen(confdata_tmp->processid)+1);
		(char*)memcpy(confdata->priority, confdata_tmp->priority, strlen(confdata_tmp->priority)+1);
		(char*)memcpy(confdata->address, confdata_tmp->address, strlen(confdata_tmp->address)+1);
		confdata->port = confdata_tmp->port;
	}
	else
	{
		return false;
	}

	free(confdata_tmp->processid);
	free(confdata_tmp->priority);
	free(confdata_tmp->address);
	free(confdata_tmp);

	return true;
}

void log_debug(const char* file_name, const char* function_name, int line_number, const char *format, ...)
{
	char log_msg_buf[4095];
	va_list args;

	va_start(args, format);
	vsprintf(log_msg_buf, format, args);

	throw_log(DEBUG, file_name, function_name, line_number, log_msg_buf);
	va_end(args);
}

void log_info(const char* file_name, const char* function_name, int line_number, const char *format, ...)
{
	char log_msg_buf[4095];
	va_list args;

	va_start(args, format);
	vsprintf(log_msg_buf, format, args);

	throw_log(INFO, file_name, function_name, line_number, log_msg_buf);
	va_end(args);
}

void log_error(const char* file_name, const char* function_name, int line_number, const char *format, ...)
{
	char log_msg_buf[4095];
	va_list args;

	va_start(args, format);
	vsprintf(log_msg_buf, format, args);

	throw_log(ERROR, file_name, function_name, line_number, log_msg_buf);
	va_end(args);
}

void log_failure(const char* file_name, const char* function_name, int line_number, const char *format, ...)
{
	char log_msg_buf[4095];
	va_list args;

	va_start(args, format);
	vsprintf(log_msg_buf, format, args);

	throw_log(FAILURE, file_name, function_name, line_number, log_msg_buf);
	va_end(args);
}

void log_critical(const char* file_name, const char* function_name, int line_number, const char *format, ...)
{
	char log_msg_buf[4095];
	va_list args;

	va_start(args, format);
	vsprintf(log_msg_buf, format, args);

	throw_log(CRITICAL, file_name, function_name, line_number, log_msg_buf);
	va_end(args);
}

/*
 {"process_log_id":"a1","time":"2016-04-23 21:43:09.548","log":{"file":"Main.java","func":"main","line":15,"level":"debug","msg":"test"}}
*/
void throw_log(PRIORITY log_level, const char* file_name, const char* function_name, int line_number, const char* log_msg)
{
	json_object* jobj = NULL;
	json_object* jobj_pslid = NULL;
	json_object* jobj_time = NULL;
	json_object* jobj_log = NULL;
	json_object* subjobj = NULL;
	json_object* jobj_file = NULL;
	json_object* jobj_function = NULL;
	json_object* jobj_line = NULL;
	json_object* jobj_level = NULL;
	json_object* jobj_msg = NULL;

	char* msg = NULL;
	PRIORITY priority = get_log_priority(confdata->priority);

	if(log_level < priority)
	{
		return;
	}

	jobj = json_object_new_object();

	if(confdata->processid)
	{
		jobj_pslid = json_object_new_string(confdata->processid);
		json_object_object_add(jobj, "process_log_id", jobj_pslid);
	}
	else
	{
		json_object_put(jobj);
		return;
	}

	const char* level = get_log_level(log_level);
	char time_buf[26];
	time_t now = time(NULL);
	strftime(time_buf, 26, "%Y-%m-%d %H:%M:%S.%03d", localtime(&now));

	jobj_time = json_object_new_string(time_buf);

	json_object_object_add(jobj, "time", jobj_time);

	jobj_log = json_object_new_object();

	if(file_name)
	{
		jobj_file = json_object_new_string(file_name);
	}

	if(function_name)
	{
		jobj_function = json_object_new_string(function_name);
	}

	if(line_number)
	{
		jobj_line = json_object_new_int(line_number);
	}

	jobj_level = json_object_new_string(level);

	if(log_msg)
	{
		if(strlen(log_msg) > (MAX_MSG_SIZE-1))
		{
			msg = (char*)malloc(MAX_MSG_SIZE-1);
			(char*)memcpy(msg, log_msg, MAX_MSG_SIZE);
			jobj_msg = json_object_new_string(msg);
		}
		else
		{
			jobj_msg = json_object_new_string(log_msg);
		}
	}

	json_object_object_add(jobj_log, "file", jobj_file);
	json_object_object_add(jobj_log, "func", jobj_function);
	json_object_object_add(jobj_log, "line", jobj_line);
	json_object_object_add(jobj_log, "level", jobj_level);
	json_object_object_add(jobj_log, "msg", jobj_msg);

	json_object_object_add(jobj, "log", jobj_log);

	/* For Test */
	send_log(json_object_to_json_string(jobj));
	json_object_put(jobj);
}

const char* get_log_level(PRIORITY log_level)
{
	if(log_level == DEBUG)
	{
		return "debug";
	}
	else if(log_level == INFO)
	{
		return "info";
	}
	else if(log_level == ERROR)
	{
		return "error";
	}
	else if(log_level == FAILURE)
	{
		return "failure";
	}
	else if(log_level == CRITICAL)
	{
		return "critical";
	}
	else
	{
		return "NONE";
	}
}

PRIORITY get_log_priority(const char* level)
{
	if(strcmp(level, "debug") == 0)
	{
		return DEBUG;
	}
	else if(strcmp(level, "info") == 0)
	{
		return INFO;
	}
	else if(strcmp(level, "error") == 0)
	{
		return ERROR;
	}
	else if(strcmp(level, "failure") == 0)
	{
		return FAILURE;
	}
	else if(strcmp(level, "critical") == 0)
	{
		return CRITICAL;
	}
	else
	{
		return NONE;
	}
}
