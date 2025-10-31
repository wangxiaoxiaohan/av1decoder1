# linux 系统目录

## /sys

Linux 的 `sysfs` 是内核通过虚拟文件系统暴露内核对象（kobject）、设备拓扑、驱动、总线、模块、参数以及运行时状态的统一入口。它以目录、属性文件和符号链接的形式呈现，支持用户空间通过读写文件实现查询和配置。

- 结构特征：每个目录代表一个内核对象（设备、驱动、总线等），常见属性包括 `uevent`、`subsystem`、`device`、`driver`、`power` 等；大量使用符号链接把“物理设备”与“逻辑类别/总线/驱动”关联起来。
- 与 udev 的关系：udev 通过监听 `uevent` 并结合 `sysfs` 属性生成 `/dev` 节点、命名与权限策略。
- 与设备树/ACPI 的关系：平台设备在启动时由设备树（ARM）或 ACPI/PCI（x86）枚举并创建到 `/sys/devices`，随后被绑定到 `/sys/bus/*/drivers/*`。
- 操作方式：读属性即查询状态；向属性写入完成配置（如绑定/解绑驱动、设置队列参数、切换电源状态）。

### /sys/devices（物理设备拓扑）

`/sys/devices` 展示系统中“物理设备”层次结构，是设备真正的宿主目录。常见子目录：

- `/sys/devices/system/*`：CPU、内存、时钟源、L2/L3 cache、机器级设备（如 `cpu/`、`mem/`）。
- `/sys/devices/platform/*`：平台设备（通过设备树/ACPI注册），如 `soc@.../` 下的 `i2c@*`、`spi@*`、`uart@*`、`mmc@*`、`gpu@*`、`vcodec@*` 等。
- `/sys/devices/pci*/*`：PCI/PCIe 总线枚举的设备（例如 `0000:01:00.0`）。
- 每个设备目录下常见文件/链接：
  - `uevent`：内核向 udev 发送的设备事件；
  - `subsystem`（符号链接）：指向所属总线，如 `.../bus/i2c`；
  - `driver`（符号链接）：绑定的驱动；`/sys/devices/.../driver` → `/sys/bus/*/drivers/<drv>`；
  - `power/*`：电源管理属性（runtime PM）；
  - `modalias`：用于自动匹配驱动的别名；
  - `of_node`（ARM）/`firmware_node`（x86）：对应设备树或 ACPI 节点；
  - `dev`：字符/块设备的主次号（如 `8:0`）。

示例：摄像头传感器（I2C 子设备）会出现在 `/sys/devices/platform/soc@.../i2c@*/<sensor>@<addr>/`，并通过符号链接出现在 `/sys/class/video4linux/*`。

#### 驱动如何在 /sys/devices 生成条目

驱动并不直接“创建” `/sys/devices` 下的目录；当设备被总线枚举（PCI/USB）或由平台层注册（设备树/ACPI/平台设备），并绑定到相应驱动后，内核会为该 `struct device` 在 `/sys/devices/...` 自动生成目录与属性。驱动可在 `probe()` 期间通过 `device_create_file()` 或 `sysfs_create_group()` 为该设备追加属性，从而出现在设备目录下。

- 典型来源：
  - 平台设备（设备树/ACPI）→ `/sys/devices/platform/...` 或 `/sys/devices/.../soc@.../*`。
  - I2C 设备（`i2c_client`）→ `/sys/devices/.../i2c@*/<name>@<addr>/`。
  - SPI 设备（`spi_device`）→ `/sys/devices/.../spi@*/<name>.<cs>/`。
  - PCI/USB 设备由硬件枚举产生，位于 `/sys/devices/pci...` 或 `/sys/devices/pci.../usb...`。

— 关键点：属性应挂在设备对象的 `kobj` 上（如 `&pdev->dev.kobj`、`&client->dev.kobj`），而不是随意新建顶层 kobject，保持对象模型一致。

示例一：Platform Driver（设备树匹配），在设备目录下添加 `foo` 属性

```c
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/io.h>

static const struct of_device_id mydev_dt_ids[] = {
    { .compatible = "myvendor,mydev" },
    { }
};
MODULE_DEVICE_TABLE(of, mydev_dt_ids);

static void __iomem *base;

static ssize_t foo_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    /* 例如读取寄存器某字段 */
    u32 reg = readl(base);
    return scnprintf(buf, PAGE_SIZE, "%u\n", reg & 0xff);
}

static ssize_t foo_store(struct device *dev, struct device_attribute *attr,
                         const char *buf, size_t count)
{
    unsigned long v;
    if (!kstrtoul(buf, 0, &v)) {
        u32 reg = readl(base);
        reg = (reg & ~0xff) | (v & 0xff);
        writel(reg, base);
    }
    return count;
}

static DEVICE_ATTR_RW(foo);

static int mydev_probe(struct platform_device *pdev)
{
    struct resource *res;
    int ret;

    res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
    base = devm_ioremap_resource(&pdev->dev, res);
    if (IS_ERR(base))
        return PTR_ERR(base);

    ret = device_create_file(&pdev->dev, &dev_attr_foo);
    if (ret)
        return ret;
    dev_info(&pdev->dev, "mydev probed, foo attr ready\n");
    return 0;
}

static int mydev_remove(struct platform_device *pdev)
{
    device_remove_file(&pdev->dev, &dev_attr_foo);
    return 0;
}

static struct platform_driver mydev_driver = {
    .probe  = mydev_probe,
    .remove = mydev_remove,
    .driver = {
        .name = "mydev",
        .of_match_table = mydev_dt_ids,
    },
};

module_platform_driver(mydev_driver);
MODULE_LICENSE("GPL");
```

- 设备树节点（简化示例）会在 `/sys/firmware/devicetree/base/...` 显示，匹配后在 `/sys/devices/platform/.../` 或 `.../soc@.../` 下生成设备目录，属性 `foo` 随之出现。

示例二：I2C Client Driver，在 I2C 设备目录下添加 `gain` 属性

```c
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/of.h>

static const struct i2c_device_id my_sensor_id[] = {
    { "my-sensor", 0 },
    { }
};
MODULE_DEVICE_TABLE(i2c, my_sensor_id);

static const struct of_device_id my_sensor_dt_ids[] = {
    { .compatible = "myvendor,my-sensor" },
    { }
};
MODULE_DEVICE_TABLE(of, my_sensor_dt_ids);

static int gain;

static ssize_t gain_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return scnprintf(buf, PAGE_SIZE, "%d\n", gain);
}

static ssize_t gain_store(struct device *dev, struct device_attribute *attr,
                          const char *buf, size_t count)
{
    int v;
    if (!kstrtoint(buf, 0, &v))
        gain = v; /* 此处可同步到传感器寄存器 */
    return count;
}

static DEVICE_ATTR_RW(gain);

static int my_sensor_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
    int ret = device_create_file(&client->dev, &dev_attr_gain);
    if (ret)
        return ret;
    dev_info(&client->dev, "sensor probed, gain attr ready\n");
    return 0;
}

static int my_sensor_remove(struct i2c_client *client)
{
    device_remove_file(&client->dev, &dev_attr_gain);
    return 0;
}

static struct i2c_driver my_sensor_driver = {
    .driver = {
        .name = "my-sensor",
        .of_match_table = my_sensor_dt_ids,
    },
    .probe    = my_sensor_probe,
    .remove   = my_sensor_remove,
    .id_table = my_sensor_id,
};

module_i2c_driver(my_sensor_driver);
MODULE_LICENSE("GPL");
```

- 匹配成功后设备目录通常为 `/sys/devices/platform/soc@.../i2c@*/<compatible>@<addr>/`，属性 `gain` 会出现在该目录下，同时出现在 `/sys/class/video4linux/videoX/device` 的跳转目标设备目录（若集成到 V4L2）。

示例三：SPI Driver，添加 `mode` 属性（简化）

```c
#include <linux/module.h>
#include <linux/spi/spi.h>
#include <linux/of.h>

static const struct of_device_id my_spi_dt_ids[] = {
    { .compatible = "myvendor,my-spi-dev" },
    { }
};
MODULE_DEVICE_TABLE(of, my_spi_dt_ids);

static int mode = SPI_MODE_0;

static ssize_t mode_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return scnprintf(buf, PAGE_SIZE, "%d\n", mode);
}
static ssize_t mode_store(struct device *dev, struct device_attribute *attr,
                          const char *buf, size_t count)
{
    int v;
    if (!kstrtoint(buf, 0, &v))
        mode = v; /* 实际应用中需调用 spi_setup() 等更新硬件 */
    return count;
}
static DEVICE_ATTR_RW(mode);

static int my_spi_probe(struct spi_device *spi)
{
    int ret = device_create_file(&spi->dev, &dev_attr_mode);
    if (ret)
        return ret;
    dev_info(&spi->dev, "spi dev probed, mode attr ready\n");
    return 0;
}

static int my_spi_remove(struct spi_device *spi)
{
    device_remove_file(&spi->dev, &dev_attr_mode);
    return 0;
}

static struct spi_driver my_spi_driver = {
    .driver = {
        .name = "my-spi-dev",
        .of_match_table = my_spi_dt_ids,
    },
    .probe  = my_spi_probe,
    .remove = my_spi_remove,
};

module_spi_driver(my_spi_driver);
MODULE_LICENSE("GPL");
```

— 联动提示：

- 绑定/解绑驱动可通过 `/sys/bus/<bus>/drivers/<drv>/{bind,unbind}` 完成（例如 PCI：`echo 0000:01:00.0 > .../bind`）。
- 设备目录常见链接：`driver`（到 `/sys/bus/*/drivers/<drv>`）、`subsystem`（到 `/sys/bus/<bus>`）、`power/*`（runtime PM）。
- `modalias` 可用于自动装载合适驱动（`udev`/`modprobe`）。

### /sys/class（逻辑设备类别）

`/sys/class` 将设备按“功能类别”组织，便于用户空间以统一接口访问。例如：

- `net/`：网络接口（`eth0`、`wlan0`、`lo`）。
- `tty/`：串口/终端设备（`ttyS*`、`ttyUSB*`、`ttyAMA*`）。
- `video4linux/`：V4L2 设备（`video0`、`vbi0`、`radio0`）。
- `input/`：输入设备（键盘、触摸屏等）。
- `graphics/`：DRM/FB 图形设备。
- `gpio/`、`power_supply/`、`leds/` 等。

类别目录下的每个条目通常是一个指向 `/sys/devices/...` 的符号链接，同时提供类别特定的属性：

- `net/<iface>/statistics/*`：网络统计；`mtu`、`carrier`、`operstate` 等。
- `video4linux/videoX/device` → 指向物理设备；`name`、`index`、`dev`。
- `leds/<name>/brightness`：设置亮度；`trigger` 选择事件触发源。

#### 驱动如何在 /sys/class 创建条目

驱动可通过内核的 `class` 与 `device` API 在 `/sys/class/<class>/<device>` 下创建条目，并结合 udev 自动创建 `/dev/<node>`。常见步骤：

- 分配设备号并注册字符设备（若需要 `/dev` 节点）：`alloc_chrdev_region`、`cdev_init`、`cdev_add`。
- 创建类对象：`class_create(THIS_MODULE, "<class>")`，在 `/sys/class/<class>/` 生成目录。
- 创建设备实例：`device_create(class, parent, devt, drvdata, "<name>")`，在 `/sys/class/<class>/<name>` 生成条目，并通过 `uevent` 通知 udev 创建 `/dev/<name>`（取决于发行版规则）。
- 导出设备属性：使用 `DEVICE_ATTR_*` 宏与 `device_create_file()` 或 `sysfs_create_group()` 在设备目录下添加可读写属性文件。
- 清理：`device_destroy`、`class_destroy`、`cdev_del`、`unregister_chrdev_region`。

注意：很多子系统（如 `video4linux`、`net`、`input`）不需要驱动手工创建类别目录，它们在注册设备时由核心框架自动把设备呈现在对应的类中。手工创建类通常用于自定义的字符设备或不属于既有子系统的轻量接口。

示例：最小字符设备，创建 `/sys/class/myclass/mydev0` 与 `/dev/mydev0`，并暴露一个 `value` 属性。

```c
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>

static struct class *my_class;
static dev_t devt;
static struct cdev my_cdev;
static struct device *my_device;
static int value;

static ssize_t value_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return scnprintf(buf, PAGE_SIZE, "%d\n", value);
}

static ssize_t value_store(struct device *dev, struct device_attribute *attr,
                           const char *buf, size_t count)
{
    int v;
    if (!kstrtoint(buf, 0, &v))
        value = v;
    return count;
}

static DEVICE_ATTR_RW(value);

static int my_open(struct inode *inode, struct file *file) { return 0; }
static int my_release(struct inode *inode, struct file *file) { return 0; }
static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off) { return 0; }
static ssize_t my_write(struct file *f, const char __user *buf, size_t len, loff_t *off) { return len; }

static const struct file_operations fops = {
    .owner   = THIS_MODULE,
    .open    = my_open,
    .release = my_release,
    .read    = my_read,
    .write   = my_write,
};

static int __init my_init(void)
{
    int ret;

    ret = alloc_chrdev_region(&devt, 0, 1, "mychr");
    if (ret)
        return ret;

    cdev_init(&my_cdev, &fops);
    my_cdev.owner = THIS_MODULE;
    ret = cdev_add(&my_cdev, devt, 1);
    if (ret)
        goto unreg;

    my_class = class_create(THIS_MODULE, "myclass");
    if (IS_ERR(my_class)) {
        ret = PTR_ERR(my_class);
        goto del_cdev;
    }

    my_device = device_create(my_class, NULL, devt, NULL, "mydev0");
    if (IS_ERR(my_device)) {
        ret = PTR_ERR(my_device);
        goto destroy_class;
    }

    ret = device_create_file(my_device, &dev_attr_value);
    if (ret)
        goto destroy_device;

    return 0;

destroy_device:
    device_destroy(my_class, devt);
destroy_class:
    class_destroy(my_class);
del_cdev:
    cdev_del(&my_cdev);
unreg:
    unregister_chrdev_region(devt, 1);
    return ret;
}

static void __exit my_exit(void)
{
    device_remove_file(my_device, &dev_attr_value);
    device_destroy(my_class, devt);
    class_destroy(my_class);
    cdev_del(&my_cdev);
    unregister_chrdev_region(devt, 1);
}

module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL");
```

使用说明：

- 加载模块后将出现 `/sys/class/myclass/mydev0/` 与属性 `value`；多数发行版的 udev 会根据 `uevent` 自动创建 `/dev/mydev0`。
- 可以通过 `echo 123 > /sys/class/myclass/mydev0/value` 设置属性，通过 `cat` 读取。
- 若 udev 未创建 `/dev` 节点，可用 `mknod` 手动创建，主次号可在 `/sys/class/myclass/mydev0/dev` 或 `ls -l /dev/mydev0` 查看。

### /sys/block（块设备与队列）

`/sys/block` 展示所有块设备（`sda`、`mmcblk0`、`nvme0n1` 等），并提供 I/O 队列与分区信息：

- 设备目录结构：
  - `sda/queue/*`：队列参数，如 `nr_requests`、`rotational`、`read_ahead_kb`、`scheduler`；
  - `sda/stat`：I/O 统计；
  - `sda/holders`、`sda/slaves`：设备堆叠关系（LVM/DM/MD）；
  - `sda/sda1`：分区目录，含 `start`、`size`、`ro` 等属性。

常用操作示例：

- 查看调度器：`cat /sys/block/sda/queue/scheduler`；切换：`echo kyber > /sys/block/sda/queue/scheduler`。
- 预读设置：`echo 128 > /sys/block/sda/queue/read_ahead_kb`。

高级要点：

- 多队列（blk-mq）设备（如 NVMe）支持调度器：`none`（直通）、`mq-deadline`、`kyber`、`bfq`（桌面/交互友好）。
- `rotational` 指示旋转介质（HDD）与非旋转（SSD），影响合并与预读策略；现代驱动通常自动设置。
- 设备堆叠关系：
  - `holders` 表示被谁持有（如被 `dm-0` 卷持有）；
  - `slaves` 表示底层设备（如 RAID/DM 的物理磁盘）。

示例代码：最小块设备（RAM Disk 骨架，仅示意接口，不适合生产）

```c
#include <linux/module.h>
#include <linux/blkdev.h>
#include <linux/blk-mq.h>

#define MYBLK_SECTORS   (1024 * 1024) /* 512MB: 1024*1024*512B */

static struct gendisk *gd;
static struct request_queue *q;
static struct blk_mq_tag_set tag_set;
static u8 *data;

static blk_status_t my_queue_rq(struct blk_mq_hw_ctx *hctx, const struct blk_mq_queue_data *bd)
{
    struct request *rq = bd->rq;
    blk_status_t ret = BLK_STS_OK;

    blk_mq_start_request(rq);
    /* 简化：直接完成请求（实际驱动应遍历 bio，读写 data[]） */
    blk_mq_end_request(rq, ret);
    return ret;
}

static const struct blk_mq_ops mq_ops = {
    .queue_rq = my_queue_rq,
};

static int __init myblk_init(void)
{
    int ret;

    data = vzalloc((size_t)MYBLK_SECTORS * 512);
    if (!data)
        return -ENOMEM;

    memset(&tag_set, 0, sizeof(tag_set));
    tag_set.ops = &mq_ops;
    tag_set.nr_hw_queues = 1;
    tag_set.queue_depth = 128;
    tag_set.numa_node = NUMA_NO_NODE;
    tag_set.cmd_size = 0;
    tag_set.flags = BLK_MQ_F_SHOULD_MERGE;
    tag_set.driver_data = NULL;

    ret = blk_mq_alloc_tag_set(&tag_set);
    if (ret)
        goto free_data;

    q = blk_mq_init_sq_queue(&tag_set, &mq_ops, & (struct blk_mq_queue_data){0});
    if (IS_ERR(q)) {
        ret = PTR_ERR(q);
        goto free_tagset;
    }
    q->queuedata = NULL;

    gd = alloc_disk(1);
    if (!gd) {
        ret = -ENOMEM;
        goto cleanup_q;
    }
    gd->major = register_blkdev(0, "myblk");
    if (gd->major < 0) {
        ret = gd->major;
        goto put_disk_out;
    }
    gd->first_minor = 0;
    gd->fops = NULL; /* 现代块设备主要通过队列处理，不必设置 file_operations */
    gd->queue = q;
    snprintf(gd->disk_name, sizeof(gd->disk_name), "myblk0");
    set_capacity(gd, MYBLK_SECTORS);
    add_disk(gd);
    pr_info("myblk: added /sys/block/%s and /dev/%s\n", gd->disk_name, gd->disk_name);
    return 0;

put_disk_out:
    put_disk(gd);
cleanup_q:
    blk_cleanup_queue(q);
free_tagset:
    blk_mq_free_tag_set(&tag_set);
free_data:
    vfree(data);
    return ret;
}

static void __exit myblk_exit(void)
{
    del_gendisk(gd);
    unregister_blkdev(gd->major, "myblk");
    put_disk(gd);
    blk_cleanup_queue(q);
    blk_mq_free_tag_set(&tag_set);
    vfree(data);
}

module_init(myblk_init);
module_exit(myblk_exit);
MODULE_LICENSE("GPL");
```

说明：加载后会出现 `/sys/block/myblk0/` 与 `/dev/myblk0`，并生成基本的队列属性。真实驱动需实现 bio 处理与数据传输，以上仅用于理解接口与 sysfs 呈现关系。

### /sys/bus（总线与驱动）

`/sys/bus` 组织所有总线类型及其设备/驱动：

- 典型总线：`pci/`、`usb/`、`i2c/`、`spi/`、`sdio/`、`platform/`、`virtio/`。
- 每个总线目录下：
  - `devices/`：该总线上的设备（符号链接到 `/sys/devices/...`）。
  - `drivers/`：已注册驱动。支持手动绑定/解绑：
    - 绑定：`echo <device> > /sys/bus/<bus>/drivers/<drv>/bind`
    - 解绑：`echo <device> > /sys/bus/<bus>/drivers/<drv>/unbind`
    - `<device>` 通常是设备名或路径，如 `0000:01:00.0`（PCI）。

在问题定位中，`/sys/bus/*/devices/*` 与 `/sys/bus/*/drivers/*` 的交叉检查可以确认驱动是否成功绑定。

实例化/移除设备（用户态）

- I2C：
  
  - 实例化：`echo <name> <addr> > /sys/bus/i2c/devices/i2c-<N>/new_device`
  - 移除：`echo <addr> > /sys/bus/i2c/devices/i2c-<N>/delete_device`
  - 示例：`echo my-sensor 0x36 > /sys/bus/i2c/devices/i2c-1/new_device`
  - 前提：对应驱动支持 `<name>` 的 `of_device_id`/`i2c_device_id`

- SPI：
  
  - 某些系统支持在 `/sys/bus/spi/devices/spi<bus>.<cs>/` 下配置参数；或通过 `spidev` 暴露 `/dev/spidev<bus>.<cs>`。
  - 也可用设备树/ACPI 静态描述；运行时实例化方式依发行版与内核配置而不同。

- PCI/USB：主要由硬件枚举与热插拔产生设备；手工绑定/解绑通过 `drivers/<drv>/{bind,unbind}` 完成。

注意：用户态实例化机制适合测试/开发，不建议在产品环境中作为设备持久化来源；正式场景应使用 DT/ACPI 或内核注册 API。

### /sys/fs（文件系统相关）

`/sys/fs` 暴露各类文件系统的运行时接口与调优参数：

- `cgroup/`、`cgroup2/`：控制组的层级、限制与统计；
- `fuse/`：FUSE 相关；
- `ext4/`、`xfs/`、`btrfs/`：特定文件系统的调试/统计；
- `pstore/`：持久化存储（崩溃日志）；
- `bpf/`：BPF maps/programs（内核版本相关）。

注意：`/sys/kernel/debug` 属于 `debugfs` 挂载点（见下节），虽然路径在 `/sys/kernel`，但它是一个单独的虚拟文件系统，需要显式挂载。

挂载与操作示例：

- 挂载 `cgroup2`（现代系统）：
  
  - `mount -t cgroup2 none /sys/fs/cgroup`
  - 创建子层级并设置限制：在子目录写入 `memory.max`、`cpu.max` 等；进程通过 `cgroup.procs` 加入。

- 挂载 `debugfs`：
  
  - `mount -t debugfs debugfs /sys/kernel/debug`
  - 许多子系统在此处提供更详细调试接口（DRM/V4L2/PCI/USB 等）。

- 读取崩溃日志（pstore）：
  
  - `ls /sys/fs/pstore` 查看 `dmesg-ramoops-*`；结合内核 `pstore`/`ramoops` 配置。

驱动内导出 debugfs 属性（示例代码）：

```c
#include <linux/module.h>
#include <linux/debugfs.h>

static struct dentry *root;
static int value;

static ssize_t dbg_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
    char tmp[32];
    int n = scnprintf(tmp, sizeof(tmp), "%d\n", value);
    return simple_read_from_buffer(buf, len, off, tmp, n);
}
static ssize_t dbg_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
    char tmp[32];
    if (len >= sizeof(tmp))
        return -EINVAL;
    if (copy_from_user(tmp, buf, len))
        return -EFAULT;
    tmp[len] = '\0';
    kstrtoint(tmp, 0, &value);
    return len;
}
static const struct file_operations dbg_fops = {
    .owner = THIS_MODULE,
    .read  = dbg_read,
    .write = dbg_write,
    .llseek = no_llseek,
};

static int __init dbg_init(void)
{
    root = debugfs_create_dir("mydrv", NULL);
    if (!root)
        return -ENOMEM;
    debugfs_create_file("value", 0644, root, NULL, &dbg_fops);
    pr_info("debugfs: /sys/kernel/debug/mydrv/value ready\n");
    return 0;
}
static void __exit dbg_exit(void)
{
    debugfs_remove_recursive(root);
}
module_init(dbg_init);
module_exit(dbg_exit);
MODULE_LICENSE("GPL");
```

说明：挂载 `debugfs` 后可在 `/sys/kernel/debug/mydrv/value` 读写，用于轻量调试，不建议暴露安全/持久配置（生产环境请使用正规 sysfs 属性或专用子系统）。

### /sys/kernel（内核全局开关与调试入口）

包含内核范围的控制与状态：

- `mm/`：内存管理相关；
- `kexec_*`：kexec 功能；
- `irq/`、`msi/`：中断与消息信号；
- `debug/`：`debugfs` 的挂载点通常是 `/sys/kernel/debug`（需要 `mount -t debugfs debugfs /sys/kernel/debug`）。
- 某些发行版提供 `sched/`、`fscache/` 等内核子系统目录。

调试建议：启用 `debugfs` 后，DRM、V4L2、PCI、USB 等子系统会在 `debugfs` 下提供更详细的调试信息。

—— 进一步详细说明（configfs / debugfs / tracefs）

- configfs：通过挂载 `configfs`（常见在 `/sys/kernel/config`）创建/配置内核对象。例如 USB Gadget 可在 `usb_gadget/` 下创建设备、配置 Function/Configuration，然后通过 UDC 绑定生效。
- debugfs：便于驱动导出调试文件；需 `mount -t debugfs debugfs /sys/kernel/debug` 后使用。调试文件应避免承载安全/持久参数。
- tracefs/ftrace：位于 `/sys/kernel/tracing`；支持函数级追踪与事件追踪，典型文件：
  - `available_tracers`、`current_tracer` 选择追踪器（如 `function`、`function_graph`、`irqsoff` 等）；
  - `set_ftrace_filter` 指定函数白名单；`set_ftrace_notrace` 黑名单；
  - `events/*` 各子系统事件开关，如 `sched/sched_switch`、`irq/irq_handler_entry`、`block/block_rq_issue`；
  - `trace` 输出结果；`trace_pipe` 流式读取。

示例（函数追踪）：

- `echo function > /sys/kernel/tracing/current_tracer`
- `echo my_driver_func > /sys/kernel/tracing/set_ftrace_filter`
- `echo 1 > /sys/kernel/tracing/tracing_on`；读取：`cat /sys/kernel/tracing/trace`
- 停止与清空：`echo 0 > tracing_on`；`echo > trace`；关闭：`echo nop > current_tracer`

### /sys/firmware（固件与平台描述）

平台固件接口与机器描述：

- `devicetree/`：设备树（DT）原始节点镜像（只读），用于 ARM/ARM64 平台。可在此定位 `compatible`、资源映射等信息。
- `acpi/`：ACPI 表（DSDT/SSDT）与设备映射（x86 主流）。
- `efi/`：EFI 运行时接口与变量（UEFI 系统）。
- `dmi/`：桌面/服务器平台的 DMI（SMBIOS）。

典型用途：驱动调试时，可从 `devicetree` 或 `acpi` 中核对设备枚举与属性，确认设备是否被正确创建到 `/sys/devices`。

—— 进一步详细说明（设备树/ACPI 与固件加载）

- 设备树（DT）：在 `/sys/firmware/devicetree/base/...` 查看节点与属性（`compatible`、`reg`、`interrupts`、`clocks` 等），与设备目录下的 `of_node` 对应；用于确认资源是否匹配驱动期望。
- ACPI：在 `/sys/firmware/acpi/tables` 查看 AML 表，设备通常通过 `_HID`/`_CID` 与 `modalias` 匹配到驱动；
- DMI/EFI：在 `/sys/firmware/dmi/` 与 `/sys/firmware/efi/` 查看平台信息与变量（UEFI 环境）。

驱动加载固件：

- 通过 `request_firmware()` 触发用户空间提供固件（通常来自 `/lib/firmware`）；失败会在 `dmesg` 打印提示。
- 某些驱动在用户空间回退流程中，会通过 `/sys/class/firmware/` 暴露 `loading`/`data` 接口。

### /sys/module（内核模块）

列出所有已加载的内核模块：

- `<module>/parameters/*`：模块参数（可运行时读写，取决于导出权限）。
- `<module>/refcnt`：引用计数。
- `<module>/sections/*`：模块内存段信息（调试用）。
- `<module>/holders`、`<module>/notes`：依赖与额外元信息。

—— 进一步详细说明（参数与示例）

- 使用 `module_param()` 导出参数后，会在 `/sys/module/<mod>/parameters/<name>` 出现对应条目；权限位决定是否可写（例如 `0644`）。
- 写入示例：`echo 2 > /sys/module/mydrv/parameters/debug_level`，用于运行时调试；不建议承载安全/持久策略。
- 若模块无法卸载（引用计数不为 0），需确认是否仍有设备绑定或其它模块依赖（检查 `holders/` 与设备目录的 `driver` 链接）。

示例：调整 `uvcvideo`、`rkisp`、`snd_hda_intel` 等模块参数以影响设备行为。

### /sys/power（电源管理）

系统电源管理入口：

- `state`：系统睡眠目标（如 `freeze`、`mem`、`disk`），写入触发睡眠：`echo mem > /sys/power/state`。
- `mem_sleep`：选择内存睡眠类型（`s2idle`/`deep`）。
- `wake_lock`/`wake_unlock`（某些版本/安卓内核）：唤醒锁接口。
- `autosleep`、`pm_test`、`wakeup_count`：自动睡眠与调试辅助。

设备级别（runtime PM）在每个设备目录的 `power/*` 下，如 `control`（`auto`/`on`）与 `runtime_status`。

—— 进一步详细说明（系统休眠与设备 Runtime PM）

- 系统休眠：`echo mem > /sys/power/state` 触发 S2RAM；`mem_sleep` 选择 `s2idle`/`deep`（平台支持不同）。
- 设备 Runtime PM：
  - `.../power/control` 设为 `auto` 允许自动进出低功耗；`on` 保持常开；
  - `.../power/autosuspend_delay_ms` 设置进入休眠的延迟；
  - `.../power/wakeup` 控制是否作为唤醒源；`runtime_status` 查看当前状态。
- 排障：若设备无法休眠，检查活跃引用、未释放的 `clk`/`regulator`、中断活动；从 `pstore`/`dmesg` 采集恢复失败日志。

驱动侧接口：

- 使用 `pm_runtime_enable()`，在需要访问硬件前调用 `pm_runtime_get_sync()`，完成后 `pm_runtime_put()`；实现 `runtime_suspend`/`runtime_resume` 与系统 `suspend`/`resume` 钩子确保时序正确。

—— 补充：常见路径速查

- 设备真实目录：`/sys/devices/...`
- 按类别访问：`/sys/class/<class>/<name>` → 指向真实设备。
- 驱动与总线：`/sys/bus/<bus>/{devices,drivers}`。
- 块设备参数：`/sys/block/<dev>/queue/*`。
- 固件/平台描述：`/sys/firmware/{devicetree,acpi,efi,dmi}`。

### 其他常见 /sys 目录与用途

- `/sys/dev`：通过主次号快速定位设备的符号链接目录。
  
  - `char/<major>:<minor>` 和 `block/<major>:<minor>` → 指向真实设备目录（位于 `/sys/devices/...`）。
  - 典型用途：已知 `/dev` 节点的主次号，反查到设备的 sysfs 位置做进一步调试。

- `/sys/class/gpio`：传统 GPIO sysfs 接口（已在新内核中弃用，推荐用 `libgpiod` 与 `/dev/gpiochipN`）。
  
  - 旧用法示例（可能被禁用）：
    - `echo <N> > /sys/class/gpio/export`，随后到 `gpio<N>/` 设置 `direction` 与 `value`。
    - 回收：`echo <N> > /sys/class/gpio/unexport`。
  - 新方式：`gpiodetect`、`gpioinfo`、`gpioset` 等工具，或用户态用 `libgpiod` 访问 `/dev/gpiochip*`。

- `/sys/class/thermal`：热管理框架。
  
  - `thermal_zoneX/{type,temp,mode,trip_point_*}`：温度传感器与策略控制点。
  - `cooling_deviceX/*`：散热设备（风扇、限频单元）能力与绑定关系。
  - 常用于定位温度异常或限频来源（例如与 `devfreq`/`cpufreq` 联动）。

- `/sys/class/hwmon`：硬件监控（电压、电流、温度、风扇）。
  
  - 每个设备目录下有标准化的传感器属性：`temp1_input`（毫度）、`pwm1`、`in1_input` 等。
  - `name` 指示设备名或驱动名，便于脚本识别目标传感器。

- `/sys/class/drm`：DRM 显示框架。
  
  - `cardN/` 下列出连接器（`*-A-*`）、模式、热插拔状态，配合 `/sys/kernel/debug/dri/` 获取更详细调试数据。
  - 常见联动：`/sys/class/backlight/*` 控制背光，`/sys/kernel/debug/dri/0/` 查看 planes/crtcs/connectors 状态。

- `/sys/class/backlight`：显示背光控制。
  
  - `brightness` 与 `max_brightness`；部分面板支持 `bl_power`（省电模式）。

- `/sys/class/power_supply`：电源/电池/充电器状态。
  
  - 典型条目：`BAT0/`（容量、状态、电压/电流）、`AC/`、`USB/` 供电状态；便于电源管理与告警。

- `/sys/class/i2c-dev` 与 `/sys/bus/i2c`：用户态 I2C 设备与总线。
  
  - 加载 `i2c-dev` 模块后，生成 `/dev/i2c-*`；`/sys/class/i2c-dev/i2c-*` 映射到具体适配器。
  - 控制器与设备在 `/sys/bus/i2c/{devices,drivers}` 与 `/sys/devices/platform/.../i2c@*` 处查看。

- `/sys/class/spi_master` 与 `/sys/bus/spi`：SPI 控制器与设备。
  
  - 控制器在 `spi_master/spiX/`；用户态设备节点通常由 `spidev` 驱动生成（如 `/dev/spidevX.Y`）。
  - 设备绑定与属性在 `/sys/bus/spi/{devices,drivers}`。

- `/sys/class/firmware`：固件加载的用户空间回退接口。
  
  - 某些驱动在 `request_firmware()` 的用户空间回退路径中，会在此处创建 `device`，用户态可向 `data` 写入固件并在 `loading` 写入控制值（现代系统多使用静态固件目录与内核直接加载）。

- `/sys/class/rtc`：实时时钟（RTC）。
  
  - `rtc0/` 下的 `date`、`time`、`hctosys`、`wakealarm` 等，便于配置与定时唤醒。

- `/sys/class/regulator`：电源稳压器控制接口。
  
  - 每个稳压器目录含 `microvolts`、`min_microvolts`、`max_microvolts`、`enable`/`disable` 等；用于调试供电问题。

- `/sys/class/devfreq`：设备频率动态调整（GPU/内存总线等）。
  
  - `devfreq/<dev>/available_governors`、`cur_freq`、`target_freq`、`min_freq`、`max_freq`；与热管理/功耗策略联动。

- `/sys/devices/system/cpu`：CPU 拓扑与频率控制。
  
  - `cpu*/cpufreq`：`scaling_governor`、`scaling_max_freq`、`scaling_cur_freq`；
  - `online`：CPU 热插拔；`topology/`：NUMA/线程拓扑。

- `/sys/kernel/config`（configfs）：通过挂载 `configfs`（通常在该路径）进行内核对象的“配置创建”。
  
  - 常见用途：USB Gadget（`/sys/kernel/config/usb_gadget`）创建/组合虚拟 USB 设备；某些内核子系统用它做运行时配置。
  - 需要先挂载：`mount -t configfs none /sys/kernel/config`（依据发行版与权限）。

- `/sys/kernel/tracing`：ftrace 主入口（某些系统作为 `/sys/kernel/debug/tracing` 的替代/链接）。
  
  - 关键文件：`available_tracers`、`current_tracer`、`trace`、`events/*`；
  - 示例：`echo function > current_tracer`，然后读取 `trace` 获取函数调用栈（生产环境谨慎使用）。

- `/sys/hypervisor`：虚拟化相关信息（如 Xen 等环境）。
  
  - 指示当前系统是否运行在某些 hypervisor 下，并提供相关入口。

## /proc

`/proc` 是一个内核导出的“伪文件系统”，用于动态呈现系统与进程的运行时信息。与 `/sys` 更偏“对象模型 + 配置属性”不同，`/proc` 更倾向于“状态快照 + 内核统计”，许多调试、排障、性能分析都依赖这里的信息。

### 总览与特性

- 内容是内核实时生成的，不驻留磁盘；读取即得到当前状态，部分文件可写用于触发行为或调优。
- 结构分两大类：
  - 系统级目录/文件（如 `cpuinfo`、`meminfo`、`net/`、`modules`、`sys/`）。
  - 进程级目录（`/proc/<pid>`），每个运行的进程对应一个目录。
- 权限与可见性：部分文件需要 root 或具备相应的 `CAP_*` 能力；容器环境中视命名空间而定。

### /proc/<pid>（进程目录）

每个进程在 `/proc` 下有一个以 PID 命名的目录，常见条目：

- `cmdline`：进程的启动命令行（以 `\0` 分隔）。
- `environ`：进程环境变量（以 `\0` 分隔）。
- `exe`：指向可执行文件的符号链接。
- `cwd`/`root`：当前工作目录与进程视角的根目录符号链接。
- `fd/`：进程打开的文件描述符（每个数字条目指向具体文件/套接字/管道）。
- `maps`/`smaps`：内存映射区域与详细内存统计（RSS、PSS、Swap 等）。
- `status`：可读的状态摘要（Uid/Gid、线程数、内存、状态、capabilities）。
- `stat`：更细粒度的调度/时间字段（便于工具解析）。
- `io`：进程级 I/O 统计（读写字节数、syscr/syscr 等）。
- `sched`/`schedstat`：调度器相关统计与参数。
- `mounts`/`mountinfo`：进程视角的挂载点信息（受命名空间影响）。
- `cgroup`：进程所属的 cgroup 路径。
- `net/`：进程视角的网络信息（受网络命名空间影响）。

特殊目录：

- `/proc/self`：指向当前读取者进程自己的目录。
- `/proc/thread-self`：指向当前线程目录（便于线程级调试）。

### 系统信息文件（常用快查）

- `cpuinfo`：CPU 型号、核数、特性标志（`flags`/`Features`）、频率等。
- `meminfo`：系统内存概览（`MemTotal`、`MemFree`、`Buffers`、`Cached`、`Swap*`、`HugePages` 等）。
- `loadavg`：系统平均负载（1/5/15 分钟）及运行队列信息。
- `uptime`：系统运行时长与空闲时间累计。
- `version`：内核版本字符串（含编译器/构建信息）。
- `cmdline`：内核启动参数（与 bootloader 配置有关）。
- `filesystems`：内核支持的文件系统列表。
- `modules`：已加载内核模块列表与引用计数。
- `kallsyms`：内核符号表（需权限，调试用）。
- `config.gz`：内核配置（若启用 `IKCONFIG`，可 `zcat /proc/config.gz`）。
- `swaps`：交换分区/文件的当前使用情况。
- `partitions`：块设备分区表；`diskstats`：磁盘 I/O 统计。
- `mdstat`：MD/RAID 状态。

### 硬件/中断/映射

- `interrupts`：各中断线的计数与绑定 CPU；定位高频中断或不均衡中断分布。
- `irq/`：中断配置与调优接口（某些系统把更多信息放在 `/proc/irq/<n>/`）。
- `iomem`：物理内存映射区域（设备/驱动使用的 MMIO 范围）。
- `ioports`：I/O 端口占用情况（x86 常见）。
- `bus/`：各总线的辅助信息（历史上含 `pci/`，现代推荐从 `/sys/bus/*` 查看）。
- `driver/`：某些驱动的专用信息出口（例如 `driver/rtc`）。
- `dma`：DMA 通道分配（老式架构）。

### 存储/挂载/文件系统

- `mounts`（或 `self/mounts`）：当前（读者进程视角）所有挂载点；
  - 建议用 `mountinfo` 获取更完整的层叠/传播/命名空间信息。
- `filesystems`：支持的文件系统类型（内核已编译入或可模块加载）。
- `diskstats`/`partitions`：磁盘与分区统计与枚举；结合 `/sys/block` 做调优。
- `swaps`：交换空间使用情况与优先级。

### 网络（/proc/net）

- 典型条目：
  - `dev`：各网络接口的收发统计（类似 `ifconfig -s`）。
  - `tcp`/`udp`/`raw`：套接字状态表；`tcp6`/`udp6` 为 IPv6。
  - `sockstat`/`sockstat6`：套接字总体使用统计。
  - `netstat`：与 `ss`/`netstat` 类似的底层数据来源（发行版差异）。
  - `arp`、`route`、`fib_trie`：邻居条目与路由表概要。
  - `nf_conntrack`：连接跟踪表（需启用 netfilter/conntrack）。

容器与网络命名空间会影响 `/proc/net` 的可见数据；对特定进程可在 `/proc/<pid>/net` 查看其视角。

### 内存/VM 调试与统计

- `vmstat`：内存与虚拟内存统计；
- `zoneinfo`/`pagetypeinfo`/`buddyinfo`：分区/伙伴系统细节（内存碎片定位）。
- `slabinfo`：内核 slab 分配器统计（需 `slub_debug` 等选项更详细）。
- `kpagecount`/`kpageflags`：每页框计数与标志（低级分析）。
- `pressure/`：PSI（内存/CPU/IO 压力指标，现代内核提供）。
- `sysrq-trigger`：写入特定字符触发内核 SysRq（调试/救急，谨慎使用）。

### 调试/日志/核心

- `kmsg`：内核日志（`dmesg` 读取来源）；写入需权限。
- `kcore`：将内核内存暴露为 ELF core 文件（仅调试用途，读取需极高权限）。
- `sched_debug`：调度器状态与统计（若启用）。
- `timer_list`：定时器列表（启用后显示）。

### /proc/sys（sysctl 接口）

内核运行时参数的层级接口，常见子树：

- `kernel/`：如 `printk`、`panic`、`threads-max`、`random/*`、`sched_*`。
- `vm/`：如 `overcommit_memory`、`swappiness`、`dirty_*`、`transparent_hugepage/*`。
- `net/`：IPv4/IPv6、TCP/UDP、路由、过滤等（如 `ipv4/ip_forward`）。
- `fs/`：文件系统参数（如 `file-max`、`inode-*`）。
- `dev/`、`abi/`：设备与兼容性相关参数。

示例（谨慎修改，建议结合持久化策略如 `sysctl.conf` 或 drop-in 配置）：

- 开启 IPv4 转发：`echo 1 > /proc/sys/net/ipv4/ip_forward`
- 调整内存过量提交策略：`echo 1 > /proc/sys/vm/overcommit_memory`
- 释放页缓存（仅测试用）：`echo 3 > /proc/sys/vm/drop_caches`

### 设备树与固件（兼容接口）

- `/proc/device-tree`：在多数 ARM/ARM64 系统上是指向 `/sys/firmware/devicetree/base` 的兼容链接；只读用于查看 DT 属性。
- `/proc/acpi`：ACPI 信息（x86 常见，现代更多信息在 `/sys/firmware/acpi`）。

### cgroups 与容器

- `cgroups`：控制组控制器的启用与层级信息（cgroup v1/v2 显示差异）。
- `self/cgroup`：当前进程所处的 cgroup 路径。

### 常用排查示例

- 排查高负载来源：
  - 查看平均负载：`cat /proc/loadavg`；
  - 结合 `/proc/<pid>/sched`、`/proc/<pid>/stat`、`/proc/<pid>/io` 分析特定进程。
- 排查内存压力/碎片：
  - `cat /proc/meminfo`、`cat /proc/vmstat`；
  - 进一步看 `zoneinfo`、`buddyinfo`、`slabinfo` 定位碎片与热点 slab。
- 排查中断风暴或 NUMA 不均衡：
  - `cat /proc/interrupts`；检查各 IRQ 在 CPU 间分布，必要时调节 `smp_affinity`（在 `/proc/irq/<n>/smp_affinity` 或 `/proc/irq/<n>/`）。
- 排查 I/O 瓶颈：
  - `cat /proc/diskstats`；
  - 结合 `/sys/block/<dev>/queue/*` 调整调度器与预读。
- 排查网络连接暴涨：
  - `wc -l /proc/net/tcp`、`/proc/net/nf_conntrack`；
  - 结合 `sockstat` 查看套接字资源占用。

late_initcall 仅用于编译进内核的驱动，优先级低，在内核启动后期加载

在 linux 内核中有很多的申请资源类的API 函数都有对应的“devm_”前缀版本。比如 devm_request_irq 和 request_irq 这两个函数，这两个函数都是申请中断的，我们使用request_irq 函数申请中断的时候，如果驱动初始化失败的话就要调用 free_irq 函数对申请成功的irq进行释放，卸载驱动的时候也需要我们手动调用 free_irq 来释放 irq。假如我们的驱动里面申请了很多资源，比如：gpio、irq、input_dev，那么就需要添加很多 goto 语句对其做处理，当这样的标签多了以后代码看起来就不整洁了。“devm_”函数就是为了处理这种情况而诞生的，“devm_”函数最大的作用就是：使用“devm_”前缀的函数申请到的资源可以由系统自动释放，不需要我们手动处理。如果我们使用devm_request_threaded_irq 函数来申请中断，那么就不需要我们再调用 free_irq 函数对其进行释放。大家可以注意一下，带有“devm_”前缀的都是一些和设备资源管理有关的函数。

中断使用：注册中断函数，在中断函数里面读写寄存器，

申请中断的同时传入中断处理函数

# 香橙派 瑞芯微摄像头驱动链路

​**​Sensor → MIPI DPHY/CPHY → CSI-2 控制器 → VICAP → `sditf` 节点 → ISP​**？

[ov13850 sensor]
  ↓
  → ov13850_out2 → mipi_in_ucam0 → &csi2_dphy0
     ↓
     → csidphy0_out → mipi2_csi2_input → &mipi2_csi2
        ↓
        → mipi2_csi2_output → cif_mipi_in2 → &rkcif_mipi_lvds2
           ↓
           → mipi2_lvds_sditf → &rkcif_mipi_lvds2_sditf
              ↓
              → isp0_vir1 → &rkisp0_vir1

# V4L2 框架

v4l2-ctl：查询设备信息、设置参数的工具

V4L2 的架构分为三个主要层次：

- **用户空间**：应用程序通过 `ioctl` 系统调用与 V4L2 设备交互。

- **V4L2 核心层**：在内核中处理 API 请求，协调设备驱动与用户空间。

- **设备驱动层**：硬件设备的具体驱动实现（如 USB 摄像头、PCI 视频采集卡）

## V4L2 应用开发

V4L2：Video for Linux two，缩写 Video4Linux2，是 Linux 内核中的一个框架，提供了一套用于视频设备驱动程序开发的 API。

它是一个开放的、通用的、模块化的视频设备驱动程序框架，允许 Linux 操作系统和应用程序与各种视频设备（如摄像头、视频采集卡等）进行交互。

V4L2 提供了通用的 API，使应用程序能够访问和控制视频设备，包括获取设备信息、设置设备参数、采集视频数据、控制设备状态等。V4L2 还提供了一个统一的视频数据格式，允许应用程序在处理视频数据时无需考虑设备的具体格式。

V4L2 是 V4L 的改进版。V4L2 支持三种方式来采集图像：内存映射方式(mmap)、直接读取方式(read)和用户指针。内存映射的方式采集速度较快，一般用于连续视频数据的采集，实际工作中的应用多；直接读取的方式相对速度慢一些，常用于静态图片数据的采集；用户指针使用较少。

### V4L2 的主要特性

1. **模块化的架构：**V4L2 是一个模块化的架构，允许多个设备驱动程序同时存在并共享同一个 API。每个设备驱动程序都是一个独立的内核模块，可以在运行时加载和卸载。这种架构可以使开发人员更容易地开发新的视频设备驱动程序，并允许多个驱动程序同时使用相同的 API。

2. **统一的设备节点：**V4L2 提供了统一的设备节点，使应用程序可以使用相同的方式访问不同类型的视频设备。这种节点通常是 /dev/videoX，其中 X 是一个数字，表示设备的编号。应用程序可以通过打开这个节点来访问设备，并使用 V4L2 API 进行数据采集和控制。

3. **统一的视频数据格式：**V4L2 提供了一个统一的视频数据格式，称为 V4L2_PIX_FMT，允许应用程序在处理视频数据时无需考虑设备的具体格式。V4L2_PIX_FMT 包括了许多常见的视频格式，如 RGB、YUV 等。应用程序可以使用 V4L2 API 来查询设备支持的数据格式，并选择适当的格式进行数据采集和处理。

4. **支持多种视频设备：**V4L2 支持许多不同类型的视频设备，包括摄像头、视频采集卡、TV 卡等。每个设备都有自己的驱动程序，提供了相应的 V4L2 API。这些驱动程序可以根据设备的不同特性，提供不同的采集模式、数据格式、控制参数等。

5. **支持流式 I/O：**V4L2 支持流式 I/O，即通过内存映射的方式将视频数据从设备直接传输到应用程序中。这种方式可以减少数据复制的次数，提高数据传输的效率。

6. **支持控制参数：**V4L2 允许应用程序通过 API 来控制视频设备的参数，包括亮度、对比度、色彩饱和度、曝光时间等。应用程序可以使用 V4L2 API 来查询设备支持的参数，并设置适当的值。

7. **支持事件通知：**V4L2 支持事件通知，当视频设备状态发生变化时，如视频信号丢失、帧率变化等，V4L2 驱动程序可以向应用程序发送通知，以便应用程序做出相应的处理。

从上面的特征可以看出，V4L2 提供了一套通用、灵活、可扩展的视频设备驱动程序框架，使得 Linux 操作系统和应用程序可以方便地与各种视频设备进行交互，并且不需要关心设备的具体实现细节。从而让开发人员能够更加专注于应用程序的开发。

### V4L2 视频采集步骤

![图片](https://mmbiz.qpic.cn/sz_mmbiz_png/hgnOITBSQYtyNuBc8arNysuYwafFZzNKfaEDQewIHqjaGdy1BNBxlKJDKSAW8483IboKWqR8G8QvFal3JiaMLLg/640?wx_fmt=png&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1)

![图片](https://mmbiz.qpic.cn/sz_mmbiz_png/hgnOITBSQYtyNuBc8arNysuYwafFZzNKfSeM80pyT4Cfl2MHuvFWufm8G5upmrlNWiakcianDmibWTdKZ4icNmzGcg/640?wx_fmt=png&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1)![图片](https://mmbiz.qpic.cn/sz_mmbiz_png/hgnOITBSQYtyNuBc8arNysuYwafFZzNK79RNMdm1gA2U17PMuyEVypJBVm29w7ffjEfrGWJjwWBhvuRjlqz5oA/640?wx_fmt=png&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1)

![图片](https://mmbiz.qpic.cn/sz_mmbiz_png/hgnOITBSQYtyNuBc8arNysuYwafFZzNKH7HLSncuJh1NKFalOErUMbYNscDmP1mukXJRznmyog2EnEDU9kYXJg/640?wx_fmt=png&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1)

## 内核数据流

流程

1. 驱动通过 `vb2_queue_init` 初始化缓冲区队列。

2. 用户空间通过 `VIDIOC_REQBUFS` 请求缓冲区。

3. 内核分配缓冲区并返回给用户空间（MMAP 或 USERPTR）。

4. 用户空间将缓冲区入队（`VIDIOC_QBUF`），驱动填充数据后通过中断或 DMA 通知完成。

5. 用户空间通过 `VIDIOC_DQBUF` 取出已填充的缓冲区处理。

### 内核数据结构

**v4l2_device**​​：代表物理设备（如摄像头控制器），包含子设备链表

​**v4l2_subdev**​：子设备实体（如传感器），通过`v4l2_subdev_ops`实现控制接口

**v4l2_format**​：描述分辨率、像素格式等参数，支持动态协商（`VIDIOC_S_FMT`/`VIDIOC_G_FMT`）

**video_device**
表示一个 V4L2 设备，包含设备名称、操作函数集（`v4l2_file_operations`）、设备能力（如 `V4L2_CAP_VIDEO_CAPTURE`）等。

**v4l2_device**
管理多个子设备（如摄像头传感器、图像处理器），用于复杂设备的层次化控制。

**v4l2_subdev**
表示子设备（如摄像头传感器、ISP），通过媒体控制器框架与其他组件通信。

# 中断：

interrupts = <GIC_SPI 97 IRQ_TYPE_LEVEL_HIGH>;

中段控制器 是一个硬件，由芯片厂商集成到soc里面

- **SGI** (Software Generated Interrupt)：软件触发的中断。软件可以通过写 GICD_SGIR 寄存器来触发一个中断事件，一般用于核间通信，内核中的 IPI：inter-processor interrupts 就是基于 SGI。

- **PPI** (Private Peripheral Interrupt)：私有外设中断。这是每个核心私有的中断。PPI会送达到指定的CPU上，应用场景有CPU本地时钟。

- **SPI** (Shared Peripheral Interrupt)：公用的外部设备中断，也定义为共享中断。中断产生后，可以分发到某一个CPU上。比如按键触发一个中断，手机触摸屏触发的中断。

- **LPI** (Locality-specific Peripheral Interrupt)：LPI 是 GICv3 中的新特性，它们在很多方面与其他类型的中断不同。LPI 始终是基于消息的中断，它们的配置保存在表中而不是寄存器。比如 PCIe 的 MSI/MSI-x 中断
  
        gpio0: gpio@fd8a0000 {
            compatible = "rockchip,gpio-bank";
            reg = <0x0 0xfd8a0000 0x0 0x100>;
            interrupts = <GIC_SPI 277 IRQ_TYPE_LEVEL_HIGH>;
            clocks = <&cru PCLK_GPIO0>, <&cru DBCLK_GPIO0>;
      
            gpio-controller;
            #gpio-cells = <2>;
            gpio-ranges = <&pinctrl 0 0 32>;
            interrupt-controller;
            #interrupt-cells = <2>;
        };

# 1.内存划分

以32位机器为例，cpu最大寻址范围为4G，Linux系统将4G虚拟地址空间划分为高1G，低3G。

低3G虚拟空间属于用户空间，都是经过映射的线性地址，供用户进程空间使用。

高1G并非都是像用户空间一样都是映射过的线性空间，Linux系统将高1G划分为三部分：DMA区，常规区，高端内存，其中0-896都是映射过的线性空间，剩下的896-1024即高端内存，这段高端内存都是未经过映射的虚拟地址，Linux系统利用这些有限的虚拟地址，临时动态的映射到大于896M的物理空间地址，实现了利用有限的虚拟地址访问到物理内存的所有地址。

# 2.内存申请函数的对比

malloc用于用户空间进程申请内存空间，kmallc和vmalloc在内核空间使用。

kmalloc申请到的内存空间，是线性连续的，可以用于dma。

vmalloc申请的内存是逻辑连续的，但是物理地址不连续，常用与申请大的内存，请注意vmalloc可能会睡眠，在中断、阻塞的环境下不能使用。

# 3.内存映射方式

虚拟地址到物理地址的转化，用户空间和内和空间采用不同的映射机制。用户空间的地址映射经过mmu(内存管理单元)管理。而内核空间的虚拟地址到物理地址的映射是一一对应的，例如虚拟空间地址0xc0000004，对应的物理地址空间地址为：0xc0000004 - 0xc0000000 = 0x04，以此类推。（待求证）。

# 4、inux中中断的实现机制，tasklet与workqueue的区别及底层实现区别？为什么要区分上半部和下半部？

中断的上下半部_天糊土的博客-CSDN博客_中断下半部

（1）Linux中断分为硬件中断和内部中断（异常），调用过程：外部中断产生->发送中断信号到中断控制器->通知处理器产生中断的中断号，让其进一步处理。即处理器收到来自中断控制器的中断处理请求，保存中断上下文，跳转到中断对应的处理处，（快速完成中断中断上半部，中断上半部返回后执行中断下半部），中断处理函数返回时恢复现场。

（2）tasklet和workqueue，两者都是中断下半部的一种实现方法。区别在于tasklet属于中断上下文，支持smp、不可睡眠和阻塞；workqueue基于线程的封装，属于进程上下文，因此支持睡眠、阻塞。

（3）为了能够在中断处理过程中被新的中断打断，将中断处理程序一分为二，上半部登记新的中断，快速处理简单的任务，剩余复杂耗时的处理留给下半部处理。下半部处理过程中可以被中断，上半部处理时不可被中断。

## 5、Linux的同步机制

常见的同步接口，包括进程同步，信号量，自旋锁，互斥锁，条件变量，读写锁。

多进程并发一般考虑使用信号量机制，在线程并发时多采用互斥锁，条件变量。

（1）条件变量在某些角度就是线程版的信号量实现，因为两者都是在考虑持有锁时间较长情况下使用。

（2）互斥锁，自旋锁一般都是用在持有锁时间不会很长的情况下，在自旋锁有使用意义的前提下，如果持锁时间会非常短则自旋锁效率高于互斥锁（否则应该使用互斥锁，因为互斥锁会持续占有cpu资源，不宜过长，而互斥锁会导致抢不到锁的线程睡眠，进入等待队列）。

（3）互斥锁和自旋锁都可以用在进程上下文，而在中断上下文只能使用自旋锁，因为互斥锁会睡眠。

（4）使用自旋锁的进程不能睡眠，使用信号量的进程可以睡眠。

# 7、/dev/下面的设备文件是怎么创建出来的?

有三种方式：devfs机制、udev机制、手动创建设备节点。

谈谈个人见解：

devfs机制，从来没用过，应该是2.6以前的内核使用的；

udev机制，其实就是现在常用的device_create()、class_create()这一套接口，所谓udev是上层用户空间程序，是基于驱动中创建使用了这两个接口而起作用的，但是udev在日常开发中几乎接触不到，我们只需在驱动中调用创建节点的这两个API就ok了，剩下的工作就交给udev去做。

mknod ，新手最常用的一种创建设备节点方法，但并非入门后就再没有用途。在某些情境下，或许有人不想使用udev机制，于是把节点创建工作写在脚本里，这样也是无可厚非的。

# 8、原子操作该怎么理解？

原子操作，就是开始执行到执行结束期间不会被打断的操作单元。

## 9、insmod一个驱动模块，会执行模块中的哪个函数？rmmod呢？这两个函数在设计上要注意哪些？遇到过卸载驱动出现异常没？是什么问题引起的？

分别会执行module_init()、module_exit()指定的init函数和exit函数。

要注意的就是尽量使在init函数中出现的资源申请及使用有对应的释放操作在exit中，init申请，eixt释放。

卸载出现的异常？那很稀松平常了，大多数都是资源使用完没释放，但是模块却卸载了。

# 10、在驱动调试过程中遇到过oops没？你是怎么处理的？

遇到过，这种类似的段错误其实最好处理，因为它有call trace，根据堆栈信息去代码里面查看就行了。

如果代码中看不到明显低级错误，就需要printk联机调试，然而这种很少。

# 11、ioctl和unlock_ioctl有什么区别？

ioctl是老的内核版本中的驱动API，unlock_ioctl是当下常用的驱动API。

区别在于ioctl调用前后，使用了大内核锁，而unlock_ioctl顾名思义就是没加大内核锁的新接口，改变的只是驱动调的方法，用户应用程序调用的接口不变。

大内核锁是Linux hacker在应付多处理器初期提出的一种锁，目的在于当一个处理核心在运行内核时，加上大内核锁，不让其他cpu核心同时运行内核程序，显然这样是有用的，然而这样大大降低了多处理器的存在意义，于是跟随时代更迭，大内核锁被一步一步的剔除，ioctl接口的升级就是典范！我觉得这样的问题太没有意义了，对开发有多大用处？

# 12、驱动中操作物理绝对地址为什么要先ioremap?

ioremp是内核中用来将外设寄存器物理地址映射到主存上去的接口，即将io地址空间映射到虚拟地址空间上去，便于操作。为什么非要映射呢，因为保护模式下的cpu只认虚拟地址，不认物理地址，给它物理地址它并不帮你做事，所以你要操作外设上的寄存器必须先映射到虚拟内存空间，拿着虚拟地址去跟cpu对接，从而操作寄存器。

# 11、设备驱动模型三个重要成员是？platform总线的匹配规则是？在具体应用上要不要先注册驱动再注册设备？有先后顺序没？

（1）总线，设备，驱动。

（2）匹配规则：当有一个新的设备挂起时，总线被唤醒，match函数被调用，用device名字去跟本总线下的所有驱动名字去比较，相反就是用驱动的名字去device链表中和所有device的名字比较。如果匹配上，才会调用驱动中的probe函数，否则不调用。

（3）至于先后顺序，鉴于个人理解，不会有影响，不管谁先谁后，bus都会完成匹配工作。

（4）谈谈对Linux设备驱动模型的认识：设备驱动模型的出现主要有三个好处

设备与驱动分离，驱动可移植性增强；

设备驱动抽象结构以总线结构表示，看起来更加清晰明，谁是属于哪一条bus的；

最后，设备与驱动分离，很好的奠定了热插拔机制。

# 12、linux中RCU原理？

**RCU（Read-Copy-Update）​**是一种针对多核环境的同步机制，核心目标是通过无锁读操作和延迟回收旧数据，实现高并发性能。其核心思想是：

- ​**读操作无锁**：读者无需加锁即可访问数据，仅通过`rcu_read_lock()`和`rcu_read_unlock()`标记临界区

- ​**写操作异步化**：写者通过复制数据副本完成修改，并在所有读者退出旧数据引用后（即**宽限期**结束）回收旧数据

- ​**宽限期（Grace Period）​**：系统确保所有旧数据引用已结束的时间窗口，通过CPU调度（如进程切换）或计数器实现

rcu是2.6出现的一种读写锁，可以说是老的读写锁的升级版，主要用在链表这种数据结构上，经典使用场景是多读者少写者的情况，rcu允许多个读者一个写者共同操作数据而不必加锁，这是经典用法，若出现多个写者时，写者与写者之间就得自己手动同步。当要删除一个节点时，删除后并不会马上释放节点，而是会等待在删除动作之前已经开始读该节点的读者都完成读操作之后才会释放此节点，这段时间被称为宽限期。

# 13、谈谈Linux软中断？

Linux系统中的软中断，是专为一些不是特别要紧的耗时任务而产生的一种机制，多数用在中断处理过程中，典型应用就是用于中断下半部，tasklet机制就是基于软中断的典型下半部应用。

软中断就是结合任务调度、延迟处理等让守护进程去处理一些不是特别紧急又耗时的任务。

# 14、linux系统实现原子操作有哪些方法？

答：提到原子操作，我首先想到的是针对整型的原子操作，atomic_t类型，这里面有一整套针对整型的原子操作API可以调用。既然整型能原子操作，那其他也应该可以吧，结合原子操作的定义，要想对其他类型结构实现原子操作，那就加锁咯，将需要原子操作的部分放在临界区。

# 15、linux中系统调用过程？

系统调用，比如open()函数，它并不是真正的系统调用实现函数，其实它只是一个c库函数。

内部实现做了两件事，先把系统调用号传递给内核，最后拉起一次软中断，自此cpu进入内核态运行。

内核在软中断向量表中找出对应的中断类型，根据中断类型找到对应的软中断执行函数，然后执行函数根据系统调用号，在系统调用号表里面找到对应的系统调用函数。

# 16、谈谈linux内核的启动过程(源代码级)？

首先，内核镜像自解压，解压完之后从head.s开始运行，即引导内核，在内核引导期间将会设置内核参数。

随后，跳转到第一个c函数start_kernel()，进入内核启动阶段，在内核启动过程中进行一些必要的硬件初始化工作。

在内核启动最后，挂载文件系统，然后创建第一个用户空间进程，init进程，进一步完成驱动挂载，用户服务初始化工作。

# 17、谈谈Linux调度原理？

Linux将进程按权限分为两大类，常规进程和实时进程

常规进程对应一种调度算法，实时进程有两种对应着两种不同的调度算法。

进程按照状态又可以分为几种，常见的状态有：运行态、可中断睡眠态、不可中断睡眠态、停止态。处于运行态的进程根据调度算法接受调度在cpu上运行。

# 18、谈谈对Linux网络子系统的认识？

网络子系统可以概括描述为

应用程序—》系统调用接口（主要是指socket接口）—》协议无关接口（由socket实现，提供一套通用接口支持不同的协议）—》网络协议（包括tcp、udp在内的网络协议）—》设备无关接口（由net_device接口组织的一组通用接口，将网络协议与各种网络设备联系起来）—》设备驱动（即各种网络设备的驱动程序，负责管理具体的网络设备）—》网络设备（具体的网络硬件设备）。

# 19、内核中申请内存有哪几个函数？有什么区别？

常见的三个接口，kmalloc()，vmalloc()，__get_free_pages()。

kmalloc（）操作的空间位于直接映射区（即4G空间中的896M区域），申请到空间物理地址多为连续地址，常用于操作频繁的数据结构，连续地址利于提高访问效率。

对于一些操作不频繁的数据结构可以用vmalloc()申请内存，vmalloc()操作的空间优先选择高端内存，这里申请出的内存物理地址往往不是连续的，所以访问效率不会很高。

__get_free_pages（）操作的区域跟kmalloc（）相同，位于直接映射区，不同的是它申请的是物理页的整倍数大小的内存。

# 20、谈谈内核函数mmap的实现机制？

（1）mmap函数，把一个文件映射到一个内存区域，从而我们可以像读写内存一样读写文件，其比单纯调用read/write要快上许多。在某些时候我们可以把内存的内容拷贝到一个文件中实现内存备份，当然也可以把文件的内容映射到内存来恢复某些服务。

（2）mmap实现共享内存也是其主要应用之一，mmap系统调用使得进程之间通过映射同一个普通文件实现共享内存。

# 21、中断上半部、下半部的实现理解

（1）当中断到来时，要完成的工作往往并不会是短小的，它可能要进行较大量的耗时处理。因此中断处理程序中，不要求立即完成的，可以交由中断下半部完成。

中断上半部主要完成尽可能少的、比较紧急的功能，例如简单地读取寄存器中的中断状态并清除中断标志后就进行“登记中断”的工作。顶半部执行的速度就会很快，可以服务更多的中断请求。

复杂的内容则交由中断下半部来执行，而且中断下半部可以被新的中断打断，这也是下半部和上半部的最大不同。

当然， 如果中断比较简单，就不用区分上下半部。

（2）Linux 系统实现下半部的机制主要有三种：tasklet，workqueue，软中断。

# 22、tasklet与workqueue的区别及底层实现区别

（1）softirq和tasklet都属于软中断，tasklet是softirq的特殊实现；workqueue是普通的工作队列。

（2）tasklet和workqueue，两者都是中断下半部的一种实现方法。区别在于tasklet属于中断上下文，支持smp、不可睡眠和阻塞；workqueue基于线程的封装，属于进程上下文，因此支持睡眠、阻塞。

# 23、软中断的理解（与硬件中断的对比）

软中断过程：

（1）当某一软中断时间发生后，首先需要设置对应的中断标记位，触发中断事务（raise_softirq（）设置软中断状态bitmap，触发软中断事务）。

（2）然后唤醒守护线程去检测中断状态寄存器（在Linux中 软中断daemon线程函数为do_softirq（））。

（3）如果通过查询发现某一软中断事务发生之后，那么通过软中断向量表调用软中断服务程序action（）。

和硬件中断的对比：

（1）一个软中断不会去抢占另一个软中断，只有硬件中断才可以抢占软中断，所以软中断能够保证对时间的严格要求。

（2）软中断与硬件中断不同在于，从中断标记到中断服务程序的映射过程。

硬件中断发生之后，CPU需要将硬件中断请求通过向量表映射成具体的服务程序，这个过程是硬件自 动完成的。

但是软中断不是，其需要守护线程去实现这一过程，这也就是软件模拟的中断，故称之为软中断。

# 24、请简述自旋锁、信号量两个概念，及它们的区别。

（1）自旋锁

自旋锁是专门为防止多处理器并发而引入的一种锁，在内核中大量应用于中断处理等部分。（对于单处理器来说，防止中断处理中的并发可简单采用关闭中断的方式，不需要自旋锁）。

自旋锁最多只能被一个内核任务持有，如果一个内核任务试图请求一个已被争用（已经被持有）的自旋锁，那么这个任务就会一直进行忙循环——旋转——等待锁重新可用。要是锁未被争用，请求它的内核任务便能立刻得到它并且继续进行。

自旋锁可以在任何时刻防止多于一个的内核任务同时进入临界区，因此这种锁可有效地避免多处理器上并发运行的内核任务竞争共享资源。

自旋锁的初衷，是在短期间内进行轻量级的锁定。一个被争用的自旋锁使得请求它的线程在等待锁重新可用的期间进行自旋(特别浪费处理器时间)，所以自旋锁不应该被持有时间过长。如果需要长时间锁定的话, 最好使用信号量。

因为自旋锁在同一时刻只能被最多一个内核任务持有，所以一个时刻只有一个线程允许存在于临界区中。这点很好地满足了对称多处理机器需要的锁定服务。在单处理器上，自旋锁仅仅当作一个设置内核抢占的开关。如果内核抢占也不存在，那么自旋锁会在编译时被完全剔除出内核。

简单的说，自旋锁在内核中主要用来防止多处理器中并发访问临界区，防止内核抢占造成的竞争。另外自旋锁不允许任务睡眠（持有自旋锁的任务睡眠会造成自死锁——因为睡眠有可能造成持有锁的内核任务被重新调度，而再次申请自己已持有的锁），它能够在中断上下文中使用。

**死锁：**假设有一个或多个内核任务和一个或多个资源，每个内核都在等待其中的一个资源，但所有的资源都已经被占用了。这便会发生所有内核任务都在相互等待，但它们永远不会释放已经占有的资源，于是任何内核任务都无法获得所需要的资源，无法继续运行，这便意味着死锁发生了。自死琐是说自己占有了某个资源，然后自己又申请自己已占有的资源，显然不可能再获得该资源，因此就自缚手脚了。

自旋锁的基本形式如下：
spin_lock(&mr_lock);
//临界区
spin_unlock(&mr_lock);

（2）信号量

Linux中的信号量是一种睡眠锁。如果有一个任务试图获得一个已被持有的信号量时，信号量会将其推入等待队列，然后让其睡眠。这时处理器获得自由去执行其它代码。当持有信号量的进程将信号量释放后，在等待队列中的一个任务将被唤醒，从而便可以获得这个信号量。

信号量的睡眠特性，使得信号量适用于锁会被长时间持有的情况；只能在进程上下文中使用，因为中断上下文中是不能被调度的；另外当代码持有信号量时，不可以再持有自旋锁。

信号量基本使用形式为：
static DECLARE_MUTEX(mr_sem);//声明互斥信号量
if(down_interruptible(&mr_sem))
//可被中断的睡眠，当信号来到，睡眠的任务被唤醒
//临界区
up(&mr_sem);

（3）信号量和自旋锁区别

1、如果代码需要睡眠（往往发生在和用户空间同步时），使用信号量是唯一的选择。由于不受睡眠的限制，使用信号量通常来说更加简单一些。

2、如果需要在自旋锁和信号量中作选择，应该取决于锁被持有的时间长短。理想情况是所有的锁都应该尽可能短的被持有，但是如果锁的持有时间较长的话，使用信号量是更好的选择。

3、信号量不同于自旋锁，它不会关闭内核抢占，所以持有信号量的代码可以被抢占。这意味者信号量不会对影响调度反应时间带来负面影响。

# 26、什么是GPIO？

general purpose input/output ，即可以把这些引脚拿来用作任何一般用途的输入输出，例如用一根引脚连到led的一极来控制它的亮灭，也可以用一根（一些）引脚连到一个传感器上以获得该传感器的状态，这给cpu提供了一个方便的控制周边设备的途经。

# 27、在Linux C中，ls这个命令 是怎么被执行的?

使用fork创建一个进程或exec函数族覆盖原进程。

# 28、写一段 C 代码让程序跳转到地址是 0x8000 0000 的位置执行

(*(void(*)(void))0x100000)()；或者((void(*)(void))0x100000)()；

# 29、简要叙述进程和线程这两个概念。

task_struct

其中第一个数据结构为thread_info

thread_info与task_struct头地址相同

进程是指一个程序在一个数据集合上的一次运行过程。

线程是进程中的一个实体，是被系统独立调度和执行的基本单位。

进程是程序的一次执行。线程可以理解为进程中执行的一段程序片段。

## 30、在一个只有128M内存并且没有交换分区的机器上，说说下面两个程序的运行结果

```c
#define MEMSIZE 1024*1024
int count = 0;
void *p = NULL;
while(1) {
  p = (void *)malloc(MEMSIZE);
  if (!p) break;
  printf(“Current allocation %d MB\n”, ++count);
}

while(1) {
  p = (void *)malloc(MEMSIZE);
  if (!p) break;
  memset(p, 1, MEMSIZE);
  printf(“Current allocation %d MB\n”, ++count);
}
```

第一道程序分配内存但没有填充，编译器可能会把内存分配优化掉，程序死循环。

第二道，程序分配内存并进行填充，系统会一直分配内存，直到内存不足，退出循环。

# 31、请定义一个宏，比较两个数a、b的大小，不能使用大于、小于、if语句

如果可以用小于号的话，可以这么写：#define compare(a,b) ((a-b)<0 ? -1 : ((a-b) == 0 ? 0 : 1))
这样一来的话：
compare(a,b) == -1表示a<b
compare(a,b) == 0表示a==b
compare(a,b) == 1表示a>b

但是如今不能用小于号，那么我们怎样不用小于号来判断一个数字是否小于0呢？我们可以用：abs(t) != t ? 1 : -1来表示。
也即如果abs(t) != t那么t<0，否则t>=0。也即t<0等价于(abs(t) != t ? 1 : -1) == 1那么前面的宏写成如下：
#define compare(a,b) ((abs(a-b) != (a-b) ? 1 : -1) == 1 ? -1 : ((a-b) == 0 ? 0 : 1))
代码：

```c
//利用宏比较大小
#include 
#include 

#define compare(a,b) ((abs(a-b) != (a-b) ? 1 : -1) == 1 ? -1 : ((a-b) == 0 ? 0 : 1))

int main()
{
    int a1 = -1, b1 = 2, a2 = 3, b2 = 3, a3 = 4, b3= 2;

cout << compare(a1, b1) << endl << compare(a2, b2) << endl << compare(a3, b3) << endl;

return 0;

}
```
