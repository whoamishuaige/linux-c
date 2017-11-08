#include <stdio.h>//提供fprintf
#include <unistd.h>//提供write,read.close
#include <fcntl.h>//提供create
#include <stdlib.h>//提供exit函数
#define BUFFSIZE 4096 //最大长度
#define  COPYMODE 0644 //权限位置,避免幻数
/*
 *命令名称：cp格式
	cp source target
	创建/重写文件
	creat函数
	写入文件 write
 * */
void oops(char *,char *);
int main(int ac,char * av[]){
	int in_fd,out_fd,n_chars;
	char buf[BUFFSIZE];
	if(ac != 3){ //cp 需要三个参数
		fprintf(stderr,"usage:%s source destination\n",*av);
		exit(1);
	}
	if((in_fd = open(av[1],O_RDONLY))==-1) //开资源，in_fd是打开的指针
		oops("cannot open",av[1]);
	if((out_fd = creat(av[2],COPYMODE))==-1) //创建新资源 out_fd 是关闭的指针
		oops("cannot write",av[2]);
	//核心循环。从in到out
	while((n_chars = read(in_fd,buf,BUFFSIZE))>0) 
		if( write(out_fd,buf,n_chars) !=n_chars)
			oops("write error to ",av[2]);
	if(n_chars == -1)
			oops("read error from ",av[1]);
	if(close(in_fd)== -1 || close(out_fd)==-1){
			oops("error close file","");
		}

}
//错误输出函数，分别用两个函数输出错误
void oops (char *s1,char *s2){
	fprintf(stderr,"error:%s",s1);
	perror(s2);
	exit(1);
}


