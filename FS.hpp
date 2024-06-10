#pragma once
#include <string>
#include "disk.hpp"
using std::string;

union Buf // 缓存区，主要用于将目录、文件放到缓冲区处理
{
    entry entries[4096];
    char data[524288];
    block blocks[512];
    Buf();
};

class Filebuf // 读文件工作区，保存已经打开的文件及权限
{
public:
    bool flag = false;
    inode fnode;
    char mod = 0;
    char name[123];
    int fafblock; // 父目录的第一个盘块
};

class FS
{
    disk *diskptr;                          // 管理的虚拟磁盘
    char *filepath;                         // 虚拟磁盘保存的位置
    Buf wdir;                               // 工作目录
    Buf wfile;                              // 文件操作缓冲区
    Filebuf wprt[10];                       // 读写指针
    int cur_blockid = 0;                    // 当前工作目录下的第一个盘块
    int cur_inode = -1;                     // 当前工作目录下的索引节点
    void loadbuf(int firstblock, Buf &buf); // 载入缓冲区，可以执行工作目录和文件操作缓冲区的加载
    void writebackdir(int firstblock);      // 写回目录，常常在切换工作目录时写回
    void writebackfile(int firstblock);     // 写回文件，完成写文件后写回
    void delfile(int firstblock);           // 删除文件，包括目录和普通文件

    /*------------------ 原子操作(只允许在当前目录下操作) --------------------------------------*/
    int cd(const char *);      // 切换目录，原子操作，返回 1 表示没有该目录
    void create(const char *); // 创建文件
    void rmdir(const char *);  // 删除文件
    void mkdir(const char *);  // 创建目录
    void ls();                 // 列出当前目录下的文件和文件夹

    string getfolerpath(string);
    string getfilename(string);

public:
    string workpath;
    FS(char *file); // 对磁盘格式化，或导入已有的磁盘文件
    ~FS();          // 写回磁盘并保存

    /*------------------ 原子操作(只允许在当前目录下操作) --------------------------------------*/
    int open(const char *, char mod); // 返回一个 wptr，只能打开当前目录的文件
    void write(int, const char *);    // 写文件，第一个参数为写指针，第二个参数为写的内容
    void close(int);                  // 关闭文件
    void read(int);                   // 读文件，参数为读指针
    void rm(int);                     // 删除文件，需要先打开文件才能删除

    /*--------------------- 允许任何在路径下操作(只有changedir 会改变工作路径)------------------------------*/
    int changedir(const char *);                // 切换工作目录
    void createfile(const char *);              // 创建文件，参数为文件路径
    void removedir(const char *);               // 删除文件夹，参数为文件夹路径
    void list(const char *);                    // 列出指定目录下的文件和文件夹
    void makedir(const char *);                 // 创建文件夹，参数为文件夹路径
    int openfile(const char *, char);           // 打开指定文件，第二个参数为读写权限，返回读写指针
    void writefile(const char *, const char *); // 写文件，第一个参数为文件路径，第二个为写入内容
    void readfile(const char *);                // 读文件
    void removefile(const char *);              // 删除文件
};