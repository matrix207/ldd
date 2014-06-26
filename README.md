ldd
===

**Linux device drivers**

Homepage of LDD <http://lwn.net/Kernel/LDD3/>

###Source
+ ftp://ftp.ora.com/pub/examples/linux/drivers/ 
+ ftp://ar.linux.it/pub/ldd3/
+ http://www.cs.fsu.edu/~baker/devices/lxr/http/source/ldd-examples 

warning:  
	LDD(third version) use kernel 2.6.10, so if the version you use is later,  
you will not compile the source (from upon link) success.  

###How to
* editor source file ( .c .h Makefile ) with vim
* `make` or `make clean`  for compile or clean
* `insmod XXX.ko`  for insert module to kernel
* `lsmod | grep XXX` for check module have been inserted
* `dmesg | tail` check message with printk function by module
* `rmmod XXX` remove module

###Manifest
+ hello		sample for "Hello, world"
+ hellop	sample for "module parameters"
+ scullc	sample for "Simple character Utility for Loading Localities"
+ netlink   sample of using netlink

###LDD for recently kernel
Refer this site <https://github.com/martinezjavier/ldd3>

###Reference
+ [How to: Compile Linux kernel modules](http://www.cyberciti.biz/tips/compiling-linux-kernel-module.html)
