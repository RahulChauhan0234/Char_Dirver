obj-m := char1.o
  
KERNSRC := /lib/modules/$(shell uname -r)/build
       
PWD := $(shell pwd)
	  
modules:
	make -C $(KERNSRC) M=$(PWD) modules
	         
modules_install:
	make -C $(KERNSRC) M=$(PWD) modules_install
	depmod -a
		     
clean:
	make -C $(KERNSRC) M=$(PWD) clean

