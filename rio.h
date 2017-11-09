/*
 *rio.h 用于健壮的io。robust io.用于处理read，write种各种原因产生的不足值 short num
 * 提供两类函数，一类是无缓冲io输入输出函数，直接在存储器和文件之间传送数据,没有应用级别缓冲
 * 一类是带缓冲的函数，是线程安全的
 * 开始rio.h
 * */
#ifndef __RIO_H__
#define __RIO_H_
/*ssize_t 类型为有符号的int，原因是他可能返回-1，size_t是无符号的int，原因是他们传入的时候肯定为正数，所以size_t的范围多ssize_t一倍左右*/
ssize_t rio_readn(int fd,void *usrbuf,size_t n);//不带缓冲的读函数
ssize_t rio_writen(int fd,void *usrbuf,size_t n);//不带缓冲的写函数


/*开始rio_readn 函数，fd文件描述符，n读取的字符数量，从文件描述种最多传送n个字符到存储器：*/
ssize_t rio_readn(int fd,void *usrbuf,size_t n){
	size_t  nleft = n;
	ssize_t nread;
	char *bufp = usrbuf;
	while(nleft >0){
		if((nread = read(fd,bufp,nleft)) < 0){
			if(errno = EINTR){ //errno是全局变量，用于处理错误问题，linux错误问题的两种处理方式，errno和错误返回值
				nread = 0;//被中断以后的处理
			}
			else 	
				return -1; //read的最初设定值
		}	
		else if (nread == 0 ){
			break;//eof 	
		}
		nleft -= nread;
		bufp  += nread;
	}
	return (n-nleft);	//返回不足值或者期望值
}/*结束rio_readn*/
ssize_t rio_writen(int fd,void *usrbuf,size_t n){
	size_t nleft = n;
	ssize_t nwrite;
	char *bufp = usrbuf;
	while(nleft >0){
		if(nwrite = write(fd,bufp,nleft))<=0){
			if(errno =  EINTR){
				nwrite = 0;//重新启动write流程
			}
			else 
				return -1;写失败
	}
			nleft -= nwrite;
			bufp  += nwrite;
		
	}
	return n;//返回写入的内容，因为不存在eof的情况，所以必须返回设定值
}
#endif /*结束rio.h*/
