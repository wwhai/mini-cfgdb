#ifndef cfgdb_h
#define cfgdb_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "hashmap.h"

#define U8_SIZE sizeof(Byte)
#define U16_SIZE sizeof(unsigned double)
#define U32_SIZE sizeof(unsigned int)
#define U64_SIZE sizeof(unsigned long)
// Object size
#define object_size(O, T) sizeof(O) / sizeof(T)
#define type_size(O) sizeof(O)
// New
#define new_object(T) (T *)malloc(sizeof(T))
#define new_objects(T, N) (T *)malloc(N * sizeof(T))
// byte
typedef unsigned char Byte;
// uint8
typedef Byte Uint8;
// uint16
typedef unsigned short Uint16;
// uint32
typedef unsigned int Uint32;
// uint64
typedef unsigned long Uint64;
// Index
typedef struct
{
    time_t ts;
    Byte *key;
    size_t file_id;
    size_t key_size;
    size_t value_size;
    size_t value_pos;
} DbIndex;

// Db
typedef struct
{
    unsigned int offset; // Offset
    DbIndex *bucket;     // Index
    size_t bucket_size;
    char *db_path; // Db file
} CfgDB;
//
CfgDB *NewFileDB(int bucket_size, char path[]);
CfgDB *NewMemoryDB(int bucket_size);
int Set(CfgDB *db, Byte *k, Byte *v);
int Get(CfgDB *db, Byte *k);
int Remove(CfgDB *db, Byte *k);
int Flush(CfgDB *db);
int Count(CfgDB *db);
Byte *Version();
DbIndex *NewDbIndex(
    time_t ts,
    Byte key[],
    Byte value[],
    size_t file_id,
    size_t value_pos);
// Data Entry
typedef struct
{
    size_t crc;
    time_t ts;
    size_t key_size;
    size_t value_size;
    Byte *key;
    Byte *value;
} Entry;

Entry *NewEntry(Byte k[], Byte v[]);
Byte *EncodeEntry(Entry e);
Entry DecodeEntry(Byte *bin);
void ToString(Entry e);
void PrintBin(Byte *bin, size_t size);
unsigned long hash(unsigned long CAPACITY, char *s);
#endif