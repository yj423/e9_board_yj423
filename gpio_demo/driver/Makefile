KDIR     = /opt/e9/linux_e9_3.0.35
KHEAD    = $(KDIR)/include
INSTALLDIR = /home/yj423/nfswork/home/yj423
CROSS_COMPILE= arm-none-linux-gnueabi-

PWD := $(shell pwd)

obj-m := e9_gpio_output.o

modules:
	$(MAKE) -C $(KDIR) -I $(KHEAD) M=$(PWD) modules
	@cp e9_gpio_output.ko $(INSTALLDIR) -rfv
install:
	cp e9_gpio_output.ko $(INSTALLDIR) -rfv

clean:
	rm -rf *.o *~core .depend .*.cmd *.ko *.mod.c *.tmp_versions
.PHONY: modules modules_install clean
  
