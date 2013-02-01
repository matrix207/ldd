# 如果已定义KERNELRELEASE，则说明是从内核构造系统调用的
# 因此可利用其内建语句
ifneq ($(KERNELRELEASE),)
	obj-m := hello.o
# 否则，是直接从命令行调用的，这时候要调用内核构造系统
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

.PHONY : clean
clean:
	rm -f .hello* *.o *.ko *.mod.c *.order *symvers

endif

