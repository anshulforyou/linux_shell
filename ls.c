#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<time.h>
// #include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <errno.h>

void main(int a, char** asd){
	char * token;
	token = strtok(asd[0], " ");
	token = strtok(NULL, " ");

	if((token == NULL) || (strcmp(token, "-a")==0)){
		struct dirent *de;
	  	// int ans, char* asd;
		// printf("%s\n", "flag value is 0 or 1");

	    DIR *dr = opendir("."); 
	    // printf("Hello");
	    if (dr == NULL)
	    {
	        printf("Could not open current directory" );
	    }
	    while ((de = readdir(dr)) != NULL){
	            printf("%s\n", de->d_name);
		}
		closedir(dr);
	
	}else if(strcmp(token, "-l")==0){
		struct dirent *de;
	  	// int ans, char* asd;
		// printf("%s\n", "flag value is 0 or 1");

	    DIR *dr = opendir(".");

	    if (dr == NULL)
	    {
	        printf("Could not open current directory" );
	    }
	    while ((de = readdir(dr)) != NULL){
            printf("%s\n",de->d_name);
	        printf("Information:\t");
	        struct stat sbuf;
	        stat(de->d_name,&sbuf);
	        if(sbuf.st_size==0)   //Check for empty file
	             printf("d");
	        if(sbuf.st_mode & S_IREAD)
	            printf("r");
	        if(sbuf.st_mode & S_IWRITE)
	            printf("w");
	        if(sbuf.st_mode & S_IEXEC)
	            printf("x");
	              //Print the size
	        printf("\t\t%ld",sbuf.st_size);
	        printf("\t%s",ctime(&sbuf.st_ctime));
		}
		closedir(dr);

	}
	else if(strcmp(token, "-A")==0){
		// struct dirent *de;
	 //  	// int ans, char* asd;
		// printf("%s\n","flag value is 2");

	 //    DIR *dr = opendir("."); 

	 //    if (dr == NULL)
	 //    {
	 //        printf("Could not open current directory" );
	 //    }
	 //    while ((de = readdir(dr)) != NULL){
	 //    		if(strcmp(de->d_name, ".")!=0 || strcmp(de->d_name, "..")!=0){
	 //            printf("%s\n", de->d_name);
		//     }
		// }
		// closedir(dr);
		system("dir");
	}
}