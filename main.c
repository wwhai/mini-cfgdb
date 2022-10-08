#include <stdio.h>
#include "cfgdb.h"
int main(int argc, char const *argv[])
{
    CfgDB *db = NewFileDB(1024000, "./test.hex");
    Byte k1[] = "K1";
    Byte v1[] = "V1";
    Set(db, k1, v1);
    return 0;
}
