
#include "rc4.h"
#include "stdio.h"
#include "string.h"
#include "time.h"

enum Mode
{
    ENCRYPT,
    DECRYPT
};
 
void print_usage()
{
    printf("Usage: \n"
           "  cyphersaber [mode] [key] [input file] [output file]\n"
           "\n"
           "Options: \n"
           "  mode: encrypt / decrypt\n"
           "  key: encryption key, may be up to 245 chars long\n"
           "  input file: the input to read\n"
           "  output file: the input to write");
}
 
int main(int argc, char* argv[])
{
    enum Mode mode;     
    char* key;
    size_t keylen;
    rc4_byte iv[10];
    rc4_byte* ivkey;
    size_t ivkeylen;
    rc4_state state;
    size_t i;
    FILE* in  = stdin;
    FILE* out = stdout;
    
    if (argc < 3)
    {
        print_usage();
    }
    
    if (strcmp(argv[1], "encrypt") == 0)
    {
        mode = ENCRYPT;
    }
    else if (strcmp(argv[1], "decrypt") == 0)
    {
        mode = DECRYPT;
    }
    else
    {
        printf("Unknown mode.\n");
        print_usage();
    }
    
    key = argv[2];
    keylen = strlen(key);
    ivkeylen = keylen + 10;   

    if (argc >= 4)
    {
        in = fopen(argv[3], "rb");
        if (in == NULL)
        {
            printf("Could not open %s for reading.", argv[3]);
            return -1;
        }
    }
    
    if (argc >= 5)
    {
        out = fopen(argv[4], "wb");
        if (out == NULL)
        {
            printf("Could not open %s for writing.", argv[3]);
            return -1;
        }
    }
    
    if (mode == ENCRYPT)
    {
        srand(time(NULL));               
        for (i = 0; i < 10; i++)
        {
            iv[i] = (rc4_byte)rand();
        }
        fwrite(iv, 1, 10, out);
    }
    else
    {
        // first 10 byted in data are iv
        int r;
        r = fread(iv, 1, 10, in);
        if (r != 10)
        {
            printf("Could not read iv.");
            return -1;
        }
    }
    
    ivkey = (rc4_byte*)malloc(ivkeylen);        
    for (i = 0; i < ivkeylen; i++)
    {
        if (i < keylen)
        {
            ivkey[i] = key[i];            
        }
        else
        {
            ivkey[i] = iv[i - keylen];
        }
    }    
    
    rc4_init(&state, ivkey, ivkeylen);
    
    int c = fgetc(in);
    while (c != EOF)
    {
        rc4_byte r = rc4(&state, (rc4_byte)c);
        
        fputc(r, out);
        
        c = fgetc(in);
    }  

    return 0;
}
