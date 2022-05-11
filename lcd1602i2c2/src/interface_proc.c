#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#include <linux/of_gpio.h>
#include <linux/i2c.h>
#include <linux/unistd.h>
#include "io_i2c.h"
#include "io_lcd1602.h"
#define NAME_OF_PROC 	("LCDI2C")

static int hello_val=0;






//-----------------------------------------------------
static int test_proc_open(struct inode *inode, struct file *file)
{
	return 0;
}



static ssize_t test_proc_read(struct file *file, char __user *buffer,size_t count, loff_t *f_pos)
{

	int len1;
	if(*f_pos > 0)
		return 0;
	len1 = sprintf(buffer, "%d\n", hello_val);
	*f_pos = *f_pos + len1;
	return len1;
}



static ssize_t test_proc_write(struct file *file, const char __user *buffer,size_t count, loff_t *f_pos)
{
	unsigned char tmpbuf[64];

	if(count <= 0)
		return -EFAULT;
	if(count > sizeof(tmpbuf)) 
		count = (16*2+1); // "\n01234567890012345678900123456789012"

	if (buffer && !copy_from_user(tmpbuf, buffer, count)) {
		LCD_parse_string (tmpbuf,count);
	}
	return count;
}



static struct file_operations test_fops = {
	.owner = THIS_MODULE,
	.open = test_proc_open,
	.read = test_proc_read,
	.write = test_proc_write,
	// .release = single_release,
	// .llseek = seq_lseek,
};


static int __init func_module_init(void)
{
	struct proc_dir_entry* file;
	int ret=0;
	file = proc_create(NAME_OF_PROC, 0644, NULL, &test_fops);
	if (!file)
		return -ENOMEM;

    
	ret=i2c_dev_init();
	LCD_init();
	return ret;
}



static void __exit func_module_exit(void)
{
	remove_proc_entry(NAME_OF_PROC, NULL);
	i2c_dev_exit();

}

module_init(func_module_init);
module_exit(func_module_exit);

MODULE_AUTHOR("greatcat@ms18.hinet.net");
MODULE_DESCRIPTION("proc_module "+NAME_OF_PROC);
MODULE_LICENSE("GPL");



