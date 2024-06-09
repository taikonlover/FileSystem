#pragma once
#include "data.hpp"

class superblock
{
public:
    int block_sum; // 盘块的数量
    int inode_sum; // 索引节点的数量
    superblock();
};

class FAT
{
public:
    int next[BLOCK_SUM]; // 链表法
    FAT();
};

class bitmap
{
public:
    char map[BLOCK_SUM / 8]; // 位示图
    bool empty(int no);      // 判断磁盘块是否分配
    void set(int);           // 将磁盘块置为已分配
    void free(int);          // 回收磁盘块
    bitmap();                // 初始化，全部为未分配
    int get();               // 申请一个磁盘块，成功则返回磁盘块号，否则返回 -1
};

class inodemap
{
public:
    char map[INODE_SUM / 8];
    bool empty(int no); // 返回当前节点是否为空
    void set(int);
    void free(int);
    inodemap(); // 初始化位示图
    int get();
};

class inode
{
public:
    int firstblock; // 第一个盘块号
    int type;       // 文件类型
};

class entry
{
public:
    bool flag;      // 目录项是否有效
    char name[123]; // 文件名
    int node;       // 索引节点号
    entry();
};

union block // 磁盘块，有两种组织形式，普通文件目录的形式
{
public:
    char data[BLOCK_SIZE];
    entry entries[8];
    block();
};

class disk
{
public:
    superblock super;
    FAT fat;
    bitmap bm;
    inodemap im;
    inode inodes[INODE_SUM];
    inode root;
    block blocks[BLOCK_SUM];
    disk();
};