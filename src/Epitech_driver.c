
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/errno.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/mm.h>
#include "Epitech_ioctl.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("TOTO");
MODULE_DESCRIPTION("Example Module");
MODULE_VERSION("0.01");

#define DEVICE_NAME "Epitech_driver"
#define EXAMPLE_MSG "Hello, World!\n"
#define MSG_BUFFER_LEN 16

/* Prototypes for device functions */
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);
static long device_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
static int device_mmap(struct file *filp, struct vm_area_struct *vm);

static int major_num;
static int device_open_count = 0;
static char *msg_buffer;

/* This structure points to all of the device functions */
static struct file_operations file_ops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release,
	.unlocked_ioctl = device_ioctl,
	.mmap = device_mmap
};

/* Called when a process opens our device */
static int device_open(struct inode *inode, struct file *file) 
{
	/* If device is open, return busy */
	if (device_open_count) {
		printk(KERN_ALERT " Driver Could not Open \n");
		return (-EBUSY);
	} else {
		printk(KERN_ALERT "Driver  Open \n");
		//device_open_count++; // We don't want to return busy for this time
	}
	try_module_get(THIS_MODULE);
	return (0);
}

/* When a process reads from our device, this gets called. */
static ssize_t device_read(struct file *flip, char *buffer, size_t size, loff_t *offset) 
{
    if (size <= 0) {
    	return (0);
	}
    /* read data from my_data->buffer to user buffer */
    if (copy_to_user(buffer, msg_buffer, size)) {
    	return (-EFAULT);
	}
	vfree(msg_buffer);
    return (size);
}

/* When a process writes from our device, this gets called. */
static ssize_t device_write(struct file *flip, const char *buffer, size_t size, loff_t *offset)
{
    if (size <= 0) {
    	return (0);
	}
	if ((msg_buffer = vmalloc(size + 1)) == NULL) {
		return (-1);
	}
    /*read data from my_data->buffer to user buffer */
    if (copy_from_user(msg_buffer, buffer, size)) {
    	return (-EFAULT);
	}
	return (size);
}

static int device_mmap(struct file *filp, struct vm_area_struct *vma)
{
	unsigned long len = vma->vm_end - vma->vm_start;
	int ret;
	static char *vmalloc_area;
	unsigned long pfn = vmalloc_to_pfn(vmalloc_area);

	ret = remap_pfn_range(vma, vma->vm_start, pfn, len, vma->vm_page_prot);
	if (ret < 0) {
		printk(KERN_ALERT "could not map the address area\n");
		return (-EIO);
	}
	return (-EINVAL);
}

static long device_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	return 0;
}

/* Called when a process closes our device */
static int device_release(struct inode *inode, struct file *file) 
{
	module_put(THIS_MODULE);
	return (0);
}

static int __init Epitech_example_init(void) 
{
	major_num = register_chrdev(0, DEVICE_NAME, &file_ops);

	if (major_num < 0) {
		printk(KERN_ALERT "Could not register device: %d\n", major_num);
		return (major_num);
	} else {
		printk(KERN_INFO  " Hello your driver module is loaded with device major number : %d\n", major_num);
		return (0);
	}
}

static void __exit Epitech_example_exit(void) 
{
	/* Remember  we have to clean up after ourselves. Unregister the character device. */
	unregister_chrdev(major_num, DEVICE_NAME);
	printk(KERN_INFO "Goodbye, World!\n");
}

/* Register module functions */
module_init(Epitech_example_init);
module_exit(Epitech_example_exit);
