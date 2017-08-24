//application: syscall-exam-user.c
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "syscall-exam.h"

static int flag = 0;
static void * pthread_1(void *arg);
static void * pthread_2(void *arg);

int main(void)
{
	int fd;
	pthread_t pthread1_id;
	pthread_t pthread2_id;

	pthread_create(&pthread1_id, NULL, pthread_1, NULL);
	pthread_create(&pthread2_id, NULL, pthread_2, NULL);
	while(1);
	
	return 0;
}

static void * pthread_1(void *arg)
{
	int fd = -1;
	struct mychrdev_window truncate_window;
	mydev_info_t mydev_info;

	fd = open("/dev/mychrdev", O_RDWR);
	if (fd < 0) {
		perror("open:");
		exit(-1);
	}
	printf("1 fd:%d\n", fd);
	ioctl(fd, MYCHRDEV_IOCTL_GET_INFO, &mydev_info);
	printf("User process1: %s(%d)\n", mydev_info.user_name, mydev_info.user_pid);
	flag = 1;
	//ioctl(fd, MYCHRDEV_IOCTL_GET_INFO, &mydev_info);
	printf("pthread_1 exit...\n");

	return NULL;
}

static void * pthread_2(void *arg)
{
	int fd = -1;
	struct mychrdev_window truncate_window;
	mydev_info_t mydev_info;

	fd = open("/dev/mychrdev", O_RDWR);
	if (fd < 0) {
		perror("open:");
		exit(-1);
	}
	printf("2 fd:%d\n", fd);
//	ioctl(fd, MYCHRDEV_IOCTL_GET_INFO, &mydev_info);
	printf("User process2: %s(%d)\n", mydev_info.user_name, mydev_info.user_pid);
	while(flag);
	ioctl(fd, MYCHRDEV_IOCTL_SET_TRUNCATE, &truncate_window);
	printf("pthread_2 exit...\n");

	return NULL;
}
