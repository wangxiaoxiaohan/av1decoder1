工具：

1.valgrind ：内存占用太多

2.gdb

3.address sanitizer

​    用来查堆内存的分配释放很好用

4.strace 追踪系统调用

5.perf 工具

6.bootchart 开机

可分析cpu/内存/io等信息

使用举例：分析系统开一段时间内个方面资源占用，找出影响开机时间的瓶颈

命令：

7. pmap 查看堆内存分布

  使用例子：发现surface内存占用比实际值多，通过pmap查看到相关的的内存块都是1024字节大小，从而发现问题，厂商代码使用了1M的page



