#include "cfgdb.h"

Entry NewEntry(unsigned char k[], unsigned char v[])
{
    Entry e = {
        .key = k,
        .value = v,
        .key_size = strlen(k),
        .value_size = strlen(v)};
    return e;
}
unsigned char *EncodeEntry(Entry e)
{
    unsigned char *bin = (unsigned char *)malloc(sizeof(U32_SIZE * 2 + e.key_size + e.value_size));
    int offset = 0;
    memcpy(bin + offset, &e.key_size, U32_SIZE);
    offset += U32_SIZE;
    memcpy(bin + offset, &e.value_size, U32_SIZE);
    offset += U32_SIZE;
    memcpy(bin + offset, e.key, e.key_size);
    offset += e.key_size;
    memcpy(bin + offset, e.value, e.value_size);
    return bin;
}
//
Entry DecodeEntry(unsigned char *bin)
{
    size_t offset = 0;
    size_t key_size = 0;
    size_t value_size = 0;
    offset += 0;
    memcpy(&key_size, bin + offset, U32_SIZE);
    offset += U32_SIZE;
    memcpy(&value_size, bin + offset, U32_SIZE);
    offset += key_size;
    unsigned char *key = (unsigned char *)malloc(sizeof(unsigned char) * key_size);
    memcpy(key, bin + offset, key_size);
    offset += value_size;
    unsigned char *value = (unsigned char *)malloc(sizeof(unsigned char) * value_size);
    memcpy(value, bin + offset, value_size);
    Entry e = {.key_size = key_size, .value_size = value_size, key : key, value : value};
    return e;
}
//
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
//
void ToString(Entry e)
{
    printf("key: %s", e.key);
    printf(" value: %s", e.value);
    printf(" key_size: %d", e.key_size);
    printf(" value_size: %d\n", e.value_size);
}