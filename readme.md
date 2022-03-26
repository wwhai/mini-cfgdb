# MINI 嵌入式配置数据库
计划实现个mini版本的 ROM 版 KV 数据库，用来保存设备的一些配置或者日志。利用 MCU 自带的ROM来存储数据。

## 原理
基于 LSM 模型实现，基于线性文件保存。理论基础来自 Riak 的 BitCask 论文。

## 设计
API：
 - Set(K,V)：保存键值对
 - Get(K) ：获取值
 - Flush()：清空数据
 - Remove(K)：删除某个Key
 - Dump()：导出数据
 - Count()：计算数据量
 - Version()：当前版本号
## Demo
### 文件模式
```c
#include <stdio.h>
#include "cfgdb.h"
int main(int argc, char const *argv[])
{
    CfgDb* db = NewFileDb(1024, MB, "./temp_db");
    Set(db, "K", "V");
    unsigned *char value =  Get(db, "K");
    Remove(db, "K");
    return 0;
}

```

### 内存模式
```c
#include <stdio.h>
#include "cfgdb.h"
int main(int argc, char const *argv[])
{
    CfgDb* db = NewMemoryDb(1024, MB);
    Set(db, "K", "V");
    unsigned *char value =  Get(db, "K");
    Remove(db, "K");
    return 0;
}

```
