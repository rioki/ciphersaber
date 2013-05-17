
#ifndef _RC4_H_
#define _RC4_H_

#include "stdlib.h"

typedef unsigned char rc4_byte;

struct rc4_state_
{
    rc4_byte i;
    rc4_byte j;
    rc4_byte state[256];
};
typedef struct rc4_state_ rc4_state;

void rc4_init(rc4_state* state, rc4_byte* key, size_t keylen);

rc4_byte rc4(rc4_state* state, rc4_byte in);

#endif
