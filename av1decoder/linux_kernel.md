
-------------------------------------------------------------------------------------------------

# 主要有哪几种内核锁？Linux 内核的同步机制是什么？

自旋锁：spin_lock 忙等，中断中使用

信号量：semxxx down/up write/read

mutex：初始化为1的信号量

读写锁，RCU(read-copy update)

# Linux 中的用户模式和内核模式是什么含义？

cpu mode，用户模式只能通过系统调用操作硬件资源，内核模式可以直接操作硬件资源

# 怎么申请大块内存？vmalloc 和 kmalloc 有什么区别？

vmalloc 用于申请大块内存，虚拟地址连续，物理地址不一定连续，不能直接用于DMA，在进程地址空间有专门的一块。

kmalloc 用于申请小内存，由 slab 管理实现，一般至少小于4KB（page）。不能申请大于128K的数据。物理地址和虚拟地址都连续，可用于DMA操作。

# 进程间通信主要有哪几种方式？

管道：两个进程需要有共同的祖先，pipe/popen

命名管道：两个进程可以无关

信号

消息队列

共享内存

信号量

套接字

Android：binder/ashmem

# 伙伴系统申请内存的函数有哪些？

alloc_page(gfp_mask, order)

__get_free_pages(gfp_mask, order)

# 通过 slab 分配器申请内存的函数有哪些？

自己构造对象：kmem_cache_create/kmem_cache_alloc

普通匿名内存申请：kmalloc

# Linux 的内核空间和用户空间如何划分的？进程地址空间布局图？

32位可配置3G/1G, 2G/2G，一般是两级页表

64位可配置几级页表，一般可选3级/4级页表，256G/256G，或512T/512T

# vmalloc() 申请内存有什么特点？

申请大块内存，虚拟地址连续，物理地址不一定连续，不能直接用于DMA。对于释放函数 vfree()。

# 用户程序使用 malloc() 申请的内存空间在什么范围？

stack 和 heap 中间。小于128M的通过brk申请，大于的通过 mmap 申请。

在支持并使能 MMU 的系统中，Linux 内核和用于程序分别运行在物理地址模式还是虚拟地址模式？
都运行在虚拟地址模式，页表转换对应由硬件单元MMU完成。

# ARM 处理器是通过几级页表进行存储空间映射的？

两级页表，PGD和PTE

# Linux 是通过什么组件来实现支持多种文件系统的？

VFS(virtual file system)

# Linux虚拟文件系统的关键数据结构有哪些？（至少写出4个）

super_block超级块

inode索引节点

dentry目录项

file文件

# 对文件系统的操作函数保存在哪个数据结构中？

struct file_operations

# Linux 中的文件包括哪些？

普通文件，目录文件，链接文件，设备文件，管道文件，套接字文件

# 创建进程的系统调用有哪些？

clone, fork, vfork

# 调用 schedule() 进行进程切换的方式有几种？

do_fork/do_timer/wake_up_process/setscheduler/sys_sched_yield

# Linux 调度程序是根据进程的动态优先级还是静态优先级来调度进程的？

cfs 会计算虚拟时间，还有一个计算出来的优先级。

实时进程根据xx

# 进程调度的核心数据结构是哪个？

struct runqueue

# 如何加载、卸载一个模块？

ismod, rmmod

# 模块和应用程序分别运行在什么空间？

模块运行在内核空间，应用程序运行在用户空间

# Linux 中的浮点运算由应用程序实现还是内核实现？

由应用程序实现，对应的数学库函数。

# 模块程序能否使用可链接的库函数？

module 运行在内核空间，不能链接库函数。

TLB 中缓存的是什么内容
translation lookaside buffer, 也叫快表，用作页表缓冲。记录虚拟地址和物理地址的对应关系，用于加快地址转换。

# Linux 中有哪几种设备？

字符设备和块设备 网络设备

# 字符设备驱动程序的关键数据结构是哪个？

struct cdev: kobject

cdev_alloc()

cdev_add()

# 设备驱动程序包括哪些功能函数？

open/read/write/ioctl/release/llseek

# 如何唯一标识一个设备？

主设备号和次设备号。dev_t，12位表示主设备号，20位表示次设备号。

MKDEV(int major, int minor)用于生产一个 dev_t 类型的对象。

# Linux 通过什么方式实现系统调用？

软件中断。系统调用编号，异常处理程序

# Linux 软中断和工作队列的作用是什么？

软中断：不可睡眠阻塞，处于中断上下文，不能进程切换，不能被自己打断。

工作队列：处理进程上下文中，可以睡眠阻塞。

