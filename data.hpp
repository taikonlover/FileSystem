#pragma once
#define BLOCK_SIZE 512      // 磁盘块大小 512 B
#define ENTRIES_PER_BLOCK 4 // 每个磁盘块最多 4 个目录项
#define BLOCK_SUM 2048      // 磁盘块数
#define INODE_SUM 2048      // 索引节点数
#define DIRSTY 0            // 目录
#define FILESTY 1           // 普通文件
#define READ 1              // 读权限
#define WRITE 2             // 写权限