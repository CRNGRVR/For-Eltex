obj-m += testmodule.o	# Имя должно совпадать с именем исходного файла

all:
				make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
				make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
