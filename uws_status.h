#ifndef __UWS_STATUS_H_
#define __UWS_STATUS_H_
#include "uws.h"
#include "uws_header.h"
#include "uws_config.h"
#include <stdio.h>
#include <setjmp.h>
#define STATUS_SUM  8

typedef int (*DataReader)(unsigned char*);

enum conn_status {//define some useful request handler statuses
    CS_WAIT,
    CS_ACCEPT,
    CS_REQUEST_READ,
    CS_UPSTREAM_WRITE,
    CS_UPSTREAM_READ,
    CS_FILE_READ,
    CS_RESPONSE_WRITE,
    CS_CLOSE
};

typedef struct {
    enum                conn_status status;     //the place of this position
    char                flag;                   //for user defined flag1
    void                *ptr;                   //to save additional data
    int                 request_id;             //a requst for router
    int                 epollfd;                //save epollfd
    int                 clientfd;               //incoming socket fd
    int                 serverfd;               //for upstream
    FILE                *input_file;            //clientfd fdopen file
    DataReader          readData;               //function to get more response data
    struct http_header  *request_header;
    struct http_header  *response_header;
    int                 status_code;            //indicate response code 
    jmp_buf             jmp_buff;               //to quick jump out of error response
    server_cfg_t*       running_server;         //Current Server Profile Used
    char                server_ip[20];
    char                client_ip[20];
} ConnInfo, *pConnInfo;
#endif
