#include <stdio.h>
#include "cfgdb.h"
int main(int argc, char const *argv[])
{
    CfgDB *db = NewFileDB(1024000, "./test.hex");
    Byte k1[] = "K1";
    Byte v1[] = "V1";
    Set(db, k1, v1);
    Byte k2[] = "K2";
    Byte v2[] = "VV2";
    Set(db, k2, v2);
    Byte k3[] = "K3";
    Byte v3[] = "VVV3";
    Set(db, k3, v3);
    Byte k4[] = "K4444";
    Byte v4[] = "VVV44444444444";
    Set(db, k4, v4);
    Get(db, k2);
    return 0;
}
