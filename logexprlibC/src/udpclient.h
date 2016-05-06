#ifndef UDPCLIENT_H_
#define UDPCLIENT_H_

#define MAX_DATA_UNIT 1024
#define MAX_MSG_SIZE MAX_DATA_UNIT * 4 
#define MAX_LOG_SIZE MAX_DATA_UNIT * 5

void send_log(const char* msg);

#endif /*UDPCLIENT_H_*/
