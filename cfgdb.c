#include "cfgdb.h"
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

    CfgDB *db = new_object(CfgDB);
    db->offset = 0;
    db->bucket = (DbIndex *)malloc(bucket_size * sizeof(DbIndex));
    db->db_path = path;
    db->bucket_size = bucket_size;
    printf("DbFile: %s\n", path);
    printf("Bucket Size: %lu\n", bucket_size * sizeof(DbIndex));
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
    DbIndex *index = NewDbIndex(ts, k, v, 0, db->offset);
    db->bucket[hash(db->bucket_size, (char *)k)] = *index;
    // 写入数据
    FILE *file = fopen(db->db_path, "wb");
    if (!file)
    {
        printf("Unable to open file!");
        return 1;
    }
    fseek(file, db->offset, SEEK_SET);
    fwrite(bin, (U32_SIZE * 2 + e->key_size + e->value_size), 1, file);
    // 更新位置
    db->offset = ftell(file);
    fflush(file);
    fclose(file);
    return 0;
}
int Get(CfgDB *db, Byte *k)
{
    DbIndex index = db->bucket[hash(db->bucket_size, (char *)k)];
    printf("DbIndex ==> key: %s", index.key);
    printf(" ts: %ld", index.ts);
    printf(" key_size: %ld", index.key_size);
    printf(" value_size: %ld", index.value_size);
    printf(" value_pos: %ld\n", index.value_pos);
    //

    // FILE *file = fopen(db->db_path, "rb+");
    // if (!file)
    // {
    //     printf("Unable to open file!");
    //     return 1;
    // }
    // size_t data_size = index.key_size + index.value_size + 8;
    // unsigned char *bin = new_objects(unsigned char, data_size);
    // fseek(file, 0, SEEK_SET);
    // fread(bin, 1, 20, file);
    // PrintBin(bin, data_size);
    // fclose(file);
    // printf("Entry ==> key: %s", entry->key);
    // printf(" value: %s", entry->value);
    // printf(" ts: %ld", entry->ts);
    // printf(" key_size: %ld", entry->ts);
    // printf(" value_size: %ld\n", entry->value_size);
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
    Byte value[],
    size_t file_id,
    size_t value_pos)
{
    DbIndex *dbIndex = new_object(DbIndex);
    dbIndex->ts = ts;
    dbIndex->key = key;
    dbIndex->key_size = strlen((char *)key);
    dbIndex->value_size = strlen((char *)value);
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
void PrintBin(Byte *bin, size_t size)
{
    printf("BIN: ");
    for (size_t i = 0; i < size; i++)
    {
        printf("%02X ", bin[i]);
    }
    printf("\n");
}

unsigned long hash(unsigned long CAPACITY, char *s)
{
    unsigned long i = 0;
    for (int j = 0; s[j]; j++)
        i += s[j];
    // printf("%s :  %lu\n", s, i % CAPACITY);
    return i % CAPACITY;
}
