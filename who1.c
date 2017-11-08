#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#define SHOWHOST
int main(){
	struct utmp current_record;
	int fd,reclen = sizeof(current_record);
	if((fd = open(UTMP_FILE,O_RDONLY))== -1){
		perror(UTMP_FILE);
		exit(1);
	}
	while(read(fd,&current_record,reclen) == reclen)
	show_info(&current_record);
	close(fd);
	return 0;

}
show_info(struct utmp * utbufp){
	if(utbufp->ut_type != USER_PROCESS)
		return;
	printf("% -8.8s %-8.8s ",utbufp->ut_name,utbufp->ut_line);
	showtime(utbufp->ut_time);
	#ifdef SHOWHOST
	printf("(%s)",utbufp->ut_host);
	#endif
	printf("\n");
}
showtime(long timeval){
	char *  cp;
	cp = ctime(&timeval);
	printf("%12.12s",cp);
}
