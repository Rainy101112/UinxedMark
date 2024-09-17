# 欢迎使用 UinxedMark ！

## UinxedMark又叫作UxMark，是RainySoft团队的Rainy101112基于ViudiraTech的Uinxed-Kernel编写的一个可以在裸机环境运行的CPU跑分工具

## 编译要求

1. 必须是Linux系统，例如Debian、Ubuntu等。
2. 必须安装好gcc、make、nasm和xorriso工具，如果需要测试，请安装qemu虚拟机。

## 编译指南

1. 将源码clone到本地。
2. 在已clone到本地的项目源码根目录内执行make命名，即可开始编译。
3. 编译后会生成两个文件：UxImage和Uinxed.iso，这两个文件分别为内核文件和带grub引导的镜像文件。
4. “make clean”清理所有中间文件及UxImage和镜像，“make run”即可通过qemu测试启动iso镜像。
