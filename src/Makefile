CONFIG_MODULE_SIG=n

obj-m += Epitech_driver.o

MAJOR= 238 #Given value when your module loaded for the first time

TESTEPITECH= testEpitech

MYTEST= myTest

load_module:
	# Clear the kernel log without echo
	sudo dmesg -C
	# Insert the module
	sudo insmod Epitech_driver.ko
	# Display the kernel log
	dmesg

create_nod:
	sudo mknod /dev/Epitech_driver c $(MAJOR) 0

unload_module:
	# We put a — in front of the rmmod command to tell make to ignore
	# an error in case the module isn’t loaded.
	-sudo rmmod Epitech_driver
	# Clear the kernel log without echo
	sudo dmesg -C

all: $(TESTEPITECH) $(MYTEST)
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	make load_module
	make create_nod

$(TESTEPITECH): 
	gcc testEpitech.c -o $(TESTEPITECH)

$(MYTEST): 
	gcc myTest.c -o $(MYTEST)

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

fclean:
	make unload_module
	make clean
	sudo rm /dev/Epitech_driver
	rm $(TESTEPITECH)
	rm $(MYTEST)

re:	fclean all
