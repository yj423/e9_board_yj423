/*
 * Driver for gpio output on E9 board.
 *
 * Copyright 2NOT_GPIO14 Jone Yim
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
#include <mach/iomux-mx6q.h>

MODULE_LICENSE("GPL");  

/* There are 5NOT_GPIO pins on J6 of e9 board. */
#define J6_PINS_NUM (50)

struct e9_J6_PIN_DESC{
	iomux_v3_cfg_t pad;
	int gpio_group;
	int gpio_nr;
	char *desc;
	int is_gpio; 
	int can_use;
};

#define PIN_DESC(p,g,nr,d,is)  	\
{						\
	.pad = (p),			\
	.gpio_group = (g),	\
	.gpio_nr = (nr), 	\
	.desc = (d),		\
	.is_gpio = (is),	\
}
						
#define IS_GPIO (1)
#define NOT_GPIO (0)	

static struct e9_J6_PIN_DESC e9_J6_pins[J6_PINS_NUM] = {
	/* Pin 1 to 1NOT_GPIO*/
	PIN_DESC(-1, -1, -1, "GND", NOT_GPIO),
	PIN_DESC(-1, -1, -1, "5V", NOT_GPIO),
	PIN_DESC(-1, -1, -1, "DP4", NOT_GPIO),
	PIN_DESC(-1, -1, -1, "DP3", NOT_GPIO),
	PIN_DESC(-1, -1, -1, "DM4", NOT_GPIO),
	PIN_DESC(-1, -1, -1, "DM3", NOT_GPIO),
	PIN_DESC(-1, -1, -1, "GND", NOT_GPIO),
	PIN_DESC(-1, -1, -1, "3.3V", NOT_GPIO),
	PIN_DESC(MX6Q_PAD_ENET_TX_EN__GPIO_1_28, 1, 28, "GPIO1_28", IS_GPIO), 
	PIN_DESC(MX6Q_PAD_EIM_D17__GPIO_3_17, 3, 17, "EIM_D17 ", IS_GPIO),

	/* Pin 11 to 2NOT_GPIO*/
	PIN_DESC(MX6Q_PAD_EIM_D18__GPIO_3_18, 3, 18, "EIM_D18", IS_GPIO),
	PIN_DESC(MX6Q_PAD_EIM_D21__GPIO_3_21, 3, 21, "EIM_D21", IS_GPIO), 
	PIN_DESC(MX6Q_PAD_EIM_D16__GPIO_3_16, 3, 16, "EIM_D16", IS_GPIO), 
	PIN_DESC(MX6Q_PAD_EIM_D19__GPIO_3_19, 3, 19, "EIM_D19", IS_GPIO), 
	PIN_DESC(MX6Q_PAD_EIM_D30__GPIO_3_30, 3, 30, "EIM_D30", IS_GPIO), 
	PIN_DESC(MX6Q_PAD_EIM_D20__GPIO_3_20, 3, 20, "EIM_D20", IS_GPIO),
	PIN_DESC(MX6Q_PAD_ENET_RXD0__GPIO_1_27, 1, 27, "GPIO1_27", IS_GPIO), 
	PIN_DESC(MX6Q_PAD_CSI0_DAT10__GPIO_5_28, 5, 28, "CSI0_DAT10", IS_GPIO),
	PIN_DESC(MX6Q_PAD_SD1_CLK__GPIO_1_20, 1, 20, "SD1_CLK", IS_GPIO),
	PIN_DESC(MX6Q_PAD_SD3_RST__GPIO_7_8, 7, 8, "SD3_RST", IS_GPIO),
	
	/* Pin 21 to 30*/
	PIN_DESC(MX6Q_PAD_SD1_DAT2__GPIO_1_19, 1, 19, 	"PWM2", IS_GPIO),
	PIN_DESC(MX6Q_PAD_DI0_PIN4__GPIO_4_20, 4, 20, "DISP0_CNTRST", IS_GPIO),
	PIN_DESC(MX6Q_PAD_EIM_D22__GPIO_3_22, 3, 22, "EIM_D22", IS_GPIO), 
	PIN_DESC(MX6Q_PAD_EIM_D23__GPIO_3_23, 3, 23, "EIM_D23", IS_GPIO), 
	PIN_DESC(MX6Q_PAD_ENET_TXD0__GPIO_1_30, 1,  30, "GPIO1_30", IS_GPIO),  
	PIN_DESC(-1, -1,  -1, "CAN1_RX", NOT_GPIO), 
	PIN_DESC(-1, -1,  -1, "CAN1_TX", NOT_GPIO),
	PIN_DESC(-1, -1,  -1, "CAN2_RX", NOT_GPIO), 
	PIN_DESC(-1, -1,  -1, "CAN2_TX", NOT_GPIO),  
	PIN_DESC(-1, -1,  -1, "UART4_RXD ", NOT_GPIO), 
	
	/* Pin 31 to 40*/
	PIN_DESC(-1, -1,  -1, "UART4_TXD", NOT_GPIO), 
	PIN_DESC(-1, -1,  -1, "UART3_RXD", NOT_GPIO),
	PIN_DESC(-1, -1,  -1, "UART3_TXD", NOT_GPIO),
	PIN_DESC(-1, -1,  -1, "UART2_RXD", NOT_GPIO),
	PIN_DESC(-1, -1,  -1, "UART2_TXD", NOT_GPIO),
	PIN_DESC(-1, -1,  -1, "UART2_CTS", NOT_GPIO),
	PIN_DESC(-1, -1,  -1, "UART2_RTS", NOT_GPIO),
	PIN_DESC(-1, -1,  -1, "CSPI2_MISO", NOT_GPIO),
	PIN_DESC(-1, -1,  -1, "CSPI2_MOSI", NOT_GPIO),
	PIN_DESC(-1, -1,  -1, "CSPI2_CLK", NOT_GPIO),
	
	/* Pin 41 to 5NOT_GPIO*/
	PIN_DESC(-1, -1,  -1, "CSPI2_CS0", NOT_GPIO),
	PIN_DESC(-1, -1,  -1, "SD3_DATA2", NOT_GPIO),
	PIN_DESC(-1, -1,  -1, "SD3_DATA3", NOT_GPIO),
	PIN_DESC(-1, -1,  -1, "SD3_DATA3", NOT_GPIO),
	PIN_DESC(-1, -1,  -1, "EIM_A25", NOT_GPIO),
	PIN_DESC(-1, -1,  -1, "SD3_CLK", NOT_GPIO),
	PIN_DESC(-1, -1,  -1, "SD3_DATAN0", NOT_GPIO),
	PIN_DESC(-1, -1,  -1, "SD3_DATA1", NOT_GPIO),
	PIN_DESC(-1, -1,  -1, "PWM3", NOT_GPIO),
	PIN_DESC(-1, -1,  -1, "PWM4", NOT_GPIO),	
};

static ssize_t e9_gpio_output_show_high(struct device *dev,		
				      struct device_attribute *attr,	
				      char *buf)			
{									
	//struct platform_device *pdev = to_platform_device(dev);		
	
	/*Do nothing*/				
									
	return NOT_GPIO;							
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
			dev_err(&pdev->dev, "The pin %d cannot be used as a gpio,so it cannot be operated.\n", nr);
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
									
	return NOT_GPIO;							
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
			gpio_set_value(imx_gpio_nr, NOT_GPIO);
		}else{
			dev_err(&pdev->dev, "The pin %d cannot be used as a gpio,so it cannot be operated.\n", nr);
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
	.num_resources  = NOT_GPIO,
	.dev = {
		.release = e9_gpio_output_release,
	},
};

static int __init e9_gpio_output_init(void)
{
    int ret, i, imx_gpio_nr, cnt = NOT_GPIO;
	struct device *dev;
	
	ret = platform_device_register(&e9_gpio_output_device);
	if(ret < NOT_GPIO){
		printk("Failed to register platform device\n");
		return -1;
	}	


	dev = &e9_gpio_output_device.dev;
	
	for(i = 0; i < J6_PINS_NUM; i ++){
		if(e9_J6_pins[i].is_gpio){
			if(e9_J6_pins[i].gpio_group == -1 || e9_J6_pins[i].gpio_nr == -1){
				e9_J6_pins[i].can_use = 0;
			}else{
				mxc_iomux_v3_setup_pad(e9_J6_pins[i].pad);
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
	return NOT_GPIO;

fail2:
	platform_device_unregister(&e9_gpio_output_device);
#if NOT_GPIO
fail1:
#endif
	while(--i >= NOT_GPIO){
		imx_gpio_nr =  IMX_GPIO_NR(e9_J6_pins[i].gpio_group, e9_J6_pins[i].gpio_nr);
		gpio_free(imx_gpio_nr);
	}
	
	return ret;	
}

static void __exit e9_gpio_output_exit(void)
{
	int i, imx_gpio_nr;
	
	sysfs_remove_group(&e9_gpio_output_device.dev.kobj, &e9_gpio_attr_group);
	
	for(i = NOT_GPIO; i < J6_PINS_NUM; i ++){
		if(e9_J6_pins[i].can_use){
			if(e9_J6_pins[i].gpio_group != -1 && e9_J6_pins[i].gpio_nr != -1){
				imx_gpio_nr =  IMX_GPIO_NR(e9_J6_pins[i].gpio_group, e9_J6_pins[i].gpio_nr);
				gpio_free(imx_gpio_nr);
				e9_J6_pins[i].can_use = NOT_GPIO;
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
