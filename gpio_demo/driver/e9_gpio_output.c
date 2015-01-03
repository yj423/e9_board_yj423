/*
 * Driver for gpio output on E9 board.
 *
 * Copyright 2014 Jone Yim
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
//#define DEBUG    1 
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>

#include <mach/iomux-mx6q.h>

MODULE_LICENSE("GPL");  

/* There are 50 pins on J6 of e9 board. */
#define J6_PINS_NUM (50)

struct e9_J6_PIN_DESC{
	int gpio_group;
	int gpio_nr;
	char *desc;
	int is_gpio; 
	int can_use;
};

#define PIN_DESC(g,nr,d,is)  	\
{						\
	.gpio_group = (g),	\
	.gpio_nr = (nr), 	\
	.desc = (d),		\
	.is_gpio = (is),	\
}
						
static struct e9_J6_PIN_DESC e9_J6_pins[J6_PINS_NUM] = {
	PIN_DESC(-1, -1, "GND", 0),
	PIN_DESC(-1, -1, "5V", 0),
	PIN_DESC(-1, -1, "DP4", 0),
	PIN_DESC(-1, -1, "DP3", 0),
	PIN_DESC(-1, -1, "DM4", 0),
	PIN_DESC(-1, -1, "DM3", 0),
	PIN_DESC(-1, -1, "GND", 0),
	PIN_DESC(-1, -1, "3.3V", 0),
	PIN_DESC(1, 28, "GPIO1_28", 1), 
	PIN_DESC(3, 17, "EIM_D17 ", 1),
	
	PIN_DESC(3, 18, "EIM_D18", 1),
	PIN_DESC(3, 21, "EIM_D21", 1), 
	PIN_DESC(3, 16, "EIM_D16", 1), 
	PIN_DESC(3, 19, "EIM_D19", 1), 
	PIN_DESC(3, 30, "EIM_D30", 1), 
	PIN_DESC(3, 20, "EIM_D20", 1),
	PIN_DESC(1, 27, "GPIO1_27", 1), 
	PIN_DESC(5, 28, "CSI0_DAT10", 1),
	PIN_DESC(1, 20, "SD1_CLK", 1),
	PIN_DESC(7, 8, "SD3_RST", 1),
	
	PIN_DESC(1, 19, "PWM2", 1),
	PIN_DESC(4, 20, "DISP0_CNTRST", 1),
	PIN_DESC(3, 22, "EIM_D22", 1), 
	PIN_DESC(3, 23, "EIM_D23", 1), 
	PIN_DESC(1,  30, "GPIO1_30", 1),  
	PIN_DESC(-1,  -1, "CAN1_RX", 0), 
	PIN_DESC(-1,  -1, "CAN1_TX", 0),
	PIN_DESC(-1,  -1, "CAN2_RX", 0), 
	PIN_DESC(-1,  -1, "CAN2_TX", 0),  
	PIN_DESC(-1,  -1, "UART4_RXD ", 0), 
	
	PIN_DESC(-1,  -1, "UART4_TXD", 0), 
	PIN_DESC(-1,  -1, "UART3_RXD", 0),
	PIN_DESC(-1,  -1, "UART3_TXD", 0),
	PIN_DESC(-1,  -1, "UART2_RXD", 0),
	PIN_DESC(-1,  -1, "UART2_TXD", 0),
	PIN_DESC(-1,  -1, "UART2_CTS", 0),
	PIN_DESC(-1,  -1, "UART2_RTS", 0),
	PIN_DESC(-1,  -1, "CSPI2_MISO", 0),
	PIN_DESC(-1,  -1, "CSPI2_MOSI", 0),
	PIN_DESC(-1,  -1, "CSPI2_CLK", 0),
	
	PIN_DESC(-1,  -1, "CSPI2_CS0", 0),
	PIN_DESC(-1,  -1, "SD3_DATA2", 0),
	PIN_DESC(-1,  -1, "SD3_DATA3", 0),
	PIN_DESC(-1,  -1, "SD3_DATA3", 0),
	PIN_DESC(-1,  -1, "EIM_A25", 0),
	PIN_DESC(-1,  -1, "SD3_CLK", 0),
	PIN_DESC(-1,  -1, "SD3_DATA0", 0),
	PIN_DESC(-1,  -1, "SD3_DATA1", 0),
	PIN_DESC(-1,  -1, "PWM3", 0),
	PIN_DESC(-1,  -1, "PWM4", 0),	
};

static ssize_t e9_gpio_output_show_high(struct device *dev,		
				      struct device_attribute *attr,	
				      char *buf)			
{									
	//struct platform_device *pdev = to_platform_device(dev);		
	
	/*Do nothing*/				
									
	return 0;							
}

static ssize_t e9_gpio_output_store_high(struct device *dev,		
				      struct device_attribute *attr,	
				      const char *buf,			
				      size_t count)			
{									
	struct platform_device *pdev = to_platform_device(dev);		
	char *after;	
	int nr, imx_gpio_nr;

	nr = simple_strtol(buf, &after, 10);
	dev_dbg(&pdev->dev, "Pin %d wants to be high\n", nr);	

	if(nr > J6_PINS_NUM){	
		dev_err(&pdev->dev, "The max pin number is %d. Try again.\r", J6_PINS_NUM);
	}else{
		if(e9_J6_pins[nr-1].can_use){
			imx_gpio_nr =  IMX_GPIO_NR(e9_J6_pins[nr-1].gpio_group, e9_J6_pins[nr-1].gpio_nr);
			gpio_set_value(imx_gpio_nr, 1);
		}else{
			dev_err(&pdev->dev, "The pin %d isn't a gpio,so it cannot be operated.\n", nr);
		}

	}	

	return count;							
}

static ssize_t e9_gpio_output_show_low(struct device *dev,		
				      struct device_attribute *attr,	
				      char *buf)			
{									
	//struct platform_device *pdev = to_platform_device(dev);		
	
	/*Do nothing*/					
									
	return 0;							
}

static ssize_t e9_gpio_output_store_low(struct device *dev,		
				      struct device_attribute *attr,	
				      const char *buf,			
				      size_t count)			
{									
	struct platform_device *pdev = to_platform_device(dev);		
	char *after;	
	int nr, imx_gpio_nr;

	nr = simple_strtol(buf, &after, 10);
	dev_dbg(&pdev->dev, "Pin %d wants to be low\n", nr);	

	if(nr > J6_PINS_NUM){
		dev_err(&pdev->dev, "The max pin number is %d. Try again.\r", J6_PINS_NUM);
	}else{
		if(e9_J6_pins[nr-1].can_use){
			imx_gpio_nr =  IMX_GPIO_NR(e9_J6_pins[nr-1].gpio_group, e9_J6_pins[nr-1].gpio_nr);
			gpio_set_value(imx_gpio_nr, 0);
		}else{
			dev_err(&pdev->dev, "The pin %d isn't a gpio,so it cannot be operated.\n", nr);
		}

	}	

	return count;						
}


/*
 * ATTRIBUTES:
 *
 * /sys/devices/platform/e9_gpio_output/gpio_high [rw]
 * /sys/devices/platform/e9_gpio_output/gpio_low [rw]
 */
static DEVICE_ATTR(gpio_high, S_IWUSR | S_IRUGO,
		   e9_gpio_output_show_high,
		   e9_gpio_output_store_high);
		   
static DEVICE_ATTR(gpio_low, S_IWUSR | S_IRUGO,
		   e9_gpio_output_show_low,
		   e9_gpio_output_store_low);


static struct attribute *e9_gpio_output_attrs[] = {
	&dev_attr_gpio_high.attr,
	&dev_attr_gpio_low.attr,
	NULL,
};

static struct attribute_group e9_gpio_attr_group = {
	.attrs = e9_gpio_output_attrs,
};

/*
**Nothing to do in this function.
**Actually this function is used to suppress the oops when invoking platform_device_unregister.
*/
static void e9_gpio_output_release(struct device *dev)
{
    return ;
}

static struct platform_device e9_gpio_output_device = {
	.name		= "e9_gpio_output",
	.id		= -1,
	.num_resources  = 0,
	.dev = {
		.release = e9_gpio_output_release,
	},
};

static int __init e9_gpio_output_init(void)
{
    int ret, i, imx_gpio_nr, cnt = 0;
	struct device *dev;
	
	ret = platform_device_register(&e9_gpio_output_device);
	if(ret < 0){
		printk("Failed to register platform device\n");
		return -1;
	}	

	dev = &e9_gpio_output_device.dev;
	
	for(i = 0; i < J6_PINS_NUM; i ++){
		if(e9_J6_pins[i].is_gpio){
			if(e9_J6_pins[i].gpio_group == -1 || e9_J6_pins[i].gpio_nr == -1){
				e9_J6_pins[i].can_use = 0;
			}else{
				imx_gpio_nr =  IMX_GPIO_NR(e9_J6_pins[i].gpio_group, e9_J6_pins[i].gpio_nr);
				ret = gpio_request(imx_gpio_nr, e9_J6_pins[i].desc);
				if (ret < 0) {
					dev_err(dev, "failed to request GPIO %d %s, error %d\n",
						imx_gpio_nr, e9_J6_pins[i].desc, ret);
					#if 0	
					goto fail1;
					#endif
					continue;
				}
				
				ret = gpio_direction_output(imx_gpio_nr, 0);
				if (ret < 0) {
					dev_err(dev, "failed to configure"
						" direction for GPIO %d %s, error %d\n",
						imx_gpio_nr,  e9_J6_pins[i].desc, ret);
					continue;
				}

				e9_J6_pins[i].can_use = 1;
				cnt ++;
				
			}
		}
	}
	
	dev_info(dev, "Successful in getting %d gpios\n", cnt);
	ret = sysfs_create_group(&e9_gpio_output_device.dev.kobj, &e9_gpio_attr_group);
	if (ret){
		dev_err(dev, "Unable to export gpio_low/gpio_high, error: %d\n",
			ret);
		goto fail2;
	}
	return 0;

fail2:
	platform_device_unregister(&e9_gpio_output_device);
#if 0
fail1:
#endif
	while(--i >= 0){
		imx_gpio_nr =  IMX_GPIO_NR(e9_J6_pins[i].gpio_group, e9_J6_pins[i].gpio_nr);
		gpio_free(imx_gpio_nr);
	}
	
	return ret;	
}

static void __exit e9_gpio_output_exit(void)
{
	int i, imx_gpio_nr;
	
	sysfs_remove_group(&e9_gpio_output_device.dev.kobj, &e9_gpio_attr_group);
	
	for(i = 0; i < J6_PINS_NUM; i ++){
		if(e9_J6_pins[i].can_use){
			if(e9_J6_pins[i].gpio_group != -1 && e9_J6_pins[i].gpio_nr != -1){
				imx_gpio_nr =  IMX_GPIO_NR(e9_J6_pins[i].gpio_group, e9_J6_pins[i].gpio_nr);
				gpio_free(imx_gpio_nr);
				e9_J6_pins[i].can_use = 0;
			}
		}
	}
	
	platform_device_unregister(&e9_gpio_output_device);
} 


module_init(e9_gpio_output_init);
module_exit(e9_gpio_output_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("jun.yan2@hirain.com");
MODULE_DESCRIPTION("E9 Board GPIO Output Driver");
