
#include "rc4.h"

void swap(rc4_byte* a, rc4_byte* b)
{
    rc4_byte t = *a;
    *a = *b;
    *b = t;
}

void rc4_init(rc4_state* state, rc4_byte* key, size_t keylen)
{
    rc4_byte i, j, n;
    
    i = 0;
    do
    {
        state->state[i] = i;
        i++;
    }    
    while (i != 255);
    
    j = 0;
    i = 0;
    do
    {
        n = i % keylen;
        j += state->state[i] + key[n];
        swap(&state->state[i], &state->state[j]);
        i++;
    }    
    while (i != 255);
    
    state->i = 0;
    state->j = 0;
}

rc4_byte rc4(rc4_state* state, rc4_byte in)
{
    rc4_byte n;
    
    state->i++;
    state->j += state->state[state->i];
    swap(&state->state[state->i], &state->state[state->j]);
    n = state->state[state->i] + state->state[state->j];
    
    return in ^ state->state[n];
}
