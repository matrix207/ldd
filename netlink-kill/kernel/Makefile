ifneq ($(KERNELRELEASE),)
	obj-m := netlink-kill.o

else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

.PHONY : clean
clean:
	rm -rf .netlink-kill* *.o *.ko *.mod.c *.order *symvers *.cmd .tmp_versions

endif

