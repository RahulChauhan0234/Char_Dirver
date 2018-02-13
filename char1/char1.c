#include<linux/init.h>
#include<linux/module.h>
#include<linux/cdev.h>
#include<linux/types.h>
#include<linux/fs.h>
MODULE_LICENSE("GPL");

int char1_open (struct inode *i, struct file *f)
{
	printk("File Opend!");
	return 0;
}
ssize_t char1_read (struct file *char1_file, char __user *buffer, size_t count, loff_t *loff)
{
	printk("File Read");
	return 0;
}
ssize_t char1_write (struct file *char1_file, const char __user *buffer, size_t count, loff_t *loff)
{
	printk("File Write");
	return 0;
}
int char1_close (struct inode *i, struct file *f)
{
	printk("File Closed!");
	return 0;
}


struct file_operations char1_fops=
{
	.open	= char1_open,
	.read	= char1_read,
	.write	= char1_write,
	.release= char1_close,
};
struct class *char1_class;
struct device *char1_device;
struct cdev char1_cdev;
dev_t dev;
static int char1_init(void)
{
	int result;
	/* Dynamic Device Number Allocation */

	result = alloc_chrdev_region(&dev,0,1,"char1");
	if(result<0)
	{
		printk("Device Number Allocation Failed");
		return -1;
	}
	/* Register character Driver */
	cdev_init(&char1_cdev,&char1_fops);
	result=cdev_add(&char1_cdev,dev,1);
	if(result<0)
	{
		printk("char device Registration Failed!");
		cdev_del(&char1_cdev);
		return -1;
	}
	/* create class */

	char1_class = class_create(THIS_MODULE,"char1_class");

	/*device create */

	char1_device= device_create(char1_class,NULL,dev,NULL,"char%d",1);
	

	return 0;
}

static void char1_exit(void)
{
	device_destroy(char1_class,dev);
	class_destroy(char1_class);
	cdev_del(&char1_cdev);
	unregister_chrdev_region(dev, 1);
}
module_init(char1_init);
module_exit(char1_exit);

