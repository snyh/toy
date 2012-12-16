#ifndef __MSG_H__
#define __MSG_H__
#include <openssl/md5.h>
#include <string>
const int version = 1;

enum Type { 
    REG_APP = 0,
    CAP_REQUEST,
    CAP_RESPONSE_OK,
    CAP_RESPONSE_ERR,
};


struct UID {
    UID(const unsigned char* in_data, size_t s) {
        MD5(in_data, s, data);
    }
    UID() { }
    unsigned char data[16];
};

std::string hash2str(const UID& h)
{
    char buf[33];
    for (int i=0; i<16; i++) {
        snprintf(buf+i*2, 3, "%02x", (unsigned char)h.data[i]);
    }
    buf[32] = '\0'; 
    return std::string(buf, 32);
}

UID str2hash(const std::string& s)
{
    UID hash; 
    for (int i=0; i<32; i+=2) {
        hash.data[i/2] = stoi(s.substr(i, 2), 0, 16);
    }
    return hash;
}


#endif
