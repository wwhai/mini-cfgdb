#include "cfgdb.h"
#include "hashmap.h"
Entry *NewEntry(Byte k[], Byte v[])
{
    Entry *e = new_object(Entry);
    e->key = k;
    e->value = v;
    e->key_size = strlen((char *)k);
    e->value_size = strlen((char *)v);
    return e;
}
Byte *EncodeEntry(Entry e)
{
    int size = (U32_SIZE * 2 + e.key_size + e.value_size);
    Byte *bin = (Byte *)malloc(size);
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
Entry DecodeEntry(Byte *bin)
{
    size_t offset = 0;
    size_t key_size = 0;
    size_t value_size = 0;
    offset += 0;
    memcpy(&key_size, bin + offset, U32_SIZE);
    offset += U32_SIZE;
    memcpy(&value_size, bin + offset, U32_SIZE);
    offset += key_size;
    Byte *key = (Byte *)malloc(sizeof(Byte) * key_size);
    memcpy(key, bin + offset, key_size);
    offset += value_size;
    Byte *value = (Byte *)malloc(sizeof(Byte) * value_size);
    memcpy(value, bin + offset, value_size);
    Entry e = {.key_size = key_size, .value_size = value_size, .key = key, .value = value};
    return e;
}
//
CfgDB *NewFileDB(int bucket_size, char path[])
{
    struct hashmap_s *map = new_object(struct hashmap_s);
    if (0 != hashmap_create(16, map))
    {
        printf("Unable to hashmap_create!");
        return NULL;
    }
    FILE *file = fopen(path, "wb");
    if (!file)
    {
        printf("Unable to open file!");
        return NULL;
    }
    CfgDB *db = new_object(CfgDB);
    db->offset = 0;
    db->bucket = (Byte *)malloc(bucket_size * sizeof(Byte));
    db->dbFile = file;
    db->map = map;
    return db;
}
int Set(CfgDB *db, Byte *k, Byte *v)
{
    Entry *e = NewEntry(k, v);
    Byte *bin = EncodeEntry(*e);
    // 时间戳
    time_t ts;
    time(&ts);
    // 更新索引
    DbIndex *index = NewDbIndex(ts, k, 0, db->offset);
    int x = 42;
    if (0 != hashmap_put(db->map, (char *)e->key, db->offset, &x))
    {
        printf("Unable to hashmap_put!");

        return 1;
    }
    // 写入数据
    fseek(db->dbFile, db->offset, SEEK_SET);
    fwrite(bin, (U32_SIZE * 2 + e->key_size + e->value_size), 1, db->dbFile);
    fseek(db->dbFile, 0, SEEK_END);
    // 更新位置
    db->offset = ftell(db->dbFile);
    return 0;
}
int Get(CfgDB *db, Byte *k)
{
    void *value = hashmap_get(db->map, (char *)k, (Uint32)strlen((char *)k));
    if (value != NULL)
    {
        printf("null\n");
    }
    size_t *pos = (size_t *)value;
    printf("POS:%zu\n", pos);
    return 0;
}
int Remove(CfgDB *db, Byte *k)
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
    Byte key[],
    size_t file_id,
    size_t value_pos)
{
    DbIndex *dbIndex = new_object(DbIndex);
    dbIndex->ts = ts;
    dbIndex->key = key;
    dbIndex->key_size = strlen((char *)key);
    dbIndex->file_id = file_id;
    dbIndex->value_pos = value_pos;
    return dbIndex;
}
//
void ToString(Entry e)
{
    printf("key: %s", e.key);
    printf(" value: %s", e.value);
    printf(" key_size: %zu", e.key_size);
    printf(" value_size: %zu\n", e.value_size);
}
void printBin(Byte *bin)
{
    printf("BIN: ");
    for (size_t i = 0; i < strlen((char *)bin); i++)
    {
        printf("%02X ", bin[i]);
    }
    printf("\n");
}