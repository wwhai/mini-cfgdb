#ifndef cfgdb_h
#define cfgdb_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define U8_SIZE sizeof(unsigned char)
#define U16_SIZE sizeof(unsigned double)
#define U32_SIZE sizeof(unsigned int)
#define U64_SIZE sizeof(unsigned long)
// Db
typedef struct
{
    unsigned int offset;   // Offset
    unsigned char *bucket; // Data Bucket

} CfgDB;
//
CfgDB *NewCfgDB(int bucket_size);
int Set(CfgDB *db, unsigned char *k, unsigned char *v);
int Get(CfgDB *db, unsigned char *k);
int Remove(CfgDB *db, unsigned char *k);
int Flush(CfgDB *db);
int Count(CfgDB *db);
unsigned char *Version();
// Index
typedef struct
{
    time_t ts;
    unsigned char *key;
    size_t file_id;
    size_t value_pos;
} DbIndex;
DbIndex *NewDbIndex(
    time_t ts,
    unsigned char *key,
    size_t file_id,
    size_t value_pos);
// Data Entry
typedef struct
{
    size_t crc;
    time_t ts;
    size_t key_size;
    size_t value_size;
    unsigned char *key;
    unsigned char *value;
} Entry;

Entry NewEntry(unsigned char k[], unsigned char v[]);
unsigned char *EncodeEntry(Entry e);
Entry DecodeEntry(unsigned char *bin);
void ToString(Entry e);
#endif