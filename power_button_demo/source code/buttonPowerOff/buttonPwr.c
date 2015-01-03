/*
 * Power button function(using apm emulation driver)
 *
 * Copyright (c) 2014 Yan Jun<jun.yan2@hirain.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 *
 * Cross-compile with cross-gcc -I/path/to/cross-kernel/include
 */


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/io.h>
#include <signal.h>

#include <linux/apm-emulation.h>
#include <linux/input.h>
#include <linux/apm_bios.h>

#define PWR_OFF_TIME 	(3) /* unit:second */
#define PWR_SUSPEND_TIME (1) /* unit:second */

#define SEC_TO_USEC(sec) (1000000 * (sec))

static void pwr_handler(int signo)
{
	char command[] = "sync;\\sync;\\poweroff";
	printf("Now shutdowning system!\n");	
	system(command);
}

int main(int argc, char **argv)
{
	int fd, ret, wakeup;
	int apm;
	struct input_event button_event;
	struct timeval prev;
	
	fd = open("/dev/event0", O_RDWR);
	if(fd < 0 ){
		printf("open /dev/event0 wrong\n");
		return -1;
	}
	
	apm = open("/dev/apm_bios", O_RDWR);
	if(apm < 0){
		printf("open /dev/apm_bios wrong\n");
		return -1;
	}
	
	signal(SIGALRM, pwr_handler); 
	
	while(1)
	{
		/* Read will block here. */
		ret = read(fd, &button_event, sizeof(button_event));
		if(ret < sizeof(button_event)){
			printf("incomplete read\n");
			return -1;
		}
		
		
		/* If event is from power button and it is pressed, launch the alarm*/
		if (button_event.code == KEY_POWER && (button_event.value == 1)){
			//printf("Power button event %d\n", button_event.value);
			alarm(PWR_OFF_TIME); /* after 3 seconds, system will suspend */
			prev.tv_sec = button_event.time.tv_sec;
			prev.tv_usec = button_event.time.tv_usec;
		/* If event is from power button and it is unpressed, cancel the alarm*/
		}else if (button_event.code == KEY_POWER && (button_event.value == 0)){	
			alarm(0); /* Cancel the alarm */
			
			if((SEC_TO_USEC(button_event.time.tv_sec) + button_event.time.tv_usec) - ( 
					SEC_TO_USEC(prev.tv_sec) + prev.tv_usec)  < SEC_TO_USEC(PWR_SUSPEND_TIME) && wakeup == 0){
				printf("Now suspending system!\n");
				wakeup = 1;
				ioctl(apm, APM_IOC_SUSPEND, 0);
			}else{
				wakeup = 0;
			}
		}
	}
	
	close(fd);
}

