// #include <conio.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h>
#include<string.h>

void main(int a, char** cmd){
	char *token;
	token = strtok(cmd[0], " ");
	token = strtok(NULL, " ");
	if ((strcmp(token, "-v") == 0)){
		printf("Flag v is executing");
		token = strtok(NULL, " ");

		int check; 
	    char dirname[100];
		strcpy(dirname, token); 
	  
	    check = mkdir(dirname,0777); 
	  
	    // check if directory is created or not 
	    if (!check) 
	        printf("Directory created\n"); 
	    else { 
	        printf("Unable to create directory\n"); 
	        // exit(1); 
	    } 
	  	
	    system("dir");

	}else if(strcmp(token, "-p")==0){
		printf("Flag p is executing");

		token = strtok(NULL, " ");

		char *partname;
		partname = strtok(token, "/");

		while (partname != NULL){

			int check; 
		    char dirname[100];
			strcpy(dirname, partname); 
		  
		    check = mkdir(dirname,0777); 
		  
		    // check if directory is created or not 
		    if (!check) 
		        printf("Directory created\n"); 
		    else { 
		        printf("Unable to create directory\n"); 
		        // exit(1); 
		    }
		  	
		    system("dir");
		    partname = strtok(token, "/");
		}
	}
	else{
		printf("No flag applied");
		int check; 
	    char dirname[100];
		strcpy(dirname, token);

	    // clrscr(); 
	  
	    check = mkdir(dirname,0777); 
	  
	    // check if directory is created or not 
	    if (!check) 
	        printf("Directory created\n"); 
	    else { 
	        printf("Unable to create directory\n"); 
	        // exit(1); 
	    }
	  	
	    // getch(); 
	  	
	    system("dir"); 
	    // getch();
	}
}