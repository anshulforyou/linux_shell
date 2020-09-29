#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include <sys/types.h> 
#include <sys/stat.h>

void main(int a, char** inp){
	char * token;
	token = strtok(inp[0], " ");
	token = strtok(NULL, " ");

	if(strcmp(token, "-i")==0){
		token = strtok(NULL, " ");
		char res[10];
		printf("%s %s", "Do you want to remove the file? ", token);
		fgets(res, 10, stdin);
		if((strcmp(res, "y")==0) || (strcmp(res, "Y")==0) || (strcmp(res, "yes")==0)){
			if (unlink(token) == 0) 
		      printf("%s\n", "Deleted successfully"); 
		   else
		      printf("%s\n", "Unable to delete the file");	
		}else{
			printf("%s\n", "File deletion process aborted");
		}
	}else if((strcmp(token, "-v"))==0 || (strcmp(token, "--verbose")==0)){
		if (unlink(token) == 0)
		      printf("%s\n", "Deleted successfully"); 
		   else
		      printf("%s\n", "Unable to delete the file");
	}

	else{
		if (unlink(token) == 0) 
	      printf("%s\n", "Deleted successfully"); 
	   else
	      printf("%s\n", "Unable to delete the file"); 
	}
}