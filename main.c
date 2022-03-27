#include <stdio.h>
#include "cfgdb.h"
int main(int argc, char const *argv[])
{
    unsigned char k[] = "KEY";
    unsigned char v[] = "Value:1234567890";
    Entry e = NewEntry(k, v);
    unsigned char *b = EncodeEntry(e);
    for (size_t i = 0; i < e.key_size + e.value_size + 8; i++)
    {
        printf("%c --> : %04X\n", b[i], b[i]);
    }
    Entry e1 = DecodeEntry(b);
    ToString(e1);
    return 0;
}
