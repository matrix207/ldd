/* 
 * 例子: 模块参数 
 * 装载: insmod hellop howmany=10 whom=“Mon" 
 * 效果: 打印10次 "hello, Mon"
 */
#include <linux/init.h>
#include <linux/module.h>
MODULE_LICENSE("Dual BSD/GPL");

static char *whom = "world";
static int howmany = 1;
module_param(howmany, int, S_IRUGO);
module_param(whom, charp, S_IRUGO);

static int __init initialization_function(void)
{ 
	int i=0;
	for(i=0; i<howmany; i++)
	{
		printk(KERN_ALERT "hello, %s\n", whom);
	}
	return 0;
}

static void __exit cleanup_function(void)
{ 
	printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_init(initialization_function);
module_exit(cleanup_function);

