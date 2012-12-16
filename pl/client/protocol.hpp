#ifndef __PROTOCOL__
#define __PROTOCOL__

// 发送请求：
// 首先发送4字节的请求类型。REG_APP, CAP_REQUEST, CAP_RESPONSE
// 紧跟：
enum {
    REG_APP = 0;
    CAP_REQ;
    CAP_RESP;
};

enum {
    CAP_RESULT = 0;
    REG_RESULT;
};


#endif
