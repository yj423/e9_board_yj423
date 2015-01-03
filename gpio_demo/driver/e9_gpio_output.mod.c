#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xb76c596d, "module_layout" },
	{ 0x31d362c3, "sysfs_remove_group" },
	{ 0xfe990052, "gpio_free" },
	{ 0xf89016e7, "platform_device_unregister" },
	{ 0x63ec13e7, "sysfs_create_group" },
	{ 0xc045c476, "_dev_info" },
	{ 0xa8f59416, "gpio_direction_output" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x27e1a049, "printk" },
	{ 0x97f445, "platform_device_register" },
	{ 0x432fd7f6, "__gpio_set_value" },
	{ 0xb5c63e4c, "dev_err" },
	{ 0xb742fd7, "simple_strtol" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

