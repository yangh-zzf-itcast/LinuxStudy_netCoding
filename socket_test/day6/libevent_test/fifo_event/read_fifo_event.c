/*************************************************************************
    > File Name: read_fifo_event.c
    > Author: yanghang
    > Mail: 2459846416@qq.com 
    > Created Time: Wed 02 Jan 2019 07:04:56 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <event2/event.h>

void sys_err(const char *str)
{
	perror(str);
	exit(1);
}

void read_cb(evutil_socket_t fd, short what, void *arg)
{
	char buf[1024] = {0};
	int len = read(fd, buf, sizeof(buf));
	printf("what = %s\n", what & EV_READ ? "read get": "read unget");
	printf("read from write : %s,  len = %d\n", buf, len);
	sleep(1);
	return;
}

int main(int argc, char *argv[])
{
	//创建一个管道fifo文件
	unlink("testfifo");
	mkfifo("testfifo", 0644);

	//打开fifo的读端
	int fd = open("testfifo", O_RDONLY | O_NONBLOCK);
	if(fd == -1)
		sys_err("open error");

	//创建一个base
	struct event_base *base = event_base_new();

	//创建一个事件
	struct event *ev = NULL;

	ev = event_new(base, fd, EV_READ | EV_PERSIST, read_cb, NULL);

	event_add(ev, NULL);

	event_base_dispatch(base);

	event_base_free(base);

	return 0;
}
