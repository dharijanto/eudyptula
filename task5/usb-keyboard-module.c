#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>
#include <linux/hid.h>

/* table of devices that work with this driver */
static struct usb_device_id skel_table[] = {
  { USB_INTERFACE_INFO(
      USB_INTERFACE_CLASS_HID,
      USB_INTERFACE_SUBCLASS_BOOT,
      USB_INTERFACE_PROTOCOL_KEYBOARD)
  },
  {}
};

static int skel_probe(struct usb_interface *interface,
		      const struct usb_device_id *id)
{
  printk(KERN_DEBUG "USB keyboard device detected!");

  return 0;
}

static void skel_disconnect(struct usb_interface *interface)
{
  printk(KERN_DEBUG "USB keyboard device disconnected!");
}

static struct usb_driver skel_driver = {
  .name        = "skeleton",
  .probe       = skel_probe,
  .disconnect  = skel_disconnect,
  .id_table    = skel_table,
};

static int hello_init(void)
{
  int ret;
  printk(KERN_DEBUG "Hello World! Welcome to USB Keyboard Module!\n");
  ret = usb_register(&skel_driver);
  if (ret) {
    printk(KERN_DEBUG "Failed to register usb driver!\n");
  }
  return ret;
}

static void hello_exit(void)
{
  usb_deregister(&skel_driver);
  printk(KERN_DEBUG "See you later.\n");
}

MODULE_DEVICE_TABLE (usb, skel_table);

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("7c1caf2f50d1");
MODULE_DESCRIPTION("Just a module");
