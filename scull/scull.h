// scull.h

#ifndef _SCULL_H_
#define _SCULL_H_

#include <linux/fs.h>
#include <linux/ioctl.h>
#include <linux/cdev.h>


#define SCULLC_QUANTUM  4000
#define SCULLC_QSET		500

#define SCULLC_MAJOR 0
#define SCULLC_DEVS 4

/* file operator */
/*
  struct module *owner; 指向拥有该结构的模块的指针
  loff_t (*llseek) (struct file *, loff_t, int); 修改文件当前读写位置
  ssize_t (*read) (struct file *, char __user *, size_t, loff_t *); 从设备中读取数据
  ssize_t (*aio_read) (struct kiocb *, char __user *, size_t, loff_t); 异步读取操作
  ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *); 向设备发送数据
  ssize_t (*aio_write) (struct kiocb *, const __user *, size_t, loff_t *); 异步写入操作
  int (*readdir) (struct file *, void *, filldir_t)
  unsigned int (*poll) (struct file *, struct poll_table_struct *);
  int (*ioctl) (struct inode *, struct file *, unsigned int, unsigned long);
  int (*mmpa) (struct file *, struct vm_area_struct *); 映射设备内存到进程地址空间
  int (*open) (struct inode *, struct file *);
  int (*flush) (struct file *);
  int (*release) (struct inode *, struct file *);
  int (*fsync) (struct file *, struct dentry *, int);
  int (*aio_fsync) (struct kiocb *, int);
  int (*lock) (struct file *, int, struct file_lock *);
  ssize_t (*readv) (struct file *, const struct iovec *, unsigned long, loff_t *);
  ssize_t (*writev) (struct file *, const struct iovec *, unsigned long, loff_t *);
  ssize_t (*sendfile) (struct file *, loff_t *, size_t, read_actor_t, void *);
  ssize_t (*sendpage) (struct file*, struct page *, int, size_t, loff_t *, int);
  unsigned long (*get_unmapped_area) (struct file *, unsigned long, unsigned long, unsigned long, unsigned long);
  int (*check_flags) (int);
  int (*dir_notify) (struct file*, unsigned long);
*/

struct file_operations scull_fops = {
	.owner =	THIS_MODULE,
	.llseek=	scull_llseek,
	.read =		scull_read,
	.write =	scull_write,
	.ioctl =	scull_ioctl,
	.open =		scull_open,
	.release =	scull_release,
};

/* file structure */
/*
  mode_t f_mode; 文件模式
  loff_t f_pos; 当前的读写位置
  unsigned int f_flags; 文件标志
  struct file_operations *f_op; 文件相关操作
  void *private_data;
  struct dentry *f_dentry; 文件对应的目录项结构
*/

/* inode structure */
/*
  dev_t i_rdev; 设备文件的inode结构
  struct cdev *i_cdev; 字符设备结构体
*/
struct scull_dev {
	struct scull_qset *data;
	int quantum;
	int qset;
	unsigned long size;
	unsigned int access_key;
	struct semaphore sem;
	struct cdev cdev;
};

struct scull_qset {
    void **data;
    struct scull_qset *next;
};

#endif
