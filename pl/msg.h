#ifndef __MSG_H__
#define __MSG_H__

typedef UID unsigned int[4]

enum RType {
    OK;
    TIMEOUT;
    CANCEL;
};

struct IRequest {
    const char* app_id;
    const char* data;
    const char* user_id;
    const char* user_key;
};

struct IResponse {
    UID id;
    RType type;
    const char* result;
};

#endif
