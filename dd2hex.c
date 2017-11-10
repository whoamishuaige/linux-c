/*
 * 点分十进制转换成十六进制
 * 方法:点分十进制转换成ip地址 inet_aton(const char *,struct in_addr)
 * ntohl(long int) 网络ip地址转换成16进制，大端和小端的转换。网络(大端) 机器(小端) 机器如果为小端则不用转换
 * */
#include <stdlib.h>//提供exit函数
#include <netinet/in.h>//提供ntohl函数
#include <stdio.h>//提供printf和sprintf
#include <arpa/inet.h>//提供inet_aton函数
int main(int ac,char ** av){
	struct in_addr inaddr;//in_addr 类型的参数
	if(ac!=2){//检查参数
		fprintf(stderr,"usage%s,<dotted-decimal>",av[0]);
		exit(0);
	}	
	if(inet_aton(av[1],&inaddr)==0){
		printf("inet_aton error");//转换错误处理
		}

	printf("0x%x\n",ntohl(inaddr.s_addr));//大端小端转换和最后输出
	exit(0);
}

