#include "apue.h"
#include <dirent.h>

int main (int argc, char *argv[]){
	DIR *dp;
	struct dirent *dirp;
 	if(argc != 2){
		err_quit("need two argument");
	}
	if((dp = opendir(argv[1]))==NULL){
		err_sys("can't open %s, agrv[1]");
	}
	while((dirp = readdir(dp)) !=NULL){
		printf("%s\n",dirp->d_reclen);
	}
	closedir(dp);
	exit(0);
}
