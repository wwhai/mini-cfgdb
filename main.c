#include <stdio.h>
#include "cfgdb.h"
int main(int argc, char const *argv[])
{
    unsigned char *k = "KKK";
    unsigned char *v = "VVVV";
    Entry e = NewEntry(k, v);
    unsigned char *b = EncodeEntry(e);
    for (size_t i = 0; i < e.key_size + e.value_size + 8; i++)
    {
        printf("%c === %04X\n", b[i], b[i]);
    }

    return 0;
}
