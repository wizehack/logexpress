#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <json-c/json.h>
#include <json-c/bits.h>

#include "config.h"

//const char* read_contents(const char* filename);

/**
 * { "processId": "loggerA", "priority": "debug", "address": "127.0.0.1", "port": 1234 }`
 */
CONFDATA* parse_config_file(const char* filename)
{
	CONFDATA *obj_conf = NULL;
	struct json_object* jobj = NULL;
	struct json_object* subjobj = NULL;

	jobj = json_object_from_file(filename);

	if( (jobj == NULL) || is_error(jobj) )
	{
		return obj_conf;
	}

	obj_conf = (CONFDATA*)malloc(sizeof(CONFDATA));

	if(json_object_object_get_ex(jobj, "processId", &subjobj))
	{
		obj_conf->processid = (char*)malloc(sizeof(json_object_get_string(subjobj)));
		(char*)memcpy(obj_conf->processid, json_object_get_string(subjobj), strlen(json_object_get_string(subjobj))+1);
	}

	if(json_object_object_get_ex(jobj, "priority", &subjobj))
	{
		obj_conf->priority = (char*)malloc(sizeof(json_object_get_string(subjobj)));
		(char*)memcpy(obj_conf->priority, json_object_get_string(subjobj), strlen(json_object_get_string(subjobj))+1);
	}

	if(json_object_object_get_ex(jobj, "address", &subjobj))
	{
		obj_conf->address = (char*)malloc(sizeof(json_object_get_string(subjobj)));
		(char*)memcpy(obj_conf->address, json_object_get_string(subjobj), strlen(json_object_get_string(subjobj))+1);
	}

	if(json_object_object_get_ex(jobj, "port", &subjobj))
	{
		obj_conf->port = json_object_get_int(subjobj);
	}

	json_object_put(jobj);
	return obj_conf;
}
