本文件适合 Windows11 x64 操作系统

这是一个开辟大约 1 M 的存储空间进行模拟文件系统。程序退出后可以保存文件系统的状态，下次运行程序会展示上一次的状态

开始在工作路径为根目录下

效果展示：
![alt text](image.png)
![alt text](image-1.png)
![alt text](image-2.png)
![alt text](image-3.png)
![alt text](image-4.png)
![alt text](image-5.png)

保存情况：
![alt text](image-6.png)
![alt text](image-7.png)

文件说明：
disk.exe、FS.exe 文件为对应 .hpp 文件对应的共享目标文件，可以链接使用

main.exe 为可执行文件

file.txt 为文件系统的初始结构

file.txt 为 /Documents/text.txt 的初始文件内容，选自 ChinaDaily