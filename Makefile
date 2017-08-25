CONFIG_MODULE_SIG=n
#obj-m := syscall_exam_kern.o  
obj-m := syscall_exam_kern_completion.o  
module-objs:=
KERNELBUILD :=/lib/modules/$(shell uname -r)/build  
default:  
	make -C $(KERNELBUILD) M=$(shell pwd) modules  
clean:  
	rm -rf *.o *.ko *.mod.c .*.cmd *.markers *.order *.symvers .tmp_versions
