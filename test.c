#include <unistd.h>//提供close函数
#include <fcntl.h>//提供open函数
#include <stdio.h>//提供printf函数
#include <stdlib.h>//提供exit函数
/*
 *一个测试函数，测试进程描述符的数字，答案是fd2=3，原因是stdin 0，stdout 1，stderr 2
这是在shell程序执行的时候就已经规定好的。
 * */
int main(){
	int fd1,fd2;
	fd1 = open("foo.txt",O_RDONLY,0);
	close(fd1);
	fd2 = open("baz.txt",O_RDONLY,0);
	printf("fd2=%d\n",fd2);
	exit(0);
}
