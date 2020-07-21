#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/printk.h>
#include <linux/kernel.h>

#define MY_ID "THIS_IS_MY_ID"
#define BUFF_LEN 100

static ssize_t eudyptula_write(struct file *file, char const __user *buf,
			size_t count, loff_t *ppos)
{
  size_t ret;
	char input[BUFF_LEN];
  ret = simple_write_to_buffer(input, BUFF_LEN, ppos, buf, count);
  pr_debug("eudyptula_write: inputlen: %ld ret: %ld input: %s my_id: %s my_id_len: %ld",
      strlen(input), ret, input, MY_ID, strlen(MY_ID));
  pr_debug("%c %c", input[13], MY_ID[ret]);
  if (!strcmp(input, MY_ID)) {
    pr_debug("eudyptula_write: you input a correct string!\n");
    return ret;
  } else {
    pr_debug("eudyptula_write: you input an incorrect string!\n");
    return -EINVAL;
  }
}

static ssize_t eudyptula_read(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
  const char* data = MY_ID;
  const int len = strlen(data) + 1;
  pr_debug("eudypula_read: invoked.\n");

  return simple_read_from_buffer(buf, count, ppos, data, len);
}

static const struct file_operations eudyptula_fops = {
	.owner = THIS_MODULE,
	.read = eudyptula_read,
	.write = eudyptula_write
};

static struct miscdevice eudyptula_dev = {
	MISC_DYNAMIC_MINOR,
	"eudyptula",
	&eudyptula_fops
};

static int eudyptula_init(void)
{
  int ret;

  pr_debug("Initializing eudyptula misc char device module...\n");
	ret = misc_register(&eudyptula_dev);
  if (ret){
    pr_err("Failed to register misc char device!\n");
    return ret;
  }

  return 0;
}

static void eudyptula_exit(void)
{
  misc_deregister(&eudyptula_dev);
  pr_debug("Exiting eudyptula misc char device module...\n");
}

module_init(eudyptula_init);
module_exit(eudyptula_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("7c1caf2f50d1");
MODULE_DESCRIPTION("Just a module");
