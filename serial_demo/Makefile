CC= arm-none-linux-gnueabi-
CFLAG= -I -I/opt/e9/linux_e9_3.0.35/include
LFLAG= -lpthread
OBJS = serial_test_e9.c

all:serial_test_e9

serial_test_e9:$(OBJS)
	$(CC)gcc -o serial_test_e9 $(CFLAG) $(OBJS) $(LFLAG)
	sudo cp -f serial_test_e9 /home/yj423/nfswork/home/yj423

clean:
	rm -f *~
	rm -f *.o
	rm -f serial_test_e9
	rm -f *.dat
