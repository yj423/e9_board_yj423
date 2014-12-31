CC= arm-none-linux-gnueabi-
CFLAG= -I. -I/opt/e9/linux_e9_3.0.35/include
LFLAG= -lpthread
OBJS = buttonPwr.c

all:buttonPwr

buttonPwr:$(OBJS)
	$(CC)gcc -o buttonPwr $(CFLAG) $(OBJS) $(LFLAG)
	sudo cp -f buttonPwr /home/yj423/nfswork/home/yj423

clean:
	rm -f *~
	rm -f *.o
	rm -f buttonPwr
	rm -f *.dat
