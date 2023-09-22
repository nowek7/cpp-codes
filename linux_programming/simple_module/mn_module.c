#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

static char* name = "";
module_param(name, charp, 0644);
MODULE_PARM_DESC(name, "String 'name'");

static int value_a = 0;
module_param(value_a, int, 0644);
MODULE_PARM_DESC(value_a, "Integer 'a'");

static int value_b = 0;
module_param(value_b, int, 0644);
MODULE_PARM_DESC(value_b, "Integer 'b'");

static int __init mInit(void)
{
  printk(KERN_INFO "[mn_module] Init module!\n");

  printk(KERN_INFO "[mn_module] Name = %s\n", name);
  printk(KERN_INFO "[mn_module] %d + %d = %d\n", value_a, value_b, value_a + value_b);

  /*
  Return 0 == success othwerwise value means that
  module failed to load and the module can't be loaded.
  */
  return 0;
}

void __exit mExit(void)
{
  printk(KERN_INFO "[mn_module] Cleanup module!\n");
}

module_init(mInit);
module_exit(mExit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("nowek7");
MODULE_DESCRIPTION("Kernel module example");
MODULE_VERSION("0.1");
