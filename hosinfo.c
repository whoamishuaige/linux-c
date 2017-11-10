#include<stdio.h>//提供printf和sprintf函数
#include<netinet/in.h>//提供in_addr数据类型和
#include<arpa/inet.h>//inet*函数
#include<netdb.h>//提供hostent类型和gethostby*函数
#include<stdlib.h>//提供exit函数
int main(int argc,char **argv){
char **pp;//之所以是这个类型，原因是1：必须是字符串，2：必须是指针，所以** 3:还有h_aliases和h_addr_list数据类型都是char** 类型不用的话无法接受/
struct in_addr addr;//数据类型来自netinet/in.h
struct hostent *hostp;//数据类型来自netdb.h

if(argc !=2){
	fprintf(stderr,"usage%s<domain name or dotted-decimal>\n",argv[0]);
	exit(0);	
}//日常参数个数判断

if(inet_aton(argv[1],&addr)!=0)//假如传入的是点分十进制，就返回一个ip地址，然后掉用ip地址进行分析
	hostp = gethostbyaddr((const char *)&addr,sizeof(addr),AF_INET);
else
	hostp = gethostbyname(argv[1]);//如果不是点分十进制，那就是域名，就进行域名分析

printf("official hostname %s\n",hostp->h_name);//读取域名

for(pp = hostp->h_aliases;*pp != NULL;pp++){
	printf("alias %s\n",*pp);//读取别名
	}

for(pp =hostp->h_addr_list;*pp !=NULL;pp++){
	addr.s_addr = ((struct in_addr *)*pp)->s_addr;//因为h_addr_list是一个in_addr类型的数组，所以这样读取
	printf("address:%s\n",inet_ntoa(addr));
	}
	exit(0);
}
