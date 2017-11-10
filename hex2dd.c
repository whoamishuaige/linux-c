/*
 * 十六进制转换成点分二进制
 * 1:htonl(long int) 16进制转换为ip地址，大端和小端的转换。网络(大端) 机器(小端) 机器如果为小端则不用转换
 * 2:ip地址转换为点分十进制 inet_ntoa(struct in_addr)；//输入in_addr类型参数，转换成点分十进制
 * */
#include <stdlib.h>//提供exit函数
#include <netinet/in.h>//提供ntohl函数
#include <stdio.h>//提供printf和sprintf
#include <arpa/inet.h>//提供inet_aton函数
int main(int ac,char ** av){
	struct in_addr inaddr;//in_addr 类型的参数
	unsigned int addr;
	if(ac!=2){//检查参数
		fprintf(stderr,"usage%s,<dotted-decimal>",av[0]);
		exit(0);
	}
	printf("%s\n",av[1]);
	//inaddr.s_addr = htonl(av[1]);//我原本想直接进行这样的操作，可是系统告诉我不行，必须进行下面的操作才可以
	
	sscanf(av[1],"%x",&addr);//以十进制的方式读取进来,存在一定的疑惑，1:包括&符号什么时候加2:addr为什么不能被输出，3:inaddr类型
	printf("%s\n",addr);
	inaddr.s_addr = htonl(addr);//输入一个16进制的数字，输出一个16进制的数字，之间的差别在于多一层数据结构包装，以及大端和小端的切换
	printf("%s\n",inet_ntoa(inaddr));//
	exit(0);
}

//存在疑惑包括1:输入输出方式2：指针，3：结构体

