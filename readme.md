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

## 其他
本项目准备做成一个基于内存的框架，只需实现保存的接口即可随时实现保存在任何地方。