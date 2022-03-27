#include "cfgdb.h"

Entry NewEntry(unsigned char k[], unsigned char v[])
{
    Entry e = {
        .key = k,
        .value = v,
        .key_size = sizeof(*k) / sizeof(unsigned char),
        .value_size = sizeof(*v) / sizeof(unsigned char)};
    return e;
}
unsigned char *EncodeEntry(Entry e)
{
    unsigned char *bin = (unsigned char *)malloc(sizeof(8 + e.key_size + e.value_size));
    int offset = 0;
    // 大端模式
    memcpy(bin + offset, &e.key_size, U32_SIZE);
    offset += U32_SIZE;
    // 大端模式
    memcpy(bin + offset, &e.value_size, U32_SIZE);
    offset += U32_SIZE;
    memcpy(bin + offset, e.key, e.key_size);
    offset += e.key_size;
    memcpy(bin + offset, e.value, e.value_size);
    return bin;
}

CfgDB *NewCfgDB(int bucket_size)
{
    CfgDB *db = (CfgDB *)malloc(sizeof(CfgDB));
    db->offset = 0;
    db->bucket = (unsigned char *)malloc(bucket_size * sizeof(unsigned char));
    return db;
}
int Set(CfgDB *db, unsigned char *k, unsigned char *v)
{
    return 0;
}
int Get(CfgDB *db, unsigned char *k)
{
    return 0;
}
int Remove(CfgDB *db, unsigned char *k)
{
    return 0;
}
int Flush(CfgDB *db)
{
    return 0;
}
int Count(CfgDB *db)
{
    return 0;
}
//
//
//
DbIndex *NewDbIndex(
    time_t ts,
    unsigned char *key,
    size_t file_id,
    size_t value_pos)
{
    return NULL;
}